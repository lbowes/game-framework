#include "CoordTransform3D.h"

namespace GF {

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

	CoordTransform3D::CoordTransform3D(glm::dvec3 translation_localToParent) :
		mTranslation_localToParent(glm::translate(translation_localToParent)),
		mRotation_localToParent(glm::dmat4(1.0)),
		mTotal_localToParent(mTranslation_localToParent * mRotation_localToParent)
	{ }

	CoordTransform3D::CoordTransform3D(glm::dvec3 translation_localToParent, glm::dquat rotation_localToParent) :
		mTranslation_localToParent(translate(translation_localToParent)),
		mRotation_localToParent(toMat4(rotation_localToParent)),
		mTotal_localToParent(mTranslation_localToParent * mRotation_localToParent)
	{ }

	CoordTransform3D::CoordTransform3D(glm::dmat4 translation_localToParent, glm::dmat4 rotation_localToParent) :
		mTranslation_localToParent(translation_localToParent),
		mRotation_localToParent(rotation_localToParent),
		mTotal_localToParent(translation_localToParent * rotation_localToParent)
	{ }

	void CoordTransform3D::setLocalToParent_position(glm::dmat4 translation_localToParent) {
		mTranslation_localToParent = translation_localToParent;
		updateTotalTransform_localToParent();
	}

	void CoordTransform3D::setLocalToParent_position(glm::dvec3 translation_localToParent) {
		mTranslation_localToParent = translate(translation_localToParent);
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

	void CoordTransform3D::updateTotalTransform_localToParent() {
		mTotal_localToParent = mTranslation_localToParent * mRotation_localToParent;
	}

}