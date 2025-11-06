#include "OtherScene.h"

void OtherScene::Init()
{
	noiseShader.Init();
	rippleShader.Init();

	sphereNoise.Init();
	sphereNoise.Translate(glm::vec3(1.5, 0.0, 0.0));
	meshList.push_back(&sphereNoise);

	sphereRipple.Init();
	sphereRipple.Translate(glm::vec3(-1.5, 0.0, 0.0));
	meshList.push_back(&sphereRipple);

	monkeyExplode.Init();
	monkeyExplode.Translate(glm::vec3(0.0, 0.0, 1.5));
	monkeyExplode.SetScale(glm::vec3(0.6));
	meshList.push_back(&monkeyExplode);

	monkeySphere.Init();
	monkeySphere.Translate(glm::vec3(0.0, 0.0, -1.5));
	monkeySphere.Rotate(180, glm::vec3(0.0, 1.0, 0.0));
	monkeySphere.SetScale(glm::vec3(0.6));
	meshList.push_back(&monkeySphere);
}

void OtherScene::Update(float dt)
{
	if (!active) return;
	//...
}

void OtherScene::Draw(glm::mat4& view, glm::mat4& projection, glm::vec3& camPos, float time)
{
	sphereNoise.Draw(noiseShader, view, projection, camPos, time, 0, 0);
	sphereRipple.Draw(rippleShader, view, projection, camPos, time, 999, 0);
	monkeyExplode.Draw(rippleShader, view, projection, camPos, time, 998, 0);
	monkeySphere.Draw(rippleShader, view, projection, camPos, time, 997, 0);
}
