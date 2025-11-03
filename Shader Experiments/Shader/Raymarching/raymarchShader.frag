#version 330 core

in vec2 TexCoords;
in vec3 Normals;
in vec3 FragPos;

uniform vec3 cameraPos;
uniform int index;
uniform float time;

out vec4 FragColor;

float sdfSphere(vec3 p, float r)
{
	return length(p) - r;
}

float sdfBox( vec3 p, vec3 b ) {
  vec3 q = abs(p) - b;
  return length(max(q,0.0)) + min(max(q.x,max(q.y,q.z)),0.0);
}

float sdfTorus( vec3 p, vec2 t )
{
  vec2 q = vec2(length(p.xz)-t.x,p.y);
  return length(q)-t.y;
}

mat3 rotateX(float angle)
{
    float s = sin(angle);
    float c = cos(angle);

    return mat3(1.0, 0.0, 0.0,
                0.0, c, s,
                0.0, -s, c);
}

float map(vec3 pos)
{
//	float dist = sdfSphere(pos - vec3(0.0, 0.0, 5.0), 1.0);
	vec3 p = pos - vec3(0.0, 0.0, 5.0);

	p = rotateX(time) * p;

	float dist = sdfTorus(p, vec2(0.5, 0.2));
	return dist;
}

const int NUM_STEPS = 256;
const float MAX_DIST = 1000.0;

vec3 Raymarch(vec3 cameraOrigin, vec3 cameraDir)
{
	vec3 pos;
	float dist = 0;

	for(int i = 0; i < NUM_STEPS; i++)
	{
		pos = cameraOrigin + dist * cameraDir;

		float distToScene = map(pos);

		if(distToScene < 0.0001)
		{
			break;
		}

		dist += distToScene;

		if(dist > MAX_DIST)
		{
			return vec3(0.0);
		}
	}

	return vec3(1.0);
}

void main()
{
	vec2 pixelCoords = vec2((TexCoords - 0.5).r * 1600, (TexCoords - 0.5).g * 900);

	vec2 sceneUvs = (TexCoords - 0.5) * 2.0;
	vec2 correctedUvs = vec2(sceneUvs.r , sceneUvs.g * (9.0 / 16.0));

	vec3 rayDir = normalize(vec3(correctedUvs, 1.0));
	vec3 rayOrigin = vec3(0.0);

	vec3 baseColor = Raymarch(rayOrigin, rayDir);

	FragColor = vec4(baseColor, 1.0);
    FragColor = pow(FragColor, vec4(1/1.8));
}
