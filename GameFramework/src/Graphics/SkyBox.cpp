#include "SkyBox.h"
#include "Shader.h"
#include "../Core/ResourceSet.h"
#include "Renderer/Renderer.h"

namespace Framework {
	namespace Graphics {

		SkyBox::SkyBox(std::vector<std::string> textures, std::string vertexShaderPath, std::string fragmentShaderPath) {
			using namespace Graphics;

			std::vector<float> positions = {
				-1.0, -1.0,  1.0,
				1.0, -1.0,  1.0,
				1.0,  1.0,  1.0,
				-1.0,  1.0,  1.0,

				-1.0, -1.0, -1.0,
				1.0, -1.0, -1.0,
				1.0,  1.0, -1.0,
				-1.0,  1.0, -1.0,
			};

			std::vector<unsigned int> indices = {
				0, 1, 2,
				2, 3, 0,

				1, 5, 6,
				6, 2, 1,

				7, 6, 5,
				5, 4, 7,

				4, 0, 3,
				3, 7, 4,

				4, 5, 1,
				1, 0, 4,

				3, 2, 6,
				6, 7, 3,
			};

			mMesh = std::make_unique<Mesh>("skyBoxMesh", GL_TRIANGLES, mTexture.get(), mShader.get(), glm::mat4(1));
			
			mShader = std::make_unique<Shader>(vertexShaderPath, fragmentShaderPath, "skyBoxShader");
			mMesh->setShader(mShader.get());
			
			mTexture = std::make_unique<TextureCube>(textures, "skyBoxTexture");
			mMesh->setTexture(mTexture.get());
			
			mPositions = std::make_unique<VertexBuffer>(GL_STATIC_DRAW, VertexFormat(0, 3, GL_FLOAT, false), positions, "skyBoxPositions");
			mMesh->addBuffer(mPositions.get());
			
			mIndices = std::make_unique<IndexBuffer>(GL_STATIC_DRAW, indices, "skyBoxIndices");
			mMesh->addIndexBuffer(mIndices.get());

			initDefaultShaderUniforms();
		}

		SkyBox::SkyBox(std::string vertexShaderPath, std::string fragmentShaderPath) {
			using namespace Graphics;

			std::vector<float> positions = {
				-1.0, -1.0,  1.0,
				1.0, -1.0,  1.0,
				1.0,  1.0,  1.0,
				-1.0,  1.0,  1.0,

				-1.0, -1.0, -1.0,
				1.0, -1.0, -1.0,
				1.0,  1.0, -1.0,
				-1.0,  1.0, -1.0,
			};

			std::vector<unsigned int> indices = {
				0, 1, 2,
				2, 3, 0,

				1, 5, 6,
				6, 2, 1,

				7, 6, 5,
				5, 4, 7,

				4, 0, 3,
				3, 7, 4,

				4, 5, 1,
				1, 0, 4,

				3, 2, 6,
				6, 7, 3,
			};

			mMesh = std::make_unique<Mesh>("skyBoxMesh", GL_TRIANGLES, mTexture.get(), mShader.get(), glm::mat4(1));

			mShader = std::make_unique<Shader>(vertexShaderPath, fragmentShaderPath, "skyBoxShader");
			mMesh->setShader(mShader.get());

			mPositions = std::make_unique<VertexBuffer>(GL_STATIC_DRAW, VertexFormat(0, 3, GL_FLOAT, false), positions, "skyBoxPositions");
			mMesh->addBuffer(mPositions.get());

			mIndices = std::make_unique<IndexBuffer>(GL_STATIC_DRAW, indices, "skyBoxIndices");
			mMesh->addIndexBuffer(mIndices.get());

			initDefaultShaderUniforms();
		}

		void SkyBox::render(Renderer& renderer) const {
			glDepthMask(GL_FALSE);

			mMesh->getShader()->bind();
			mMesh->getShader()->setUniform(0, glm::mat4(glm::mat3(renderer.getCamera()->getView())));
			mMesh->getShader()->setUniform(1, renderer.getCamera()->getProjection());

			if(mMesh->getTexture())
				mMesh->getTexture()->bind();
			mMesh->getVertexArray()->draw();

			glDepthMask(GL_TRUE);
		}

		void SkyBox::initDefaultShaderUniforms() const {
			mMesh->getShader()->addUniform("viewMatrix");
			mMesh->getShader()->addUniform("projectionMatrix");
		}

	}																   
}
