#ifndef CAMERA_H
#define CAMERA_H
#pragma once

#include <glm/glm.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <memory>

#define DEFAULT_FOV 45.0f

namespace GF {

	enum ProjectionType { PERSPECTIVE, ORTHOGRAPHIC };

	class Camera {
	private:
		static unsigned mNumCameras;
	
	protected:
		float 
			mAspect = 0.0f,
			mNear = 0.1f, 
			mFar = 1000.0f,
			mFOVY = 0.0f;

		glm::vec3
			mPosition,
			mFixedPosition,
			mFront,
			mFixedFront,
			mUp,
			mFixedUp;
		
		glm::mat4 
			mView, 
			mProjection;

	public:		 
		Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up, float near, float far, float aspect, float FOVY = DEFAULT_FOV);
		void operator=(const Camera& other);
		~Camera() = default;

		void setAspect(float newAspect);
		void setFOVY(float newFOVY);
		void setPosition(glm::vec3 newPosition);
		void transformPosition(glm::mat4 initialToGoalTransform);
		void setFront(glm::vec3 newFront);
		void rotateFront(glm::quat initialToGoalRotation);
		void setUp(glm::vec3 newUp);
		void rotateUp(glm::quat initialToGoalRotation);
		void transform(glm::mat4 initialToGoalTransform);
		void rotate(glm::quat initialToGoalRotation);

		float getAspect() const { return mAspect; }
		float getFOVY() const { return mFOVY; }
		glm::vec3 getPosition() const { return mPosition; }
		glm::vec3 getFront() const { return mFront; }
		glm::vec3 getUp() const { return mUp; }
		glm::mat4 getView() const { return mView; }
		glm::mat4 getProjection() const { return mProjection; }
		glm::mat4 getViewProjection() const { return mProjection * mView; }

	protected:
		void updateView();
		virtual void updateProjection();

	};

}

#endif