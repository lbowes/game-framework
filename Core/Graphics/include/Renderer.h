#ifndef RENDERER_H
#define RENDERER_H
#pragma once

#include "Camera.h"
#include "RenderQueue.h"

namespace GF {
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

			RenderQueue& getQueue() { return mQueue; }
			Camera* getCamera() const { return mCurrentlyBound; }

		};
	}
}

#endif
