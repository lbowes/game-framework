#include "PerspectiveCamera.h"
#include <iostream>

namespace Framework {

	PerspectiveCamera::PerspectiveCamera(glm::vec3 position, glm::vec3 front, glm::vec3 up, float near, float far, float aspect, float FOV) :
		Camera(position, front, up, near, far, aspect, FOV)
	{
		updateProjection();
	}

	void PerspectiveCamera::updateProjection() {
		mProjection = glm::perspective(mFOVY, mAspect, mNear, mFar);
	}

}