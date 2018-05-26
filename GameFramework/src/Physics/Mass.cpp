#include "Mass.h"

namespace Framework {
	namespace Physics {

		Mass::Mass() :
			mValue(0.0),
			mCentre(glm::dvec3(0.0))
		{ }

		Mass::Mass(double value) :
			mValue(value),
			mCentre(glm::dvec3(0.0))
		{ }

		Mass::Mass(double value, glm::dvec3 centre) :
			mValue(value),
			mCentre(centre)
		{ }

		void Mass::operator=(const Mass& other) {
			this->mValue = other.mValue;
			this->mCentre = other.mCentre;
		}

		void Mass::operator=(const double& otherValue) {
			this->mValue = otherValue;
		}

		bool Mass::operator==(const Mass& other) {
			return (this->mValue == other.mValue) && (this->mCentre == other.mCentre);
		}

		bool Mass::operator<(const Mass& other) {
			return this->mValue < other.mValue;
		}

		bool Mass::operator<(const double& otherValue) {
			return this->mValue < otherValue;
		}

		bool Mass::operator>(const Mass& other) {
			return this->mValue > other.mValue;
		}

		bool Mass::operator>(const double& otherValue) {
			return this->mValue > otherValue;
		}

		Mass Mass::operator+(const Mass& other) {
			double newMass = this->mValue + other.mValue;

			if (newMass > 0.0)
				return Mass(newMass, (this->mValue * this->mCentre + other.mValue * other.mCentre) / newMass);

			return Mass();
		}

		Mass Mass::operator+(const double& otherValue) {
			double newMass = this->mValue + otherValue;

			if (newMass > 0.0)
				return Mass(newMass, this->mCentre);

			return Mass();
		}

		Mass Mass::operator+=(const Mass& other) {
			double newMass = this->mValue + other.mValue;

			if (newMass > 0.0) {
				//The order of the following two statements is crucial
				this->mCentre = (this->mValue * this->mCentre + other.mValue * other.mCentre) / newMass;
				this->mValue = newMass;
			}
			else
				this->mValue = 0.0;

			return *this;
		}

		Mass Mass::operator+=(const double& otherValue) {
			double newMass = this->mValue + otherValue;

			if (newMass > 0.0)
				this->mValue += otherValue;
			else
				this->mValue = 0.0;

			return *this;
		}

		Mass Mass::operator-(const double& otherValue) {
			double newMass = this->mValue - otherValue;

			if (newMass > 0.0)
				return Mass(newMass, this->mCentre);

			return Mass();
		}

		Mass Mass::operator-=(const double& otherValue) {
			double newMass = this->mValue - otherValue;

			if (newMass > 0.0)
				this->mValue -= otherValue;
			else
				this->mValue = 0.0;

			return *this;
		}

	}
}