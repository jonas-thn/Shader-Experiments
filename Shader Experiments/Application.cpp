#include "Application.h"

void Application::Init()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	window = SDL_CreateWindow("Shader Experiments", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	glContext = SDL_GL_CreateContext(window);

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		printf("GLEW Init Error: %s\n", glewGetErrorString(err));
		running = false; 
		return;
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; 
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;    
	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForOpenGL(window, glContext);
	ImGui_ImplOpenGL3_Init("#version 130");

	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_FrameBg] = grey02Color;
	style.Colors[ImGuiCol_FrameBgHovered] = grey04Color;
	style.Colors[ImGuiCol_FrameBgActive] = grey06Color;
	style.Colors[ImGuiCol_PopupBg] = grey02Color;
	style.Colors[ImGuiCol_Border] = grey04Color;
	style.Colors[ImGuiCol_BorderShadow] = blackColor;
	style.Colors[ImGuiCol_Header] = grey04Color;
	style.Colors[ImGuiCol_HeaderHovered] = grey06Color;
	style.Colors[ImGuiCol_HeaderActive] = grey08Color;
	style.Colors[ImGuiCol_Text] = whiteColor;
	style.Colors[ImGuiCol_CheckMark] = whiteColor;
	style.Colors[ImGuiCol_ScrollbarBg] = grey02Color;
	style.Colors[ImGuiCol_ScrollbarGrab] = grey04Color;
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = grey06Color;
	style.Colors[ImGuiCol_ScrollbarGrabActive] = grey08Color;
	style.Colors[ImGuiCol_Button] = grey04Color;
	style.Colors[ImGuiCol_SliderGrab] = grey08Color;
	style.Colors[ImGuiCol_SliderGrabActive] = whiteColor;
	style.Colors[ImGuiCol_ButtonHovered] = grey06Color;
	style.Colors[ImGuiCol_ButtonActive] = grey08Color;
	style.Colors[ImGuiCol_TextSelectedBg] = grey06Color;
	style.Colors[ImGuiCol_Separator] = grey04Color;
	style.Colors[ImGuiCol_SeparatorHovered] = grey06Color;
	style.Colors[ImGuiCol_SeparatorActive] = grey08Color;
	style.Colors[ImGuiCol_TitleBg] = grey02Color;
	style.Colors[ImGuiCol_TitleBgActive] = grey04Color;
	style.Colors[ImGuiCol_TitleBgCollapsed] = grey02Color;
	style.Colors[ImGuiCol_ResizeGrip] = grey04Color;
	style.Colors[ImGuiCol_ResizeGripHovered] = grey06Color;
	style.Colors[ImGuiCol_ResizeGripActive] = grey08Color;
	style.Colors[ImGuiCol_DragDropTarget] = grey08Color;
	style.Colors[ImGuiCol_NavHighlight] = grey06Color;
	style.Colors[ImGuiCol_NavWindowingHighlight] = grey06Color;
	style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0, 0, 0, 0.4f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0, 0, 0, 0.4f);
	style.WindowPadding = ImVec2(20.0f, 20.0f);

	glEnable(GL_DEPTH_TEST);
	glViewport(-uiWidth, 0, width + uiWidth, height);
}

void Application::Setup()
{
	projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
	view = glm::lookAt(glm::vec3(1.0f, 0.0f, 5.0f), //cam pos
		glm::vec3(1.0f, 0.0f, 0.0f), //look at
		glm::vec3(0.0f, 1.0f, 0.0f) //up
	);

	for (auto scene : sceneList)
	{
		scene->Init();
	}

	grassScene->Init();

	emptyScene->active = true;
}

void Application::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		ImGui_ImplSDL2_ProcessEvent(&event);
		if (event.type == SDL_QUIT)
		{
			running = false;
		}

		if (event.type == SDL_WINDOWEVENT)
		{
			if (event.window.event == SDL_WINDOWEVENT_RESIZED)
			{
				width = event.window.data1;
				height = event.window.data2;
				projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
				glViewport(-uiWidth, 0, width + uiWidth, height);
			}
		}
	}
}

void Application::Update()
{
	float deltaTime = (SDL_GetTicks() - lastFrame) / 1000.0f;
	lastFrame = SDL_GetTicks();

	uiWidth = width * uiWidthPercent;
	
	static float angle = 0.0f;
	angle -= camSpeed * deltaTime;

	camPos.x = sin(angle) * camRadius;
	camPos.y = 0.0f; 
	camPos.z = cos(angle) * camRadius;

	view = glm::lookAt(camPos + glm::vec3(0.0, cameraHeight, 0.0), //cam pos
		glm::vec3(0.0, 0.0, 0.0), //look at
		glm::vec3(0.0f, 1.0f, 0.0f) //up
	);

	for (auto scene : sceneList)
	{
		scene->Update(deltaTime);
	}
}

void Application::Render()
{
	glViewport(-uiWidth, 0, width + uiWidth, height);

	DrawGUI();
	DrawScene();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	SDL_GL_SwapWindow(window);
}

