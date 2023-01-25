#include "SteelComposite.h"

SteelComposite::SteelComposite(const GF::CoordTransform3D& toWorld) :
	RigidBodyGroup(Integrator::rungeKutta4, SubUpdateDepth::deep),
	mSteelCube1({ 0.0, 0.0, 0.0 }, 400.0),
	mSteelCube2({ 0.0, 0.0, 0.0 }, 400.0)
{
	mOrigin = mState.getObjectSpace().toParentSpace();
	mCentreMass = mState.getObjectSpace().toParentSpace(mState.getMass_local().getCentre());

	assemble();
}

void SteelComposite::update(double t, double dt) {
	mSteelCube1.update(t, dt);
	mSteelCube2.update(t, dt);
	
	RigidBodyGroup::update(t, dt);
	mOrigin = mState.getObjectSpace().toParentSpace();
	mCentreMass = mState.getObjectSpace().toParentSpace(mState.getMass_local().getCentre());

	//basicCollision();
}

void SteelComposite::checkInput() {
	mSteelCube1.checkInput();
	mSteelCube2.checkInput();
	
	if (GF::Input::isKeyPressed(GLFW_KEY_ENTER)) {
		mSubBodies[0].disconnect();
		mSubBodies[1].disconnect();
	}

	if (GF::Input::isKeyPressed(GLFW_KEY_G)) {
		mState.reset();

		mSteelCube1.mutableState().reset();
		mSteelCube2.mutableState().reset();

		mSubBodies[0].disconnect();
		mSubBodies[1].disconnect();

		addBody(mSteelCube1);
		addBody(mSteelCube2, glm::dvec3(0.0, 5.0, 0.0));
	}

	if (GF::Input::isKeyPressed(GLFW_KEY_UP))
		mSteelCube2.mutableState().setMassCentre_local({0.0, 2.0, 0.0});
}

void SteelComposite::basicCollision() {
	glm::dvec3 currentPosition = mState.getObjectSpace().toParentSpace();

	const double groundHeight = 0.0;

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

void SteelComposite::assemble() {
	addBody(mSteelCube1, GF::CoordTransform3D({ 0.0, 0.0, 0.0 }));	
	addBody(mSteelCube2, GF::CoordTransform3D({ 0.0, 4.0, 0.0 }));
}