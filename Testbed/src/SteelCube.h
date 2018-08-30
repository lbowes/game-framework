#ifndef STEELCUBE_H
#define STEELCUBE_H
#pragma once

#include <GraphicsFramework/Input.h>
#include <PhysicsFramework/RigidBody.h>

class SteelCube : public RigidBody {
	friend class SteelCubeModel;
public:
	SteelCube(glm::dvec3 position_world, double mass);
	~SteelCube() = default;

	void update(double t, double dt);
	void checkInput();
	void basicCollision();

private:
	void addForces(const State& state, double t);
	void addTorques(const State& state, double t);


};

#endif
