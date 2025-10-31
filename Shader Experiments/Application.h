#pragma once

#include <gl/glew.h>

#include <SDL.h>

#include "MeshData.h"
#include "Shader.h"

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


public:
	bool running = true;

private:
	SDL_Window* window;
	SDL_GLContext glContext;

	int width = 800;
	int height = 600;

	float lastFrame;

	unsigned int VBO;
	unsigned int VAO;

	Shader shader = Shader("Shader/Standard/standardShader.vert", "Shader/Standard/standardShader.frag");
};

