#include "RigidBody.h"

namespace Framework {
	namespace Physics {

		RigidBody::RigidBody(IntegrationMethod integrationMethod) : 
			mIntegrationMethod(integrationMethod)
		{ }

		void RigidBody::integrate(double t, double dt) {
			Derivative changeWithTime;

			switch (mIntegrationMethod) {
				case IntegrationMethod::EULER:
					euler(changeWithTime, t, dt);
					break;

				case IntegrationMethod::RUNGE_KUTTA_4:
					RK4(changeWithTime, t, dt);
					break;

				default:
					break;
			}

			mState.mMomentum_world += changeWithTime.dm * dt;
			mState.mAngularMomentum_world += changeWithTime.dam * dt;
			mState.mPosition_world += changeWithTime.dx * dt;
			mState.mOrientation_world += changeWithTime.dor * dt;
			
			mAcceleration = changeWithTime.dm / mState.mMass.getValue();

			mState.recalc();
		}

		glm::dvec3 RigidBody::velocityAtWorldPoint_world(glm::dvec3 worldSpacePoint) {
			return mState.mVelocity_world + cross(mState.mAngularVelocity_world, worldSpacePoint - mState.mObjectSpace.toParentSpace_total(mState.mMass.getCentre()));
		}

		glm::dvec3 RigidBody::velocityAtLocalPoint_world(glm::dvec3 localSpacePoint_local) {
			//First convert the point into world space
			glm::dvec3 worldSpace = glm::dvec3(mState.mObjectSpace.toParentSpace_total(localSpacePoint_local));
			return velocityAtWorldPoint_world(worldSpace);
		}
		
		//void RigidBody::addForceAtPoint_local(glm::dvec3 force_local, glm::dvec3 applicationPoint_local = CoM) {
		//	using namespace glm;
		//	
		//	if (applicationPoint_local == CoM)
		//		return;
		//
		//	//Calculate the torque resulting from adding this force at a local position
		//	mTorques_world.push_back(
		//		cross(
		//			mState.mObjectSpace.toParentSpace_direction(applicationPoint_local - mState.getMass().getCentre()), 
		//			mState.mObjectSpace.toParentSpace_direction(force_local)
		//		)
		//	);
		//}
		//
		//void RigidBody::addForceThroughCM_world(glm::dvec3 force_world) {
		//	mForces_world.push_back(force_world);
		//}

		void RigidBody::addLocalForceAtLocalPoint(glm::dvec3 force_local, glm::dvec3 applicationPoint_local) {
			glm::dvec3 force_world = mState.getObjectSpace().toParentSpace_direction(force_local);

			mForces_world.push_back({ force_world, applicationPoint_local });

			//Calculate the torque resulting from adding this force at a local position
			mTorques_world.push_back(
				cross(
					mState.mObjectSpace.toParentSpace_direction(applicationPoint_local - mState.getMass().getCentre()), 
					force_world
				)
			);
		}

		void RigidBody::addWorldForceAtLocalPoint(glm::dvec3 force_world, glm::dvec3 applicationPoint_local) {
			mForces_world.push_back({ force_world, applicationPoint_local });

			//Calculate the torque resulting from adding this force at a local position
			mTorques_world.push_back(
				cross(
					mState.mObjectSpace.toParentSpace_direction(applicationPoint_local - mState.getMass().getCentre()),
					force_world
				)
			);
		}

		void RigidBody::addLocalForceThroughCM(glm::dvec3 force_local) {
			mForces_world.push_back(mState.getObjectSpace().toParentSpace_direction(force_local));
		}

		void RigidBody::addWorldForceThroughCM(glm::dvec3 force_world) {
			mForces_world.push_back(force_world);
		}

		void RigidBody::addTorque_world(glm::dvec3 torque_world) {
			mTorques_world.push_back(torque_world);
		}
		
		void RigidBody::addTorque_local(glm::dvec3 torque_local) {
			mTorques_world.push_back(mState.mObjectSpace.toParentSpace_direction(torque_local));
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

		//Takes a state and calculates the new derivatives of this state at t + dt
		Derivative RigidBody::evaluate(State& initial, double t, double dt, const Derivative& d) {
			State next;
			next.mPosition_world = initial.mPosition_world + d.dx * dt;
			next.mMomentum_world = initial.mMomentum_world + d.dm * dt;
			next.mOrientation_world = initial.mOrientation_world + d.dor * dt;
			next.mAngularMomentum_world = initial.mAngularMomentum_world + d.dam * dt;
			next.mMass = initial.mMass;
			next.mInertiaTensor_local = initial.mInertiaTensor_local;

			next.recalc();

			Derivative output;
			output.dx = next.mVelocity_world;
			output.dor = next.mSpin_world;

			//mTotalForce_world = glm::dvec3(0.0);
			//mTotalTorque_world = glm::dvec3(0.0);
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

			//output.dm = getForce_world(next, t + dt);
			//output.dam = getTorque_world(next, t + dt);

			mAcceleration = output.dm / mState.mMass.getValue();

			return output;
		}

	}
}