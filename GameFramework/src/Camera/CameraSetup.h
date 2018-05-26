#ifndef CAMERASETUP_H
#define CAMERASETUP_H
#pragma once

#include <vector>
#include <memory>

#include "PerspectiveCamera.h"
#include "OrthographicCamera.h"

namespace Framework {
	struct CameraHandle {
		std::string mId = "";
		Camera* mCamera = nullptr;

	public:
		CameraHandle(std::string id, Camera* camera) :
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

		Camera* operator[](const uint32_t index) const;
		Camera* getCamera(uint32_t index) const;
		Camera* getCameraById(std::string id) const;
		uint32_t getCameraIndex(std::string id) const;

		inline uint32_t getNumCameras() const { return mHandles.size(); }

		void addNewCamera(std::string id, ProjectionType type, glm::vec3 position, glm::vec3 front, glm::vec3 up, float near, float far, float aspect, float FOVY = DEFAULT_FOV);
		void addExistingCamera(std::string id, Camera* existingCamera);

	};
}

#endif
