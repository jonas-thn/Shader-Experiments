#include "PlanetScene.h"

void PlanetScene::Init()
{
	planetShader.Init();

	screen.Init();
	meshList.push_back(&screen);
}

void PlanetScene::Update(float dt)
{
	//...
}

void PlanetScene::Draw(glm::mat4& view, glm::mat4& projection, glm::vec3& camPos, float time)
{
	for (int i = 0; i < meshList.size(); i++)
	{
		meshList[i]->Draw(planetShader, view, projection, camPos, time, i, 0);
	}
}
