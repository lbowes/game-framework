#include "Input.h"

namespace GF {

	Window* Input::mWindow = nullptr;
	
	bool
		Input::mKeysPressed[MAX_KEYS],
		Input::mKeysReleased[MAX_KEYS],
		Input::mKeysReleased_previous[MAX_KEYS],
		Input::mMouseButtonsPressed[MAX_BUTTONS],
		Input::mMouseButtonsReleased[MAX_BUTTONS],
		Input::mMouseButtonsReleased_previous[MAX_BUTTONS],
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
			mKeysReleased_previous[i] = false;
		}

		for (int i = 0; i < MAX_BUTTONS; i++) {
			mMouseButtonsPressed[i] = false;
			mMouseButtonsReleased[i] = false;
			mMouseButtonsReleased_previous[i] = false;
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

		for (int i = 0; i < MAX_KEYS; i++)
			mKeysReleased_previous[i] = mKeysReleased[i];

		for (int i = 0; i < MAX_BUTTONS; i++)
			mMouseButtonsReleased_previous[i] = mMouseButtonsReleased[i];
	}

	bool Input::isKeyPressed(unsigned short keycode) {
		return keycode > MAX_KEYS ? false : mKeysPressed[keycode];
	}

	bool Input::isKeyReleased(unsigned short keycode) {
		if (keycode > MAX_KEYS)
			return false;
		
		return mKeysReleased[keycode];
	}
	
	bool Input::isKeyClicked(unsigned short keycode) {
		if (keycode > MAX_KEYS)
			return false;

		//TODO: Implement this
		//Store a separate 'difference' map of key release *changes* between this update and the previous.
		//This should be implemented in the form of a separate array that we iterate through each update.
		//The array should store the release state array of the previous update cycle.
		//Then, in this function, we check whether the mPreviousReleased[KEY] != mCurrentReleased[KEY]

		//For example, if the release state for GLFW_KEY_A was 0 last update and it is now 1, that means
		//the user lifted their finger off the key this update and therefore a click event has occured.

		return !mKeysReleased_previous[keycode] && mKeysReleased[keycode];
	}

	bool Input::isMouseButtonPressed(unsigned char button) {
		return button > MAX_BUTTONS ? false : mMouseButtonsPressed[button];
	}

	bool Input::isMouseButtonReleased(unsigned char button) {
		if (button > MAX_BUTTONS)
			return false;
	
		return mMouseButtonsReleased[button];
	}

	bool Input::isMouseButtonClicked(unsigned char button) {
		//TODO: Implement this - see isKeyClicked()
		
		if (button > MAX_BUTTONS)
			return false;
		
		return !mMouseButtonsReleased_previous[button] && mMouseButtonsReleased[button];
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