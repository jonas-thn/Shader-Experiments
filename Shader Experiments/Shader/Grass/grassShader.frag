#version 330 core

in vec2 TexCoords;
in vec3 Normals;
in vec3 FragPos;

in vec3 vColor;

uniform vec3 cameraPos;

out vec4 FragColor;

void main()
{
	vec3 lightDir = normalize(vec3(-1.0, 1.0, 2.0));
	float diffuse = max(0.0, dot(lightDir, normalize(Normals)));
	vec3 finalColor = mix(vColor * diffuse, vColor, 0.7);

	FragColor = vec4(finalColor, 0.0);
}
