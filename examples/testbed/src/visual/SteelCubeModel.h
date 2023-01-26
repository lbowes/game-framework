#ifndef STEELCUBEMODEL_H
#define STEELCUBEMODEL_H
#pragma once

#include <GraphicsFramework/Renderer.h>
#include <GraphicsFramework/ResourceSet.h>

#include "../SteelCube.h"

class SteelCubeModel {
private:
	SteelCube& mDataSource;
	GF::Graphics::Renderer& mRenderer;
	GF::ResourceSet& mResourceContainer;

	GF::Graphics::Shader& mShader;
	GF::Graphics::Mesh* mMesh = nullptr;

	glm::vec3
		mDataSourceCentreMass,
		mDataSourceOrigin;

public:
	SteelCubeModel(SteelCube& dataSource, GF::Graphics::Renderer& renderer, GF::ResourceSet& resourceContainer, GF::Graphics::Shader& shader);
	~SteelCubeModel() = default;

	void render();

	glm::vec3& getCentreMass() { return mDataSourceCentreMass; }
	glm::vec3& getOrigin() { return mDataSourceOrigin; }

private:
	void load();
	void update();

};

#endif
