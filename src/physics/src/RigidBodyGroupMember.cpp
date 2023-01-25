#include "RigidBodyGroupMember.h"

RBGroupMember::RBGroupMember(RigidBody& member, CoordTransform3D memberToGroup) :
	mRigidBody(&member),
	mMemberToGroup(memberToGroup)
{ }

void RBGroupMember::operator=(const RBGroupMember& other) {
	mConnected = other.mConnected;
	mRigidBody = other.mRigidBody;
	mMemberToGroup = other.mMemberToGroup;
}

void RBGroupMember::disconnect() { 
	mConnected = false; 
	mRigidBody = nullptr;
}
