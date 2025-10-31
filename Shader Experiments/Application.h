#pragma once

#include <gl/glew.h>

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_sdl2.h"
#include "ImGui/imgui_impl_opengl3.h"

#include <SDL.h>

#include "MeshData.h"
#include "Shader.h"
#include "Mesh.h"

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

public:
	bool running = true;

private:
	SDL_Window* window;
	SDL_GLContext glContext;

	int width = 800;
	int height = 600;

	float lastFrame;

	Shader standardShader = Shader("Shader/Standard/standardShader.vert", "Shader/Standard/standardShader.frag");

	Mesh quad = Mesh(
		std::vector<float>(std::begin(quadVertices), std::end(quadVertices)),
		std::vector<unsigned int>(std::begin(quadIndices), std::end(quadIndices))
	);

	std::vector<Mesh*> meshList;
	Mesh triangle = Mesh("./Models/triangle.obj"); 

	glm::mat4 projection = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);

	float camRadius = 5.0f;
	float camSpeed = 2.0f;

	float uiWidthPercent = 0.35f;
	int uiWidth = width * uiWidthPercent;
	ImVec4 blackColor = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	ImVec4 grey02Color = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
	ImVec4 grey04Color = ImVec4(0.4f, 0.4f, 0.4f, 1.0f);
	ImVec4 grey06Color = ImVec4(0.6f, 0.6f, 0.6f, 1.0f);
	ImVec4 grey08Color = ImVec4(0.8f, 0.8f, 0.8f, 1.0f);
	ImVec4 whiteColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
};

