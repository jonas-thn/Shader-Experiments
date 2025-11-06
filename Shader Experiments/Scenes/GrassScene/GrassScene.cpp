#include "GrassScene.h"

void GrassScene::Init()
{
	standardShader.Init();
	grassShader.Init();

	plane.Init();
	plane.Translate(glm::vec3(0.0, -1.0, 0.0));
	plane.Rotate(90.0f, glm::vec3(1.0, 0.0, 0.0));
	plane.SetScale(glm::vec3(4.0));

	grass1.Init();
	grass2.Init();
}

void GrassScene::Draw(glm::mat4& view, glm::mat4& projection, glm::vec3& camPos, float time)
{
	plane.Draw(standardShader, view, projection, camPos, time, 0, 0);

	grass1.Draw(grassShader, view, projection, camPos, time, 0, count);
	grass2.Draw(grassShader, view, projection, camPos, time, 1, count);
}

