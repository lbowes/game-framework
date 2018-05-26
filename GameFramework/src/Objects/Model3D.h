#ifndef MODEL3D_H
#define MODEL3D_H
#pragma once

#include "../Graphics/Mesh.h"

namespace Framework {
	class Renderer;

	class Model3D {
	protected:
		bool mVisible = true;
		std::vector<Graphics::Mesh*> mMeshes;
		glm::mat4 mWorldTransform;

	public:
		Model3D();
		Model3D(glm::mat4 transform);
		~Model3D() = default;

		void sendRenderCommands(Graphics::Renderer& renderer);
		void addMesh(Graphics::Mesh* mesh);
		Graphics::Mesh* getMesh(unsigned int index);

		inline void setVisibility(bool newVisibility) { mVisible = newVisibility; }

	};

}

#endif
