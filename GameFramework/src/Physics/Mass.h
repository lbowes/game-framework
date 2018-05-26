#ifndef MASS_H
#define MASS_H
#pragma once

#include <glm/glm/vec3.hpp>
#include <cmath>

namespace Framework {
	namespace Physics {
		class Mass {
		private:
			double mValue = 0.0;
			glm::dvec3 mCentre;

		public:
			Mass();
			Mass(double value);
			Mass(double value, glm::dvec3 centre);
			~Mass() = default;

			void operator=(const Mass& other);
			void operator=(const double& otherValue);

			bool operator==(const Mass& other);
			bool operator<(const Mass& other);
			bool operator<(const double& otherValue);
			bool operator>(const Mass& other);
			bool operator>(const double& otherValue);

			Mass operator+(const Mass& other);
			Mass operator+(const double& otherValue);
			Mass operator+=(const Mass& other);
			Mass operator+=(const double& otherValue);
			Mass operator-(const double& otherValue);
			Mass operator-=(const double& otherValue);

			inline void reset() { mValue = 0.0; mCentre = glm::dvec3(0.0); }
			inline void setCentre(glm::dvec3 newCentre) { mCentre = newCentre; }

			inline double getValue() const { return mValue; }
			inline glm::dvec3 getCentre() const { return mCentre; }

		};
	}
}

#endif
