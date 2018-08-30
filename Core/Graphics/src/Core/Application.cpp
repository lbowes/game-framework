#include "Application.h"
#include "Logger.h"
#include <time.h>

namespace GF {

	Application::Application(const std::string& windowTitle, const std::string& iconPath, bool focusOnCreation) :
		mWindow(windowTitle, focusOnCreation)
	{
		init();

		if(iconPath != "")
			mWindow.setIcon(iconPath);
	}

	Application::~Application() {
		//IMGUI
		ImGui_ImplGlfwGL3_Shutdown();
		ImGui::DestroyContext();
	}

	void Application::init() {
		//HWND consoleWindow = GetConsoleWindow();
		//SetWindowPos(consoleWindow, 0, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE);

		Input::init(&mWindow);
		//Utils::Logger::open(/*"src/ErrorLog.txt"*/);

		srand((unsigned)time(NULL));

		//IMGUI
		ImGui::CreateContext();
		ImGui_ImplGlfwGL3_Init(mWindow.getHandle(), false);
	}

	void Application::run() {
		while (mRunning) {
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
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
		glPolygonMode(GL_FRONT_AND_BACK, *mode);

		mWindow.update();
	}

}