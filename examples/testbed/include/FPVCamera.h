#ifndef FPVCAMERA_H
#define FPVCAMERA_H
#pragma once

#include <GraphicsFramework/PerspectiveCamera.h>
#include <GraphicsFramework/Input.h>
#include <GraphicsFramework/Vendor/ImGui/imgui.h>
#include <glm/gtx/vector_angle.hpp>

class FPVCamera {
private:
	GF::PerspectiveCamera mPerspectiveCamera;

	bool mHasFocus = false;

	const float
		mMovementSpeed = 100.0f,        //100.0f
		mMovementFriction = 10.5f,      //7.0f
		mZoomSensitivity = 0.1f,        //0.1f
		mLookAroundSensitivity = 0.05f; //0.05f

	float
		mPitch = 0.0f,
		mYaw = 0.0f;

	glm::vec3
		mPosition_OGL,
		mVelocity_OGL = glm::vec3(0.0f),
		mDirection_OGL;

	ImVec2
		mMousePosition,
		mPrevMousePosition;

public:
	FPVCamera(glm::dvec3 position_OGL, glm::vec3 direction_OGL, float near, float far, float aspect, float FOV);
	~FPVCamera() = default;

	void update(float windowAspect, float dt);
	void handleInput(float dt);

	inline GF::Camera& getInternalCamera() { return mPerspectiveCamera; }
	inline bool hasFocus() const { return mHasFocus; }
	inline void setFocus(bool focus) { mHasFocus = focus; }

private:
	void handleDirectionInput();
	void handleMovementInput(float dt);
	void handleZoomInput();

};

#endif
