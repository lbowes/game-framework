#ifndef STATE_H
#define STATE_H
#pragma once

#include <glm/glm/vec3.hpp>
#include <glm/glm/gtc/quaternion.hpp>
#include <glm/glm/gtx/quaternion.hpp>
#include <glm/glm/gtc/matrix_inverse.hpp>
#include <glm/glm/gtx/transform.hpp>

#include "InertiaTensor.h"
#include "Mass.h"
#include "../Objects/CoordinateSpace3D.hpp"

namespace Framework {
	namespace Physics {

		struct Derivative {
			glm::dvec3
				dx,
				dm,
				dam;

			glm::dquat dor;
		};

		class State {
			friend class RigidBody;
		private:
			//Primary properties
			glm::dvec3
				mPosition_world,
				mMomentum_world,
				mAngularMomentum_world;
			
			glm::dquat mOrientation_world;

			//Secondary	properties
			glm::dvec3
				mVelocity_world,
				mAngularVelocity_world;
			
			glm::dquat mSpin_world;

			//Non-integrated properties
			InertiaTensor mInertiaTensor_local;
			
			Mass mMass;
			
			CoordinateSpace3D
				mCentreMassSpace,
				mObjectSpace;

		public:
			State() = default;
			~State() = default;

			void reset() {
				using namespace glm;

				mPosition_world = dvec3(0.0);
				mMomentum_world = dvec3(0.0);
				mAngularMomentum_world = dvec3(0.0);
				mOrientation_world = dquat(vec3(0.0));
				mVelocity_world = dvec3(0.0);
				mAngularVelocity_world = dvec3(0.0);
				mSpin_world = dquat(vec3(0.0));

				recalc();
			}

			inline glm::dvec3 getPosition_world() const { return mPosition_world; }
			inline glm::dvec3 getMomentum_world() const { return mMomentum_world; }
			inline glm::dvec3 getAngularMomentum_world() const { return mAngularMomentum_world; }
			inline glm::dquat getOrientation_world() const { return mOrientation_world; }
			inline glm::dvec3 getVelocity_world() const { return mVelocity_world; }
			inline glm::dvec3 getAngularVelocity_world() const { return mAngularVelocity_world; }
			inline InertiaTensor getInertiaTensor_local() const { return mInertiaTensor_local; }
			inline Mass getMass() const { return mMass; }
			inline CoordinateSpace3D& getCentreMassSpace() { return mCentreMassSpace; }
			inline CoordinateSpace3D& getObjectSpace() { return mObjectSpace; }

			void setPosition_world(glm::dvec3 newPosition_world) {
				mPosition_world = newPosition_world;
				updateTransforms();
			}
			
			void setMomentum_world_world(glm::dvec3 newMomentum_world) {
				mMomentum_world = newMomentum_world;
				mVelocity_world = mMomentum_world / mMass.getValue();
			}

			void setAngularMomentum_world(glm::dvec3 newAngularMomentum_world) {
				mAngularMomentum_world = newAngularMomentum_world;
				//mAngularVelocity_world = mOrientation_world * (mInertiaTensor_local.inverse() * (inverse(mOrientation_world) * newAngularMomentum_world));
			}

			void setOrientation_world(glm::dquat newOrientation_world) {
				mOrientation_world = normalize(newOrientation_world);
				//
				//mAngularVelocity_world = mOrientation_world * (inverse(mInertiaTensor_local.getInternal()) * (inverse(mOrientation_world) * mAngularMomentum_world));
				//glm::dquat q(0.0, mAngularVelocity_world);
				//mSpin_world = 0.5 * q * mOrientation_world;
				//updateTransforms();
			}

			void setVelocity_world(glm::dvec3 newVelocity_world) {
				mVelocity_world = newVelocity_world;
				mMomentum_world = newVelocity_world * mMass.getValue();
			}

			void setAngularVelocity_world(glm::dvec3 newAngularVelocity_world) {
				mAngularVelocity_world = newAngularVelocity_world;
				mAngularMomentum_world = mOrientation_world * (mInertiaTensor_local * (inverse(mOrientation_world) * newAngularVelocity_world));
			}

			void setInertiaTensor_local(InertiaTensor newInertiaTensor_local) {
				mInertiaTensor_local = newInertiaTensor_local;
				//mAngularVelocity_world = mOrientation_world * (mInertiaTensor_local.inverse() * (inverse(mOrientation_world) * mAngularMomentum_world));
			}

			void setMass_local(Mass newMass_local) {
				//This should not be used anymore
				//mMass_local = newMass_local;

				mMass = newMass_local.getValue();
				setMassCentre_local(newMass_local.getCentre());

				mMomentum_world = newMass_local.getValue() * mVelocity_world;
			}

			void setMassValue_local(double newMassValue_local) {
				mMass = newMassValue_local;
			}

			void setMassCentre_local(glm::dvec3 newMassCentre_local) {
				mMass.setCentre(newMassCentre_local);
				mCentreMassSpace.setLocalToParent_position(-newMassCentre_local);
			}

		private:
			void recalc() {
				using namespace glm;

				//Protection against division by zero
				double mass = mMass.getValue();
				if (mass > 0.0)
					mVelocity_world = mMomentum_world / mass;

				//This line is a protection against -nan(ind). glm::inverse returns a matrix full of -nan(ind), if it is called with a 
				//matrix containing all 0s (make sure the matrix is not completely full of 0s)
				if (mInertiaTensor_local.getInternal() != dmat3(0.0))
					//1. Torque, and by extension, angular momentum comes in in world space.
					//2. Angular momentum is then converted to local space (using inverse orientation)
					//3. Local space angular momentum and inertia tensor are used to calculate local space angular velocity
					//4. Lastly, the local angular velocity is converted to world space angular velocity.
					mAngularVelocity_world = mOrientation_world * (mInertiaTensor_local.inverse() * (inverse(mOrientation_world) * mAngularMomentum_world));

				//The alternative is to convert local inertia tensor into world space tensor using 'toWorld * localInertia * inverse(toWorld)'
				//mAngularVelocity = inverse(toMat3(mOrientation) * mInertiaTensor_L.getInternal() * inverse(toMat3(mOrientation))) * mAngularMomentum;

				dquat q(0.0, mAngularVelocity_world);
				mSpin_world = 0.5 * q * mOrientation_world;

				mOrientation_world = normalize(mOrientation_world);

				updateTransforms();
			}

			void updateTransforms() {
				mObjectSpace.setLocalToParent_position(glm::dvec3(
					glm::translate(mPosition_world) * 
					glm::toMat4(mOrientation_world) *
					mCentreMassSpace.getLocalToParent_total() * 
					glm::dvec4(0.0, 0.0, 0.0, 1.0))
				);
				
				mObjectSpace.setLocalToParent_direction(glm::toMat4(mOrientation_world));
			}

		};

	}
}

#endif
