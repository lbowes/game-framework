#include "SteelCubeModel.h"

#include <GraphicsFramework/Vendor/ImGui/imgui.h>

SteelCubeModel::SteelCubeModel(SteelCube& dataSource, GF::Graphics::Renderer& renderer, GF::ResourceSet& resourceContainer, GF::Graphics::Shader& shader) :
	mDataSource(dataSource),
	mRenderer(renderer),
	mResourceContainer(resourceContainer),
	mShader(shader)
{
	load();
}

void SteelCubeModel::load() {
	using namespace GF::Graphics;

	mMesh = mResourceContainer.addOBJMesh("steelCubeMesh", "res/models/cube.obj");
	mMesh->setShader(&mShader);
}

void SteelCubeModel::update() {
	mMesh->setModelTransform(mDataSource.mState.getObjectSpace().getLocalToParent_total());
	mDataSourceCentreMass = mDataSource.mState.getObjectSpace().toParentSpace(mDataSource.mState.getMass_local().getCentre());
	mDataSourceOrigin = mDataSource.mState.getObjectSpace().toParentSpace();
}

void SteelCubeModel::render() {
	update();
	mMesh->sendRenderCommand(mRenderer);
}
