#include "EmptyScene.h"

void EmptyScene::Init()
{
	standardShader.Init();

	text.Init();
	text.Rotate(-120, glm::vec3(0.0, 1.0, 0.0));
	meshList.push_back(&text);
}

void EmptyScene::Update(float dt)
{
	if (!active) return;
}

void EmptyScene::Draw(glm::mat4& view, glm::mat4& projection, glm::vec3& camPos, float time)
{
	for (int i = 0; i < meshList.size(); i++)
	{
		meshList[i]->Draw(standardShader, view, projection, camPos, time, i, 0);
	}
}
