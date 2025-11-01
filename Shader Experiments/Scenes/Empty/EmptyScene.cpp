#include "EmptyScene.h"

void EmptyScene::Init()
{
	standardShader.Init();

	text.Init();
	meshList.push_back(&text);
}

void EmptyScene::Update(float dt)
{
	//...
}

void EmptyScene::Draw(glm::mat4& view, glm::mat4& projection, glm::vec3& camPos, float time)
{
	for (int i = 0; i < meshList.size(); i++)
	{
		meshList[i]->Draw(standardShader, view, projection, camPos, time, i);
	}
}
