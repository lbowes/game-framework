#include "Input.h"
#include "../Utils/ConsoleLogger.h"

namespace Framework {

	Window* Input::mWindow = nullptr;
	
	bool 
		Input::mKeysPressed[MAX_KEYS],
		Input::mKeysReleased[MAX_KEYS],
		Input::mMouseButtonsPressed[MAX_BUTTONS],
		Input::mMouseButtonsReleased[MAX_BUTTONS],
		Input::mControllerButtonsPressed[MAX_BUTTONS],
		Input::mControllerButtonsReleased[MAX_BUTTONS],
		Input::mCursorJustHidden = false,
		Input::mFocusJustCaptured = true,
		Input::mControllerConnected = glfwJoystickPresent(GLFW_JOYSTICK_1);
	
	float Input::mMouseScroll = 0.0f;
	
	int 
		Input::mJoystickAxisCount = 0,
		Input::mControllerButtonCount = 0;

	float Input::mJoystickAxes[MAX_JOYSTICK_AXES];

	std::string Input::mLastJoystickName = "NO_JOYSTICK";

	glm::vec2 
		Input::mMousePosition,
		Input::mMousePositionPrev,
		Input::mMouseDelta;	

	void Input::init(Window* window) {
		mWindow = window;

		setAllCallbacks();

		//Handling the case where a controller is connected before the application starts
		if (glfwJoystickPresent(GLFW_JOYSTICK_1)) {
			mControllerConnected = true;
			refreshJoystickState();
		}

		for (int i = 0; i < MAX_KEYS; i++) {
			mKeysPressed[i] = false;
			mKeysReleased[i] = false;
		}

		for (int i = 0; i < MAX_BUTTONS; i++) {
			mMouseButtonsPressed[i] = false;
			mMouseButtonsReleased[i] = false;
		}

		for (int i = 0; i < MAX_BUTTONS; i++) {
			mControllerButtonsPressed[i] = false;
			mControllerButtonsReleased[i] = false;
		}
	}

	void Input::update() {
		mMouseScroll = 0.0f;

		if (!mFocusJustCaptured) {
			if (mCursorJustHidden) {
				mMouseDelta = glm::vec2(0.0);
				mCursorJustHidden = false;
			}
			else
				mMouseDelta = mMousePosition - mMousePositionPrev;

			mMousePositionPrev = mMousePosition;
		}

		if (mControllerConnected && glfwJoystickPresent(GLFW_JOYSTICK_1)) {
			int count;

			//Update controller joystick state
			const float* controllerAxes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &count);
			
			for (unsigned char i = 0; i < count; i++)
				mJoystickAxes[i] = controllerAxes[i];

			//Update controller button state
			const unsigned char* controllerButtons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &count);
			for (unsigned char i = 0; i < count; i++) {
				if (controllerButtons[i] == GLFW_RELEASE) {
					mControllerButtonsPressed[i] = false;
					mControllerButtonsReleased[i] = true;
				}
				else {
					mControllerButtonsPressed[i] = true;
					mControllerButtonsReleased[i] = false;
				}
			}
		}
		else {
			for (unsigned char i = 0; i < mJoystickAxisCount; i++)
				mJoystickAxes[i] = 0.0;

			for (unsigned char i = 0; i < mControllerButtonCount; i++) {
				mControllerButtonsPressed[i] = false;
				mControllerButtonsReleased[i] = false;
			}
		}
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

	bool Input::isControllerButtonPressed(unsigned char button) {
		return button > mControllerButtonCount ? false : mControllerButtonsPressed[button];
	}

	bool Input::isControllerButtonReleased(unsigned char button) {
		if (button > mControllerButtonCount)
			return false;

		if (mControllerButtonsReleased[button] == true) {
			mControllerButtonsReleased[button] = false;
			return true;
		}

		return false;
	}

	void Input::showCursor() {
		glfwSetInputMode(mWindow->getHandle(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	void Input::hideCursor() {
		glfwSetInputMode(mWindow->getHandle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		if(mCursorJustHidden = false)
			mCursorJustHidden = true;
	}

	glm::vec2 Input::getMousePosition() {
		return glfwGetWindowAttrib(mWindow->getHandle(), GLFW_FOCUSED) ? mMousePosition : glm::vec2(-1.0f);
	}

	float Input::getJoystickAxis(unsigned char axis) {
		if (mControllerConnected && axis >= 0 && axis < mJoystickAxisCount)
			return mJoystickAxes[axis];
		else
			return 0.0f;
	}

	void Input::setMousePosition(glm::vec2 newMousePosition) {
		glfwSetCursorPos(mWindow->getHandle(), newMousePosition.x, newMousePosition.y);
		mMousePosition = newMousePosition;
	}

	void Input::setAllCallbacks() {
		GLFWwindow* tempWindow = mWindow->getHandle();
		glfwSetWindowUserPointer(tempWindow, (GLvoid*)0); //Give the window to this class temporarily

		glfwSetKeyCallback(tempWindow, keyCallback);
		glfwSetMouseButtonCallback(tempWindow, mouseButtonCallback);
		glfwSetScrollCallback(tempWindow, scrollCallback);
		glfwSetCursorPosCallback(tempWindow, mousePositionCallback);
		glfwSetWindowCloseCallback(tempWindow, windowCloseCallback);
		glfwSetFramebufferSizeCallback(tempWindow, windowFrameBufferSizeCallback);
		glfwSetJoystickCallback(joystickEventCallback);

		glfwSetWindowUserPointer(tempWindow, tempWindow); //Hand it back to the original window (that was passed in)
	}

	void Input::refreshJoystickState() {
		glfwGetJoystickAxes(GLFW_JOYSTICK_1, &mJoystickAxisCount);
		glfwGetJoystickButtons(GLFW_JOYSTICK_1, &mControllerButtonCount);
		mLastJoystickName = glfwGetJoystickName(GLFW_JOYSTICK_1);
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
			else {
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
		
		mMousePosition = glm::vec2(xPos, yPos);
	}

	void Input::windowCloseCallback(GLFWwindow* window) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	void Input::windowFrameBufferSizeCallback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);

		mWindow->setWidth(width);
		mWindow->setHeight(height);
	}

	void Input::joystickEventCallback(int joy, int event) {
		using namespace Utils;
		
		if (event == GLFW_CONNECTED) {
			mControllerConnected = true;
			refreshJoystickState();

			std::string info = "Controller """ + mLastJoystickName + " connected with " + std::to_string(mJoystickAxisCount) + " joystick axes\n";
			ConsoleLogger::log(ConsoleLogger::LogType::INFO, info);
		}
		else if (event == GLFW_DISCONNECTED) {
			mControllerConnected = false;
			mJoystickAxisCount = 0;
			mControllerButtonCount = 0;

			std::string info = "Controller """ + mLastJoystickName + " disconnected\n";
			ConsoleLogger::log(ConsoleLogger::LogType::INFO, info);
		}
	}

}