#ifndef RIGIDBODY_H
#define RIGIDBODY_H
#pragma once

#include <vector>

#include "State.hpp"

#define CoM glm::dvec3(0.0)

namespace Framework {
	namespace Physics {
		struct Force_world {
			glm::dvec3	
				mForce_world,
				mApplicationPoint_local;

			Force_world(glm::dvec3 force_world, glm::dvec3 applicationPoint_local = CoM) :
				mForce_world(force_world),
				mApplicationPoint_local(applicationPoint_local)
			{ }
		};
		
		class RigidBody {
		public:
			enum class IntegrationMethod { EULER, RUNGE_KUTTA_4 };

		protected:
			State mState;
			
			IntegrationMethod mIntegrationMethod = IntegrationMethod::EULER;

			glm::dvec3
				mTotalForce_world,
				mTotalTorque_world,
				mAcceleration;

			std::vector<Force_world> mForces_world;
			std::vector<glm::dvec3> mTorques_world;

		public:
			RigidBody() = default;
			RigidBody(IntegrationMethod integrationMethod);
			virtual ~RigidBody() = default;

			inline void setIntegrationMethod(IntegrationMethod m) { mIntegrationMethod = m; }
			inline glm::dvec3 getAcceleration_world() const { return mAcceleration; }

		protected:
			void integrate(double t, double dt);
			glm::dvec3 velocityAtWorldPoint_world(glm::dvec3 worldSpacePoint);
			glm::dvec3 velocityAtLocalPoint_world(glm::dvec3 localSpacePoint);
			inline glm::dvec3 getTotalForce_world() const { return mTotalForce_world; }
			inline glm::dvec3 getTotalTorque_world() const { return mTotalTorque_world; }
			inline std::vector<Force_world>& getForces_world() { return mForces_world; }
			inline std::vector<glm::dvec3>& getTorques_world() { return mTorques_world; }

			virtual void addForces(State& state, double t) = 0;
			virtual void addTorques(State& state, double t) = 0;

			void addLocalForceAtLocalPoint(glm::dvec3 force_local, glm::dvec3 applicationPoint_local);
			void addWorldForceAtLocalPoint(glm::dvec3 force_world, glm::dvec3 applicationPoint_local);
			void addLocalForceThroughCM(glm::dvec3 force_local);
			void addWorldForceThroughCM(glm::dvec3 force_world);
			void addTorque_local(glm::dvec3 torque_local);
			void addTorque_world(glm::dvec3 torque_world);

			//virtual glm::dvec3 getForce_world(State& state, double t) = 0;
			//virtual glm::dvec3 getTorque_world(State& state, double t) = 0;

		private:
			void RK4(Derivative& changeWithTime, double t, double dt);
			void euler(Derivative& changeWithTime, double t, double dt);

			Derivative evaluate(State& initial, double t, double dt, const Derivative &d);

		};
	}
}

#endif
