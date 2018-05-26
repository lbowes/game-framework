#include "Application.h"
#include "../Utils/ConsoleLogger.h"
#include <Windows.h>
#include <time.h>

namespace Framework {

	Application::Application(std::string windowTitle, std::string iconImagePath, bool focusOnCreation) :
		mWindow(windowTitle, focusOnCreation)
	{
		init();

		if(iconImagePath != "")
			mWindow.setIcon(iconImagePath);
	}

	Application::~Application() {
		//IMGUI
		ImGui_ImplGlfwGL3_Shutdown();
	}

	void Application::init() {
		HWND consoleWindow = GetConsoleWindow();
		SetWindowPos(consoleWindow, 0, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE);

		Input::init(&mWindow);
		Utils::ConsoleLogger::open(/*"src/ErrorLog.txt"*/);

		srand(time(NULL));

		//IMGUI
		ImGui_ImplGlfwGL3_Init(mWindow.getHandle());
	}

	void Application::run() {
		while (mRunning) {
			mNumFrames++;
			mRunning = !glfwWindowShouldClose(mWindow.getHandle());

			mCurrentTime = glfwGetTime();
			mFrameTime = mCurrentTime - mLastTime;
			mLastTime = mCurrentTime;
			mAccumulator += mFrameTime;

			//IMGUI
			ImGui_ImplGlfwGL3_NewFrame();

			onInputCheck();
			Input::update();

			while (mAccumulator >= mUpdateDelta) {
				mAccumulator -= mUpdateDelta;
				onUpdate();
			}

			render();
		}
	}

	void Application::render() {
		mWindow.clear();

		onRender();
		
		//IMGUI on top of everything else
		GLint mode[2];
		glGetIntegerv(GL_POLYGON_MODE, mode);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		ImGui::Render();
		glPolygonMode(GL_FRONT_AND_BACK, *mode);

		mWindow.update();
	}

}