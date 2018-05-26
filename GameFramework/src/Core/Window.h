#ifndef WINDOW_H
#define WINDOW_H
#pragma once

#include <iostream>

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm/vec4.hpp>
#include <SOIL/SOIL.h>

//#define GLEW_STATIC

namespace Framework {

	class Window {
		friend class Application;
	public:
		static bool mOpenGLInitialised;

	private:
		int 
			mWidth = 0, 
			mHeight = 0, 
			mResolutionWidth = 0, 
			mResolutionHeight = 0;

		const float mWindowToScreenScale = 0.6f;
		
		const char* mTitle = "";
		
		GLFWwindow* mWindow = nullptr;
		
		GLFWmonitor* mMonitor = nullptr;
		
		glm::vec4 mClearColour = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);

		bool mFocusOnCreation = false;

	public:
		Window(std::string title, bool focusOnCreation = false);
		~Window();

		inline GLFWwindow* getHandle() const { return mWindow; }
		inline int getWidth() const { return mWidth; }
		inline int getHeight() const { return mHeight; }
		inline float getAspect() const { return static_cast<float>(mWidth) / mHeight; }
		inline bool isClosed() const { return glfwWindowShouldClose(mWindow) == 1;  }
		inline glm::vec4& getClearColour() { return mClearColour; }

		inline void setWidth(int newWidth) { mWidth = newWidth; }
		inline void setHeight(int newHeight) { mHeight = newHeight; }
		inline void setClearColour(glm::vec4 newClearColour) { mClearColour = newClearColour; }
		inline void close() { glfwSetWindowShouldClose(mWindow, GL_TRUE); }
		void setIcon(std::string iconImagePath);

	private:
		bool init();
		void setResolution();
		void clear() const;
		void update() const;

	};

}

#endif
