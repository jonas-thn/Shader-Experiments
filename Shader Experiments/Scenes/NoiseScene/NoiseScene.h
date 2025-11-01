#pragma once

#include "../Scene.h"
#include "../../MeshData.h"
#include "../../Mesh.h"
#include <vector>

class NoiseScene : public Scene
{
public:
	NoiseScene() = default;
	virtual ~NoiseScene() = default;

	void Init() override;
	void Update(float dt) override;
	void Draw(glm::mat4& view, glm::mat4& projection, glm::vec3& camPos, float time) override;

private:
	Shader noiseShader = Shader("./Shader/Noise/noiseShader.vert", "./Shader/Noise/noiseShader.frag");

	Mesh screen = Mesh(
		std::vector<float>(std::begin(screenVertices), std::end(screenVertices)),
		{}
	);
};

