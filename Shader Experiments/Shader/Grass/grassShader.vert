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

out vec3 vColor;

vec2 hashVec2(float p) {
  vec2 r = vec2(
      dot(vec2(p), vec2(17.43267, 23.8934543)),
      dot(vec2(p), vec2(13.98342, 37.2435232)));
  return fract(sin(r) * 1743.54892229);
}

vec3 hashVec3(vec3 p)
{
	p = vec3(
        dot(p,vec3(127.1,311.7, 74.7)),
			  dot(p,vec3(269.5,183.3,246.1)),
			  dot(p,vec3(113.5,271.9,124.6)));

	return fract(sin(p)*43758.5453123);
}

vec3 quadraticBezier(vec3 p0, vec3 p1, vec3 p2, float t) {
    float u = 1.0 - t;
    return u * u * p0 + 2.0 * u * t * p1 + t * t * p2;
}

vec3 cubicBezier(vec3 p0, vec3 p1, vec3 p2, vec3 p3, float t) {
    float u = 1.0 - t;
    return u * u * u * p0 + 
           3.0 * u * u * t * p1 + 
           3.0 * u * t * t * p2 + 
           t * t * t * p3;
}

mat3 rotateY(float theta) {
  float c = cos(theta);
  float s = sin(theta);
  return mat3(
      vec3(c, 0, s),
      vec3(0, 1, 0),
      vec3(-s, 0, c)
  );
}

const vec3 BASE_COLOR = vec3(0.02, 0.1, 0.01);
const vec3 TIP_COLOR = vec3(0.5, 0.7, 0.3);

void main()
{
    const float PI = 3.141562;

    //rotation
    float angle = fract(sin(float(gl_InstanceID + 0.1 * index) * 12.9898) * 43758.5453) * 2.0 * PI;
    vec3 rotatedPos = rotateY(angle) * aPos;

    //bend
    float bendAmount = sin(time) * 0.5; 
    rotatedPos.x += rotatedPos.y * rotatedPos.y * bendAmount;

    //offset
    vec2 hashed2D = hashVec2(float(gl_InstanceID + 0.1 * index)) * 2.0 - 1.0;
    vec3 grassOffset = vec3(hashed2D.x, -0.5, hashed2D.y) * 2.0;
	vec3 localPos = rotatedPos + grassOffset;
    vec4 worldPos = model * vec4(localPos, 1.0);

    FragPos = worldPos.xyz;
    TexCoords = aTexCoords;
    Normals = normalize(transpose(inverse(mat3(model))) * aNormals);
    gl_Position = projection * view * worldPos;

    vColor = mix(BASE_COLOR, TIP_COLOR, aPos.y / 0.5);
}
