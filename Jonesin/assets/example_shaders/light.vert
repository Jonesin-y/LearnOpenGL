#version 430 core
layout (location = 0) in vec3 position;
layout(std140,binding = 0)uniform CameraMat
{
	mat4 Proj;
	mat4 View;
};
uniform mat4 u_Model;
void main()
{
	mat4 MVP = Proj * View * u_Model;
	gl_Position = MVP * vec4(position, 1.0);
}