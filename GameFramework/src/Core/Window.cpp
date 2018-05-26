#include "Window.h"
#include "../Utils/ConsoleLogger.h"

namespace Framework {

	bool Window::mOpenGLInitialised = false;

	Window::Window(std::string title, bool focusOnCreation) : 
		mTitle(title.c_str()),
		mFocusOnCreation(focusOnCreation)
	{
		using namespace Utils;

		if (!init()) {
			std::string error = "Window could not be initialised!";
			ConsoleLogger::log(ConsoleLogger::LogType::ERROR_HALT, error);
			glfwTerminate();
		}
	}

	Window::~Window() {
		glfwDestroyWindow(mWindow);
		glfwTerminate();
	}

	void Window::setIcon(std::string iconImagePath) {
		using namespace Utils;
		
		GLFWimage icon;

		icon.pixels = 0;
		icon.pixels = SOIL_load_image(iconImagePath.c_str(), &icon.width, &icon.height, 0, SOIL_LOAD_RGBA);

		if (icon.pixels == 0) {
			std::string error = "Icon image '" + iconImagePath + "': " + SOIL_last_result();
			ConsoleLogger::log(ConsoleLogger::LogType::ERROR_WARN, error);
		}
		else
			glfwSetWindowIcon(mWindow, 1, &icon);

		SOIL_free_image_data(icon.pixels);
	}

	bool Window::init() {
		using namespace Utils;

		if (!glfwInit()) {
			ConsoleLogger::log(ConsoleLogger::LogType::ERROR_HALT, "Error initialising GLFW!");
			return false;
		}

		mMonitor = glfwGetPrimaryMonitor();

		setResolution();
		mWidth = mResolutionWidth * mWindowToScreenScale;
		mHeight = mResolutionHeight * mWindowToScreenScale;

		//Gets rid of title bar
		//glfwWindowHint(GLFW_DECORATED, false);

		if (mFocusOnCreation) {
			glfwWindowHint(GLFW_FOCUSED, true);
			glfwWindowHint(GLFW_FLOATING, true);
		}

		mWindow = glfwCreateWindow(mWidth, mHeight, mTitle, /*mMonitor*/nullptr, nullptr);
		glfwSetWindowPos(mWindow, mResolutionWidth * 0.5f - mWidth * 0.5f, mResolutionHeight * 0.5f - mHeight * 0.5f);

		if (!mWindow) {
			ConsoleLogger::log(ConsoleLogger::LogType::ERROR_HALT, "Error creating window!");
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(mWindow);
		glewExperimental = GL_TRUE;

		if (glewInit() != GLEW_OK) {
			ConsoleLogger::log(ConsoleLogger::LogType::ERROR_HALT, "Error initialising GLEW!");
			return false;
		}
		else
			mOpenGLInitialised = true;

		return true;
	}

	void Window::setResolution() {
		const GLFWvidmode* mode = glfwGetVideoMode(mMonitor);
		mResolutionWidth = mode->width;
		mResolutionHeight = mode->height;
	}

	void Window::clear() const {
		glClearColor(mClearColour.r, mClearColour.g, mClearColour.b, mClearColour.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::update() const {
		glfwPollEvents();
		glfwSwapBuffers(mWindow);
	}

}