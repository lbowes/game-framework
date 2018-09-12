#include "RigidBody.h"

RigidBody::RigidBody(Integrator integrator) :
	mIntegrator(integrator)
{ }

glm::dvec3 RigidBody::getAccel_world() const {
	if (mLastStateTimeDelta == 0.0)
		return glm::dvec3(0.0);
	else
		return (mState.getVelocity_world() - mLastState.getVelocity_world()) / mLastStateTimeDelta;
}

glm::dvec3 RigidBody::getAccelAtLocalPoint_world(glm::dvec3 position_local) const {
	if (mLastStateTimeDelta == 0.0)
		return glm::dvec3(0.0);
	else
		return (mState.velocityAtLocalPoint_world(position_local) - mLastState.velocityAtLocalPoint_world(position_local)) / mLastStateTimeDelta;
}

void RigidBody::integrate(double t, double dt) {
	Derivative changeWithTime;

	switch (mIntegrator) {
		case Integrator::euler:
			euler(changeWithTime, t, dt);
			break;

		case Integrator::rungeKutta4:
			RK4(changeWithTime, t, dt);
			break;

		default:
			break;
	}

	mLastState = mState;
	mLastStateTimeDelta = dt;

	mState.mMomentum_world += changeWithTime.dm * dt;
	mState.mAngularMomentum_world += changeWithTime.dam * dt;
	mState.mCMPosition_world += changeWithTime.dx * dt;
	mState.mOrientation_world += changeWithTime.dor * dt;

	mState.recalcSecondaryProps();
}

void RigidBody::addForce(const Force_world& force) {
	addWorldForceAtLocalPoint(force.mForce_world, force.mApplicationPoint_local);
}

void RigidBody::addLocalForceAtLocalPoint(glm::dvec3 force_local, glm::dvec3 applicationPoint_local) {
	glm::dvec3 force_world = mState.mObjectSpace.toParentSpace_rotation(force_local);

	mForces_world.push_back({ force_world, applicationPoint_local });

	//Calculate the torque resulting from adding this force at a local position
	mTorques_world.push_back(
		cross(
			mState.mObjectSpace.toParentSpace_rotation(applicationPoint_local - mState.mMass_local.getCentre()),
			force_world
		)
	);
}

void RigidBody::addWorldForceAtLocalPoint(glm::dvec3 force_world, glm::dvec3 applicationPoint_local) {
	mForces_world.push_back({ force_world, applicationPoint_local });

	//Calculate the torque resulting from adding this force at a local position
	mTorques_world.push_back(
		cross(
			mState.mObjectSpace.toParentSpace_rotation(applicationPoint_local - mState.mMass_local.getCentre()),
			force_world
		)
	);
}

void RigidBody::addLocalForceThroughCM(glm::dvec3 force_local) {
	mForces_world.push_back({ mState.mObjectSpace.toParentSpace_rotation(force_local), mState.mMass_local.getCentre() });
}

void RigidBody::addWorldForceThroughCM(glm::dvec3 force_world) {
	mForces_world.push_back({force_world, mState.mMass_local.getCentre()});
}

void RigidBody::addTorque_local(glm::dvec3 torque_local) {
	mTorques_world.push_back(mState.mObjectSpace.toParentSpace_rotation(torque_local));
}

void RigidBody::addTorque_world(glm::dvec3 torque_world) {
	mTorques_world.push_back(torque_world);
}

void RigidBody::RK4(Derivative& changeWithTime, double t, double dt) {
	Derivative
		a = evaluate(mState, t, 0.0, Derivative()),
		b = evaluate(mState, t, dt * 0.5, a),
		c = evaluate(mState, t, dt * 0.5, b),
		d = evaluate(mState, t, dt, c);

	changeWithTime.dx =  1.0 / 6.0 * (a.dx +  2.0 * (b.dx + c.dx)  +  d.dx);
	changeWithTime.dm =  1.0 / 6.0 * (a.dm +  2.0 * (b.dm + c.dm)  +  d.dm);
	changeWithTime.dor = 1.0 / 6.0 * (a.dor + 2.0 * (b.dor + c.dor) + d.dor);
	changeWithTime.dam = 1.0 / 6.0 * (a.dam + 2.0 * (b.dam + c.dam) + d.dam);
}

void RigidBody::euler(Derivative& changeWithTime, double t, double dt) {
	Derivative
		d1 = evaluate(mState, t, 0.0, Derivative()), //current derivative
		d2 = evaluate(mState, t, dt, d1);
	
	changeWithTime.dx = d2.dx;
	changeWithTime.dm = d2.dm;
	changeWithTime.dor = d2.dor;
	changeWithTime.dam = d2.dam;
}

Derivative RigidBody::evaluate(State& initial, double t, double dt, const Derivative& d) 
	//Takes a state and calculates the new derivatives of this state at t + dt
{
	State next;
	next.mCMPosition_world = initial.mCMPosition_world + d.dx * dt;
	next.mMomentum_world = initial.mMomentum_world + d.dm * dt;
	next.mOrientation_world = initial.mOrientation_world + d.dor * dt;
	next.mAngularMomentum_world = initial.mAngularMomentum_world + d.dam * dt;
	next.mMass_local = initial.mMass_local;
	next.mInertiaTensor_local = initial.mInertiaTensor_local;

	next.recalcSecondaryProps();

	Derivative output;
	output.dx = next.mVelocity_world;
	output.dor = next.mSpin_world;

	mForces_world.clear();
	mTotalForce_world = glm::dvec3();
	mTorques_world.clear();
	mTotalTorque_world = glm::dvec3();

	addForces(next, t + dt);
	addTorques(next, t + dt);

	for (const Force_world& force : mForces_world)
		mTotalForce_world += force.mForce_world;

	for (const glm::dvec3& torque : mTorques_world)
		mTotalTorque_world += torque;

	output.dm = mTotalForce_world;
	output.dam = mTotalTorque_world;

	return output;
}