#include "Renderer.h"
#include "../Shader.h"
#include "../Texture/Texture.h"
#include "../Core/VertexArray.h"

namespace Framework {
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
				shader->setUniform(0, c.getTransform());
				shader->setUniform(1, mCurrentlyBound->getView());
				shader->setUniform(2, mCurrentlyBound->getProjection());

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