#ifndef ORTHOGRAPHICCAMERA_H
#define ORTHOGRAPHICCAMERA_H
#pragma once

#include "Camera.h"

namespace GF {

	class OrthographicCamera : public Camera {
	private:
		float 
			mLeft = 0.0f, 
			mRight = 0.0f, 
			mTop = 0.0f, 
			mBottom = 0.0f;

	public:
		OrthographicCamera(glm::vec3 position, glm::vec3 front, glm::vec3 up, float near, float far, float aspect, float FOV);
		~OrthographicCamera() = default;

	private:
		void updateProjection();

	};

}

#endif
