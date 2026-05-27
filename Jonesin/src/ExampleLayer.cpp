#include"pch.h"
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "shader.h"
#include"Buffer.h"
#include"VertexArray.h"
#include"Texture2D.h"
#include"Camera.h"
#include"CameraController.h"
#include"Materials/Material.h"
#include"lightSource.h"
#include"Core.h"

bool f_Pressed = false;


float deltaTime = 0.0f;
float lastFrame = 0.0f;
float rotateSpeed = 125.0f;
float moveSpeed = 5.0f;
static glm::vec3 cameraFront = glm::vec3(0.0f,0.0f,-1.0f);
double lastX = 0.0f;
double lastY = 0.0f;

Camera myCamera;
CameraController myCameraController(myCamera);
lightSource u_DirLight;
lightSource u_FlashLight;
lightSource u_PointLight[4];
void camera_cursor_callback(GLFWwindow* window, double xPos, double yPos)
{
	static bool firstMouse = true;

	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}
	static double xOffset = 0.0f;
	static double yOffset = 0.0f;
	xOffset = xPos - lastX;
	yOffset = lastY - yPos;
	lastX = xPos;
	lastY = yPos;
	myCamera.ProcessMouseMovement(xOffset, yOffset);
}
int main(void)
{
	u_PointLight[0].position = glm::vec3(0.0f, 0.0f, 0.0f);
	u_PointLight[0].ambient = glm::vec3(0.02f, 0.06f, 0.08f);
	u_PointLight[0].diffuse = glm::vec3(0.1f, 0.3f, 0.4f);
	u_PointLight[0].specular = glm::vec3(0.2f, 0.6f, 0.8f);
	u_PointLight[0].radius = 10.0f;
	u_PointLight[0].intensity= 25.0f;

	u_PointLight[1].position = glm::vec3(2.0f, 5.0f, -15.0f);
	u_PointLight[1].ambient = glm::vec3(0.04f, 0.02f, 0.08f);
	u_PointLight[1].diffuse = glm::vec3(0.4f, 0.2f, 0.8f);
	u_PointLight[1].specular = glm::vec3(0.4f, 0.2f, 0.8f);
	u_PointLight[1].radius = 17.0f;
	u_PointLight[1].intensity = 50.0f;

	u_PointLight[2].position = glm::vec3(-1.5f, -2.2f, -2.5f);
	u_PointLight[2].ambient = glm::vec3(0.03f, 0.00f, 0.00f);
	u_PointLight[2].diffuse = glm::vec3(0.3f, 0.0f, 0.0f);
	u_PointLight[2].specular = glm::vec3(0.4f, 0.0f, 0.0f);
	u_PointLight[2].radius = 14.0f;
	u_PointLight[2].intensity = 21.4f;

	u_PointLight[3].position = glm::vec3(-3.8f, -2.0f, -12.3f);
	u_PointLight[3].ambient = glm::vec3(0.04f, 0.04f, 0.04f);
	u_PointLight[3].diffuse = glm::vec3(0.6f, 0.6f, 0.6f);
	u_PointLight[3].specular = glm::vec3(0.5f, 0.5f, 0.5f);
	u_PointLight[3].radius = 7.0f;
	u_PointLight[3].intensity = 22.0f;

	u_DirLight.direction = glm::vec3(0.5, 0.5, 0.5);
	u_DirLight.ambient = glm::vec3(0.04f, 0.04f, 0.04f);
	u_DirLight.diffuse = glm::vec3(0.6f, 0.6f, 0.6f);
	u_DirLight.specular = glm::vec3(0.5f, 0.5f, 0.5f);
	u_DirLight.intensity = 2.0f;

	u_FlashLight.ambient = glm::vec3(0.04f, 0.04f, 0.04f);
	u_FlashLight.diffuse = glm::vec3(0.6f, 0.6f, 0.6f);
	u_FlashLight.specular = glm::vec3(1.0f, 1.0f, 1.0f);
	u_FlashLight.radius = 67.0f;
	u_FlashLight.intensity = 52.0f;
	u_FlashLight.innerCut = cos(glm::radians(20.0f));
	u_FlashLight.outCut = cos(glm::radians(25.0f));



	//Material materials[]
	//{
	//	// 0. gold (金)
	//	Material(0.4,glm::vec3(0.24725,0.1995,0.0745),glm::vec3(0.75164,0.60648,0.22648),glm::vec3(0.628281,0.555902,0.366065)),
	//	// 1. emerald (绿宝石)
	//	Material(0.6f, glm::vec3(0.0215f, 0.1745f, 0.0215f), glm::vec3(0.07568f, 0.61424f, 0.07568f), glm::vec3(0.633f, 0.727811f, 0.633f)),
	//
	//	// 2. ruby (红宝石)
	//	Material(0.6f, glm::vec3(0.1745f, 0.01175f, 0.01175f), glm::vec3(0.61424f, 0.04136f, 0.04136f), glm::vec3(0.727811f, 0.626959f, 0.626959f)),
	//
	//	// 3. chrome (铬合金/高光金属)
	//	Material(0.6f, glm::vec3(0.25f, 0.25f, 0.25f), glm::vec3(0.4f, 0.4f, 0.4f), glm::vec3(0.774597f, 0.774597f, 0.774597f)),
	//
	//	// 4. copper (铜)
	//	Material(0.1f, glm::vec3(0.19125f, 0.0735f, 0.0225f), glm::vec3(0.7038f, 0.27048f, 0.0828f), glm::vec3(0.256777f, 0.137622f, 0.086014f)),
	//
	//	// 5. silver (银)
	//	Material(0.4f, glm::vec3(0.19225f, 0.19225f, 0.19225f), glm::vec3(0.50754f, 0.50754f, 0.50754f), glm::vec3(0.508273f, 0.508273f, 0.508273f)),
	//
	//	// 6. red plastic (红塑料)
	//	Material(0.25f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.0f, 0.0f), glm::vec3(0.7f, 0.6f, 0.6f)),
	//
	//	// 7. cyan plastic (青色塑料)
	//	Material(0.25f, glm::vec3(0.0f, 0.1f, 0.06f), glm::vec3(0.0f, 0.50980392f, 0.50980392f), glm::vec3(0.50196078f, 0.50196078f, 0.50196078f)),
	//
	//	// 8. black rubber (黑橡胶)
	//	Material(0.078125f, glm::vec3(0.02f, 0.02f, 0.02f), glm::vec3(0.01f, 0.01f, 0.01f), glm::vec3(0.4f, 0.4f, 0.4f))
	//
	//
	//};
	Material u_mapMaterial;
	u_mapMaterial.shininess = 32.0f;
	u_mapMaterial.diffuseMapID = 1;
	u_mapMaterial.specularMapID = 2;
	u_mapMaterial.emissionMapID = 3;

	float vertices[] = {
		// positions          // normals           // texture coords
		//back
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,//0
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,//1
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,//2
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,//3
		//front
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,//4
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,//5
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,//6
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,//7
		//left
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,//8
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,//9
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,//10
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,//11
		//right
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,//12
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,//13
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,//14
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,//15
		 //bottom
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,//16
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,//17
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,//18
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,//19
		//top
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,//20
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,//21
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,//22
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,//23
	};
	int indices[] = {
		//back
		0,1,2,
		2,3,0,
		//front
		4,5,6,
		6,7,4,
		//left
		8,9,10,
		10,11,8,
		//right
		12,13,14,
		14,15,12,
		//bottom
		16,17,18,
		18,19,16,
		//top
		20,21,22,
		22,23,20
	};
	
glm::vec3 cubePositions[] = 
{
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};


	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(960, 640, "My OpenGL", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("Failed to initialize GLAD\n");
		return -1;
	}
	glEnable(GL_DEPTH_TEST);
	EnableOpenGLDebugging();
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, camera_cursor_callback);

	glClearColor(0.05f, 0.15f, 0.2f, 0.7f);



	//preprocess OpenGL_obj
	std::shared_ptr<Texture2D> defaultTexture = Texture2D::Create("assets/Texture2D/defaultTexture.png");
	std::shared_ptr<Texture2D>  container2 = Texture2D::Create("assets/Texture2D/container2.png");
	std::shared_ptr<Texture2D>  SpecularMap = Texture2D::Create("assets/Texture2D/SpecularMap.png");
	std::shared_ptr<Texture2D>  emission = Texture2D::Create("assets/Texture2D/emission.jpg");
	defaultTexture->Bind(0);
	container2->Bind(1);
	SpecularMap->Bind(2);
	emission->Bind(3);
	std::shared_ptr<Shader>Basic_shader = Shader::Create("assets/shaders/cube.vert","assets/shaders/cube.frag");
	std::shared_ptr<Shader>Light_shader = Shader::Create("assets/shaders/light.vert","assets/shaders/light.frag");
	GLuint Basic_shader_id = Basic_shader->GetShaderID();
	GLuint Light_shader_id = Light_shader->GetShaderID();
	VertexArray VAO = VertexArray();
	auto vb = VertexBuffer::Create(vertices, sizeof(vertices));
	auto ib = IndexBuffer::Create(indices, sizeof(indices));
	BufferLayout layout = {
		{ShaderType::Float3,"a_Position"},
		{ShaderType::Float3,"a_Normal"},
		{ShaderType::Float2,"a_TexCoord"}
	};
	vb->SetBufferLayout(layout);
	VAO.AddVertexBuffer(vb);
	//default shader
	Basic_shader->Bind();
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 View = glm::mat4(1.0f);


	glm::mat4 Projection = glm::mat4(1.0);
	glm::mat4 MVP = Projection * View * Model;
	Basic_shader->SetUniformMat4f("u_MVP", 1, GL_FALSE, &MVP[0][0]);
	float rotateRad = 0.0f;
	float rad = 0.0f;
	u_PointLight[0].ApplyToShader(Basic_shader, "u_PointLight[0]");
	u_PointLight[1].ApplyToShader(Basic_shader, "u_PointLight[1]");
	u_PointLight[2].ApplyToShader(Basic_shader, "u_PointLight[2]");
	u_PointLight[3].ApplyToShader(Basic_shader, "u_PointLight[3]");
	u_DirLight.ApplyToShader(Basic_shader, "u_DirLight");


	u_mapMaterial.ApplyToShader(Basic_shader, "u_mapMaterial");

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		float currentFrame = glfwGetTime();
		deltaTime = (deltaTime == 0.0f
			) ? 1.0 / 144.0f : currentFrame - lastFrame;
		glfwPollEvents();

		//deal with key code
		if(glfwGetKey(window,GLFW_KEY_LEFT_SHIFT)==GLFW_PRESS)
			rad = rad + rotateSpeed * deltaTime;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)				myCamera.ProcessKeyboard(BACKWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)				myCamera.ProcessKeyboard(FORWARD, deltaTime) ;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)				myCamera.ProcessKeyboard(LEFT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)				myCamera.ProcessKeyboard(RIGHT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)			myCamera.ProcessKeyboard(UP, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)	myCamera.ProcessKeyboard(DOWN, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && !f_Pressed)
		{
			f_Pressed = true;
			if (u_FlashLight.enableLight == true) u_FlashLight.enableLight = false;
			else if (u_FlashLight.enableLight == false) u_FlashLight.enableLight = true;
		}
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_RELEASE && f_Pressed) f_Pressed = false;
		if (glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)	glfwSetWindowShouldClose(window, true);
		rotateRad = rotateRad + rotateSpeed * deltaTime;

		lastFrame = currentFrame;
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		
		View = myCamera.GetViewMatrix();
			u_FlashLight.direction = myCamera.Front;
			u_FlashLight.position = glm::vec4(myCamera.Position, 1.0f);
		
		Projection = glm::perspective(glm::radians(45.0f), 960.0f / 640.0f, 0.1f, 100.0f);
		glm::mat4 rotation = glm::mat4(1.0f);
		
		
		u_FlashLight.ApplyToShader(Basic_shader, "u_FlashLight");

		Basic_shader->Bind();
		
		Basic_shader->SetUniform3f("u_viewPos", myCamera.Position.x, myCamera.Position.y, myCamera.Position.z);
		for (int i = 4;i < 10;i++)
		{
				float angle = 20.0 * i;
				rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle + rad), glm::vec3(0.5f, 0.5f, 0.0f));

				glm::mat4 translation0 = glm::translate(glm::mat4(1.0f), glm::vec3(cubePositions[i].x, cubePositions[i].y, cubePositions[i].z));
				Model = translation0 * rotation;
				Basic_shader->SetUniformMat4f("u_Model", 1, GL_FALSE, &Model[0][0]);
				glm::mat3 normalMat = glm::mat3(glm::transpose(glm::inverse(Model)));
				Basic_shader->SetUniformMat3f("u_normalMat", 1, GL_FALSE, &normalMat[0][0]);

				MVP = Projection * View * Model;

				Basic_shader->SetUniformMat4f("u_MVP", 1, GL_FALSE, &MVP[0][0]);
				//Basic_shader->ShaderLog();


				glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
		}
		Light_shader->Bind();
		for (int i = 0;i < 4;i++)
		{
			u_PointLight[i].ApplyToShader(Light_shader, "u_light");

			auto position1 = cubePositions[i];
			glm::mat4 translation1 = glm::translate(glm::mat4(1.0f), glm::vec3(position1.x, position1.y, position1.z));
			Model = translation1;
			MVP = Projection * View * Model;
			Light_shader->SetUniformMat4f("u_MVP", 1, GL_FALSE, &MVP[0][0]);
			//Light_shader->ShaderLog();

			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
		}
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

	}

	glfwTerminate();
	return 0;
}