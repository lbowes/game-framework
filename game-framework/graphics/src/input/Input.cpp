#include "Input.h"

#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"

namespace GF {

	Window* Input::mWindow = nullptr;

	bool
		Input::mKeysDown[MAX_KEYS],
		Input::mKeysDown_previous[MAX_KEYS],
		Input::mMouseButtonsDown[MAX_BUTTONS],
		Input::mMouseButtonsDown_previous[MAX_BUTTONS],
		Input::mCursorJustHidden = false,
		Input::mWindowFocused = true,
		Input::mCursorHidden = false,
		Input::mMouseDragging= false;

	float Input::mMouseScroll = 0.0f;

	glm::dvec2
		Input::mMousePosition,
		Input::mMousePositionPrev,
		Input::mMouseMoveDelta;

	void Input::init(Window* window) {
		mWindow = window;

		setAllCallbacks();

		for (int i = 0; i < MAX_KEYS; i++) {
			mKeysDown[i] = false;
			mKeysDown_previous[i] = false;
		}

		for (int i = 0; i < MAX_BUTTONS; i++) {
			mMouseButtonsDown[i] = false;
			mMouseButtonsDown_previous[i] = false;
		}
	}

	void Input::update() {
		mMouseScroll = 0.0f;

		mMouseMoveDelta = mMousePosition - mMousePositionPrev;
		mMousePositionPrev = mMousePosition;

		for (int i = 0; i < MAX_KEYS; i++)
			mKeysDown_previous[i] = mKeysDown[i];

		for (int i = 0; i < MAX_BUTTONS; i++)
			mMouseButtonsDown_previous[i] = mMouseButtonsDown[i];
	}

	bool Input::isKeyDown(unsigned short keycode) {
		return keycode > MAX_KEYS ? false : mKeysDown[keycode];
	}

	bool Input::isKeyUp(unsigned short keycode) {
		return keycode > MAX_KEYS ? false : !mKeysDown[keycode];
	}

	bool Input::isKeyPressed(unsigned short keycode) {
		return keycode <= MAX_KEYS && !mKeysDown_previous[keycode] && mKeysDown[keycode];
	}

	bool Input::isKeyReleased(unsigned short keycode) {
		return keycode <= MAX_KEYS && mKeysDown_previous[keycode] && !mKeysDown[keycode];
	}

	bool Input::isMouseButtonDown(unsigned char button) {
		return button > MAX_BUTTONS ? false : mMouseButtonsDown[button];
	}

	bool Input::isMouseButtonUp(unsigned char button) {
		return button > MAX_BUTTONS ? false : !mMouseButtonsDown[button];
	}

	bool Input::isMouseButtonPressed(unsigned char button) {
		return button <= MAX_BUTTONS && !mMouseButtonsDown_previous[button] && mMouseButtonsDown[button];
	}

	bool Input::isMouseButtonReleased(unsigned char button) {
		return button <= MAX_KEYS && mMouseButtonsDown_previous[button] && !mMouseButtonsDown[button];
	}

	void Input::showCursor() {
		glfwSetInputMode(mWindow->getHandle(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		mCursorHidden = false;
	}

	void Input::hideCursor() {
		glfwSetInputMode(mWindow->getHandle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		if(mCursorJustHidden = false)
			mCursorJustHidden = true;

		mCursorHidden = true;
	}

	bool Input::isCursorHidden() {
		return mCursorHidden;
	}

	void Input::setMousePosition(glm::vec2 newMousePosition) {
		glfwSetCursorPos(mWindow->getHandle(), newMousePosition.x, newMousePosition.y);
		mMousePosition = newMousePosition;
	}

	void Input::setAllCallbacks() {
		GLFWwindow* window = mWindow->getHandle();
		glfwSetWindowUserPointer(window, (GLvoid*)0);

		glfwSetKeyCallback(window, keyCallback);
		glfwSetMouseButtonCallback(window, mouseButtonCallback);
		glfwSetScrollCallback(window, scrollCallback);
		glfwSetCursorPosCallback(window, mousePositionCallback);
		glfwSetWindowCloseCallback(window, windowCloseCallback);
		glfwSetFramebufferSizeCallback(window, windowFrameBufferSizeCallback);

		glfwSetWindowUserPointer(window, window);
	}

	void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		//This check is needed because extra keys on big keyboard (like volume wheels, mute buttons, play buttons)
		// - basically all non-standard keys - are not recognised by glfw and their key code is -1. This will
		//obviously cause an array out of bounds exception, when trying to index the arrays with -1.
		if (key >= 0 && key < MAX_KEYS)
			mKeysDown[key] = action == GLFW_PRESS ? true : false;

		ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
	}

	void Input::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
		mMouseScroll += (float)yoffset;
		ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
	}

	void Input::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
		if (button >= 0 && button < MAX_BUTTONS)
			mMouseButtonsDown[button] = action == GLFW_PRESS ? true : false;
	}

	void Input::mousePositionCallback(GLFWwindow* window, double xPos, double yPos) {
		mMousePosition = { xPos, yPos };
	}

	void Input::windowCloseCallback(GLFWwindow* window) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	void Input::windowFrameBufferSizeCallback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
		mWindow->setDimensions({ width, height });
	}

	void Input::windowFocusCallback(GLFWwindow* window, int focused) {
    	mWindowFocused = focused;
	}

	void Input::windowRefreshCallback(GLFWwindow* window) {
		glfwSwapBuffers(window);
	}

}