#ifndef APPLICATION_H
#define APPLICATION_H
#pragma once

#include "Window.h"
#include "../Input/Input.h"
#include "ResourceSet.h"
#include "../Imgui/imgui_impl_glfw_gl3.h"
#include "../Imgui/imgui.h"

namespace Framework {
	class Application {
	protected:
		Window mWindow;
		ResourceSet mResourceSet;

		const double mUpdateDelta = 1.0 / 2000.0;
		
		double
			mCurrentTime = 0.0,
			mLastTime = 0.0,
			mFrameTime = 0.0,
			mAccumulator = 0.0;

		bool mRunning = true;
		
		unsigned int mNumFrames = 0;

	public:
		Application(std::string windowTitle = "Application", std::string iconImagePath = "", bool focusOnCreation = true);
		virtual ~Application();

		void init();
		void run();

		virtual	void onLoad() = 0;
		virtual void onInputCheck() = 0;
		virtual void onUpdate() = 0;
		virtual void onRender() = 0;

	private:
		void render();

	};
}

#endif
