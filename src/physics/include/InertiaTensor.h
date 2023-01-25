#ifndef INERTIATENSOR_H
#define INERTIATENSOR_H
#pragma once

#include <glm/mat3x3.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/matrix_inverse.hpp>

class InertiaTensor {
private:
	glm::dmat3 mInternal = glm::mat3(1.0f);

public:
	InertiaTensor(); //Point mass                            
	InertiaTensor(glm::dmat3 mat);
	~InertiaTensor() = default;

	static InertiaTensor cube(double mass, double sideLength);
	static InertiaTensor cuboid(double mass, double height, double width, double depth);
	static InertiaTensor solidCylinder(double mass, double diameter, double height);
	static InertiaTensor thickWalledCylinder(double mass, double diameter, double wallThickness, double height);
	static InertiaTensor parallelAxis(const InertiaTensor& cmInertia, double mass, glm::dvec3 displacement);
	static InertiaTensor pointParallelAxis(double mass, glm::dvec3 displacement);

	void operator=(const InertiaTensor& other);
	InertiaTensor operator+=(const InertiaTensor& other);
	InertiaTensor afterRotation(const glm::dmat3& rotationMatrix);
	InertiaTensor afterRotation(const glm::dmat4& rotationMatrix);
	glm::dmat3 getInternal() const { return mInternal; }
	InertiaTensor inverse() const { return glm::inverse(mInternal); }
	void reset() { mInternal = glm::dmat3(0.0); }
	void rotate(const glm::dmat3 rotationMatrix);
	
	friend bool operator==(const InertiaTensor& l, const InertiaTensor& r);
	friend bool operator!=(const InertiaTensor& l, const InertiaTensor& r);
	friend InertiaTensor operator+(const InertiaTensor& l, const InertiaTensor& r);
	friend glm::dvec3 operator*(const InertiaTensor& l, const glm::dvec3& r);

};

bool operator==(const InertiaTensor& l, const InertiaTensor& r);
bool operator!=(const InertiaTensor& l, const InertiaTensor& r);
InertiaTensor operator+(const InertiaTensor& l, const InertiaTensor& r);
glm::dvec3 operator*(const InertiaTensor& l, const glm::dvec3& r);

#endif
