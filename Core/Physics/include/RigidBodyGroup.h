#ifndef RIGIDBODYGROUP_H
#define RIGIDBODYGROUP_H
#pragma once

#include "RigidBody.h"
#include "RigidBodyGroupMember.h"

class RigidBodyGroup : public RigidBody {
public:
	//After calculating the physical state of the group each update:
	// - A deep update will give each member of the group its complete state.
	// - A shallow update will only give each member of the group a position_world and orientation_world
	//   but will supply the remaining state when the member disconnects from the group.
	enum class MemberUpdateDepth { deep, shallow };

protected:
	std::vector<RBGroupMember> mMembers;

private:
	MemberUpdateDepth mMemberUpdateDepth;

public:
	RigidBodyGroup(Integrator integrator = Integrator::rungeKutta4, MemberUpdateDepth depth = MemberUpdateDepth::shallow);
	~RigidBodyGroup() = default;

	void addBody(RigidBody& member, CoordTransform3D memberToGroup = CoordTransform3D());
	
	void setPosition_world(glm::dvec3 newPosition_world);
	void setMomentum_world(glm::dvec3 newMomentum_world);
	void setAngularMomentum_world(glm::dvec3 newAngularMomentum_world);
	void setOrientation_world(glm::dquat newOrientation_world);
	void setVelocity_world(glm::dvec3 newVelocity_world);
	void setAngularVelocity_world(glm::dvec3 newAngularVelocity_world);
	void setObjectToParentTransform(CoordTransform3D objectToParent);

protected:
	void update(double t, double dt);
	void updateCombinedMass_local();
	void updateCombinedInertia_local();

private:
	void addForces(const State& state, double t);
	void addTorques(const State& state, double t);
	void updateAllMemberStates();
	void updateMemberState(RBGroupMember& toUpdate);
	bool isFullyFragmented();

};

#endif
