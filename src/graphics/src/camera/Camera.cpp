#include "Camera.h"

namespace GF {

	unsigned Camera::mNumCameras = 0;

	Camera::Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up, float near, float far, float aspect, float FOVY) :
		mPosition(position),
		mFixedPosition(position),
		mFront(front),
		mFixedFront(front),
		mUp(up),
		mFixedUp(up),
		mNear(near),
		mFar(far),
		mAspect(aspect),
		mFOVY(FOVY)
	{
		//Default to perspective projection if the user creates a 'Camera' (base class) object, as opposed to 'PerspectiveCamera' etc
		mProjection = glm::perspective(FOVY, aspect, near, far);

		updateView();
	}

	void Camera::operator=(const Camera& other) {
		this->mAspect = other.mAspect;
		this->mNear = other.mNear;
		this->mFar = other.mFar;
		this->mFOVY = other.mFOVY;
		this->mPosition = other.mPosition;
		this->mFixedPosition = other.mFixedPosition;
		this->mFront = other.mFront;
		this->mFixedFront = other.mFixedFront;
		this->mUp = other.mUp;
		this->mFixedUp = other.mFixedUp;
		this->mView = other.mView;
		this->mProjection = other.mProjection;
	}

	void Camera::setAspect(float newAspect) {
		mAspect = newAspect;
		updateProjection();
	}

	void Camera::setFOVY(float newFOVY) {
		mFOVY = newFOVY;
		updateProjection();
	}

	void Camera::setPosition(glm::vec3 newPosition) {
		mPosition = newPosition;
		updateView();
	}

	void Camera::transformPosition(glm::mat4 initialToGoalTransform) {
		mPosition = glm::vec3(initialToGoalTransform * glm::vec4(mFixedPosition, 1.0f));
		updateView();
	}

	void Camera::setFront(glm::vec3 newFront) {
		mFront = normalize(newFront);
		updateView();
	}

	void Camera::rotateFront(glm::quat initialToGoalRotation) {
		mFront = glm::vec3(initialToGoalRotation * glm::vec4(mFixedFront, 1.0f));
		updateView();
	}

	void Camera::setUp(glm::vec3 newUp) {
		mUp = normalize(newUp);
		updateView();
	}

	void Camera::rotateUp(glm::quat initialToGoalRotation) {
		mUp = glm::vec3(initialToGoalRotation * glm::vec4(mFixedUp, 1.0f));
		updateView();
	}

	void Camera::transform(glm::mat4 initialToGoalTransform) {
		mPosition = glm::vec3(initialToGoalTransform * glm::vec4(mFixedPosition, 1.0));
		mFront = glm::vec3(initialToGoalTransform * glm::vec4(mFixedFront, 1.0));
		mUp = glm::vec3(initialToGoalTransform * glm::vec4(mFixedUp, 1.0));

		updateView();
	}

	void Camera::rotate(glm::quat initialToGoalRotation) {
		mFront = glm::vec3(initialToGoalRotation * glm::vec4(mFixedFront, 1.0));
		mUp = glm::vec3(initialToGoalRotation * glm::vec4(mFixedUp, 1.0));

		updateView();
	}

	void Camera::updateView() {
		if(mFront != glm::vec3(0.0) && mUp != glm::vec3(0.0))
			mView = glm::lookAt(mPosition, mPosition + mFront, mUp);
	}

	void Camera::updateProjection() {
		//mProjection = glm::ortho(-mAspect * mFOVY, mAspect * mFOVY, -1 * mFOVY, 1 * mFOVY, mNear, mFar);
		mProjection = glm::perspectiveRH(mFOVY, mAspect, mNear, mFar);
	}

}