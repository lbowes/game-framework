#ifndef SKYBOX_H
#define SKYBOX_H
#pragma once

#include "Texture/TextureCube.h"
#include "Mesh.h"

namespace Framework {
	class ResourceSet;
	
	namespace Graphics {
		class Shader;
		class Renderer;

		class SkyBox {
		private:
			std::unique_ptr<Mesh> mMesh;
			std::unique_ptr<Shader> mShader;
			std::unique_ptr<TextureCube> mTexture;
			std::unique_ptr<VertexBuffer> mPositions;
			std::unique_ptr<IndexBuffer> mIndices;

		public:
			SkyBox(std::vector<std::string> textures, std::string vertexShaderPath, std::string fragmentShaderPath);
			SkyBox(std::string vertexShaderPath, std::string fragmentShaderPath);
			~SkyBox() = default;

			void render(Renderer& renderer) const;

			inline Shader* getShader() const { return mShader.get(); }
			inline TextureCube* getTexture() const { return mTexture.get(); }

		private:
			void initDefaultShaderUniforms() const;

		};

	}
}

#endif
