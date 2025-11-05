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

float sdfPlane(vec3 pos)
{
	return pos.y;
}

mat3 rotateX(float angle)
{
    float s = sin(angle);
    float c = cos(angle);

    return mat3(1.0, 0.0, 0.0,
                0.0, c, s,
                0.0, -s, c);
}

vec3 RED = vec3(1.0, 0.0, 0.0);
vec3 BLUE = vec3(0.0, 0.0, 1.0);
vec3 GREEN = vec3(0.0, 1.0, 0.0);
vec3 GREY = vec3(0.5);
vec3 WHITE = vec3(1.0);

struct MaterialData {
	vec3 color;
	float dist;
};

MaterialData map(vec3 pos)
{
//	p = rotateX(time) * p; //nach Offset

	MaterialData result = MaterialData(GREY, sdfPlane(pos - vec3(0.0, -1.0, 0.0)));
	
	float dist = 0.0;

	dist = sdfBox(pos - vec3(-2.0, -0.0, 5.0), vec3(0.8));
	result.color = dist < result.dist ? RED : result.color;
	result.dist = min(result.dist, dist);

	dist = sdfBox(pos - vec3(2.0, -0.5, 5.0), vec3(0.8));
	result.color = dist < result.dist ? BLUE : result.color;
	result.dist = min(result.dist, dist);

	dist = sdfBox(pos - vec3(2.0, 1.5, 50 + sin(time) * 25.0), vec3(2.0));
	result.color = dist < result.dist ? GREEN : result.color;
	result.dist = min(result.dist, dist);

	return result;
}

vec3 CalculateNormal(vec3 pos)
{
	const float EPS = 0.0001;
	vec3 n = vec3(
		map(pos + vec3(EPS, 0.0, 0.0)).dist - map(pos - vec3(EPS, 0.0, 0.0)).dist, 
		map(pos + vec3(0.0, EPS, 0.0)).dist - map(pos - vec3(0.0, EPS, 0.0)).dist, 
		map(pos + vec3(0.0, 0.0, EPS)).dist - map(pos - vec3(0.0, 0.0, EPS)).dist
	);

	return normalize(n);
}

vec3 CalculateLighting(vec3 pos, vec3 normal, vec3 lightColor, vec3 lightDir)
{
	float dp = clamp((dot(normal, lightDir)), 0.0, 1.0);

	return lightColor * dp;
}

float CalculateShadow(vec3 pos, vec3 lightDir)
{
	float d = 0.01;
	for(int i = 0; i < 64; i++)
	{
		float distToScene = map(pos + lightDir * d).dist;

		if(distToScene < 0.001)
		{
			return 0.0;
		}

		d += distToScene;
	}

	return 1.0;
}

float CalculateAO(vec3 pos, vec3 normal)
{
	float ao = 0.0;
	float stepSize = 0.1;

	for(float i = 0.0; i < 5.0; i++)
	{
	float distFactor = 1.0 / pow(2.0, i);

		ao += distFactor * (i* stepSize - map(pos + normal * i * stepSize).dist);
	}

	return clamp(pow(1.0 - ao, 5.0), 0.0, 1.0);
}

const int NUM_STEPS = 256;
const float MAX_DIST = 1000.0;

vec3 Raymarch(vec3 cameraOrigin, vec3 cameraDir)
{
	vec3 pos;
	MaterialData material = MaterialData(vec3(0.0), 0.0);

	vec3 skyColor = vec3(0.55, 0.6, 1.0);

	for(int i = 0; i < NUM_STEPS; i++)
	{
		pos = cameraOrigin + material.dist * cameraDir;

		MaterialData result = map(pos);

		if(result.dist < 0.0001)
		{
			break;
		}

		material.dist += result.dist;
		material.color = result.color;

		if(material.dist > MAX_DIST)
		{
			return skyColor;
		}
	}

	vec3 lightDir = normalize(vec3(1.0, 3.0, -1.0));
	vec3 lightColor = WHITE;
	vec3 normal = CalculateNormal(pos);
	float shadows = CalculateShadow(pos, lightDir);
	vec3 lighting = CalculateLighting(pos, normal, lightColor, lightDir);
	lighting *= shadows;
	float ao = CalculateAO(pos, normal);
	vec3 color = material.color * lighting * ao;

	float fogFactor = 1.0 - exp(-pos.z * 0.01);
	color = mix(color, skyColor, fogFactor);

	return color;
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
