#include "State.h"

#include <iostream>

void State::operator=(const State& other) {
	this->mCoMPosition_world = other.mCoMPosition_world;
	this->mMomentum_world = other.mMomentum_world;
	this->mAngularMomentum_world = other.mAngularMomentum_world;
	this->mOrientation_world = other.mOrientation_world;
	this->mVelocity_world = other.mVelocity_world;
	this->mAngularVelocity_world = other.mAngularVelocity_world;
	this->mSpin_world = other.mSpin_world;
	this->mObjectSpace = other.mObjectSpace;
	this->mInertiaTensor_local = other.mInertiaTensor_local;
	this->mMass_local = other.mMass_local;
}

void State::reset() {
	mCoMPosition_world = glm::dvec3(0.0);
	mMomentum_world = glm::dvec3(0.0);
	mAngularMomentum_world = glm::dvec3(0.0);
	mOrientation_world = glm::dquat(glm::vec3(0.0));
	mVelocity_world = glm::dvec3(0.0);
	mAngularVelocity_world = glm::dvec3(0.0);
	mSpin_world = glm::dquat(glm::vec3(0.0));

	recalcSecondaryProps();
}

glm::dvec3 State::velocityAtWorldPoint_world(glm::dvec3 position_world) const {
	return mVelocity_world + cross(mAngularVelocity_world, position_world - mObjectSpace.toParentSpace(mMass_local.getCentre()));
}

glm::dvec3 State::velocityAtLocalPoint_world(glm::dvec3 position_local) const {
	//First convert the point into world space
	glm::dvec3 worldSpace = mObjectSpace.toParentSpace(position_local);
	return velocityAtWorldPoint_world(worldSpace);
}

void State::setPosition_world(glm::dvec3 newPosition_world) {
	mCoMPosition_world = newPosition_world + mObjectSpace.toParentSpace_rotation(mMass_local.getCentre());
	mObjectSpace.setLocalToParent_translation(newPosition_world);
}

void State::setCoMPosition_world(glm::dvec3 newCoMPosition_world) {
	mCoMPosition_world = newCoMPosition_world;
	mObjectSpace.setLocalToParent_translation(newCoMPosition_world - mObjectSpace.toParentSpace_rotation(mMass_local.getCentre()));
}

void State::setMomentum_world(glm::dvec3 newMomentum_world) {
	mMomentum_world = newMomentum_world;

	if(mMass_local.getValue() > 0.0)
		mVelocity_world = mMomentum_world / mMass_local.getValue();
}

void State::setAngularMomentum_world(glm::dvec3 newAngularMomentum_world) {
	mAngularMomentum_world = newAngularMomentum_world;

	if (mInertiaTensor_local != glm::dmat3(0.0))
		mAngularVelocity_world = mOrientation_world * (mInertiaTensor_local.inverse() * (inverse(mOrientation_world) * newAngularMomentum_world));
}

void State::setOrientation_world(glm::dquat newOrientation_world) {
	mOrientation_world = normalize(newOrientation_world);
	mObjectSpace.setLocalToParent_rotation(glm::toMat4(newOrientation_world));
	updateCoordSpace3D();

	if (mInertiaTensor_local != glm::dmat3(0.0))
		mAngularVelocity_world = mOrientation_world * (mInertiaTensor_local.inverse() * (inverse(mOrientation_world) * mAngularMomentum_world));

	glm::dquat q(0.0, mAngularVelocity_world);
	mSpin_world = 0.5 * q * mOrientation_world;
}

void State::setVelocity_world(glm::dvec3 newVelocity_world) {
	mVelocity_world = newVelocity_world;
	mMomentum_world = newVelocity_world * mMass_local.getValue();
}

void State::setAngularVelocity_world(glm::dvec3 newAngularVelocity_world) {
	mAngularVelocity_world = newAngularVelocity_world;

	InertiaTensor inertiaTensor_world = mInertiaTensor_local.afterRotation(mObjectSpace.getLocalToParent_rotation());
	mAngularMomentum_world = mAngularVelocity_world * inertiaTensor_world.getInternal();
}

void State::setInertiaTensor_local(InertiaTensor newInertiaTensor_local) {
	mInertiaTensor_local = newInertiaTensor_local;

	if (newInertiaTensor_local != glm::dmat3(0.0) && mOrientation_world != glm::dquat())
		mAngularVelocity_world = mOrientation_world * (mInertiaTensor_local.inverse() * (inverse(mOrientation_world) * mAngularMomentum_world));
}

void State::setMass_local(Mass newMass_local) {
	mMass_local = newMass_local.getValue();
	setMassCentre_local(newMass_local.getCentre());

	mMomentum_world = newMass_local.getValue() * mVelocity_world;
}

void State::setMassValue_local(double newMassValue_local) {
	mMass_local = newMassValue_local;
	mMomentum_world = newMassValue_local * mVelocity_world;
}

void State::setMassCentre_local(glm::dvec3 newMassCentre_local) {
	mMass_local.setCentre(newMassCentre_local);
	mCoMPosition_world = mObjectSpace.toParentSpace(newMassCentre_local);
}

void State::setObjectToParentTransform(CoordTransform3D objectToParent) {
	mObjectSpace = objectToParent;

	setPosition_world(objectToParent.toParentSpace());
	setOrientation_world(glm::toQuat(objectToParent.getLocalToParent_rotation()));
}

void State::recalcSecondaryProps() {
	//Linear velocity
	double mass = mMass_local.getValue();
	if (mass > 0.0)
		mVelocity_world = mMomentum_world / mass;

	//Angular velocity
	if (mInertiaTensor_local.getInternal() != glm::dmat3(0.0) && mOrientation_world != glm::dquat())
		mAngularVelocity_world = mOrientation_world * (mInertiaTensor_local.inverse() * (inverse(mOrientation_world) * mAngularMomentum_world));

	//Spin
	glm::dquat q(0.0, mAngularVelocity_world);
	mSpin_world = 0.5 * q * mOrientation_world;
	mOrientation_world = normalize(mOrientation_world);

	mObjectSpace.setLocalToParent_rotation(glm::toMat4(mOrientation_world));

	//Object space
	updateCoordSpace3D();
}

void State::updateCoordSpace3D() {
	mObjectSpace.setLocalToParent_translation(mCoMPosition_world - mObjectSpace.toParentSpace_rotation(mMass_local.getCentre()));
	mObjectSpace.setLocalToParent_rotation(glm::toMat4(mOrientation_world));
}