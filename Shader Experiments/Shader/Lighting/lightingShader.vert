#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormals;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;
uniform int index;

out vec2 TexCoords;
out vec3 Normals;
out vec3 FragPos;

void main()
{
    vec3 locPos = aPos;

    if(index == 1)
    {
        float t = sin(locPos.y * 20.0 + time * 10.0);
        t += 1.0;
        locPos += aNormals * t * 0.1;
    }

	vec4 worldPos = model * vec4(locPos, 1.0);
    FragPos = worldPos.xyz;
    TexCoords = aTexCoords;
    Normals = normalize(transpose(inverse(mat3(model))) * aNormals);
    gl_Position = projection * view * worldPos;
}
