#include "LightingScene.h"

void LightingScene::Init()
{
	lightingShader.Init();

	cone.Init();
	cone.Translate(glm::vec3(0.0f, conePos, 0.0f));
	meshList.push_back(&cone);

	sphere.Init();
	sphere.Translate(glm::vec3(0.0f, spherePos, 0.0f));
	meshList.push_back(&sphere);

	pyramid.Init();
	pyramid.Translate(glm::vec3(0.0f, pyramidPos, 0.0f));
	meshList.push_back(&pyramid);

	cube.Init();
	cube.Translate(glm::vec3(0.0f, cubePos, 0.0f));
	meshList.push_back(&cube);

	ring.Init();
	ring.Translate(glm::vec3(0.0f, ringPos, 0.0f));
	meshList.push_back(&ring);
}

void LightingScene::Update(float dt)
{
	if (!active) return;

	MoveMesh(conePos, cone, dt);
	MoveMesh(spherePos, sphere, dt);
	MoveMesh(pyramidPos, pyramid, dt);
	MoveMesh(cubePos, cube, dt);
	MoveMesh(ringPos, ring, dt);
}

void LightingScene::Draw(glm::mat4& view, glm::mat4& projection, glm::vec3& camPos, float time)
{
	for (int i = 0; i < meshList.size(); i++)
	{
		meshList[i]->Draw(lightingShader, view, projection, camPos, time, i, 0);
	}
}

void LightingScene::MoveMesh(float& pos, Mesh& mesh, float dt)
{
	if (pos < lowerBound)
	{
		pos = upperBound;
	}

	pos -= speed * dt;

	mesh.SetPos(glm::vec3(0.0f, pos, 0.0f));
}

