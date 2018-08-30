#ifndef GF_UTILS_OBJLOADER_H
#define GF_UTILS_OBJLOADER_H
#pragma once

#include "Mesh.h"
#include "FileManager.h"
#include "StringUtils.hpp"

#include <sstream>
#include <fstream>
#include <unordered_map>

namespace GF {
	class ResourceSet;

	namespace Utils {

		struct Vertex {
			glm::vec3 
				position,
				normal;

			glm::vec2 textureCoord;
		};

		struct VertexSet {
			std::vector<glm::vec3>
				positions,
				normals;

			std::vector<glm::vec2>
				textureCoords;
		};

		struct IndexSet {
			unsigned
				posIndex = 0,
				texCoordIndex = 0,
				normalIndex = 0;

			bool operator==(const IndexSet& other) const
			{
				return posIndex == other.posIndex && texCoordIndex == other.texCoordIndex && normalIndex == other.normalIndex;
			}
		};

		class OBJLoader {
		public:
			enum class AttribType { POSITION, TEXTURE_COORD, NORMAL };
			
		public:
			static void loadOBJData(ResourceSet& dataHolder, Graphics::Mesh* target, const std::string& filePath);

		private:
			static void insertVertex(std::vector<Vertex>& vertices, std::vector<unsigned>& indices, std::unordered_map<IndexSet, int>& mapping, VertexSet& inputVertices, IndexSet& indexSet);
			static std::vector<float> extractAttribData(std::vector<Vertex>& vertices, AttribType type);

		};

	}
}

#endif
