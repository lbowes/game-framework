#if 1
#include "Testbed.h"
#include <GraphicsFramework/Logger.h>

#include <glm/vec4.hpp>

Testbed::Testbed() :
	Application("GraphicsFramework testbed")
{
	onLoad();
}

void Testbed::onLoad() {
	using namespace GF::Graphics;
	using namespace glm;

	mWindow.setClearColour(glm::vec4(0.9607843137254902f, 0.9529411764705882f, 0.9490196078431373f, 1.0f));
	ImGui::StyleColorsLight();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Load plane shader
	mFlatShader = mResourceSet.addShader("flatShader", "res/shaders/flat.vert", "res/shaders/flat.frag");
	mFlatShader->addUniform("modelMatrix");
	mFlatShader->addUniform("viewMatrix");
	mFlatShader->addUniform("projectionMatrix");

	//Add shader to mesh
	mPlaneMesh = std::make_unique<Mesh>("planeMesh");
	mPlaneMesh->setShader(mFlatShader);

	//Create buffers
	float
		planeSize = 10.0f,
		planeHeight = 0.0f;

	std::vector<float> planeVertPositions = {
		-planeSize * 0.5f, planeHeight, -planeSize * 0.5f,
		-planeSize * 0.5f, planeHeight,  planeSize * 0.5f,
		 planeSize * 0.5f, planeHeight,  planeSize * 0.5f,
		 planeSize * 0.5f, planeHeight, -planeSize * 0.5f
	};
	VertexFormat planeVertexFormat(0, 3, GL_FLOAT, false);
	VertexBuffer* planeVBO = mResourceSet.addVertexBuffer("planeVBO", GL_STATIC_DRAW, planeVertexFormat, planeVertPositions);

	std::vector<unsigned> planeIndices = { 0, 1, 2, 2, 3, 0 };
	IndexBuffer* planeIBO = mResourceSet.addIndexBuffer("planeIBO", GL_STATIC_DRAW, planeIndices);

	//Add buffers to the mesh
	mPlaneMesh->addBuffer(planeVBO);
	mPlaneMesh->addIndexBuffer(planeIBO);

	glm::dquat compositeRotation = glm::rotate(glm::dquat(), glm::radians(0.0), glm::normalize(glm::dvec3(0.0, 0.0, 1.0)));
	mSteelComposite = std::make_unique<SteelComposite>(GF::CoordTransform3D({ 0.0, 10.0, 0.0 }, compositeRotation));
	mSteelComposite->mutableState().setObjectToParentTransform({ {0.0, 0.0, 0.0}, compositeRotation });

	mSteelCubeModel1 = std::make_unique<SteelCubeModel>(mSteelComposite->getSteelCube1(), mRenderer, mResourceSet, *mFlatShader);
	mSteelCubeModel2 = std::make_unique<SteelCubeModel>(mSteelComposite->getSteelCube2(), mRenderer, mResourceSet, *mFlatShader);

	mPhysicsOverlay = std::make_unique<PhysicsOverlay>(mWindow.getAspect());
	mPhysicsOverlay->addMarker(mSteelCubeModel1->getCentreMass(), Marker2D::Type::centreMass);
	mPhysicsOverlay->addMarker(mSteelCubeModel1->getOrigin(), Marker2D::Type::origin);

	mPhysicsOverlay->addMarker(mSteelCubeModel2->getCentreMass(), Marker2D::Type::centreMass);
	mPhysicsOverlay->addMarker(mSteelCubeModel2->getOrigin(), Marker2D::Type::origin);

	mPhysicsOverlay->addMarker(mSteelComposite->getCentreMass(), Marker2D::Type::centreMass);
	mPhysicsOverlay->addMarker(mSteelComposite->getOrigin(), Marker2D::Type::origin);

	//Create a camera looking at the origin
	mFPVCamera = std::make_unique<FPVCamera>(vec3(0.0f, 2.0f, 10.0f), vec3(0.0f, 0.0f, -1.0f), 0.1f, 5000.0f, mWindow.getAspect(), 45.0f);

	//Attach the camera to the renderer
	mRenderer.setCamera(mFPVCamera->getInternalCamera());
}

