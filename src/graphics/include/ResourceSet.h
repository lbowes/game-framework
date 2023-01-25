#ifndef GF_RESOURCESET_H
#define GF_RESOURCESET_H
#pragma once

#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "TextureCube.h"
#include "Mesh.h"

namespace GF {
	
	class ResourceSet {
	private:
		std::vector<std::unique_ptr<Resource>> mResources;

	public:
		ResourceSet() = default;
		~ResourceSet() = default;

		Graphics::Texture2D* addTexture2D(const std::string& resID, const std::string& path);
		Graphics::TextureCube* addTextureCube(const std::string& resID, const std::vector<std::string>& textures);
		Graphics::Shader* addShader(const std::string& resID, const std::string& vertPath, const std::string& fragPath, const std::string& geomPath = "");
		Graphics::VertexBuffer* addVertexBuffer(const std::string& resID, unsigned usage, const Graphics::VertexFormat& format, const std::vector<float>& data);
		Graphics::IndexBuffer* addIndexBuffer(const std::string& resID, unsigned usage, const std::vector<unsigned>& data);
		Graphics::Mesh* addMesh(const std::string& resID, unsigned geometryType = GL_TRIANGLES, Graphics::Texture* texture = nullptr, Graphics::Shader* shader = nullptr, glm::mat4 modelTransform = glm::mat4(1));
		Graphics::Mesh* addOBJMesh(const std::string& resID, const std::string& path, unsigned geometryType = GL_TRIANGLES, Graphics::Texture* texture = nullptr, Graphics::Shader* shader = nullptr, glm::mat4 modelTransform = glm::mat4(1));

		unsigned getResourceIndex(const std::string& resID);
		Resource* getResource(const std::string& resID);
		Resource* getResource(unsigned index);
		
		template <class T>
		T* getResource(const std::string& resID);
		template <class T>
		T* getResource(unsigned index);

		bool resourceAdded(const std::string& resID);
		Resource* operator[](unsigned index);

		size_t getResourceCount() const { return mResources.size(); }

	private:
		void alreadyAddedError(const std::string& resID);

	};

}

#endif
