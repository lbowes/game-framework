#if 0

#include "Renderable2D.h"
#include "Renderer/Renderer2D.h"

namespace Framework {

	Renderable2D::Renderable2D(glm::vec2 position, glm::vec2 size, glm::vec3 colour, std::string vertexFilepath, std::string fragmentShaderFilepath) :
		mPosition(position),
		mSize(size),
		mColour(colour)
	{
		//mShaderUsed = new Graphics::Shader(vertexFilepath, fragmentShaderFilepath);
		mShaderUsed = std::make_unique<Graphics::Shader>(vertexFilepath, fragmentShaderFilepath);

		initMesh();
	}

	Renderable2D::Renderable2D(glm::vec2 position, glm::vec2 size, glm::vec3 colour, Graphics::Shader* shader) :
		mPosition(position),
		mSize(size),
		mColour(colour)
	{
		//mShaderUsed = shader;
		mShaderUsed.reset(shader);

		initMesh();
	}

	/*Renderable2D::~Renderable2D() {
		delete mShaderUsed;
		mShaderUsed = nullptr;

		delete mQuad;
		mQuad = nullptr;
	}*/
	
	void Renderable2D::setTexture(Graphics::Texture* texture) const {
		mQuad->setTexture(texture);
	}

	void Renderable2D::setTexture(std::string filepath) const {
		mQuad->setTexture(new Graphics::Texture2D(filepath));
	}

	void Renderable2D::setShader(Graphics::Shader* shader) {
		//mShaderUsed = shader; //set it to point to this new shader
		mShaderUsed.reset(shader); //set it to point to this new shader
	}

	void Renderable2D::setShader(std::string vertexFilepath, std::string fragmentShaderFilepath) {
		//mShaderUsed = new Graphics::Shader(vertexFilepath, fragmentShaderFilepath); //set it to point to this new shader
		mShaderUsed = std::make_unique<Graphics::Shader>(vertexFilepath, fragmentShaderFilepath); //set it to point to this new shader
	}

	void Renderable2D::render(Renderer::Renderer2D& renderer) const {
		glDisable(GL_DEPTH_TEST);
		
		mShaderUsed->bind();
		
		mShaderUsed->setUniform(0, mQuad->getTransform());
		mShaderUsed->setUniform(1, renderer.mProjection);

		mQuad->render();
	}

	void Renderable2D::initDefaultShaderUniforms() const {
		mShaderUsed->addUniform("modelMatrix");
		mShaderUsed->addUniform("projectionMatrix");
	}

	void Renderable2D::initMesh() {
		using namespace Graphics;

		mQuad = std::make_unique<Mesh>(true, GL_TRIANGLES, NO_2D_TRANSFORM, nullptr, mShaderUsed.get());

		mQuad->getVAO()->attachBuffer(GL_STATIC_DRAW/*, false*/);
		mQuad->getVAO()->attachBuffer(GL_STATIC_DRAW/*, false*/);
		mQuad->getVAO()->attachBuffer(GL_STATIC_DRAW/*, false*/);

		mQuad->setIndexBuffer(new IndexBuffer(false));

		mQuad->getVAO()->bind();
		{
			mQuad->getVAO()->getAllBuffers()[0]->setFormat(new BufferFormat(0, 2, GL_FLOAT, false));
			mQuad->getVAO()->getAllBuffers()[1]->setFormat(new BufferFormat(1, 3, GL_FLOAT, false));
			mQuad->getVAO()->getAllBuffers()[2]->setFormat(new BufferFormat(2, 2, GL_UNSIGNED_INT, false));

			mQuad->getIndexBuffer()->bind();
		}
		mQuad->getVAO()->unbind();

		std::vector<float> positionData = {
			mPosition.x,           mPosition.y,           //bottom left
			mPosition.x + mSize.x, mPosition.y,           //bottom right
			mPosition.x + mSize.x, mPosition.y + mSize.y, //top right
			mPosition.x,           mPosition.y + mSize.y  //top left
		};

		std::vector<float> colourData;
		for (unsigned int i = 0; i < 4; i++) {
			colourData.push_back(mColour.x);
			colourData.push_back(mColour.y);
			colourData.push_back(mColour.z);
		}

		std::vector<unsigned int> texCoordData = {
			0, 0,
			1, 0,
			1, 1,
			0, 1
		};

		std::vector<unsigned int> indexData = { 0, 1, 2, 2, 3, 0 };

		mQuad->getVAO()->getVertexBuffer(0)->updateData(positionData.size() * sizeof(float), &positionData[0]);
		mQuad->getVAO()->getVertexBuffer(1)->updateData(colourData.size() * sizeof(float), &colourData[0]);
		mQuad->getVAO()->getVertexBuffer(2)->updateData(texCoordData.size() * sizeof(float), &texCoordData[0]);
		mQuad->getIndexBuffer()->updateData(6, &indexData[0]);

		initDefaultShaderUniforms();
	}

}
#endif