#ifndef GRAPHICS_RENDERCOMMAND_HPP
#define GRAPHICS_RENDERCOMMAND_HPP
#pragma once

#include <glm/mat4x4.hpp>

namespace GF {
	namespace Graphics {
		
		class Texture;
		class Shader;
		class VertexArray;

		struct RenderCommand {
			friend class RenderQueue;
		private:
			//At the moment these are textures and shaders - there is no other state (yet) that changes between draw calls.
			//Other properties of a RenderCommand can be added in here. Any state changes that occur at rendering should
			//all be held by this class, so that the RenderQueue can sort them.

			//Not used yet
			//enum Priority { SHADER, TEXTURE };
			//const unsigned mNumRenderStateVariables = 2;
			//

			Texture* mTexture = nullptr;
			Shader* mShader = nullptr;
			VertexArray* mVAO = nullptr;
			glm::mat4 mTransform;

		public:
			RenderCommand(Texture* texture, Shader* shader, VertexArray* VAO, glm::mat4 transform) :
				mTexture(texture),
				mShader(shader),
				mVAO(VAO),
				mTransform(transform)
			{ }

			~RenderCommand() = default;

			inline Texture* getTexture() const { return mTexture; }
			inline Shader* getShader() const { return mShader; }
			inline VertexArray* getVAO() const { return mVAO; }
			inline glm::mat4 getTransform() const { return mTransform; }

		};

	}
}

#endif
