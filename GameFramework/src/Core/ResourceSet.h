#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#pragma once

#include "../Graphics/Core/IndexBuffer.h"
#include "../Graphics/Core/VertexBuffer.h"
#include "../Graphics/Texture/TextureCube.h"
#include "../Graphics/Mesh.h"

namespace Framework {
	class ResourceSet {
	private:
		std::vector<std::unique_ptr<Resource>> mResources;

	public:
		ResourceSet() = default;
		~ResourceSet() = default;

		Graphics::Texture2D* addTexture2D(std::string path, std::string resourceID);
		Graphics::TextureCube* addTextureCube(std::vector<std::string> textures, std::string resourceID);
		Graphics::Shader* addShader(std::string vertexShaderPath, std::string fragmentShaderPath, std::string resourceID);
		Graphics::Shader* addShader(std::string vertexShaderPath, std::string fragmentShaderPath, std::string geometryShaderPath, std::string resourceID);
		Graphics::VertexBuffer* addVertexBuffer(unsigned int usage, const Graphics::VertexFormat& format, const std::vector<float>& data, std::string resourceID);
		Graphics::IndexBuffer* addIndexBuffer(unsigned int usage, const std::vector<unsigned int>& data, std::string resourceID);
		
		Graphics::Mesh* addMesh(
			std::string resourceID, 
			unsigned int geometryType = GL_TRIANGLES, 
			Graphics::Texture* texture = nullptr, 
			Graphics::Shader* shader = nullptr, 
			glm::mat4 worldTransform = glm::mat4(1));
		
		Graphics::Mesh* addOBJMesh(
			std::string resourceID, 
			std::string path, 
			unsigned int geometryType = GL_TRIANGLES, 
			Graphics::Texture* texture = nullptr, 
			Graphics::Shader* shader = nullptr, 
			glm::mat4 worldTransform = glm::mat4(1));

		unsigned int getResourceIndex(std::string resourceID);
		Resource* getResource(std::string resourceID);
		Resource* getResource(unsigned int index);

		template <class T>
		T* getResource(std::string resourceID);
		
		template <class T>
		T* getResource(unsigned int index);

		bool resourceAdded(std::string resourceID);
		Resource* operator[](unsigned int index);

		inline unsigned int getResourceCount() const { return mResources.size(); }

	};

}

#endif
