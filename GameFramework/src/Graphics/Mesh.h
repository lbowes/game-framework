#ifndef MESH_H
#define MESH_H
#pragma once

#include "Texture/Texture2D.h"
#include "Shader.h"             //Consider possibly combinging these two into 'Material.h'
#include "Core/VertexArray.h"

namespace Framework {
	namespace Graphics {

		class Renderer;

		class Mesh : public Resource {
		private:
			Texture* mTexture = nullptr;
			Shader* mShader = nullptr;
			glm::mat4 mWorldTransform;
			
			std::unique_ptr<VertexArray> mVAO;
			bool mVisible = true;

		public:
			Mesh(std::string resourceID, unsigned int geometryType = GL_TRIANGLES);
			Mesh(std::string resourceID, unsigned int geometryType = GL_TRIANGLES, Texture* texture = nullptr, Shader* shader = nullptr, glm::mat4 worldTransform = glm::mat4(1));
			~Mesh() = default;
			
			void addBuffer(VertexBuffer* buffer);
			void addIndexBuffer(IndexBuffer* indexBuffer);
			void sendRenderCommand(Renderer& renderer);

			inline Texture* getTexture() const { return mTexture; }
			inline Shader* getShader() const { return mShader; }
			inline glm::mat4 getWorldTransform() const { return mWorldTransform; }
			inline VertexArray* getVertexArray() const { return mVAO.get(); }
			inline bool isVisible() const { return mVisible; }

			inline void setTexture(Texture* texture) { mTexture = texture; }
			inline void setShader(Shader* shader) { mShader = shader; }
			inline void setWorldTransform(glm::mat4 newWorldTransform) { mWorldTransform = newWorldTransform; }
			inline void setVisibility(bool newVisibility) { mVisible = newVisibility; }

		};

	}
}

#endif
