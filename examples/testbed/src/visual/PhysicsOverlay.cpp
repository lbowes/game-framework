#include "PhysicsOverlay.h"

#include <GraphicsFramework/Vendor/ImGui/imgui.h>
#include <GraphicsFramework/Input.h>

PhysicsOverlay::PhysicsOverlay(float windowAspect) {
	load(windowAspect);
}

void PhysicsOverlay::render(glm::mat4 viewProjection, float windowAspect, glm::vec2 windowDimensions) {
	mOrthoCam->setAspect(windowAspect);

	if (!mMarkers.empty()) {
		updateMarkers(viewProjection, windowAspect);
	
		mMesh->sendRenderCommand(mRenderer);
		glClear(GL_DEPTH_BUFFER_BIT);
		mRenderer.flush();

		checkCursorOverMarker(windowAspect, windowDimensions);
	}
}

void PhysicsOverlay::addMarker(glm::vec3& target, Marker2D::Type type) {
	mMarkers.push_back({ &target, type });
	rebuildBuffers();
}

void PhysicsOverlay::checkCursorOverMarker(float windowAspect, glm::vec2 windowDimensions) {
	//ImVec2 NDCMouseCoords = ImVec2(ImGui::GetMousePos().x / windowDimensions.x, ImGui::GetMousePos().y / windowDimensions.y);
	glm::vec2 NDCMouseCoords = glm::vec2(GF::Input::getMousePosition().x / windowDimensions.x, GF::Input::getMousePosition().y / windowDimensions.y);
	NDCMouseCoords.y = 1.0f - NDCMouseCoords.y;
	NDCMouseCoords = glm::vec2((NDCMouseCoords.x - 0.5f) * 2.0f, (NDCMouseCoords.y - 0.5f) * 2.0f);
	NDCMouseCoords.x *= windowAspect;

	for (Marker2D& m : mMarkers) {
		if (glm::length(NDCMouseCoords - glm::vec2(m.mResult_NDC)) < mMarkerRadius && !GF::Input::isCursorHidden()) {
			ImGui::SetNextWindowPos(ImGui::GetMousePos());
			ImGui::Begin("Marker position");
			ImGui::Text("x: %f y: %f z: %f", m.mTarget_world->x, m.mTarget_world->y, m.mTarget_world->z);
			ImGui::End();
		}
	}
}

void PhysicsOverlay::load(float windowAspect) {
	using namespace GF::Graphics;

	Shader* shader = mResourceContainer.addShader("physicsOverlayShader", "res/shaders/overlay.vert", "res/shaders/overlay.frag");
	shader->addUniform("modelMatrix");
	shader->addUniform("viewMatrix");
	shader->addUniform("projectionMatrix");

	Texture2D* texture = mResourceContainer.addTexture2D("markerTexture", "res/textures/Markers.png");

	mMesh = mResourceContainer.addMesh("physicsOverlayMesh", GL_TRIANGLES, texture, shader);

	VertexFormat
		vertPosFormat(0, 3, GL_FLOAT, false),
		vertTexCoordFormat(1, 2, GL_FLOAT, false);
	
	mPositionVBO = mResourceContainer.addVertexBuffer("overlayVBO", GL_STATIC_DRAW, vertPosFormat, mPositions);
	mTexCoordVBO = mResourceContainer.addVertexBuffer("overlayTexCoords", GL_STATIC_DRAW, vertTexCoordFormat, mTexCoords);
	mIBO = mResourceContainer.addIndexBuffer("overlayIndices", GL_STATIC_DRAW, mIndices);

	mMesh->addBuffer(mPositionVBO);
	mMesh->addBuffer(mTexCoordVBO);
	mMesh->addIndexBuffer(mIBO);

	mOrthoCam = std::make_unique<GF::OrthographicCamera>(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 1.0f, -1.0f, windowAspect, 1.0f);
	mRenderer.setCamera(*mOrthoCam);
}

void PhysicsOverlay::rebuildBuffers() {
	mPositions.clear();
	mTexCoords.clear();
	mIndices.clear();

	for (int i = 0; i < mMarkers.size(); i++) {
		//Position data...
		for (int i = 0; i < 12; i++)
			mPositions.push_back(0.0f);

		if (mMarkers[i].mType == Marker2D::Type::centreMass) {
			//Texture coordinate data for origin symbol
			mTexCoords.push_back(0.0f);
			mTexCoords.push_back(0.0f);
			mTexCoords.push_back(0.0f);
			mTexCoords.push_back(0.5f);
			mTexCoords.push_back(0.5f);
			mTexCoords.push_back(0.5f);
			mTexCoords.push_back(0.5f);
			mTexCoords.push_back(0.0f);
		}
		else if (mMarkers[i].mType == Marker2D::Type::origin) {
			//Texture coordinate data for centre of mass symbol
			mTexCoords.push_back(0.5f);
			mTexCoords.push_back(0.0f);
			mTexCoords.push_back(0.5f);
			mTexCoords.push_back(0.5f);
			mTexCoords.push_back(1.0f);
			mTexCoords.push_back(0.5f);
			mTexCoords.push_back(1.0f);
			mTexCoords.push_back(0.0f);
		}
		else {
			for(int i = 0; i < 8; i++)
				mTexCoords.push_back(0.0f);
		}

		//Index data
		mIndices.push_back(i * 4);
		mIndices.push_back(i * 4 + 1);
		mIndices.push_back(i * 4 + 2);
		mIndices.push_back(i * 4 + 2);
		mIndices.push_back(i * 4 + 3);
		mIndices.push_back(i * 4);
	}

	mPositionVBO->updateData(mPositions);
	mTexCoordVBO->updateData(mTexCoords);
	mIBO->updateData(mIndices);
}

void PhysicsOverlay::updateMarkers(glm::mat4 viewProjection, float windowAspect) {
	for (Marker2D& m : mMarkers)
		m.recalc(viewProjection, windowAspect);

	updateBuffers(viewProjection, windowAspect);
}

void PhysicsOverlay::updateBuffers(glm::mat4 viewProjection, float windowAspect) {
	for (int i = 0; i < mMarkers.size(); i++) {

		//v1
		mPositions[i * 12] = mMarkers[i].mResult_NDC.x - mMarkerRadius;
		mPositions[i * 12 + 1] = mMarkers[i].mResult_NDC.y - mMarkerRadius;
		mPositions[i * 12 + 2] = mMarkers[i].mResult_NDC.z;

		//v2
		mPositions[i * 12 + 3] = mMarkers[i].mResult_NDC.x - mMarkerRadius;
		mPositions[i * 12 + 4] = mMarkers[i].mResult_NDC.y + mMarkerRadius;
		mPositions[i * 12 + 5] = mMarkers[i].mResult_NDC.z;

		//v3
		mPositions[i * 12 + 6] = mMarkers[i].mResult_NDC.x + mMarkerRadius;
		mPositions[i * 12 + 7] = mMarkers[i].mResult_NDC.y + mMarkerRadius;
		mPositions[i * 12 + 8] = mMarkers[i].mResult_NDC.z;

		//v4
		mPositions[i * 12 + 9] = mMarkers[i].mResult_NDC.x + mMarkerRadius;
		mPositions[i * 12 + 10] = mMarkers[i].mResult_NDC.y - mMarkerRadius;
		mPositions[i * 12 + 11] = mMarkers[i].mResult_NDC.z;
	}

	mPositionVBO->updateData(mPositions);
}