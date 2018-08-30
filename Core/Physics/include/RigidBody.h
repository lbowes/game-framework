#ifndef RIGIDBODY_H
#define RIGIDBODY_H
#pragma once

#include "State.h"

#include <vector>

struct Derivative {
	glm::dvec3
		dx,
		dm,
		dam;
		
	glm::dquat dor;
};

struct Force_world {
	glm::dvec3	
		mForce_world,
		mApplicationPoint_local;

	Force_world(glm::dvec3 force_world, glm::dvec3 applicationPoint_local) :
		mForce_world(force_world),
		mApplicationPoint_local(applicationPoint_local)
	{ }
};
		
class RigidBody {
	friend class RigidBodyGroup;
		
public:
	enum class Integrator { euler, rungeKutta4 };

protected:
	State mState;

	Integrator mIntegrator = Integrator::rungeKutta4;

	glm::dvec3
		mTotalForce_world,
		mTotalTorque_world;

	std::vector<Force_world> mForces_world;
	std::vector<glm::dvec3> mTorques_world;

private:
	double mLastStateTimeDelta = 0.0;
	State mLastState;

public:
	RigidBody(Integrator integrator = Integrator::rungeKutta4);
	virtual ~RigidBody() = default;

	void setIntegrator(Integrator m) { mIntegrator = m; }
	State& mutableState() { return mState; }
	const State& immutableState() const { return mState; }
	glm::dvec3 getAccel_world() const;
	glm::dvec3 getAccelAtLocalPoint_world(glm::dvec3 position_local) const;

protected:
	void integrate(double t, double dt);
			
	//Need to use mLastState and mLastStateTimeDelta to provide function to get acceleration.
	glm::dvec3 getTotalForce_world() const { return mTotalForce_world; }
	glm::dvec3 getTotalTorque_world() const { return mTotalTorque_world; }
	const std::vector<Force_world>& getForces_world() const { return mForces_world; }
	const std::vector<glm::dvec3>& getTorques_world() const { return mTorques_world; }

	virtual void addForces(const State& state, double t) = 0;
	virtual void addTorques(const State& state, double t) = 0;

	void addForce(const Force_world& force);
	void addLocalForceAtLocalPoint(glm::dvec3 force_local, glm::dvec3 applicationPoint_local);
	void addWorldForceAtLocalPoint(glm::dvec3 force_world, glm::dvec3 applicationPoint_local);
	void addLocalForceThroughCM(glm::dvec3 force_local);
	void addWorldForceThroughCM(glm::dvec3 force_world);
	void addTorque_local(glm::dvec3 torque_local);
	void addTorque_world(glm::dvec3 torque_world);

private:
	void RK4(Derivative& changeWithTime, double t, double dt);
	void euler(Derivative& changeWithTime, double t, double dt);

	Derivative evaluate(State& initial, double t, double dt, const Derivative &d);

};

#endif
