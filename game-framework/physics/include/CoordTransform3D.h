#ifndef COORDTRANSFORM3D_H
#define COORDTRANSFORM3D_H
#pragma once

#include <glm/mat4x4.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <glm/gtx/matrix_interpolation.hpp>

#include <glm/vec3.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_inverse.hpp>

class CoordTransform3D {
private:
	glm::dmat4
		mTranslation_localToParent = glm::dmat4(1.0),
		mRotation_localToParent = glm::dmat4(1.0),
		mTotal_localToParent = glm::dmat4(1.0);

public:
	CoordTransform3D(const CoordTransform3D& other);
	void operator=(const CoordTransform3D& other);
	CoordTransform3D(glm::dvec3 translation_localToParent = glm::dvec3(0.0), glm::dmat4 rotation_localToParent = glm::dmat4(1.0));
	~CoordTransform3D() = default;

	//----------------------------------------LOCAL TO PARENT SPACE CONVERSIONS----------------------------------------
	glm::dvec3 toParentSpace_translation() const { return glm::dvec3(mTranslation_localToParent * glm::dvec4(0.0, 0.0, 0.0, 1.0)); }
	glm::dvec3 toParentSpace_translation(glm::dvec3 position_local) const { return glm::dvec3(mTranslation_localToParent * glm::dvec4(position_local, 1.0)); }

	glm::dvec3 toParentSpace_rotation(glm::dvec3 direction_local) const { return glm::dvec3(mRotation_localToParent * glm::dvec4(direction_local, 1.0)); }
	glm::dquat toParentSpace_rotation(glm::dquat direction_local) const { return glm::toQuat(mRotation_localToParent) * direction_local; }
	glm::dmat4 toParentSpace_rotation(glm::dmat4 direction_local) const { return mRotation_localToParent * direction_local; }

	glm::dvec3 toParentSpace() const { return glm::dvec3(mTotal_localToParent * glm::dvec4(0.0, 0.0, 0.0, 1.0)); }
	glm::dvec3 toParentSpace(glm::dvec3 position_local) const { return glm::dvec3(mTotal_localToParent * glm::dvec4(position_local, 1.0)); }

	//----------------------------------------PARENT TO LOCAL SPACE CONVERSIONS----------------------------------------
	glm::dvec3 toLocalSpace_translation() const { return glm::dvec3(glm::inverse(mTranslation_localToParent) * glm::dvec4(0.0, 0.0, 0.0, 1.0)); }
	glm::dvec3 toLocalSpace_translation(glm::dvec3 position_parent) const { return glm::dvec3(glm::inverse(mTranslation_localToParent) * glm::dvec4(position_parent, 1.0)); }

	glm::dvec3 toLocalSpace_rotation(glm::dvec3 direction_parent) const { return glm::dvec3(glm::inverse(mRotation_localToParent) * glm::dvec4(direction_parent, 1.0)); }
	glm::dquat toLocalSpace_rotation(glm::dquat direction_parent) const { return glm::toQuat(glm::inverse(mRotation_localToParent)) * direction_parent; }
	glm::dmat4 toLocalSpace_rotation(glm::dmat4 direction_parent) const { return glm::inverse(mRotation_localToParent) * direction_parent; }

	glm::dvec3 toLocalSpace() const { return glm::dvec3(glm::inverse(mTotal_localToParent) * glm::dvec4(0.0, 0.0, 0.0, 1.0)); }
	glm::dvec3 toLocalSpace(glm::dvec3 position_parent) const { return glm::dvec3(glm::inverse(mTotal_localToParent) * glm::dvec4(position_parent, 1.0)); }

	//-----------------------------------------------------------------------------------------------------------------
	glm::dmat4 getLocalToParent_translation() const { return mTranslation_localToParent; }
	glm::dmat4 getLocalToParent_rotation() const { return mRotation_localToParent; }
	glm::dmat4 getLocalToParent_total() const { return mTotal_localToParent; }

	void setLocalToParent_translation(glm::dmat4 translation_localToParent);
	void setLocalToParent_translation(glm::dvec3 translation_localToParent);
	void setLocalToParent_rotation(glm::dmat4 rotation_localToParent);
	void setLocalToParent_rotation(glm::dquat rotation_localToParent);

	void lerp(const CoordTransform3D &dest, double x);
	friend CoordTransform3D lerp(const CoordTransform3D& a, const CoordTransform3D& b, double x);

  private:
	void updateTotalTransform_localToParent();

};

CoordTransform3D lerp(const CoordTransform3D &a, const CoordTransform3D &b, double x);

#endif
