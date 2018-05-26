#include "Model3D.h"
#include "../Core/ResourceSet.h"

namespace Framework {

	Model3D::Model3D() :
		mWorldTransform(glm::mat4(1))
	{ }

	Model3D::Model3D(glm::mat4 transform) :
		mWorldTransform(transform)
	{ }

	void Model3D::sendRenderCommands(Graphics::Renderer& renderer) {
		if (!mVisible)
			return;
		
		for (Graphics::Mesh* m : mMeshes) {
			m->setWorldTransform(m->getWorldTransform() * mWorldTransform);
			m->sendRenderCommand(renderer);
		}
	}

	void Model3D::addMesh(Graphics::Mesh* mesh) {
		mMeshes.push_back(mesh);
	}

	Graphics::Mesh* Model3D::getMesh(unsigned int index) {
		if (index >= 0 && index < mMeshes.size())
			return mMeshes[index];
		else
			return nullptr;
	}

}