#version 330 core

in vec2 TexCoords;
in vec3 Normals;
in vec3 FragPos;

in vec3 vColor;

uniform vec3 cameraPos;

out vec4 FragColor;

void main()
{
	vec3 color = vec3(0.3, 0.8, 0.3);
//	vec3 ambient = vec3(0.3, 0.8, 0.3);
//
//	vec3 lightDir = normalize(vec3(-1.0, 1.0, -1.0));
//	float diffuse = max(0.0, dot(lightDir, normalize(Normals)));
//	vec3 finalColor = baseColor * diffuse + ambient * 0.5;

	FragColor = vec4(vColor, 1.0);
}
