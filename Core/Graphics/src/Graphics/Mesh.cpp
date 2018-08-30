#include "Mesh.h"
#include "Renderer.h"

namespace GF {
	namespace Graphics {

		Mesh::Mesh(const std::string& resID, unsigned geometryType, Texture* texture, Shader* shader, glm::mat4 modelTransform) :
			Resource(resID),
			mTexture(texture),
			mShader(shader),
			mModelTransform(modelTransform)
		{
			mVAO = std::make_unique<VertexArray>(geometryType);
		}

		void Mesh::addBuffer(VertexBuffer* buffer) {
			mVAO->attachBuffer(buffer);
		}

		void Mesh::addIndexBuffer(IndexBuffer* indexBuffer) {
			mVAO->attachIndexBuffer(indexBuffer);
		}

		void Mesh::sendRenderCommand(Renderer& renderer) {
			if (!mVisible) return;

			renderer.getQueue().submitCommand(RenderCommand(mTexture, mShader, mVAO.get(), mModelTransform));
		}

	}
}