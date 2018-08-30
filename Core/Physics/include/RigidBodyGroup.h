#ifndef RIGIDBODYGROUP_H
#define RIGIDBODYGROUP_H
#pragma once

#include "RigidBody.h"

class SubBody {
	friend class RigidBodyGroup;

private:
	bool mConnected = true;
	RigidBody* mRigidBody = nullptr;
	GF::CoordTransform3D mSubToComposite;

public:
	SubBody(RigidBody& sub, GF::CoordTransform3D subToComposite = GF::CoordTransform3D()) :
		mRigidBody(&sub),
		mSubToComposite(subToComposite)
	{ }

	void operator=(const SubBody& other) {
		mConnected = other.mConnected;
		mRigidBody = other.mRigidBody;
		mSubToComposite = other.mSubToComposite;
	}

	~SubBody() = default;

	RigidBody* getRigidBody() const { return mRigidBody; }
	bool isConnected() const { return mConnected; }

	void disconnect() { 
		mConnected = false; 
		mRigidBody = nullptr;
	}

};

class RigidBodyGroup : public RigidBody {
public:
	//After calculating the physical state of the group each update:
	// - A deep update will give each member of the group its complete state.
	// - A shallow update will only give each member of the group a position_world and orientation_world
	//   but will supply the remaining state when the sub disconnects from the group.
	enum class SubUpdateDepth { deep, shallow };

protected:
	std::vector<SubBody> mSubBodies;

private:
	SubUpdateDepth mSubUpdateDepth;

public:
	RigidBodyGroup(Integrator integrator = Integrator::rungeKutta4, SubUpdateDepth subUpdateDepth = SubUpdateDepth::shallow);
	~RigidBodyGroup() = default;

	void addBody(RigidBody& sub, GF::CoordTransform3D subToComposite = GF::CoordTransform3D());

protected:
	void update(double t, double dt);
	void updateCombinedMass_local();
	void updateCombinedInertia_local();

private:
	void addForces(const State& state, double t);
	void addTorques(const State& state, double t);
	void updateAllSubStates();
	void updateSubState(SubBody& toUpdate);
	bool isFullyFragmentated();

};

#endif
