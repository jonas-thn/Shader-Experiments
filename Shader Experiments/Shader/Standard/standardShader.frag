#version 330 core

in vec2 TexCoords;
in vec3 Normals;
in vec3 FragPos;

uniform vec3 cameraPos;

out vec4 FragColor;

void main()
{
	vec3 baseColor = vec3(0.2);

	vec3 lightDir = normalize(vec3(1.0, 1.0, 1.0));
	float diffuse = max(0.0, dot(lightDir, normalize(Normals)));
	vec3 finalColor = baseColor + diffuse;

	FragColor = vec4(finalColor, 1.0);
}
