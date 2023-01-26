#include "RigidBodyStateSnapshot.h"

void RigidBodyStateSnapshot::load(const RigidBodyStateSnapshot& source, State& dest)
	//Initialises target State object ('dest') based on RigidBodyStateSnapshot object ('source')
{
	dest.setCoMPosition_world(source.CoMPosition_world);
	dest.setVelocity_world(source.velocity);
	dest.setMomentum_world(source.momentum);
	dest.setOrientation_world(source.orientation);
	dest.setAngularVelocity_world(source.angularVelocity);
	dest.setAngularMomentum_world(source.angularMomentum);
	dest.setMass_local(source.mass_local);
	dest.setInertiaTensor_local(source.inertiaTensor_local);
	dest.setObjectToParentTransform(source.localToWorld);
}

void RigidBodyStateSnapshot::save(const RigidBody& source, RigidBodyStateSnapshot& dest)
	//Saves a target RigidBody object ('source') into a RigidBodyStateSnapshot object ('dest')
{
	const State& s = source.getState();

	dest.CoMPosition_world = s.getCoMPosition_world();
	dest.velocity = s.getVelocity_world();
	dest.acceleration = source.getAccel_world();
	dest.momentum = s.getMomentum_world();
	dest.orientation = s.getOrientation_world();
	dest.angularVelocity = s.getAngularVelocity_world();
	dest.angularMomentum = s.getAngularMomentum_world();
	dest.mass_local = s.getMass_local();
	dest.inertiaTensor_local = s.getInertiaTensor_local();
	dest.localToWorld = s.getObjectSpace();
}

void RigidBodyStateSnapshot::lerp(const RigidBodyStateSnapshot& a, const RigidBodyStateSnapshot& b, double x, RigidBodyStateSnapshot& dest)
	//Linearly interpolates between two RigidBodyStateSnapshot objects ('a' and 'b') and stores the result in 'dest'
{
	dest.CoMPosition_world = glm::lerp(a.CoMPosition_world, b.CoMPosition_world, x);
	dest.velocity = glm::lerp(a.velocity, b.velocity, x);
	dest.acceleration = glm::lerp(a.acceleration, b.acceleration, x);
	dest.momentum = glm::lerp(a.momentum, b.momentum, x);
	dest.orientation = glm::slerp(a.orientation, b.orientation, x);
	dest.angularVelocity = glm::lerp(a.angularVelocity, b.angularVelocity, x);
	dest.angularMomentum = glm::lerp(a.angularMomentum, b.angularMomentum, x);
	dest.mass_local = ::lerp(a.mass_local, b.mass_local, x);
	dest.localToWorld = ::lerp(a.localToWorld, b.localToWorld, x);

	//The inertia tensor cannot be interpolated without first interpolating all components that influence it, so the most recent snapshot is used
	dest.inertiaTensor_local = a.inertiaTensor_local;
}
