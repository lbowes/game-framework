#ifndef PERSPECTIVECAMERA_H
#define PERSPECTIVECAMERA_H
#pragma once

#include "Camera.h"

namespace Framework {

	class PerspectiveCamera : public Camera {
	public:
		PerspectiveCamera(glm::vec3 position, glm::vec3 front, glm::vec3 up, float near, float far, float aspect, float FOV);
		~PerspectiveCamera() = default;

		inline float getHorizontalFOV() { return mFOVY * mAspect; }
	
	private:
		void updateProjection();

	};

}

#endif
