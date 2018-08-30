#include "Input.h"

namespace GF {

	Window* Input::mWindow = nullptr;
	
	bool
		Input::mKeysPressed[MAX_KEYS],
		Input::mKeysReleased[MAX_KEYS],
		Input::mMouseButtonsPressed[MAX_BUTTONS],
		Input::mMouseButtonsReleased[MAX_BUTTONS],
		Input::mCursorJustHidden = false,
		Input::mFocusJustCaptured = true,
		Input::mCursorHidden;

	float Input::mMouseScroll = 0.0f;

	glm::dvec2 
		Input::mMousePosition,
		Input::mMousePositionPrev,
		Input::mMouseDelta;	

	void Input::init(Window* window) {
		mWindow = window;

		setAllCallbacks();

		for (int i = 0; i < MAX_KEYS; i++) {
			mKeysPressed[i] = false;
			mKeysReleased[i] = false;
		}

		for (int i = 0; i < MAX_BUTTONS; i++) {
			mMouseButtonsPressed[i] = false;
			mMouseButtonsReleased[i] = false;
		}
	}

	void Input::update() {
		mMouseScroll = 0.0f;

		//if (!mFocusJustCaptured) {
		//	if (mCursorJustHidden) {
		//		mMouseDelta = glm::vec2(0.0);
		//		mCursorJustHidden = false;
		//	}
		//	else
		//		mMouseDelta = mMousePosition - mMousePositionPrev;

		//	mMousePositionPrev = mMousePosition;
		//}
		
		//if(mCursorJustHidden)
		//	mCursorJustHidden = false;

		mMouseDelta = mMousePosition - mMousePositionPrev;
		mMousePositionPrev = mMousePosition;
	}

	bool Input::isKeyPressed(unsigned short keycode) {
		return keycode > MAX_KEYS ? false : mKeysPressed[keycode];
	}

	bool Input::isKeyReleased(unsigned short keycode) {
		if (keycode > MAX_KEYS)
			return false;
		
		if (mKeysReleased[keycode] == true) {
			mKeysReleased[keycode] = false;
			return true;
		}

		return false;
	}
	
	bool Input::isMouseButtonPressed(unsigned char button) {
		return button > MAX_BUTTONS ? false : mMouseButtonsPressed[button];
	}

	bool Input::isMouseButtonReleased(unsigned char button) {
		if (button > MAX_BUTTONS)
			return false;
		
		if (mMouseButtonsReleased[button] == true) {
			mMouseButtonsReleased[button] = false;
			return true;
		}
		
		return false;
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
		glfwSetWindowUserPointer(window, (GLvoid*)0); //Give the window to this class temporarily

		glfwSetKeyCallback(window, keyCallback);
		glfwSetMouseButtonCallback(window, mouseButtonCallback);
		glfwSetScrollCallback(window, scrollCallback);
		glfwSetCursorPosCallback(window, mousePositionCallback);
		glfwSetWindowCloseCallback(window, windowCloseCallback);
		glfwSetFramebufferSizeCallback(window, windowFrameBufferSizeCallback);

		glfwSetWindowUserPointer(window, window); //Hand it back to the original window (that was passed in)
	}

	void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		//Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));

		//This check is needed because extra keys on big keyboard (like volume wheels, mute buttons, play buttons)
		// - basically all non-standard keys - are not recognised by glfw and their key code is -1. This will
		//obviously cause an array out of bounds exception, when trying to index the arrays with -1.
		if (key >= 0 && key < MAX_KEYS) {
			if (action == GLFW_RELEASE) {
				mKeysPressed[key] = false;
				mKeysReleased[key] = true;
			}
			else {
				mKeysPressed[key] = true;
				mKeysReleased[key] = false;
			}
		}
	}

	void Input::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
		mMouseScroll += (float)yoffset;
	}

	void Input::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
		if (button >= 0 && button < MAX_BUTTONS) {
			if (action == GLFW_RELEASE) {
				mMouseButtonsPressed[button] = false;
				mMouseButtonsReleased[button] = true;
			}
			else if(action == GLFW_PRESS) {
				mMouseButtonsPressed[button] = true;
				mMouseButtonsReleased[button] = false;
			}
		}
	}

	void Input::mousePositionCallback(GLFWwindow* window, double xPos, double yPos) {
		if (mFocusJustCaptured) {
			//mMousePositionPrev = glm::vec2(xPos, yPos);
			mFocusJustCaptured = false;
		}

		mMousePosition = { xPos, yPos };
	}

	void Input::windowCloseCallback(GLFWwindow* window) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	void Input::windowFrameBufferSizeCallback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
		mWindow->setDimensions({ width, height });
	}

}