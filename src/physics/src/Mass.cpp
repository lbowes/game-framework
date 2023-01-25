#include "Mass.h"

Mass::Mass() :
	mValue(0.0),
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

void Mass::operator=(double other) {
	this->mValue = other;
}

void Mass::lerp(const Mass &b, double x) {
	mCentre = glm::lerp(mCentre, b.mCentre, x);
	mValue = mValue + (b.mValue - mValue) * x;
}

Mass Mass::operator+=(const Mass& other) {
	double newMass = this->mValue + other.mValue;

	if (newMass != 0.0) {
		//The order of the following two statements is crucial
		this->mCentre = (this->mValue * this->mCentre + other.mValue * other.mCentre) / newMass;
		this->mValue = newMass;
	}
	else
		this->mValue = 0.0;

	return *this;
}

Mass Mass::operator-=(const Mass& other) {
	double newMass = this->mValue - other.mValue;

	if (newMass != 0.0) {
		//The order of the following two statements is crucial
		this->mCentre = (this->mValue * this->mCentre - other.mValue * other.mCentre) / newMass;
		this->mValue = newMass;
	}
	else
		this->mValue = 0.0;

	return *this;
}

void Mass::reset() {
	mValue = 0.0;
	mCentre = glm::dvec3(0.0);
}

bool operator==(const Mass& l, const Mass& r) {
	return (l.mValue == r.mValue) && (l.mCentre == r.mCentre);
}

bool operator!=(const Mass& l, const Mass& r) {
	return (l.mValue != r.mValue) || (l.mCentre != r.mCentre);
}

bool operator<(const Mass& l, const Mass& r) {
	return l.mValue < r.mValue;
}

bool operator>(const Mass& l, const Mass& r) {
	return l.mValue > r.mValue;
}

Mass operator+(const Mass& l, const Mass& r) {
	double newMass = l.mValue + r.mValue;

	if (newMass != 0.0)
		return Mass(newMass, (l.mValue * l.mCentre + r.mValue * r.mCentre) / newMass);
	else
		return Mass(0.0, l.mCentre);
}

Mass operator-(const Mass& l, const Mass& r){
	double newMass = l.mValue - r.mValue;

	if (newMass != 0.0)
		return Mass(newMass, (l.mValue * l.mCentre - r.mValue * r.mCentre) / newMass);
	else
		return Mass(0.0, l.mCentre);
}

Mass lerp(const Mass &a, const Mass &b, double x) {
	Mass output;
	
	output.mCentre = glm::lerp(a.mCentre, b.mCentre, x);
	output.mValue = a.mValue + (b.mValue - a.mValue) * x;

	return output;
}

long double operator""_lbs(long double lbs) {
	return lbs / 2.20462;
}

long double operator""_slugs(long double slugs) {
	return slugs / 0.0685218;
}

long double operator""_grams(long double grams) {
	return grams / 1000.0;
}

long double operator""_tonnes(long double tonnes) {
	return tonnes * 1000.0;
}