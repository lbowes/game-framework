#ifndef RIGIDBODYGROUPMEMBER_H
#define RIGIDBODYGROUPMEMBER_H
#pragma once

#include "RigidBody.h"

class RBGroupMember {
	friend class RigidBodyGroup;

private:
	bool mConnected = true;
	RigidBody* mRigidBody = nullptr;
	CoordTransform3D mMemberToGroup;

public:
	RBGroupMember(RigidBody& member, CoordTransform3D memberToGroup = CoordTransform3D());
	void operator=(const RBGroupMember& other);
	~RBGroupMember() = default;

	void disconnect();

	RigidBody* getRigidBody() const { return mRigidBody; }
	bool isConnected() const { return mConnected; }

}; 

#endif
