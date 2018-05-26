#include "../Core/ResourceSet.h"
#include "../Utils/OBJLoader.h"
#include "../Utils/ConsoleLogger.h"

namespace Framework {

	Graphics::Texture2D* ResourceSet::addTexture2D(std::string path, std::string resourceID) {
		if (!resourceAdded(resourceID)) {
			mResources.push_back(std::make_unique<Graphics::Texture2D>(path, resourceID));
			return static_cast<Graphics::Texture2D*>(mResources.back().get());
		}
		else {
			Utils::ConsoleLogger::log(Utils::ConsoleLogger::LogType::WARNING, "Resource '" + resourceID + "' has already been created.\n\n");
			return getResource<Graphics::Texture2D>(resourceID);
		}
	}
	
	Graphics::TextureCube* ResourceSet::addTextureCube(std::vector<std::string> textures, std::string resourceID) {
		if (!resourceAdded(resourceID)) {
			mResources.push_back(std::make_unique<Graphics::TextureCube>(textures, resourceID));
			return static_cast<Graphics::TextureCube*>(mResources.back().get());
		}
		else {
			Utils::ConsoleLogger::log(Utils::ConsoleLogger::LogType::WARNING, "Resource '" + resourceID + "' has already been created.\n\n");
			return getResource<Graphics::TextureCube>(resourceID);
		}
	}
	
	Graphics::Shader* ResourceSet::addShader(std::string vertexShaderPath, std::string fragmentShaderPath, std::string resourceID) {
		if (!resourceAdded(resourceID)) {
			mResources.push_back(std::make_unique<Graphics::Shader>(vertexShaderPath, fragmentShaderPath, resourceID));
			return static_cast<Graphics::Shader*>(mResources.back().get());
		}
		else {
			Utils::ConsoleLogger::log(Utils::ConsoleLogger::LogType::WARNING, "Resource '" + resourceID + "' has already been created.\n\n");
			return getResource<Graphics::Shader>(resourceID);
		}
	}
	
	Graphics::Shader* ResourceSet::addShader(std::string vertexShaderPath, std::string fragmentShaderPath, std::string geometryShaderPath, std::string resourceID) {
		if (!resourceAdded(resourceID)) {
			mResources.push_back(std::make_unique<Graphics::Shader>(vertexShaderPath, fragmentShaderPath, geometryShaderPath, resourceID));
			return static_cast<Graphics::Shader*>(mResources.back().get());
		}
		else {
			Utils::ConsoleLogger::log(Utils::ConsoleLogger::LogType::WARNING, "Resource '" + resourceID + "' has already been created.\n\n");
			return getResource<Graphics::Shader>(resourceID);
		}
	}
	
	Graphics::VertexBuffer* ResourceSet::addVertexBuffer(unsigned int usage, const Graphics::VertexFormat& format, const std::vector<float>& data, std::string resourceID) {
		if (!resourceAdded(resourceID)) {
			mResources.push_back(std::make_unique<Graphics::VertexBuffer>(usage, format, data, resourceID));
			return static_cast<Graphics::VertexBuffer*>(mResources.back().get());
		}
		else {
			Utils::ConsoleLogger::log(Utils::ConsoleLogger::LogType::WARNING, "Resource '" + resourceID + "' has already been created.\n\n");
			return getResource<Graphics::VertexBuffer>(resourceID);
		}
	}
	
	Graphics::IndexBuffer* ResourceSet::addIndexBuffer(unsigned int usage, const std::vector<unsigned int>& data, std::string resourceID) {
		if (!resourceAdded(resourceID)) {
			mResources.push_back(std::make_unique<Graphics::IndexBuffer>(usage, data, resourceID));
			return static_cast<Graphics::IndexBuffer*>(mResources.back().get());
		}
		else {
			Utils::ConsoleLogger::log(Utils::ConsoleLogger::LogType::WARNING, "Resource '" + resourceID + "' has already been created.\n\n");
			return getResource<Graphics::IndexBuffer>(resourceID);
		}
	}

