#include "RaymarchingScene.h"

void RaymarchingScene::Init()
{
	raymarchShader.Init();

	screen.Init();
	meshList.push_back(&screen);
}

void RaymarchingScene::Update(float dt)
{
	//...
}

void RaymarchingScene::Draw(glm::mat4& view, glm::mat4& projection, glm::vec3& camPos, float time)
{
	for (int i = 0; i < meshList.size(); i++)
	{
		meshList[i]->Draw(raymarchShader, view, projection, camPos, time, i, 0);
	}
}
