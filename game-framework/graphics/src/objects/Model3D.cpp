#include "Model3D.h"
#include "ResourceSet.h"

namespace GF {

	Model3D::Model3D() :
		mModelTransform(glm::mat4(1))
	{ }

	Model3D::Model3D(glm::mat4 transform) :
		mModelTransform(transform)
	{ }

	void Model3D::sendRenderCommands(Graphics::Renderer& renderer) {
		if (!mVisible)
			return;

		for (Graphics::Mesh* m : mMeshes) {
			m->setModelTransform(m->getModelTransform() * mModelTransform);
			m->sendRenderCommand(renderer);
		}
	}

	void Model3D::addMesh(Graphics::Mesh* mesh) {
		mMeshes.push_back(mesh);
	}

	Graphics::Mesh* Model3D::getMesh(unsigned index) {
		if (index >= 0 && index < mMeshes.size())
			return mMeshes[index];
		else
			return nullptr;
	}

}