	Graphics::Mesh* ResourceSet::addMesh(std::string resourceID, unsigned int geometryType, Graphics::Texture* texture, Graphics::Shader* shader, glm::mat4 worldTransform) {
		if (!resourceAdded(resourceID)) {
			mResources.push_back(std::make_unique<Graphics::Mesh>(resourceID, geometryType, texture, shader, worldTransform));
			return static_cast<Graphics::Mesh*>(mResources.back().get());
		}
		else {
			Utils::ConsoleLogger::log(Utils::ConsoleLogger::LogType::WARNING, "Resource '" + resourceID + "' has already been created.\n\n");
			return getResource<Graphics::Mesh>(resourceID);
		}
	}

	Graphics::Mesh* ResourceSet::addOBJMesh(std::string resourceID, std::string path, unsigned int geometryType, Graphics::Texture* texture, Graphics::Shader* shader, glm::mat4 worldTransform) {
		if (!resourceAdded(resourceID)) {
			mResources.push_back(std::make_unique<Graphics::Mesh>(resourceID, geometryType, texture, shader, worldTransform));
			Graphics::Mesh* justAdded = static_cast<Graphics::Mesh*>(mResources.back().get());
			Utils::OBJLoader::loadOBJData(*this, justAdded, path);
			
			return justAdded;
		}
		else {
			Utils::ConsoleLogger::log(Utils::ConsoleLogger::LogType::WARNING, "Resource '" + resourceID + "' has already been created.\n\n");
			return getResource<Graphics::Mesh>(resourceID);
		}
	}

	unsigned int ResourceSet::getResourceIndex(std::string resourceID) {
		for (unsigned int i = 0; i < mResources.size(); i++) {
			if (mResources[i].get()->getUniqueID() == resourceID)
				return i;
		}

		return -1;
	}
	
	Resource* ResourceSet::getResource(std::string resourceID) {
		Resource* temp = nullptr;
		
		for (const auto& r : mResources) {
			temp = r.get();
			if (temp->getUniqueID() == resourceID)
				return temp;
		}
		
		Utils::ConsoleLogger::log(Utils::ConsoleLogger::LogType::ERROR_HALT, "Could not find resource with ID '" + resourceID + "'.");
		return nullptr;
	}

	Resource* ResourceSet::getResource(unsigned int index) {
		return (index >= 0 && index < mResources.size()) ? mResources[index].get() : nullptr;
	}
	
	template <class T>
	T* ResourceSet::getResource(std::string resourceID) {
		Resource* temp = nullptr;

		for (const auto& r : mResources) {
			temp = r.get();
			if (temp->getUniqueID() == resourceID)
				return static_cast<T*>(temp);
		}

		Utils::ConsoleLogger::log(Utils::ConsoleLogger::LogType::ERROR_HALT, "Could not find resource with ID '" + resourceID + "'.");
		return nullptr;
	}

	template <class T>
	T* ResourceSet::getResource(unsigned int index) {
		return (index >= 0 && index < mResources.size()) ? static_cast<T*>(mResources[index].get()) : nullptr;
	}

	Resource* ResourceSet::operator[](unsigned int index) {
		return (index >= 0 && index < mResources.size()) ? mResources[index].get() : nullptr;
	}

	bool ResourceSet::resourceAdded(std::string resourceID) {
		for (const auto& r : mResources) {
			if (r.get()->getUniqueID() == resourceID)
				return true;
		}
		return false;
	}

	template Graphics::Texture2D* ResourceSet::getResource<Graphics::Texture2D>(std::string resourceID);
	template Graphics::TextureCube* ResourceSet::getResource<Graphics::TextureCube>(std::string resourceID);
	template Graphics::Shader* ResourceSet::getResource<Graphics::Shader>(std::string resourceID);
	template Graphics::VertexBuffer* ResourceSet::getResource<Graphics::VertexBuffer>(std::string resourceID);
	template Graphics::IndexBuffer* ResourceSet::getResource<Graphics::IndexBuffer>(std::string resourceID);
	template Graphics::Mesh* ResourceSet::getResource<Graphics::Mesh>(std::string resourceID);
	
}