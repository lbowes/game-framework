#include "InertiaTensor.h"

namespace Framework {
	namespace Physics {

		InertiaTensor::InertiaTensor() :
			mInternal(glm::dmat3(0.0)) //Point masses do not have a moment of inertia about their centre of mass
		{ }

		InertiaTensor::InertiaTensor(glm::dmat3 mat) {
			mInternal = mat;
		}

		InertiaTensor InertiaTensor::solidCylinder(double mass, double diameter, double height) {
			InertiaTensor output;

			double
				rSquared = pow(diameter / 2.0, 2),
				hSquared = pow(height, 2);

			output.mInternal[0][0] = (1.0 / 12.0) * mass * (3 * rSquared + hSquared); //x
			output.mInternal[1][1] = 0.5 * mass * rSquared;							  //y
			output.mInternal[2][2] = (1.0 / 12.0) * mass * (3 * rSquared + hSquared); //z

			return output;
		}

		InertiaTensor InertiaTensor::thickWalledCylinder(double mass, double diameter, double wallThickness, double height) {
			InertiaTensor output;

			double
				hSquared = pow(height, 2),
				r1Squared = pow(diameter / 2 - wallThickness, 2),
				r2Squared = pow(diameter / 2, 2);

			output.mInternal[0][0] = (1.0 / 12.0) * mass * (3 * (r1Squared + r2Squared) + hSquared); //x
			output.mInternal[1][1] = 0.5 * mass * (r1Squared + r2Squared);			                   //y
			output.mInternal[2][2] = (1.0 / 12.0) * mass * (3 * (r1Squared + r2Squared) + hSquared); //z

			return output;
		}

		InertiaTensor InertiaTensor::parallelAxis(InertiaTensor& cmInertia, double mass, glm::dvec3 displacement) {
			//http://homepages.wmich.edu/~kamman/Me555InertiaMatrix.pdf
			//https://en.wikipedia.org/wiki/Parallel_axis_theorem#Tensor_generalisation
			//http://www-robotics.cs.umass.edu/~grupen/603/slides/DynamicsI.pdf

			using namespace glm;

			double dSquared = pow(length(displacement), 2);

			return 
				cmInertia + dmat3(mass * (dSquared - displacement.x*displacement.x), mass * (-displacement.y*displacement.x), mass * (-displacement.z*displacement.x),
				                  mass * (-displacement.x*displacement.y), mass * (dSquared - displacement.y*displacement.y), mass * (-displacement.z*displacement.y),
								  mass * (-displacement.x*displacement.z), mass * (-displacement.y*displacement.z), mass * (dSquared - displacement.z*displacement.z));
		}

		InertiaTensor InertiaTensor::pointParallelAxis(double mass, glm::dvec3 displacement) {
			using namespace glm;

			dmat3 temp;
			double dSquared = pow(length(displacement), 2);

				     temp = dmat3(mass * (dSquared - displacement.x*displacement.x), mass * (-displacement.y*displacement.x), mass * (-displacement.z*displacement.x),
					 			  mass * (-displacement.x*displacement.y), mass * (dSquared - displacement.y*displacement.y), mass * (-displacement.z*displacement.y),
					 			  mass * (-displacement.x*displacement.z), mass * (-displacement.y*displacement.z), mass * (dSquared - displacement.z*displacement.z));

			return InertiaTensor(temp);
		}

		void InertiaTensor::operator=(const InertiaTensor& other) {
			this->mInternal = other.mInternal;
		}

		glm::dvec3 InertiaTensor::operator*(const glm::dvec3 vector) {
			return mInternal * vector;
		}

		InertiaTensor InertiaTensor::operator+(const glm::dmat3& mat) {
			return InertiaTensor(this->mInternal + mat);
		}

		InertiaTensor InertiaTensor::operator+(const InertiaTensor& other) {
			return InertiaTensor(this->mInternal + other.mInternal);
		}

		InertiaTensor& InertiaTensor::operator+=(const glm::dmat3& mat) {
			this->mInternal += mat;
			return *this;
		}

		InertiaTensor& InertiaTensor::operator+=(const InertiaTensor& other) {
			this->mInternal += other.mInternal;
			return *this;
		}

		bool InertiaTensor::operator==(const InertiaTensor& other) {
			return this->mInternal == other.mInternal;
		}

		bool InertiaTensor::operator==(const glm::dmat3 other) {
			return this->mInternal == other;
		}

		bool InertiaTensor::operator!=(const InertiaTensor& other) {
			return this->mInternal != other.mInternal;
		}

		bool InertiaTensor::operator!=(const glm::dmat3 other) {
			return this->mInternal != other;
		}

		void InertiaTensor::rotate(glm::dmat3 rotationMatrix) {
			mInternal = glm::inverse(rotationMatrix) * mInternal * rotationMatrix;
		}

		InertiaTensor InertiaTensor::afterRotation(glm::dmat3 rotationMatrix) {
			return rotationMatrix * mInternal * glm::transpose(rotationMatrix);
		}

		InertiaTensor InertiaTensor::afterRotation(glm::dmat4 rotationMatrix) {
			return glm::dmat3(rotationMatrix * glm::dmat4(mInternal) * glm::transpose(rotationMatrix));
		}

	}
}