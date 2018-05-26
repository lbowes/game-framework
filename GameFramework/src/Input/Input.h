#ifndef INPUT_H
#define INPUT_H
#pragma once

#include <glm/glm/vec2.hpp>

#include "../Core/Window.h"

#define MAX_KEYS 1024
#define MAX_BUTTONS 16
#define MAX_JOYSTICK_AXES 8

namespace Framework {
	
	class Input {
	public:
		enum JoystickAxes { LEFT_HORIZONTAL, LEFT_VERTICAL, RIGHT_HORIZONTAL, RIGHT_VERTICAL };
	
	private:
		static Window* mWindow;
		
		static bool 
			mKeysPressed[MAX_KEYS],
			mKeysReleased[MAX_KEYS],
			mMouseButtonsPressed[MAX_BUTTONS],
			mMouseButtonsReleased[MAX_BUTTONS],
			mControllerButtonsPressed[MAX_BUTTONS],
			mControllerButtonsReleased[MAX_BUTTONS],
			mCursorJustHidden,
			mFocusJustCaptured,
			mControllerConnected;

		static float mMouseScroll;
		
		static int
			mJoystickAxisCount,
			mControllerButtonCount;

		static float mJoystickAxes[MAX_JOYSTICK_AXES];

		static std::string mLastJoystickName;

		static glm::vec2 
			mMousePosition,
			mMousePositionPrev,
			mMouseDelta;

	public:
		static void init(Window* window);
		static void update();

		static bool isKeyPressed(unsigned short keycode);
		static bool isKeyReleased(unsigned short keycode);
		static bool isMouseButtonPressed(unsigned char button);
		static bool isMouseButtonReleased(unsigned char button);
		static bool isControllerButtonPressed(unsigned char button);
		static bool isControllerButtonReleased(unsigned char button);
		static void showCursor();
		static void hideCursor();

		static glm::vec2 getMousePosition();
		static inline glm::vec2 getMouseDelta() { return mMouseDelta; }
		static inline double getMouseX() { return mMousePosition.x; }
		static inline double getMouseY() { return mMousePosition.y; }
		static inline double getMouseScroll() { return mMouseScroll; }
		static float getJoystickAxis(unsigned char axis);

		static void setMousePosition(glm::vec2 newMousePosition);
		static inline void setMouseX(double x) { mMousePosition.x = x; }
		static inline void setMouseY(double y) { mMousePosition.y = y; }
		static inline void setMouseScroll(float newValue) { mMouseScroll = newValue; }
		static inline bool isControllerConnected() { return mControllerConnected; }

	private:
		static void setAllCallbacks();
		static void refreshJoystickState();
		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void mousePositionCallback(GLFWwindow* window, double xPos, double yPos);
		static void windowCloseCallback(GLFWwindow* window);
		static void windowFrameBufferSizeCallback(GLFWwindow* window, int width, int height);
		static void joystickEventCallback(int joy, int event);

	};

}

#endif
