#include "NoiseScene.h"

void NoiseScene::Init()
{
	noiseShader.Init();

	screen.Init();
	meshList.push_back(&screen);
}

void NoiseScene::Update(float dt)
{
	//...
}

void NoiseScene::Draw(glm::mat4& view, glm::mat4& projection, glm::vec3& camPos, float time)
{
	for (int i = 0; i < meshList.size(); i++)
	{
		meshList[i]->Draw(noiseShader, view, projection, camPos, time, i);
	}
}
