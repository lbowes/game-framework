#ifndef RENDERER_H
#define RENDERER_H
#pragma once

#include "../../Camera/Camera.h"
#include "RenderQueue.h"

namespace Framework {
	namespace Graphics {
		class Renderer {
		private:
			Camera* mCurrentlyBound = nullptr;
			RenderQueue mQueue;

		public:
			Renderer(Camera* startCamera = nullptr);
			~Renderer() = default;

			void flush();
			void setCamera(Camera& newCamera);

			inline RenderQueue& getQueue() { return mQueue; }
			inline Camera* getCamera() const { return mCurrentlyBound; }

		};
	}
}

#endif
