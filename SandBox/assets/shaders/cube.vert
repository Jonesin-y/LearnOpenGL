#version 430 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout(location = 2) in vec2 TexCoord;
layout(std140,binding = 0)uniform CameraMat
{
	vec3 viewPos;
	mat4 Proj;
	mat4 View;
};
uniform mat4 u_Model;

uniform mat3 u_normalMat;
out vec2 f_TexCoord;
out vec3 f_fragPos;
out vec3 f_normal;
void main()
{
	f_fragPos = vec3(u_Model * vec4(position, 1.0));
	f_normal = u_normalMat * normal;
	
	mat4 MVP = Proj * View * u_Model; 
	gl_Position = MVP * vec4(position,1.0);
	f_TexCoord = TexCoord;
	
}