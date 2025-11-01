#version 330 core

in vec2 TexCoords;
in vec3 FragPos;

uniform vec3 cameraPos;

out vec4 FragColor;

void main()
{
	vec3 baseColor = vec3(1.0);

	float dist = distance(vec2(0, 0), FragPos.xy);

	FragColor = vec4(dist, dist, dist, 1.0);
}
