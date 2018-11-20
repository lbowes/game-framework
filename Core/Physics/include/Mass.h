#ifndef MASS_H
#define MASS_H
#pragma once

#include <glm/vec3.hpp>
#include <cmath>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>

class Mass {
private:
	double mValue = 0.0;
	glm::dvec3 mCentre = glm::dvec3(0.0);

public:
	Mass();
	Mass(double value, glm::dvec3 centre = glm::dvec3(0.0));
	~Mass() = default;

	void operator=(const Mass& other);
	void operator=(double other);
	void lerp(const Mass &b, double x);
	Mass operator+=(const Mass& other);
	Mass operator-=(const Mass& other);
	
	double getValue() const { return mValue; }
	glm::dvec3 getCentre() const { return mCentre; }
	void setCentre(glm::dvec3 newCentre) { mCentre = newCentre; }
	void reset();

	friend bool operator==(const Mass& l, const Mass& r);
	friend bool operator!=(const Mass& l, const Mass& r);
	friend bool operator<(const Mass& l, const Mass& r);
	friend bool operator>(const Mass& l, const Mass& r);
	friend Mass operator+(const Mass& l, const Mass& r);
	friend Mass operator-(const Mass& l, const Mass& r);
	friend Mass lerp(const Mass &a, const Mass &b, double x);
			
};

bool operator==(const Mass& l, const Mass& r);
bool operator!=(const Mass& l, const Mass& r);
bool operator<(const Mass& l, const Mass& r);
bool operator>(const Mass& l, const Mass& r);
Mass operator+(const Mass& l, const Mass& r);
Mass operator-(const Mass& l, const Mass& r);
Mass lerp(const Mass &a, const Mass &b, double x);

long double operator""_lbs(long double lbs);
long double operator""_slugs(long double slugs);
long double operator""_grams(long double grams);
long double operator""_tonnes(long double tonnes);

#endif
