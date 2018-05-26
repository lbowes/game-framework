#if 0

#include "Objects/Renderable2D.h"
#include "Camera/OrthographicCamera.h"

namespace Framework {
	namespace Graphics {
		
		Renderer2D::Renderer2D(unsigned int screenWidth, unsigned int screenHeight) :
			mCamera(std::make_shared<OrthographicCamera>(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 1.0f, static_cast<float>(screenWidth) / screenHeight, 1.0f))
		{ 
			init();
		}

		Renderer2D::Renderer2D(OrthographicCamera* startCamera) {
			mCamera.reset(startCamera);
			setProjection();
		}

		void Renderer2D::render(Renderable2D& instance) {
			glDisable(GL_DEPTH_TEST);
			instance.render(*this);
		}

		/*void Renderer2D::bindCamera(OrthographicCamera* newCamera) {
			if (!mOwnsCamera && mCamera != newCamera)
				mCamera = newCamera;
		}*/

		void Renderer2D::bindCamera(OrthographicCamera* nextCamera) {
			//mCamera = newCamera;
			mCamera.reset(nextCamera);
		}

		void Renderer2D::init() {
			glDisable(GL_DEPTH_TEST);
			setProjection();
		}

		void Renderer2D::setProjection() {
			mProjection = mCamera->getProjection();
		}

	}
}


#endif