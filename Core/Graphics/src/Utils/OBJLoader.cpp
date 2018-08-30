#include "OBJLoader.h"
#include "ResourceSet.h"
#include "Logger.h"

template<>
struct std::hash<GF::Utils::IndexSet>
{
	const size_t operator()(const GF::Utils::IndexSet& key) const
	{
		return (key.posIndex) ^ (key.normalIndex << 14) ^ (key.texCoordIndex << 23);
	}
};

namespace GF {
	namespace Utils {

		void OBJLoader::loadOBJData(ResourceSet& dataHolder, Graphics::Mesh* target, const std::string& filePath) {
			using namespace GF::Graphics;
			
			std::vector<std::string> lines = splitString(FileManager::fileToString(filePath), '\n');

			VertexSet inputVertices;
			std::vector<Vertex> vertices;
			std::vector<unsigned> indices;
			std::unordered_map<IndexSet, int> mapping;

			unsigned
				lineIndex = 0,
				loadingAnimationIndex = 0;
				
			for (const std::string& line : lines) {
				const char* cstr = line.c_str();

				if (strstr(cstr, "#") || strstr(cstr, "s"))
					continue;
				else if(strstr(cstr, "v")) {
					if (strstr(cstr, "vt")) {
						glm::vec2 texCoord;
						int result = sscanf(cstr, "%*s %f %f", &texCoord.x, &texCoord.y);
						if (result == 0)
							continue;
						texCoord.y = 1.0f - texCoord.y;
						inputVertices.textureCoords.push_back(texCoord);
					}
					else if (strstr(cstr, "vn")) {
						glm::vec3 normal;
						int result = sscanf(cstr, "%*s %f %f %f", &normal.x, &normal.y, &normal.z);
						if (result == 0)
							continue;
						inputVertices.normals.push_back(normal);
					}
					else {
						glm::vec3 position;
						int result = sscanf(cstr, "%*s %f %f %f", &position.x, &position.y, &position.z);
						if (result == 0)
							continue;
						inputVertices.positions.push_back(position);
					}
				}
				else if (strstr(cstr, "f")) {
					IndexSet indexSet[3];
					std::vector<std::string> faceVertices = splitString(line.substr(2), ' ');
					if (faceVertices.size() > 3) {
						Logger::log(Logger::LogType::ERROR_HALT, "OBJ model " + filePath + " was not exported with triangulated faces.");
						return;
					}

					for (unsigned short vertexCount = 0; vertexCount < faceVertices.size(); vertexCount++) {
						std::vector<std::string> vertexAttribs = splitString(faceVertices[vertexCount], '/');
						
						//It is certain that there will be at least positions
						indexSet[vertexCount].posIndex = stoi(vertexAttribs[0]);
						
						//If the size is 3, then there will be 3 strings. The 2nd may or may not be a null character, but there will be 3 strings to 
						//process.
						if (vertexAttribs.size() == 3) {
							if (vertexAttribs[1] != "\0") indexSet[vertexCount].texCoordIndex = stoi(vertexAttribs[1]);
							indexSet[vertexCount].normalIndex = stoi(vertexAttribs[2]);
						}
						else if (vertexAttribs.size() == 2) {
							indexSet[vertexCount].posIndex = stoi(vertexAttribs[0]);
							indexSet[vertexCount].texCoordIndex = stoi(vertexAttribs[1]);
						}
					}
					
					insertVertex(vertices, indices, mapping, inputVertices, indexSet[0]);
					insertVertex(vertices, indices, mapping, inputVertices, indexSet[1]);
					insertVertex(vertices, indices, mapping, inputVertices, indexSet[2]);
				}
			}
			//Logger::log(Logger::LogType::INFO, "OBJ Mesh loaded from '" + filePath + ".\n\n");

			//Giving OpenGL this data
			bool
				containsPositions = !inputVertices.positions.empty(),
				containsTexCoords = !inputVertices.textureCoords.empty(),
				containsNormals = !inputVertices.normals.empty();

			if (containsPositions) {
				dataHolder.addVertexBuffer(target->getUniqueID() + ":POSITIONS", GL_STATIC_DRAW, VertexFormat(0, 3, GL_FLOAT, false), extractAttribData(vertices, AttribType::POSITION));
				target->addBuffer(dataHolder.getResource<VertexBuffer>(target->getUniqueID() + ":POSITIONS"));
			}
			
			if (containsTexCoords) {
				dataHolder.addVertexBuffer(target->getUniqueID() + ":TEX_COORDS", GL_STATIC_DRAW, VertexFormat(1, 2, GL_FLOAT, false), extractAttribData(vertices, AttribType::TEXTURE_COORD));
				target->addBuffer(dataHolder.getResource<VertexBuffer>(target->getUniqueID() + ":TEX_COORDS"));
			}
			
			if (containsNormals) {
				dataHolder.addVertexBuffer(target->getUniqueID() + ":NORMALS", GL_STATIC_DRAW, VertexFormat(2, 3, GL_FLOAT, false), extractAttribData(vertices, AttribType::NORMAL));
				target->addBuffer(dataHolder.getResource<VertexBuffer>(target->getUniqueID() + ":NORMALS"));
			}
			
			dataHolder.addIndexBuffer(target->getUniqueID() + ":INDICES", GL_STATIC_DRAW, indices);
			target->addIndexBuffer(dataHolder.getResource<IndexBuffer>(target->getUniqueID() + ":INDICES"));
		}

		void OBJLoader::insertVertex(std::vector<Vertex>& vertices, std::vector<unsigned>& indices, std::unordered_map<IndexSet, int>& mapping, VertexSet& inputVertices, IndexSet& indexSet) {
			auto lookup = mapping.find(indexSet);

			if (lookup != mapping.end())
				indices.push_back(lookup->second);
			else {
				mapping[indexSet] = (int)vertices.size();
				indices.push_back((unsigned)vertices.size());
				
				Vertex vertex;
				
				if (indexSet.posIndex > 0) vertex.position = inputVertices.positions[indexSet.posIndex - 1];
				if (indexSet.normalIndex > 0) vertex.normal = inputVertices.normals[indexSet.normalIndex - 1];
				if (indexSet.texCoordIndex > 0) vertex.textureCoord = inputVertices.textureCoords[indexSet.texCoordIndex - 1];

				vertices.push_back(vertex);
			}
		}

		std::vector<float> OBJLoader::extractAttribData(std::vector<Vertex>& vertices, AttribType type) {
			std::vector<float> output;

			switch (type) {
				case AttribType::POSITION: {
					for (Vertex& v : vertices) {
						output.push_back(v.position.x);
						output.push_back(v.position.y);
						output.push_back(v.position.z);
					}
				}
				break;

				case AttribType::TEXTURE_COORD: {
					for (Vertex& v : vertices) {
						output.push_back(v.textureCoord.x);
						output.push_back(v.textureCoord.y);
					}
				}
				break;

				case AttribType::NORMAL: {
					for (Vertex& v : vertices) {
						output.push_back(v.normal.x);
						output.push_back(v.normal.y);
						output.push_back(v.normal.z);
					}
				}
				break;
			}

			return output;
		}

	}
}