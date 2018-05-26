#if 0

#ifndef RENDERABLE2D_H
#define RENDERABLE2D_H
#pragma once

#include <glm/glm/vec2.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtx/transform.hpp>

#include "Graphics/Mesh.h"
#include "Graphics/Texture/Texture2D.h"
#include "Renderer/Renderer2D.h"

#define NO_2D_TRANSFORM glm::mat4()

namespace Framework {

	namespace Renderer {
		class Renderer2D;
	}

	class Renderable2D {
	protected:
		glm::mat4 mTransform = glm::mat4(1);
		glm::vec2 
			mPosition, 
			mSize;
		glm::vec3 mColour;
		
		std::unique_ptr<Graphics::Mesh> mQuad;
		std::unique_ptr<Graphics::Shader> mShaderUsed;

	public:
		Renderable2D(glm::vec2 position, glm::vec2 size, glm::vec3 colour, std::string vertexFilepath, std::string fragmentShaderFilepath);
		Renderable2D(glm::vec2 position, glm::vec2 size, glm::vec3 colour, Graphics::Shader* shader);
		~Renderable2D() = default;

		friend void Renderer::Renderer2D::render(Renderable2D& Renderable);

		void setTexture(Graphics::Texture* texture) const;
		void setTexture(std::string filepath) const;
		void setShader(Graphics::Shader* shader);
		void setShader(std::string vertexFilepath, std::string fragmentShaderFilepath);

		void render(Renderer::Renderer2D& renderer) const;
		void initDefaultShaderUniforms() const;

	protected:
		void initMesh();

	};

}

#endif
#endif