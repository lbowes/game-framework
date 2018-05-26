#ifndef COORDINATESPACE3D_H
#define COORDINATESPACE3D_H
#pragma once

#include <glm/glm/mat4x4.hpp>
#include <glm/glm/gtx/transform.hpp>
#include <glm/glm/vec3.hpp>
#include <glm/glm/gtx/quaternion.hpp>
#include <glm/glm/gtc/matrix_inverse.hpp>

#define ROOT glm::dmat4(1.0)

class CoordinateSpace3D {
private:
	glm::dmat4
		mTranslation_localToParent,
		mRotation_localToParent,
		mTotal_localToParent;

public:
	CoordinateSpace3D(glm::dmat4 translation_localToParent = ROOT, glm::dmat4 rotation_localToParent = ROOT) :
		mTranslation_localToParent(translation_localToParent),
		mRotation_localToParent(rotation_localToParent),
		mTotal_localToParent(translation_localToParent * rotation_localToParent)
	{ }

	CoordinateSpace3D(glm::dvec3 translation_localToParent, glm::dquat rotation_localToParent) :
		mTranslation_localToParent(translate(translation_localToParent)),
		mRotation_localToParent(toMat4(rotation_localToParent)),
		mTotal_localToParent(mTranslation_localToParent * mRotation_localToParent)
	{ }

	~CoordinateSpace3D() = default;

	inline glm::dvec3 toParentSpace_total(glm::dvec3 position_local) const { return glm::dvec3(mTotal_localToParent * glm::dvec4(position_local, 1.0)); }
	inline glm::dvec4 toParentSpace_total(glm::dvec4 position_local) const { return mTotal_localToParent * position_local; }
	inline glm::dvec3 toParentSpace_position(glm::dvec3 position_local) const { return glm::dvec3(mTranslation_localToParent * glm::dvec4(position_local, 1.0)); }
	inline glm::dvec4 toParentSpace_position(glm::dvec4 position_local) const { return mTranslation_localToParent * position_local; }
	inline glm::dvec3 toParentSpace_direction(glm::dvec3 direction_local) const { return glm::dvec3(mRotation_localToParent * glm::dvec4(direction_local, 1.0)); }
	inline glm::dvec4 toParentSpace_direction(glm::dvec4 direction_local) const { return mRotation_localToParent * direction_local; }
	inline glm::dquat toParentSpace_direction(glm::dquat direction_local) const { return glm::toQuat(mRotation_localToParent) * direction_local; }
	inline glm::dmat4 toParentSpace_direction(glm::dmat4 direction_local) const { return mRotation_localToParent * direction_local; }

	inline glm::dvec3 toLocalSpace_total(glm::dvec3 position_parent) const { return glm::dvec3(glm::inverse(mTotal_localToParent) * glm::dvec4(position_parent, 1.0)); }
	inline glm::dvec4 toLocalSpace_total(glm::dvec4 position_parent) const { return glm::inverse(mTotal_localToParent) * position_parent; }
	inline glm::dvec3 toLocalSpace_position(glm::dvec3 position_parent) const { return glm::dvec3(glm::inverse(mTranslation_localToParent) * glm::dvec4(position_parent, 1.0)); }
	inline glm::dvec4 toLocalSpace_position(glm::dvec4 position_parent) const { return glm::inverse(mTranslation_localToParent) * position_parent; }
	inline glm::dvec3 toLocalSpace_direction(glm::dvec3 direction_parent) const { return glm::dvec3(glm::inverse(mRotation_localToParent) * glm::dvec4(direction_parent, 1.0)); }
	inline glm::dvec4 toLocalSpace_direction(glm::dvec4 direction_parent) const { return glm::inverse(mRotation_localToParent) * direction_parent; }
	inline glm::dquat toLocalSpace_direction(glm::dquat direction_parent) const { return glm::toQuat(glm::inverse(mRotation_localToParent)) * direction_parent; }
	inline glm::dmat4 toLocalSpace_direction(glm::dmat4 direction_parent) const { return glm::inverse(mRotation_localToParent) * direction_parent; }

	inline glm::dmat4 getLocalToParent_total() const { return mTotal_localToParent; }
	inline glm::dmat4 getLocalToParent_position() const { return mTranslation_localToParent; }
	inline glm::dmat4 getLocalToParent_direction() const { return mRotation_localToParent; }

	void setLocalToParent_position(glm::dvec3 translation_localToParent) {
		mTranslation_localToParent = translate(translation_localToParent);
		updateTotalTransform_localToParent();
	}

	void setLocalToParent_direction(glm::dmat4 rotation_localToParent) {
		mRotation_localToParent = rotation_localToParent;
		updateTotalTransform_localToParent();
	}

	void setLocalToParent_direction(glm::dquat rotation_localToParent) {
		mRotation_localToParent = glm::toMat4(rotation_localToParent);
		updateTotalTransform_localToParent();
	}

private:
	void updateTotalTransform_localToParent() {
		mTotal_localToParent = mTranslation_localToParent * mRotation_localToParent;
	}

};

#endif
