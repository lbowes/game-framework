#ifndef RIGIDBODYSTATESNAPSHOT_H
#define RIGIDBODYSTATESNAPSHOT_H
#pragma once

#include "RigidBody.h"

class RigidBodyStateSnapshot {
private:
	glm::dvec3
		CoMPosition_world = glm::dvec3(0.0),
		velocity = glm::dvec3(0.0),
		acceleration = glm::dvec3(0.0),
		momentum = glm::dvec3(0.0),
		angularVelocity = glm::dvec3(0.0),
		angularMomentum = glm::dvec3(0.0);

	glm::dquat orientation = glm::dquat();
		
	Mass mass_local;
		
	InertiaTensor inertiaTensor_local;
		
	CoordTransform3D localToWorld;

public:
	RigidBodyStateSnapshot() = default;
	~RigidBodyStateSnapshot() = default;

	//Note: The two functions below do not contain the same parameters, because rigid body acceleration is implicit: it can be saved, but not loaded.
	//Therefore loadRigidBodyState() only requires a State instance, not a RigidBody.
	static void load(const RigidBodyStateSnapshot& source, State& dest);
	static void save(const RigidBody& source, RigidBodyStateSnapshot& dest);
	 
	static void lerp(const RigidBodyStateSnapshot& a, const RigidBodyStateSnapshot& b, double x, RigidBodyStateSnapshot& dest);

};

#endif
