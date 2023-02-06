#ifndef STEELCOMPOSITE_H
#define STEELCOMPOSITE_H
#pragma once

#include "SteelCube.h"

#include <PhysicsFramework/RigidBodyGroup.h>
#include <GraphicsFramework/Input.h>

class SteelComposite : public RigidBodyGroup {
private:
	glm::vec3
		mCentreMass,
		mOrigin;

	SteelCube
		mSteelCube1,
		mSteelCube2;

public:
	SteelComposite(const GF::CoordTransform3D& toWorld);
	~SteelComposite() = default;

	void update(double t, double dt);
	void checkInput();

	glm::vec3& getCentreMass() { return mCentreMass; }
	glm::vec3& getOrigin() { return mOrigin; }
	SteelCube& getSteelCube1() { return mSteelCube1; }
	SteelCube& getSteelCube2() { return mSteelCube2; }

private:
	void assemble();
	void basicCollision();

};

#endif