void Application::Destroy()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Application::DrawGUI()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	ImGui::SetNextWindowPos(ImVec2(width - uiWidth, 0));
	ImGui::SetNextWindowSize(ImVec2(uiWidth, height));

	ImGui::Begin("Shader Scenes", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);

	const int buttonHeight = 20;

	//Lighting Scene
	ImGui::SeparatorText("Lighting");
	if (ImGui::Button("Load Scene##1", ImVec2(-1, buttonHeight)))
	{
		activeScene = ActiveScene::Lighting;
		ResetScenes();
		lightingScene->active = true;
	}
	ImGui::Text("Lighting Shader:");
	ImGui::BulletText("Ambient");
	ImGui::BulletText("Hemispheric");
	ImGui::BulletText("Diffuse");
	ImGui::BulletText("Specular");
	ImGui::BulletText("Fresnel");

	ImGui::Dummy(ImVec2(0.0, 10.0));

	ImGui::SeparatorText("Planet");
	if (ImGui::Button("Load Scene##2", ImVec2(-1, buttonHeight)))
	{
		activeScene = ActiveScene::Planet;
		ResetScenes();
		planetScene->active = true;
	}
	ImGui::Text("Planet and Stars Shader:");
	ImGui::BulletText("Signed Distance Fields");
	ImGui::BulletText("Noise");
	ImGui::BulletText("3D Mapping");

	ImGui::Dummy(ImVec2(0.0, 10.0));

	ImGui::SeparatorText("Raymarching");
	if (ImGui::Button("Load Scene##3", ImVec2(-1, buttonHeight)))
	{
		activeScene = ActiveScene::Raymarching;
		ResetScenes();
		raymrchingScene->active = true;
	}
	ImGui::Text("Raymacrhing Shader:");
	ImGui::BulletText("Smooth Blending");
	ImGui::BulletText("Distance Fog");
	ImGui::BulletText("Soft Shadows");
	ImGui::BulletText("Ambient Occlusion");

	ImGui::Dummy(ImVec2(0.0, 10.0));

	ImGui::SeparatorText("Terrain");
	if (ImGui::Button("Load Scene##4", ImVec2(-1, buttonHeight)))
	{
		activeScene = ActiveScene::Terrain;
		ResetScenes();
		terrainScene->active = true;
	}
	ImGui::Text("Terrain Shader:");
	ImGui::BulletText("Procedual Generation");
	ImGui::BulletText("Atmosphere");

	ImGui::Dummy(ImVec2(0.0, 10.0));

	ImGui::SeparatorText("Grass");
	if (ImGui::Button("Load Scene##5", ImVec2(-1, buttonHeight)))
	{
		activeScene = ActiveScene::Grass;
		ResetScenes();
	}
	ImGui::Text("Grass Shader:");
	ImGui::BulletText("Instancing");
	ImGui::BulletText("Bending");

	ImGui::Dummy(ImVec2(0.0, 10.0));

	ImGui::SeparatorText("Firework");
	if (ImGui::Button("Load Scene##6", ImVec2(-1, buttonHeight)))
	{
		activeScene = ActiveScene::Firework;
		ResetScenes();
		fireworkScene->active = true;
	}
	ImGui::Text("Firework Shader:");

	ImGui::Dummy(ImVec2(0.0, 10.0));

	ImGui::SeparatorText("Water");
	ImGui::Text("WORK IN PROGRESS...");

	ImGui::Dummy(ImVec2(0.0, 10.0));

	ImGui::SeparatorText("Tunnel");
	ImGui::Text("WORK IN PROGRESS...");

	ImGui::Dummy(ImVec2(0.0, 10.0));

	ImGui::SeparatorText("Other");
	if (ImGui::Button("Load Scene##9", ImVec2(-1, buttonHeight)))
	{
		activeScene = ActiveScene::Other;
		ResetScenes();
		otherScene->active = true;
	}
	ImGui::Text("Other Shaders:");
	ImGui::BulletText("Dissolve");
	ImGui::BulletText("Ripple");
	ImGui::BulletText("Spherify");
	ImGui::BulletText("Explosion");

	ImGui::End();

	ImGui::Render();
}

void Application::DrawScene()
{
	glClearColor(0.1, 0.1, 0.105, 1.1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (activeScene == ActiveScene::None)
	{
		emptyScene->Draw(view, projection, camPos, (SDL_GetTicks() * 0.001f));
	}
	else if(activeScene == ActiveScene::Lighting)
	{
		camRadius = 7.0f;
		camSpeed = 1.0f;
		cameraHeight = 1.75;

		lightingScene->Draw(view, projection, camPos, (SDL_GetTicks() * 0.001f));
	}
	else if (activeScene == ActiveScene::Planet)
	{
		planetScene->Draw(view, projection, camPos, (SDL_GetTicks() * 0.001f));
	}
	else if (activeScene == ActiveScene::Raymarching)
	{
		raymrchingScene->Draw(view, projection, camPos, (SDL_GetTicks() * 0.001f));
	}
	else if (activeScene == ActiveScene::Terrain)
	{
		terrainScene->Draw(view, projection, camPos, (SDL_GetTicks() * 0.001f));
	}
	else if (activeScene == ActiveScene::Firework)
	{
		fireworkScene->Draw(view, projection, camPos, (SDL_GetTicks() * 0.001f));
	}
	else if (activeScene == ActiveScene::Grass)
	{
		camRadius = 7.0f;
		camSpeed = 0.3f;
		cameraHeight = 2;
		grassScene->Draw(view, projection, camPos, (SDL_GetTicks() * 0.001f));
	}
	else if (activeScene == ActiveScene::Other)
	{
		camRadius = 6.0f;
		camSpeed = 0.2f;
		cameraHeight = 0.5f;
		otherScene->Draw(view, projection, camPos, (SDL_GetTicks() * 0.001f));
	}
}

void Application::ResetScenes()
{
	for (std::shared_ptr<Scene> scene : sceneList)
	{
		scene->active = false;
	}
}

