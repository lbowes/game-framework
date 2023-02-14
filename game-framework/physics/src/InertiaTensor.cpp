#include "InertiaTensor.h"


InertiaTensor::InertiaTensor() :
	mInternal(glm::dmat3(0.0f)) //Point masses do not have a moment of inertia about their centre of mass
{ }

InertiaTensor::InertiaTensor(glm::dmat3 mat) {
	mInternal = mat;
}

InertiaTensor InertiaTensor::cube(double mass, double sideLength) {
	InertiaTensor output;

	double value = (1.0 / 6.0) * mass * (pow(sideLength, 2.0));

	output.mInternal[0][0] = value; //x
	output.mInternal[1][1] = value; //y
	output.mInternal[2][2] = value; //z

	return output;
}

InertiaTensor InertiaTensor::cuboid(double mass, double width, double height, double depth) {
	InertiaTensor output;

	output.mInternal[0][0] = (1.0 / 12.0) * mass * (pow(height, 2.0) + pow(depth, 2.0)); //x
	output.mInternal[1][1] = (1.0 / 12.0) * mass * (pow(width, 2.0) + pow(depth, 2.0));  //y
	output.mInternal[2][2] = (1.0 / 12.0) * mass * (pow(width, 2.0) + pow(height, 2.0)); //z

	return output;
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
	output.mInternal[1][1] = 0.5 * mass * (r1Squared + r2Squared);			                 //y
	output.mInternal[2][2] = (1.0 / 12.0) * mass * (3 * (r1Squared + r2Squared) + hSquared); //z

	return output;
}

InertiaTensor InertiaTensor::parallelAxis(const InertiaTensor& cmInertia, double mass, glm::dvec3 displacement) {
	//http://homepages.wmich.edu/~kamman/Me555InertiaMatrix.pdf
	//https://en.wikipedia.org/wiki/Parallel_axis_theorem#Tensor_generalisation
	//http://www-robotics.cs.umass.edu/~grupen/603/slides/DynamicsI.pdf

	double dSquared = pow(length(displacement), 2);

	return cmInertia + glm::dmat3(mass * (dSquared - displacement.x*displacement.x), mass * (-displacement.y*displacement.x), mass * (-displacement.z*displacement.x),
		                  mass * (-displacement.x*displacement.y), mass * (dSquared - displacement.y*displacement.y), mass * (-displacement.z*displacement.y),
						  mass * (-displacement.x*displacement.z), mass * (-displacement.y*displacement.z), mass * (dSquared - displacement.z*displacement.z));
}

InertiaTensor InertiaTensor::pointParallelAxis(double mass, glm::dvec3 displacement) {
	double dSquared = pow(length(displacement), 2);

	return glm::dmat3(mass * (dSquared - displacement.x*displacement.x), mass * (-displacement.y*displacement.x), mass * (-displacement.z*displacement.x),
		mass * (-displacement.x*displacement.y), mass * (dSquared - displacement.y*displacement.y), mass * (-displacement.z*displacement.y),
		mass * (-displacement.x*displacement.z), mass * (-displacement.y*displacement.z), mass * (dSquared - displacement.z*displacement.z));
}

void InertiaTensor::operator=(const InertiaTensor& other) {
	this->mInternal = other.mInternal;
}

InertiaTensor InertiaTensor::operator+=(const InertiaTensor& other) {
	this->mInternal += other.mInternal;
	return *this;
}

InertiaTensor InertiaTensor::afterRotation(const glm::dmat3& rotationMatrix) {
	return rotationMatrix * mInternal * glm::transpose(rotationMatrix);
}

InertiaTensor InertiaTensor::afterRotation(const glm::dmat4& rotationMatrix) {
	return glm::dmat3(rotationMatrix * glm::dmat4(mInternal) * glm::transpose(rotationMatrix));
}

void InertiaTensor::rotate(glm::dmat3 rotationMatrix) {
	mInternal = glm::inverse(rotationMatrix) * mInternal * rotationMatrix;
}

bool operator==(const InertiaTensor& l, const InertiaTensor& r) {
	return l.mInternal == r.mInternal;
}

bool operator!=(const InertiaTensor& l, const InertiaTensor& r) {
	return l.mInternal != r.mInternal;
}

InertiaTensor operator+(const InertiaTensor& l, const InertiaTensor& r) {
	return InertiaTensor(l.mInternal + r.mInternal);
}

glm::dvec3 operator*(const InertiaTensor& l, const glm::dvec3& r) {
	return l.mInternal * r;
}