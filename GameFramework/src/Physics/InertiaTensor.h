#ifndef INERTIATENSOR_H
#define INERTIATENSOR_H
#pragma once

#include <glm/glm/mat3x3.hpp>
#include <glm/glm/geometric.hpp>
#include <glm/glm/gtc/matrix_inverse.hpp>

namespace Framework {
	namespace Physics {
		class InertiaTensor {
		private:
			glm::dmat3 mInternal;

		public:
			InertiaTensor(); //Point mass                            
			InertiaTensor(glm::dmat3 mat);
			~InertiaTensor() = default;

			static InertiaTensor solidCylinder(double mass, double diameter, double height);
			static InertiaTensor thickWalledCylinder(double mass, double diameter, double wallThickness, double height);
			static InertiaTensor parallelAxis(InertiaTensor& cmInertia, double mass, glm::dvec3 displacement);
			static InertiaTensor pointParallelAxis(double mass, glm::dvec3 displacement);

			void operator=(const InertiaTensor& other);
			glm::dvec3 operator*(const glm::dvec3 vector);
			InertiaTensor operator+(const glm::dmat3& mat);
			InertiaTensor operator+(const InertiaTensor& other);
			InertiaTensor& operator+=(const glm::dmat3& mat);
			InertiaTensor& operator+=(const InertiaTensor& other);
			bool operator==(const InertiaTensor& other);
			bool operator==(const glm::dmat3 other);
			bool operator!=(const InertiaTensor& other);
			bool operator!=(const glm::dmat3 other);
			void rotate(const glm::dmat3 rotationMatrix);
			InertiaTensor afterRotation(const glm::dmat3 rotationMatrix);
			InertiaTensor afterRotation(const glm::dmat4 rotationMatrix);
			inline void reset() { mInternal = glm::dmat3(0.0); }

			inline glm::dmat3 getInternal() const { return mInternal; }
			inline InertiaTensor inverse() const { return glm::inverse(mInternal); }

			//temp
			glm::dvec3& operator[](unsigned int index) { return mInternal[index]; }
			//

		};

	}
}

#endif
