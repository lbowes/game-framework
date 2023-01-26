#ifndef PHYSICSOVERLAY_H
#define PHYSICSOVERLAY_H
#pragma once

#include <GraphicsFramework/Shader.h>
#include <GraphicsFramework/Renderer.h>
#include <GraphicsFramework/ResourceSet.h>
#include <GraphicsFramework/Texture2D.h>
#include <GraphicsFramework/OrthographicCamera.h>

struct Marker2D {
	enum class Type { origin, centreMass };

	glm::vec3
		*mTarget_world,
		mResult_NDC;

	Type mType;

	Marker2D(glm::vec3* target_world, Type type) :
		mTarget_world(target_world),
		mType(type)
	{ }

	void recalc(glm::mat4 viewProjection, float windowAspect) {
		glm::vec4 clipSpace = viewProjection * glm::vec4(*mTarget_world, 1.0);

		if (clipSpace.x > clipSpace.w || clipSpace.x < -clipSpace.w) clipSpace.x = clipSpace.w * 2.0f;
		if (clipSpace.y > clipSpace.w || clipSpace.y < -clipSpace.w) clipSpace.y = clipSpace.w * 2.0f;
		if (clipSpace.z > clipSpace.w || clipSpace.z < -clipSpace.w) clipSpace.z = clipSpace.w * 2.0f;

		mResult_NDC = glm::vec3(clipSpace) / clipSpace.w;
		mResult_NDC.x *= windowAspect;
	}

};

class PhysicsOverlay {
private:
	GF::Graphics::Renderer mRenderer;
	GF::ResourceSet mResourceContainer;

	GF::Graphics::Mesh* mMesh = nullptr;
	GF::Graphics::VertexBuffer
		*mPositionVBO = nullptr,
		*mTexCoordVBO = nullptr;
	GF::Graphics::IndexBuffer* mIBO = nullptr;

	std::unique_ptr<GF::OrthographicCamera> mOrthoCam;

	std::vector<Marker2D> mMarkers;

	std::vector<float> mPositions;
	std::vector<float> mTexCoords;
	std::vector<unsigned> mIndices;

	float mMarkerRadius = 0.025f; //0.025f

public:
	PhysicsOverlay(float windowAspect);
	~PhysicsOverlay() = default;

public:
	void render(glm::mat4 viewProjection, float windowAspect, glm::vec2 windowDimensions);
	void addMarker(glm::vec3& target, Marker2D::Type type);
	void checkCursorOverMarker(float windowAspect, glm::vec2 windowDimensions);

private:
	void load(float windowAspect);
	void rebuildBuffers();
	void updateMarkers(glm::mat4 viewProjection, float windowAspect);
	void updateBuffers(glm::mat4 viewProjection, float windowAspect);

};

#endif
