#include "CameraSetup.h"

namespace GF {

	Camera* CameraSetup::operator[](const unsigned index) const {
		return getCamera(index);
	}

	Camera* CameraSetup::getCamera(const unsigned index) const {
		if (index >= 0 && index < mHandles.size())
			return mHandles[index].mCamera;
		else
			return nullptr;
	}

	Camera* CameraSetup::getCameraById(const std::string& id) const {
		for (const auto& handle : mHandles) {
			if (handle.mId == id)
				return handle.mCamera;
		}
		return nullptr;
	}

	unsigned CameraSetup::getCameraIndex(const std::string& id) const {
		for (unsigned i = 0; i < mHandles.size(); i++) {
			if (mHandles[i].mId == id)
				return i;
		}
		return 0;
	}

	void CameraSetup::addNewCamera(const std::string& id, ProjectionType type, glm::vec3 position, glm::vec3 front, glm::vec3 up, float near, float far, float aspect, float FOVY) {
		if (type == ProjectionType::PERSPECTIVE) {
			mOwnedCameras.push_back(std::make_unique<PerspectiveCamera>(position, front, up, near, far, aspect, FOVY));
		}
		else if (type == ProjectionType::ORTHOGRAPHIC)
			mOwnedCameras.push_back(std::make_unique<OrthographicCamera>(position, front, up, near, far, aspect, FOVY));

		mHandles.push_back(CameraHandle(id, mOwnedCameras.back().get()));
	}

	void CameraSetup::addExistingCamera(const std::string& id, Camera* existingCamera) {
		mHandles.push_back(CameraHandle(id, existingCamera));
	}

}