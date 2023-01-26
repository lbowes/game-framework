#ifndef TESTBED_H
#define TESTBED_H
#pragma once

#include <GraphicsFramework/Application.h>
#include <GraphicsFramework/Renderer.h>
#include <GraphicsFramework/PerspectiveCamera.h>

#include "Visual/FPVCamera.h"
#include "SteelCube.h"
#include "Visual/SteelCubeModel.h"
#include "Visual/PhysicsOverlay.h"
#include "SteelComposite.h"

class Testbed : public GF::Application {
private:
	GF::Graphics::Shader* mFlatShader;
	std::unique_ptr<GF::Graphics::Mesh> mPlaneMesh;
	GF::Graphics::Renderer mRenderer;
	std::unique_ptr<FPVCamera> mFPVCamera;

	std::unique_ptr<SteelCubeModel>
		mSteelCubeModel1,
		mSteelCubeModel2;

	std::unique_ptr<SteelComposite> mSteelComposite;

	std::unique_ptr<PhysicsOverlay> mPhysicsOverlay;

	glm::vec3 testVector = glm::vec3(0.0, 20.0, 0.0);

public:
	Testbed();
	~Testbed() = default;

private:
	virtual	void onLoad();
	virtual void onInputCheck();
	virtual void onUpdate();
	virtual void onRender();

};

#endif
