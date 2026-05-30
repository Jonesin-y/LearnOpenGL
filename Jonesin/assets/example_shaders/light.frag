#version 430 core
struct mapMaterial
{
	float shininess;
	vec3 colorAmbient;
	vec3 colorDiffuse;
	vec3 colorSpecular;
	sampler2D diffuseMapID;
	sampler2D specularMapID;
	sampler2D emissionMapID;
};
uniform mapMaterial u_lightMaterial;
out vec4 FragColor;
void main()
{
	vec3 result = u_lightMaterial.colorAmbient + u_lightMaterial.colorDiffuse + u_lightMaterial.colorSpecular;
	FragColor = vec4(result, 1.0f);
}