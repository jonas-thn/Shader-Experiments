#pragma once

#include "../Scene.h"

class EmptyScene : public Scene
{
public:
	EmptyScene() = default;
	virtual ~EmptyScene() = default;

	void Init() override;
	void Update(float dt) override;
	void Draw(glm::mat4& view, glm::mat4& projection, glm::vec3& camPos, float time) override;

private:
	Shader standardShader = Shader("./Shader/Standard/standardShader.vert", "./Shader/Standard/standardShader.frag");

	Mesh text = Mesh("./Models/text.obj");
};

