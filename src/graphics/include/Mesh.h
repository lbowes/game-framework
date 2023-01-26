#ifndef GRAPHICS_MESH_H
#define GRAPHICS_MESH_H
#pragma once

#include "Texture2D.h"	//
#include "Shader.h"             //Consider possibly combinging these two into 'Material.h'
#include "VertexArray.h"

namespace GF {
	namespace Graphics {

		class Renderer;

		class Mesh : public Resource {
		private:
			Texture* mTexture = nullptr;
			Shader* mShader = nullptr;
			glm::mat4 mModelTransform;

			std::unique_ptr<VertexArray> mVAO;
			bool mVisible = true;

		public:
			Mesh(const std::string& resID, unsigned geometryType = GL_TRIANGLES, Texture* texture = nullptr, Shader* shader = nullptr, glm::mat4 modelTransform = glm::mat4(1.0f));
			~Mesh() = default;

			void addBuffer(VertexBuffer* buffer);
			void addIndexBuffer(IndexBuffer* indexBuffer);
			void sendRenderCommand(Renderer& renderer);

			inline Texture* getTexture() const { return mTexture; }
			inline Shader* getShader() const { return mShader; }
			inline glm::mat4 getModelTransform() const { return mModelTransform; }
			inline VertexArray* getVertexArray() const { return mVAO.get(); }
			inline bool isVisible() const { return mVisible; }

			inline void setTexture(Texture* texture) { mTexture = texture; }
			inline void setShader(Shader* shader) { mShader = shader; }
			inline void setModelTransform(glm::mat4 newModelTransform) { mModelTransform = newModelTransform; }
			inline void setVisibility(bool newVisibility) { mVisible = newVisibility; }

		};

	}
}

#endif
