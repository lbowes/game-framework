#include "Window.h"
#include "Logger.h"

namespace GF {

	bool Window::mOpenGLInitialised = false;

	Window::Window(const std::string& title, bool focusOnCreation) : 
		mTitle(title.c_str()),
		mFocusOnCreation(focusOnCreation)
	{
		using namespace Utils;

		if (!init())
			glfwTerminate();
	}

	Window::~Window() {
		glfwDestroyWindow(mWindow);
		glfwTerminate();
	}

	void Window::setIcon(const std::string& iconPath) {
		GLFWimage icon;

		int bpp = 0;

		icon.pixels = 0;
		icon.pixels = stbi_load(iconPath.c_str(), &icon.width, &icon.height, &bpp, 4);

		if (icon.pixels == 0)
			Utils::Logger::log(Utils::Logger::LogType::ERROR_WARN, "Icon image '" + iconPath + "' could not be loaded.");
		else
			glfwSetWindowIcon(mWindow, 1, &icon);

		stbi_image_free(icon.pixels);
	}

	bool Window::init() {
		using namespace Utils;

		if (!glfwInit()) {
			Logger::log(Logger::LogType::ERROR_HALT, "GLFW initialisation error.");
			return false;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		mMonitor = glfwGetPrimaryMonitor();

		setResolution();
		mDimensions.x = mMonitorResolution.x * mWindowToScreenScale;
		mDimensions.y = mMonitorResolution.y * mWindowToScreenScale;

		//Gets rid of title bar
		//glfwWindowHint(GLFW_DECORATED, false);

		//if (mFocusOnCreation) {
			//glfwWindowHint(GLFW_FOCUSED, true);
			//glfwWindowHint(GLFW_FLOATING, true);
		//}

		mWindow = glfwCreateWindow(mDimensions.x, mDimensions.y, mTitle, /*mMonitor*/nullptr, nullptr);
		glfwSetWindowPos(mWindow, static_cast<int>(mMonitorResolution.x * 0.5f - mDimensions.x * 0.5f), static_cast<int>(mMonitorResolution.y * 0.5f - mDimensions.y * 0.5f));

		if (!mWindow) {
			Logger::log(Logger::LogType::ERROR_HALT, "Window creation error.");
			return false;
		}

		glfwMakeContextCurrent(mWindow);
		glewExperimental = GL_TRUE;

		if (glewInit() != GLEW_OK) {
			Logger::log(Logger::LogType::ERROR_HALT, "GLEW initialisation error.");
			return false;
		}
		else
			mOpenGLInitialised = true;

		return true;
	}

	void Window::setResolution() {
		const GLFWvidmode* mode = glfwGetVideoMode(mMonitor);
		mMonitorResolution.x = mode->width;
		mMonitorResolution.y = mode->height;
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