#version 430 core
struct mapMaterial
{
	float shininess;
	sampler2D diffuseMapID;
	sampler2D specularMapID;
	sampler2D emissionMapID;
};
struct lightSource
{
	bool enableLight;
	float radius;
	float intensity;
	float outCut;
	float innerCut;
	vec3 position;
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};



uniform mapMaterial u_mapMaterial;

uniform lightSource u_light;

uniform lightSource u_DirLight;
uniform lightSource u_PointLight[4];
uniform lightSource u_FlashLight;

uniform vec3 u_viewPos;
uniform mat4 u_Model;
in vec3 f_normal;
in vec3 f_fragPos;
in vec2 f_TexCoord;
out vec4 FragColor;

vec3 norm;
vec3 viewDir;
vec3 material_ambient;
vec3 material_diffuse;
vec3 material_specular;
vec3 material_emission;


vec3 caculateDirLight(lightSource DirLight)
{
	vec3 lightDir = normalize(DirLight.direction);
	vec3 ambient = material_ambient*DirLight.ambient;
	float diff =  max(dot(lightDir,norm),0.0f);
	vec3 diffuse = DirLight.intensity *diff * material_diffuse * DirLight.diffuse;
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(reflectDir,viewDir),0.0f),u_mapMaterial.shininess);
	vec3 specular = DirLight.intensity*spec*material_specular * DirLight.specular;
	return ambient + diffuse + specular ;
	
}

vec3 caculateSpotLight(lightSource SpotLight)
{
	vec3 viewDir = normalize(u_viewPos - f_fragPos);
	vec3 lightDir = normalize(SpotLight.position - f_fragPos);

	//caculate attenuation
	float attenuation = 1.0f;
	float distance = length(SpotLight.position-f_fragPos);
	attenuation*= 1.0f/(distance*distance + 1.0f);
	float over_r = distance/SpotLight.radius;
	float over_r_4 = over_r *over_r *over_r *over_r;
	float window = clamp(1-over_r_4,0.0f,1.0f);
	attenuation*=window * window;

	vec3 ambient =attenuation*material_ambient * SpotLight.ambient;
	
	float diff = max(dot(norm,lightDir),0.0f);
	vec3 diffuse =  SpotLight.intensity*attenuation*diff *material_diffuse*SpotLight.diffuse;

	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0f),u_mapMaterial.shininess);
	vec3 specular = SpotLight.intensity*attenuation * spec * material_specular*SpotLight.specular;
	

	return ambient + diffuse + specular ;
}

vec3 caculateFlashLight(lightSource FlashLight)
{
	vec3 lightDir = normalize(FlashLight.position - f_fragPos);
	vec3 viewDir = normalize(u_viewPos - f_fragPos);
	//caculate attenuation
	float attenuation = 1.0f;
	float distance = length(FlashLight.position-f_fragPos);
	attenuation*=1.0/(distance*distance + 1.0f);
	float over_r = distance/FlashLight.radius;
	float over_r_4 =over_r*over_r*over_r*over_r;
	float window = clamp(1-over_r_4,0.0f,1.0f);
	attenuation*=window*window;
	//caculate I
	float theta = dot(-FlashLight.direction,lightDir);
	float I = clamp((theta - FlashLight.outCut)/(FlashLight.innerCut - FlashLight.outCut),0.0f,1.0f);
	vec3 ambient = attenuation*material_ambient*FlashLight.ambient;
	float diff = max(dot(lightDir,norm),0.0f);
	vec3 diffuse = FlashLight.intensity*I* attenuation*diff *material_diffuse*FlashLight.diffuse;

	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0f),u_mapMaterial.shininess);
	vec3 specular = FlashLight.intensity*I*attenuation*spec * material_specular*FlashLight.specular;
	if(!FlashLight.enableLight) return vec3(0.0f);
	return ambient + diffuse + specular ;
}
	
	void main()
	{
		norm = normalize(f_normal);
		viewDir = normalize(u_viewPos - f_fragPos);
		
		material_diffuse = vec3(texture(u_mapMaterial.diffuseMapID,f_TexCoord));
		material_ambient =material_diffuse;
		material_specular = vec3(texture(u_mapMaterial.specularMapID,f_TexCoord));
		material_emission = vec3(texture(u_mapMaterial.emissionMapID,f_TexCoord));

		vec3 DirLight  	= 	caculateDirLight(u_DirLight);
		vec3 SpotLight 	= 	caculateSpotLight(u_PointLight[0])+
							caculateSpotLight(u_PointLight[1])+
							caculateSpotLight(u_PointLight[2])+
							caculateSpotLight(u_PointLight[3]);
		vec3 FlashLight = 	caculateFlashLight(u_FlashLight);

		vec3 emission 	=0.3*material_emission;
		vec3 result		= DirLight + SpotLight + FlashLight + emission;
		FragColor = vec4(result, 1.0f);
		//for debug
		//FragColor = texture(u_mapMaterial.diffuseMapID,f_TexCoord);
		//FragColor = texture(u_mapMaterial.specularMapID, f_TexCoord);

	}