void Testbed::onInputCheck() {
	using namespace GF;

	if (Input::isKeyPressed(GLFW_KEY_ESCAPE))
		mWindow.close();

	mSteelComposite->checkInput();

	//Hide/show cursor for menu interaction/camera focus respectively
	glm::vec2 windowDimensions = glm::vec2(mWindow.getDimensions().x, mWindow.getDimensions().y);

	if (Input::isMouseButtonReleased(GLFW_MOUSE_BUTTON_RIGHT) && mFPVCamera->hasFocus()) {
		Input::showCursor();
		Input::setMousePosition(windowDimensions / 2.0f);
		mFPVCamera->setFocus(false);
	}
	if (Input::isMouseButtonReleased(GLFW_MOUSE_BUTTON_LEFT) && !ImGui::GetIO().WantCaptureMouse) {
		Input::hideCursor();
		mFPVCamera->setFocus(true);
	}

	if (mFPVCamera->hasFocus())
		mFPVCamera->handleInput((float)mFrameTime);
}

void Testbed::onUpdate() {
	mSteelComposite->update(mCurrentTime, mUpdateDelta);

	//mSteelCube1->basicCollision();
	//mSteelCube2->basicCollision();
}

void Testbed::onRender() {
	mFPVCamera->update(mWindow.getAspect(), (float)mFrameTime);

	mPlaneMesh->sendRenderCommand(mRenderer);
	mSteelCubeModel1->render();
	mSteelCubeModel2->render();
	mRenderer.flush();

	const State& compositeState = mSteelComposite->immutableState();
	ImGui::Begin("SteelComposite debug info");
	glm::dvec3 vec = compositeState.getObjectSpace().toParentSpace();
	ImGui::Text("Origin position: (%f, %f, %f)", vec.x, vec.y, vec.z);
	vec = compositeState.getObjectSpace().toParentSpace(compositeState.getMass_local().getCentre());
	ImGui::Text("CoM position:    (%f, %f, %f)", vec.x, vec.y, vec.z);
	vec = compositeState.getAngularMomentum_world();
	ImGui::Text("Angular momentum:    (%f, %f, %f)", vec.x, vec.y, vec.z);

	ImGui::End();

	mPhysicsOverlay->render(mFPVCamera->getInternalCamera().getViewProjection(), mWindow.getAspect(), mWindow.getDimensions());
}
#else
#include "Testbed.h"
#include <GraphicsFramework/ConsoleLogger.h>

#include <glm/vec4.hpp>

Testbed::Testbed() :
	Application("GraphicsFramework testbed")
{
	onLoad();
}

void Testbed::onLoad() {
	using namespace GF::Graphics;
	using namespace glm;

	mWindow.setClearColour(glm::vec4(0.5f, 0.3f, 0.4f, 1.0f));
	//ImGui::StyleColorsLight();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Create a camera looking at the origin
	mFPVCamera = std::make_unique<FPVCamera>(vec3(0.0f, 2.0f, 10.0f), vec3(0.0f, 0.0f, -1.0f), 0.1f, 5000.0f, mWindow.getAspect(), 45.0f);

	//Attach the camera to the renderer
	mRenderer.setCamera(mFPVCamera->getInternalCamera());
}

void Testbed::onInputCheck() {
	using namespace GF;

	glm::vec2 mousePosition = GF::Input::getMousePosition();
	printf("mousePosition: %f, %f\n", mousePosition.x, mousePosition.y);

	if (Input::isKeyPressed(GLFW_KEY_ENTER))
		std::cout<<"Key pressed\n";
}

void Testbed::onUpdate() { }

void Testbed::onRender() {
	ImGui::ShowDemoWindow();
}
#endif