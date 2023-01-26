#ifndef SPRING_HPP
#define SPRING_HPP
#pragma once

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

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
		mDampingCoefficient(dampingCoefficient),
		mRestLength(restLength)
	{ }

	void operator=(const Spring& other) {
		mK = other.mK;
		mDampingCoefficient = other.mDampingCoefficient;
		mRestLength = other.mRestLength;
		mLength = other.mLength;
		mForce = other.mForce;
		mCompressionRate = other.mCompressionRate;
	}

	~Spring() = default;

	void update(double length, double compressionRate) {
		mLength = length;
		mCompressionRate = compressionRate;

		mForce = -mK * (length - mRestLength) - mDampingCoefficient * compressionRate;
	}

	void setDamping(double damping) { mDampingCoefficient = damping; }
	void setSpringConstant(double springConstant) { mK = springConstant; }

	double getForce() const { return mForce; }
	double getRestLength() const { return mRestLength; }
	double getCurrentLength() const { return mLength; }
	double getCompressionRate() const { return mCompressionRate; }

};

#endif
