#ifndef STATE_H
#define STATE_H
#pragma once

#include "InertiaTensor.h"
#include "Mass.h"
#include "CoordTransform3D.h"

#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtx/transform.hpp>

class State {
	friend class RigidBody;
private:
	//Primary state	
	glm::dvec3
		mCoMPosition_world,
		mMomentum_world,
		mAngularMomentum_world;
			
	glm::dquat mOrientation_world;

	//Secondary state
	glm::dvec3
		mVelocity_world,
		mAngularVelocity_world;
			
	glm::dquat mSpin_world;
			
	CoordTransform3D mObjectSpace;

	//Tertiary state
	InertiaTensor mInertiaTensor_local;
	Mass mMass_local;

public:
	State() = default;
	void operator=(const State& other);
	~State() = default;				 

	void reset();

	glm::dvec3 getCoMPosition_world() const { return mCoMPosition_world; }
	glm::dquat getOrientation_world() const { return mOrientation_world; }
	glm::dvec3 getVelocity_world() const { return mVelocity_world; }
	glm::dvec3 getAngularVelocity_world() const { return mAngularVelocity_world; }
	glm::dvec3 getMomentum_world() const { return mMomentum_world; }
	glm::dvec3 getAngularMomentum_world() const { return mAngularMomentum_world; }
	InertiaTensor getInertiaTensor_local() const { return mInertiaTensor_local; }
	Mass getMass_local() const { return mMass_local; }
	const CoordTransform3D& getObjectSpace() const { return mObjectSpace; }
			
	glm::dvec3 velocityAtWorldPoint_world(glm::dvec3 position_world) const;
	glm::dvec3 velocityAtLocalPoint_world(glm::dvec3 position_local) const;
			
	void setPosition_world(glm::dvec3 newPosition_world);
	void setCoMPosition_world(glm::dvec3 newCoMPosition_world);
	void setMomentum_world(glm::dvec3 newMomentum_world);
	void setAngularMomentum_world(glm::dvec3 newAngularMomentum_world);
	void setOrientation_world(glm::dquat newOrientation_world);
	void setVelocity_world(glm::dvec3 newVelocity_world);
	void setAngularVelocity_world(glm::dvec3 newAngularVelocity_world);
	void setInertiaTensor_local(InertiaTensor newInertiaTensor_local);
	void setMass_local(Mass newMass_local);
	void setMassValue_local(double newMassValue_local);
	void setMassCentre_local(glm::dvec3 newMassCentre_local);
	void setObjectToParentTransform(CoordTransform3D objectToParent);

private:
	void recalcSecondaryProps();
	void updateCoordSpace3D();

};

#endif
