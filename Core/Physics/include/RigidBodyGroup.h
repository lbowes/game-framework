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
