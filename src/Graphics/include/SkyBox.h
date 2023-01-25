#ifndef GF_GRAPHICS_SKYBOX_H
#define GF_GRAPHICS_SKYBOX_H
#pragma once

#include "TextureCube.h"
#include "Mesh.h"

namespace GF {
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
			SkyBox(const std::vector<std::string>& textures, const std::string& vertPath, const std::string& fragPath);
			SkyBox(const std::string& vertPath, const std::string& fragPath);
			~SkyBox() = default;

			void render(Renderer& renderer) const;

			Shader* getShader() const { return mShader.get(); }
			TextureCube* getTexture() const { return mTexture.get(); }

		private:
			void initDefaultShaderUniforms() const;

		};

	}
}

#endif
