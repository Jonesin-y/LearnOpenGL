#vertex
#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout(location = 2) in vec2 TexCoord;
uniform mat4 u_MVP;
uniform mat4 u_Model;

uniform mat3 u_normalMat;
out vec2 f_TexCoord;
out vec3 f_fragPos;
out vec3 f_normal;
void main()
{
	f_fragPos = vec3(u_Model * vec4(position, 1.0));
	f_normal = u_normalMat * normal;
	
	gl_Position = u_MVP * vec4(position,1.0);
	f_TexCoord = TexCoord;
	
}
#fragment
#version 330 core
struct mapMaterial
{
	float shininess;
	sampler2D diffuseMapID;
	sampler2D specularMapID;
	sampler2D emissionMapID;
};
uniform mapMaterial u_mapMaterial;
struct lightSource
{
	bool enableLight;
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

	uniform vec3 u_viewPos;
	uniform mat4 u_Model;
    in vec3 f_normal;
    in vec3 f_fragPos;
	in vec2 f_TexCoord;
	out vec4 FragColor;
	void main()
	{
	float attenuation = 1.0f;
	float I = 1.0f;
//ambient sets
		vec3 norm = normalize(f_normal);
		vec3 lightDir;
		vec3 direction = normalize(u_light.direction);
		
	if (u_light.position.w == 1.0f)
//caculate attenuation	
	{
		lightDir = normalize(vec3(u_light.position) - f_fragPos);
		float theta = dot(direction , -lightDir);
		I = clamp((theta - u_light.outCut) / (u_light.innerCut - u_light.outCut), 0.0f, 1.0f);
		float distance = length(vec3(u_light.position) - f_fragPos);
		attenuation = 1.0 / (distance * distance + 1.0f);
		float over_r = distance / u_light.radius;
		float over_r_4 = over_r * over_r * over_r * over_r;
		float window = clamp(1.0 - over_r_4, 0.0f, 1.0f);
		attenuation *= window * window;
	}
	else if (u_light.position.w == 0.0f)
			lightDir = normalize(vec3(-u_light.position));
//diffuse sets
	
		vec3 viewDir = normalize(vec3(u_viewPos) - f_fragPos);
		vec3 reflectDir = reflect(-lightDir, norm);
		
//specular sets
		float spec = pow(max(dot(reflectDir, viewDir), 0.0f), u_mapMaterial.shininess);
		vec3 ambient = vec3(texture(u_mapMaterial.diffuseMapID, f_TexCoord)) * u_light.ambient;
		float diff = max(dot(norm, lightDir), 0.0f);
		vec3 diffuse = vec3(texture(u_mapMaterial.diffuseMapID, f_TexCoord)) * (diff * u_light.diffuse);
		vec3 currentSpecular = vec3(texture(u_mapMaterial.specularMapID, f_TexCoord));
		vec3 specular = currentSpecular * (spec * u_light.specular);
		vec3 emission = 0.3 * vec3(texture(u_mapMaterial.emissionMapID, f_TexCoord));
		
		vec3 result;
		ambient *= attenuation;
		if (u_light.enableLight)
	    {	
		diffuse *= attenuation * u_light.intensity * I;
		specular *= attenuation * u_light.intensity * I;
		result = ambient + diffuse + specular + emission;
		}
		else
		{
		result = ambient + emission;
		}
	
		
		FragColor = vec4(result, 1.0f);
		//for debug
		//FragColor = texture(u_mapMaterial.diffuseMapID,f_TexCoord);
		//FragColor = texture(u_mapMaterial.specularMapID, f_TexCoord);

	}