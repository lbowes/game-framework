#if 0

#ifndef RENDERER2D_H
#define RENDERER2D_H
#pragma once

#include <memory>
#include <glm\glm\mat4x4.hpp>
#include <glm\glm\gtx\string_cast.hpp>

namespace Framework {
	
	class OrthographicCamera;
	class Renderable2D;
	
	namespace Renderer {
		
		class Renderer2D {
			friend class Renderable2D;
		private:
			glm::mat4 mProjection;

			//This is a shared pointer because the camera could be owned by another class
			std::shared_ptr<OrthographicCamera> mCamera;

		public:
			Renderer2D(unsigned int screenWidth, unsigned int screenHeight);
			Renderer2D(OrthographicCamera* startCamera);
			~Renderer2D() = default;

			virtual void render(Renderable2D& instance);

			inline OrthographicCamera* getCamera() const { return mCamera.get(); }
			void bindCamera(OrthographicCamera* nextCamera);

		private:
			void init();
			void setProjection();

		};

	}
}

#endif
#endif