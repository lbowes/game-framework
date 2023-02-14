#include "SkyBox.h"
#include "Shader.h"
#include "ResourceSet.h"
#include "Renderer.h"

namespace GF {
	namespace Graphics {

		SkyBox::SkyBox(const std::vector<std::string>& textures, const std::string& vertPath, const std::string& fragPath) {
			using namespace Graphics;

			const std::vector<float> positions = {
				-1.0, -1.0,  1.0,
				1.0, -1.0,  1.0,
				1.0,  1.0,  1.0,
				-1.0,  1.0,  1.0,

				-1.0, -1.0, -1.0,
				1.0, -1.0, -1.0,
				1.0,  1.0, -1.0,
				-1.0,  1.0, -1.0,
			};

			const std::vector<unsigned> indices = {
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

			mShader = std::make_unique<Shader>(vertPath, fragPath, "skyBoxShader");
			mMesh->setShader(mShader.get());

			mTexture = std::make_unique<TextureCube>(textures, "skyBoxTexture");
			mMesh->setTexture(mTexture.get());

			mPositions = std::make_unique<VertexBuffer>(GL_STATIC_DRAW, VertexFormat(0, 3, GL_FLOAT, false), positions, "skyBoxPositions");
			mMesh->addBuffer(mPositions.get());

			mIndices = std::make_unique<IndexBuffer>(GL_STATIC_DRAW, indices, "skyBoxIndices");
			mMesh->addIndexBuffer(mIndices.get());

			initDefaultShaderUniforms();
		}

		SkyBox::SkyBox(const std::string& vertPath, const std::string& fragPath) {
			using namespace Graphics;

			const std::vector<float> positions = {
				-1.0, -1.0,  1.0,
				 1.0, -1.0,  1.0,
				 1.0,  1.0,  1.0,
				-1.0,  1.0,  1.0,

				-1.0, -1.0, -1.0,
				 1.0, -1.0, -1.0,
				 1.0,  1.0, -1.0,
				-1.0,  1.0, -1.0,
			};

			const std::vector<unsigned> indices = {
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

			mShader = std::make_unique<Shader>(vertPath, fragPath, "skyBoxShader");
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
			mMesh->getShader()->setUniform("viewMatrix", glm::mat4(glm::mat3(renderer.getCamera()->getView())));
			mMesh->getShader()->setUniform("projectionMatrix", renderer.getCamera()->getProjection());

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
