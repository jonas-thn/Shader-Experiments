#include "OtherScene.h"

void OtherScene::Init()
{
	noiseShader.Init();
	rippleShader.Init();

	sphereNoise.Init();
	sphereNoise.Translate(glm::vec3(1.0, 0.0, 0.0));
	meshList.push_back(&sphereNoise);

	sphereRipple.Init();
	sphereRipple.Translate(glm::vec3(-1.0, 0.0, 0.0));
	meshList.push_back(&sphereRipple);
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
}
