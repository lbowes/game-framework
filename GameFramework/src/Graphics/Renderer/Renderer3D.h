#if 0

#ifndef RENDERER3D_H
#define RENDERER3D_H
#pragma once

#include <memory>
#include <glm\glm\mat4x4.hpp>
#include <glm\glm\gtx\string_cast.hpp>

#include "Camera/Camera.h"

namespace Framework {
	
	class Renderable3D;

	namespace Graphics {
														  
		class Renderer3D {
			friend class Renderable3D;
		private:
			glm::mat4 
				mProjection, 
				mView;
	
			//Camera* mCurrentCamera = nullptr;
			std::shared_ptr<Camera> mCamera;

		public:
			Renderer3D(Camera* startCamera);
			~Renderer3D() = default;

			void bindCamera(Camera* nextCamera);
			void updateViewProjection();
			virtual void render(Framework::Renderable3D& instance);
			
			//inline Camera* getCamera() const { return mCurrentCamera; }
			inline Camera* getCamera() const { return mCamera.get(); }

		private:
			void init();

		};
	}
}

#endif

#endif