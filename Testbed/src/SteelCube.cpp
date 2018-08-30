#include "SteelCube.h"

SteelCube::SteelCube(glm::dvec3 position_world, double mass) :
	RigidBody(RigidBody::Integrator::rungeKutta4)
{
	//Mass of a 1m^3 block of steel
	mState.setMassValue_local(mass);
	mState.setMassCentre_local({ 0.0, 0.5, 0.0 });
	mState.setInertiaTensor_local(InertiaTensor::cube(mass, 1.0));
	
	mState.setPosition_world(position_world);
}

void SteelCube::update(double t, double dt) {
	mState.setMassCentre_local({ 0.0, 0.5, 0.0 });
	integrate(t, dt);
	//basicCollision();
}

void SteelCube::checkInput() {
	if (GF::Input::isKeyPressed(GLFW_KEY_U)) {
		mState.setMomentum_world(glm::dvec3(0.0));
		mState.setVelocity_world(glm::dvec3(0.0));
		glm::dvec3 currentPosition = mState.getObjectSpace().toParentSpace();
		mState.setPosition_world(glm::dvec3(currentPosition.x, 10.0, currentPosition.z));
	}
}

void SteelCube::addForces(const State& state, double t) {
	//Weight
	glm::dvec3 weight = glm::dvec3(0.0, -9.80665 * mState.getMass_local().getValue(), 0.0);
	//addWorldForceThroughCM(weight);
}

void SteelCube::addTorques(const State& state, double t) {
	//TODO
}

void SteelCube::basicCollision() {
	glm::dvec3 currentPosition = mState.getObjectSpace().toParentSpace();

	double groundHeight = 0.0;

	if (currentPosition.y < groundHeight) {
		currentPosition.y += groundHeight - currentPosition.y;

		mState.setPosition_world(currentPosition);

		glm::dvec3 temp = mState.getVelocity_world();
		temp.y = 0.0;
		mState.setVelocity_world(temp);

		temp = mState.getMomentum_world();
		temp.y = 0.0;
		mState.setMomentum_world(temp);
	}
}