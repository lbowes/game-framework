#include "Mesh.h"
#include "Renderer/Renderer.h"

namespace Framework {
	namespace Graphics {

		Mesh::Mesh(std::string resourceID, unsigned int geometryType) :
			Resource(resourceID)
		{
			mVAO = std::make_unique<VertexArray>(geometryType);
		}

		Mesh::Mesh(std::string resourceID, unsigned int geometryType, Texture* texture, Shader* shader, glm::mat4 worldTransform) :
			Resource(resourceID),
			mTexture(texture),
			mShader(shader),
			mWorldTransform(worldTransform)
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

			renderer.getQueue().submitCommand(RenderCommand(mTexture, mShader, mVAO.get(), mWorldTransform));
		}

	}
}