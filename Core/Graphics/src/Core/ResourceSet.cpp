#include "ResourceSet.h"
#include "OBJLoader.h"
#include "Logger.h"

namespace GF {

	Graphics::Texture2D* ResourceSet::addTexture2D(const std::string& resID, const std::string& path) {
		if (!resourceAdded(resID)) {
			mResources.push_back(std::make_unique<Graphics::Texture2D>(path, resID));
			return static_cast<Graphics::Texture2D*>(mResources.back().get());
		}
		else {
			alreadyAddedError(resID);
			return getResource<Graphics::Texture2D>(resID);
		}
	}
	
	Graphics::TextureCube* ResourceSet::addTextureCube(const std::string& resID, const std::vector<std::string>& textures) {
		if (!resourceAdded(resID)) {
			mResources.push_back(std::make_unique<Graphics::TextureCube>(textures, resID));
			return static_cast<Graphics::TextureCube*>(mResources.back().get());
		}
		else {
			alreadyAddedError(resID);
			return getResource<Graphics::TextureCube>(resID);
		}
	}
	
	Graphics::Shader* ResourceSet::addShader(const std::string& resID, const std::string& vertPath, const std::string& fragPath, const std::string& geomPath) {
		if (!resourceAdded(resID)) {
			mResources.push_back(std::make_unique<Graphics::Shader>(resID, vertPath, fragPath, geomPath));
			return static_cast<Graphics::Shader*>(mResources.back().get());
		}
		else {
			alreadyAddedError(resID);
			return getResource<Graphics::Shader>(resID);
		}
	}
	
	Graphics::VertexBuffer* ResourceSet::addVertexBuffer(const std::string& resID, unsigned usage, const Graphics::VertexFormat& format, const std::vector<float>& data) {
		if (!resourceAdded(resID)) {
			mResources.push_back(std::make_unique<Graphics::VertexBuffer>(usage, format, data, resID));
			return static_cast<Graphics::VertexBuffer*>(mResources.back().get());
		}
		else {
			alreadyAddedError(resID);
			return getResource<Graphics::VertexBuffer>(resID);
		}
	}
	
	Graphics::IndexBuffer* ResourceSet::addIndexBuffer(const std::string& resID, unsigned usage, const std::vector<unsigned>& data) {
		if (!resourceAdded(resID)) {
			mResources.push_back(std::make_unique<Graphics::IndexBuffer>(usage, data, resID));
			return static_cast<Graphics::IndexBuffer*>(mResources.back().get());
		}
		else {
			alreadyAddedError(resID);
			return getResource<Graphics::IndexBuffer>(resID);
		}
	}

	Graphics::Mesh* ResourceSet::addMesh(const std::string& resID, unsigned geometryType, Graphics::Texture* texture, Graphics::Shader* shader, glm::mat4 modelTransform) {
		if (!resourceAdded(resID)) {
			mResources.push_back(std::make_unique<Graphics::Mesh>(resID, geometryType, texture, shader, modelTransform));
			return static_cast<Graphics::Mesh*>(mResources.back().get());
		}
		else {
			alreadyAddedError(resID);
			return getResource<Graphics::Mesh>(resID);
		}
	}

	Graphics::Mesh* ResourceSet::addOBJMesh(const std::string& resID, const std::string& path, unsigned geometryType, Graphics::Texture* texture, Graphics::Shader* shader, glm::mat4 modelTransform) {
		if (!resourceAdded(resID)) {
			mResources.push_back(std::make_unique<Graphics::Mesh>(resID, geometryType, texture, shader, modelTransform));
			Graphics::Mesh* justAdded = static_cast<Graphics::Mesh*>(mResources.back().get());
			Utils::OBJLoader::loadOBJData(*this, justAdded, path);
			
			return justAdded;
		}
		else {
			alreadyAddedError(resID);
			return getResource<Graphics::Mesh>(resID);
		}
	}

	unsigned ResourceSet::getResourceIndex(const std::string& resID) {
		for (unsigned i = 0; i < mResources.size(); i++) {
			if (mResources[i].get()->getUniqueID() == resID)
				return i;
		}

		return -1;
	}
	
	Resource* ResourceSet::getResource(const std::string& resID) {
		Resource* temp = nullptr;
		
		for (const auto& r : mResources) {
			temp = r.get();
			if (temp->getUniqueID() == resID)
				return temp;
		}
		
		Utils::Logger::log(Utils::Logger::LogType::ERROR_HALT, "Could not find resource with ID '" + resID + "'.");
		return nullptr;
	}

	Resource* ResourceSet::getResource(unsigned index) {
		return (index >= 0 && index < mResources.size()) ? mResources[index].get() : nullptr;
	}
	
	template <class T>
	T* ResourceSet::getResource(const std::string& resID) {
		Resource* temp = nullptr;

		for (const auto& r : mResources) {
			temp = r.get();
			if (temp->getUniqueID() == resID)
				return static_cast<T*>(temp);
		}

		Utils::Logger::log(Utils::Logger::LogType::ERROR_HALT, "Could not find resource with ID '" + resID + "'.");
		return nullptr;
	}

	template <class T>
	T* ResourceSet::getResource(unsigned index) {
		return (index >= 0 && index < mResources.size()) ? static_cast<T*>(mResources[index].get()) : nullptr;
	}

	Resource* ResourceSet::operator[](unsigned index) {
		return (index >= 0 && index < mResources.size()) ? mResources[index].get() : nullptr;
	}

	bool ResourceSet::resourceAdded(const std::string& resID) {
		for (const auto& r : mResources) {
			if (r.get()->getUniqueID() == resID)
				return true;
		}
		return false;
	}

	void ResourceSet::alreadyAddedError(const std::string& resID) {
		Utils::Logger::log(Utils::Logger::LogType::WARNING, "Resource '" + resID + "' has already been created.\n");
	}

	template Graphics::Texture2D* ResourceSet::getResource<Graphics::Texture2D>(const std::string& resID);
	template Graphics::TextureCube* ResourceSet::getResource<Graphics::TextureCube>(const std::string& resID);
	template Graphics::Shader* ResourceSet::getResource<Graphics::Shader>(const std::string& resID);
	template Graphics::VertexBuffer* ResourceSet::getResource<Graphics::VertexBuffer>(const std::string& resID);
	template Graphics::IndexBuffer* ResourceSet::getResource<Graphics::IndexBuffer>(const std::string& resID);
	template Graphics::Mesh* ResourceSet::getResource<Graphics::Mesh>(const std::string& resID);
	
}