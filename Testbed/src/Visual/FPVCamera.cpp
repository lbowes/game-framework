#include "FPVCamera.h"

FPVCamera::FPVCamera(glm::dvec3 position_OGL, glm::vec3 direction_OGL, float near, float far, float aspect, float FOV) :
	mPerspectiveCamera(position_OGL, glm::vec3(), glm::vec3(), near, far, aspect, FOV),
	mPosition_OGL(position_OGL),
	mDirection_OGL(direction_OGL)
{
	using namespace glm;

	mPerspectiveCamera.setFront(direction_OGL);
	mPerspectiveCamera.setUp({ 0.0f, 1.0f, 0.0f });

	//Calculating intial yaw and pitch values from direction vector
	vec3 horizontalDirection = normalize(vec3(direction_OGL.x, 0.0f, direction_OGL.z));
	mYaw = degrees(orientedAngle(horizontalDirection, { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }));
	mPitch = degrees(asin(normalize(direction_OGL).y));
}

void FPVCamera::update(float windowAspect, float dt) {
	mPerspectiveCamera.setAspect(windowAspect);

	mPosition_OGL += mVelocity_OGL * dt;
	mPerspectiveCamera.setPosition(mPosition_OGL);

	mVelocity_OGL *= 1.0f / (1.0f + (dt * mMovementFriction));
}

void FPVCamera::handleInput(float dt) {
	handleDirectionInput();
	handleMovementInput(dt);
	handleZoomInput();
}

void FPVCamera::handleDirectionInput() {
	glm::vec2 mouseDelta = GF::Input::getMouseDelta();

	mYaw += mouseDelta.x * mLookAroundSensitivity;
	mPitch -= mouseDelta.y * mLookAroundSensitivity;

	if (mPitch > 89.0f) mPitch = 89.0f;
	if (mPitch < -89.0f) mPitch = -89.0f;

	mDirection_OGL.x = cos(glm::radians(mPitch)) * cos(glm::radians(mYaw));
	mDirection_OGL.y = sin(glm::radians(mPitch));
	mDirection_OGL.z = cos(glm::radians(mPitch)) * sin(glm::radians(mYaw));
	mDirection_OGL = normalize(mDirection_OGL);

	mPerspectiveCamera.setFront(mDirection_OGL);
}

void FPVCamera::handleMovementInput(float dt) {
	using namespace GF;
	using namespace glm;

	if (Input::isKeyPressed(GLFW_KEY_W))          mVelocity_OGL += normalize(vec3(mDirection_OGL.x, 0.0f, mDirection_OGL.z)) * mMovementSpeed * dt;
	if (Input::isKeyPressed(GLFW_KEY_S))          mVelocity_OGL -= normalize(vec3(mDirection_OGL.x, 0.0f, mDirection_OGL.z)) * mMovementSpeed * dt;
	if (Input::isKeyPressed(GLFW_KEY_A))          mVelocity_OGL -= normalize(cross(mDirection_OGL, vec3(0.0f, 1.0f, 0.0f))) *  mMovementSpeed * dt;
	if (Input::isKeyPressed(GLFW_KEY_D))          mVelocity_OGL += normalize(cross(mDirection_OGL, vec3(0.0f, 1.0f, 0.0f))) *  mMovementSpeed * dt;
	if (Input::isKeyPressed(GLFW_KEY_SPACE))      mVelocity_OGL.y += mMovementSpeed * dt;
	if (Input::isKeyPressed(GLFW_KEY_LEFT_SHIFT)) mVelocity_OGL.y -= mMovementSpeed * dt;
}

void FPVCamera::handleZoomInput() {
	using namespace GF;

	float
		mouseScroll = GF::Input::getMouseScroll(),
		currentFOV = mPerspectiveCamera.getFOVY(),
		newTargetFOV = currentFOV -= mouseScroll * mZoomSensitivity;

	if (newTargetFOV >= 44.0f && newTargetFOV <= 46.0f)
		mPerspectiveCamera.setFOVY(currentFOV -= mouseScroll * mZoomSensitivity);

	if (Input::isMouseButtonReleased(GLFW_MOUSE_BUTTON_5) || Input::isMouseButtonReleased(GLFW_MOUSE_BUTTON_MIDDLE))
		mPerspectiveCamera.setFOVY(45.0f);
}