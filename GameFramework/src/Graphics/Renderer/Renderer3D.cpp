#if 0

#include "Objects/Renderable3D.h"
				  
namespace Framework {
	namespace Renderer {

		Renderer3D::Renderer3D(Camera* startCamera) {
			mCamera.reset(startCamera);

			init();
		}

		void Renderer3D::bindCamera(Camera* nextCamera) {
			mCamera.reset(nextCamera);
			
			/*if (nextCamera != mCurrentCamera)
				mCurrentCamera = nextCamera;*/
		}

		void Renderer3D::updateViewProjection() {
			//mView = mCurrentCamera->getView();
			mView = mCamera->getView();
			
			//mProjection = mCurrentCamera->getProjection();
			mProjection = mCamera->getProjection();
		}

		void Renderer3D::render(Renderable3D& instance) {
			glEnable(GL_DEPTH_TEST);
			instance.render(*this);
		}

		void Renderer3D::init() {
			glEnable(GL_DEPTH_TEST);
			glLineWidth(1.0f);
			
			updateViewProjection();
		}
		
	}
}

#endif