#pragma once

#include <vector>
#include "../Shader.h"
#include "../Mesh.h"

class Scene
{
public:
	virtual ~Scene() = default;

	virtual void Init() = 0;
	virtual void Update(float dt) = 0;
	virtual void Draw(glm::mat4& view, glm::mat4& projection, glm::vec3& camPos, float time) = 0;

protected:
	std::vector<Mesh*> meshList;
};