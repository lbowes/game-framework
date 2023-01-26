#ifndef GF_INPUT_H
#define GF_INPUT_H
#pragma once

#include "Window.h"

#include <glm/vec2.hpp>

#define MAX_KEYS 1024
#define MAX_BUTTONS 16

namespace GF {

	class Input {
	private:
		static Window* mWindow;

		static bool
			mKeysDown[MAX_KEYS],
			mKeysDown_previous[MAX_KEYS],
			mMouseButtonsDown[MAX_BUTTONS],
			mMouseButtonsDown_previous[MAX_BUTTONS],
			mCursorJustHidden,
			mWindowFocused,
			mControllerConnected,
			mCursorHidden,
			mMouseDragging;

		static float mMouseScroll;

		static glm::dvec2
			mMousePosition,
			mMousePositionPrev,
			mMouseMoveDelta;

	public:
		static void init(Window* window);
		static void update();

		static bool isKeyDown(unsigned short keycode);
		static bool isKeyUp(unsigned short keycode);
		static bool isKeyPressed(unsigned short keycode);
		static bool isKeyReleased(unsigned short keycode);

		static bool isMouseButtonDown(unsigned char button);
		static bool isMouseButtonUp(unsigned char button);
		static bool isMouseButtonPressed(unsigned char button);
		static bool isMouseButtonReleased(unsigned char button);

		static bool isControllerButtonPressed(unsigned char button);
		static bool isControllerButtonReleased(unsigned char button);
		static void showCursor();
		static void hideCursor();

		static glm::vec2 getMousePosition() { return mMousePosition;}
		static float getMouseX() { return mMousePosition.x; }
		static float getMouseY() { return mMousePosition.y; }
		static float getMouseScroll() { return mMouseScroll; }
		static bool isCursorHidden();

		static void setMousePosition(glm::vec2 newMousePosition);
		static void setMouseX(float x) { mMousePosition.x = x; }
		static void setMouseY(float y) { mMousePosition.y = y; }
		static void setMouseScroll(float newValue) { mMouseScroll = newValue; }

	private:
		static void loadImGuiKeys();
		static void setAllCallbacks();
		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void mousePositionCallback(GLFWwindow* window, double xPos, double yPos);
		static void windowCloseCallback(GLFWwindow* window);
		static void windowFrameBufferSizeCallback(GLFWwindow* window, int width, int height);
		static void windowFocusCallback(GLFWwindow* window, int focused);
		static void windowRefreshCallback(GLFWwindow* window);

	};

}

#endif
