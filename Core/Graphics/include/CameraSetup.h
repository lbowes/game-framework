#ifndef CAMERASETUP_H
#define CAMERASETUP_H
#pragma once

#include <vector>
#include <memory>

#include "PerspectiveCamera.h"
#include "OrthographicCamera.h"

namespace GF {
	struct CameraHandle {
		std::string mId = "";
		Camera* mCamera = nullptr;

	public:
		CameraHandle(const std::string& id, Camera* camera) :
			mId(id),
			mCamera(camera)
		{ }
	};

	class CameraSetup {
	private:
		std::vector<std::unique_ptr<Camera>> mOwnedCameras;
		std::vector<CameraHandle> mHandles;

	public:
		CameraSetup() = default;
		~CameraSetup() = default;

		Camera* operator[](const unsigned index) const;
		Camera* getCamera(unsigned index) const;
		Camera* getCameraById(const std::string& id) const;
		unsigned getCameraIndex(const std::string& id) const;

		inline size_t getNumCameras() const { return mHandles.size(); }

		void addNewCamera(const std::string& id, ProjectionType type, glm::vec3 position, glm::vec3 front, glm::vec3 up, float near, float far, float aspect, float FOVY = DEFAULT_FOV);
		void addExistingCamera(const std::string& id, Camera* existingCamera);

	};
}

#endif
