#include "OrthographicCamera.h"

namespace Framework {

	OrthographicCamera::OrthographicCamera(glm::vec3 position, glm::vec3 front, glm::vec3 up, float near, float far, float aspect, float FOV) :
		Camera(position, front, up, near, far, aspect, FOV)
	{
		updateProjection();
	}

	void OrthographicCamera::updateProjection() {
		mProjection = glm::ortho(-mAspect * mFOVY, mAspect * mFOVY, -1 * mFOVY, 1 * mFOVY, mNear, mFar);
	}

}