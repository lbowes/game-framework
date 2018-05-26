#ifndef SPRING_H
#define SPRING_H
#pragma once

#include <glm/glm/vec3.hpp>
#include <glm/glm/geometric.hpp>

namespace Framework {
	namespace Physics {
		class Spring {
		private:
			double
				mK = 0.0,
				mDampingCoefficient = 0.0, //0.0 -> 1.0
				mRestLength = 0.0,         //m
				mLength = 0.0,             //m
				mForce = 0.0,              //N
				mCompressionRate = 0.0;    //m/s

		public:
			Spring(double k, double restLength, double dampingCoefficient) :
				mK(k),
				mRestLength(restLength),
				mDampingCoefficient(dampingCoefficient)
			{ }

			~Spring() = default;

			void update(double length, double compressionRate) {
				mLength = length;
				mCompressionRate = compressionRate;

				mForce = -mK * (length - mRestLength) - mDampingCoefficient * compressionRate;
			}

			inline void setDamping(double damping) { mDampingCoefficient = damping; }
			inline void setSpringConstant(double springConstant) { mK = springConstant; }

			inline double getForce() const { return mForce; }
			inline double getRestLength() const { return mRestLength; }
			inline double getCurrentLength() const { return mLength; }

		};
	}
}

#endif
