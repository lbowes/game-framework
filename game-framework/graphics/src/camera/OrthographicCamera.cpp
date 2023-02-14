#include "OrthographicCamera.h"

namespace GF {

	OrthographicCamera::OrthographicCamera(glm::vec3 position, glm::vec3 front, glm::vec3 up, float near, float far, float aspect, float FOV) :
		Camera(position, front, up, near, far, aspect, FOV)
	{
		updateProjection();
	}

	void OrthographicCamera::updateProjection() {
		mProjection = glm::ortho(-mAspect * mFOVY, mAspect * mFOVY, -mFOVY, mFOVY, mNear, mFar);
	}

}