#pragma once

#include <gl/glew.h>

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_sdl2.h"
#include "ImGui/imgui_impl_opengl3.h"

#include <SDL.h>

#include <memory>

#include "MeshData.h"
#include "Shader.h"
#include "Mesh.h"
#include "Scenes/LightingScene/LightingScene.h"
#include "Scenes/EmptyScene/EmptyScene.h"
#include "Scenes/NoiseScene/NoiseScene.h"
#include "Scenes/OtherScene/OtherScene.h"
#include "Scenes/PlanetScene/PlanetScene.h"
#include "Scenes/RaymarchingScene/RaymarchingScene.h"

enum class ActiveScene
{
	None,
	Lighting,
	Planet,
	Other,
	Raymarching
};

class Application
{
public:
	void Init();
	void Setup();
	void ProcessInput();
	void Update();
	void Render();
	void Destroy();

private:
	void DrawGUI();
	void DrawScene();
	void ResetScenes();

public:
	bool running = true;

private:
	SDL_Window* window;
	SDL_GLContext glContext;

	int width = 800;
	int height = 600;

	float lastFrame;

	//Scenes
	ActiveScene activeScene = ActiveScene::None;
	std::shared_ptr<Scene> emptyScene = std::make_shared<EmptyScene>();
	std::shared_ptr<Scene> lightingScene = std::make_shared<LightingScene>();
	std::shared_ptr<Scene> planetScene = std::make_shared<PlanetScene>();
	std::shared_ptr<Scene> raymrchingScene = std::make_shared<RaymarchingScene>();
	std::shared_ptr<Scene> otherScene = std::make_shared<OtherScene>();
	std::vector <std::shared_ptr<Scene>> sceneList = {emptyScene, lightingScene, planetScene, raymrchingScene, otherScene};

	glm::vec3 camPos;
	glm::mat4 projection = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);

	float camRadius = 2.5f;
	float camSpeed = 1.0f;
	float cameraHeight = 0.0f;

	float uiWidthPercent = 0.35f;
	int uiWidth = width * uiWidthPercent;
	ImVec4 blackColor = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	ImVec4 grey02Color = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
	ImVec4 grey04Color = ImVec4(0.4f, 0.4f, 0.4f, 1.0f);
	ImVec4 grey06Color = ImVec4(0.6f, 0.6f, 0.6f, 1.0f);
	ImVec4 grey08Color = ImVec4(0.8f, 0.8f, 0.8f, 1.0f);
	ImVec4 whiteColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
};

