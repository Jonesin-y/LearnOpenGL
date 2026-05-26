#version 330 core
struct lightSource
{
	int enableLight;
	float radius;
	float intensity;
	float outCut;
	float innerCut;
	vec4 position;
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform lightSource u_light;
out vec4 FragColor;
void main()
{
	vec3 result = u_light.ambient + u_light.diffuse + u_light.specular;
	FragColor = vec4(result, 1.0f);
}