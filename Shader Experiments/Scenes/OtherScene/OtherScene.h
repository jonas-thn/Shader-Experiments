#pragma once

#include "../Scene.h"
#include "../../MeshData.h"
#include "../../Mesh.h"
#include <vector>

class OtherScene : public Scene
{
public:
	OtherScene() = default;
	virtual ~OtherScene() = default;

	void Init() override;
	void Update(float dt) override;
	void Draw(glm::mat4& view, glm::mat4& projection, glm::vec3& camPos, float time) override;

private:
	Shader noiseShader = Shader("./Shader/Noise/noiseShader.vert", "./Shader/Noise/noiseShader.frag");
	Shader rippleShader = Shader("./Shader/Lighting/lightingShader.vert", "./Shader/Lighting/lightingShader.frag");

	Mesh sphereNoise = Mesh("./Models/sphere_high.obj");
	Mesh sphereRipple = Mesh("./Models/sphere_high.obj");
	Mesh monkeyExplode = Mesh("./Models/monkey_high.obj");
	Mesh monkeySphere = Mesh("./Models/monkey_high.obj");
};
