#pragma once

#include "../Scene.h"

class LightingScene : public Scene
{
public:
	LightingScene() = default;
	virtual ~LightingScene() = default;

	void Init() override;
	void Update(float dt) override;
	void Draw(glm::mat4& view, glm::mat4& projection, glm::vec3& camPos, float time) override;

private:
	Shader lightingShader = Shader("./Shader/Lighting/lightingShader.vert", "./Shader/Lighting/lightingShader.frag");

	Mesh pyramid = Mesh("./Models/pyramid.obj");
	Mesh sphere = Mesh("./Models/sphere_high.obj");
	Mesh monkey = Mesh("./Models/monkey_high.obj");
	Mesh cube = Mesh("./Models/cube.obj");
	Mesh ring = Mesh("./Models/ring.obj");
};

