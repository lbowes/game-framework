#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"

namespace GF {
	namespace Graphics {

		Renderer::Renderer(Camera* startCamera) :
			mCurrentlyBound(startCamera)
		{ }

		void Renderer::flush() {
			if (mCurrentlyBound == nullptr) {
				mQueue.clear();
				return;	
			}

			glEnable(GL_DEPTH_TEST);
			mQueue.sort();

			Shader* shader = nullptr;
			Texture* texture = nullptr;
			VertexArray* VAO = nullptr;

			for (RenderCommand& c : mQueue.getAllCommands()) {
				shader = c.getShader();
				texture = c.getTexture();
				VAO = c.getVAO();

				shader->bind();
				shader->setUniform("modelMatrix", c.getTransform());
				shader->setUniform("viewMatrix", mCurrentlyBound->getView());
				shader->setUniform("projectionMatrix", mCurrentlyBound->getProjection());

				if(texture) texture->bind();
				if(VAO) VAO->draw();
			}

			mQueue.clear();
		}

		void Renderer::setCamera(Camera& newCamera) {
			if (mCurrentlyBound == &newCamera)
				return;

			mCurrentlyBound = &newCamera;
		}

	}
}