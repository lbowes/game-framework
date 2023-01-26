#include "CoordTransform3D.h"

CoordTransform3D::CoordTransform3D(const CoordTransform3D& other) :
	mTranslation_localToParent(other.mTranslation_localToParent),
	mRotation_localToParent(other.mRotation_localToParent),
	mTotal_localToParent(other.mTotal_localToParent)
{ }

void CoordTransform3D::operator=(const CoordTransform3D& other) {
	this->mTranslation_localToParent = other.mTranslation_localToParent;
	this->mRotation_localToParent = other.mRotation_localToParent;
	this->mTotal_localToParent = other.mTotal_localToParent;
}

CoordTransform3D::CoordTransform3D(glm::dvec3 translation_localToParent, glm::dmat4 rotation_localToParent) :
	mTranslation_localToParent(translate(glm::dmat4(1.0), translation_localToParent)),
	mRotation_localToParent(rotation_localToParent),
	mTotal_localToParent(mTranslation_localToParent * rotation_localToParent)
{ }

void CoordTransform3D::setLocalToParent_translation(glm::dmat4 translation_localToParent) {
	mTranslation_localToParent = translation_localToParent;
	updateTotalTransform_localToParent();
}

void CoordTransform3D::setLocalToParent_translation(glm::dvec3 translation_localToParent) {
	mTranslation_localToParent = translate(glm::dmat4(1.0), translation_localToParent);
	updateTotalTransform_localToParent();
}

void CoordTransform3D::setLocalToParent_rotation(glm::dmat4 rotation_localToParent) {
	mRotation_localToParent = rotation_localToParent;
	updateTotalTransform_localToParent();
}

void CoordTransform3D::setLocalToParent_rotation(glm::dquat rotation_localToParent) {
	mRotation_localToParent = glm::toMat4(rotation_localToParent);
	updateTotalTransform_localToParent();
}

void CoordTransform3D::lerp(const CoordTransform3D &dest, double x) {
	mTranslation_localToParent = glm::interpolate(mTranslation_localToParent, dest.mTranslation_localToParent, x);
	mRotation_localToParent = glm::interpolate(mRotation_localToParent, dest.mRotation_localToParent, x);

	updateTotalTransform_localToParent();
}

void CoordTransform3D::updateTotalTransform_localToParent() {
	mTotal_localToParent = mTranslation_localToParent * mRotation_localToParent;
}

CoordTransform3D lerp(const CoordTransform3D &a, const CoordTransform3D &b, double x) {
	CoordTransform3D output;

	output.mTranslation_localToParent = glm::interpolate(a.mTranslation_localToParent, b.mTranslation_localToParent, x);

	output.mRotation_localToParent =
		glm::mat4_cast(
			glm::slerp(
				glm::quat_cast(a.mRotation_localToParent),
				glm::quat_cast(b.mRotation_localToParent),
				x
			)
		);

	output.updateTotalTransform_localToParent();

	return output;
}