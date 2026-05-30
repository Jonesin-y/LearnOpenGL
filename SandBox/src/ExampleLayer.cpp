#include "ExampleLayer.h"
#include<iostream>
ExampleLayer::ExampleLayer()
{
	Renderer3D::Init();
	m_ShaderLibrary = std::make_shared<ShaderLibrary>();
	//Set Camera
	m_Cameras.emplace("myCamera",std::make_shared<Camera>());
	m_CameraControllers.emplace( "myCamera",std::make_shared<CameraController>(m_Cameras["myCamera"]) );
	//Set Texture2Ds
	std::shared_ptr<Texture2D>  defaultTexture = Texture2D::Create("assets/Texture2D/defaultTexture.png");
	std::shared_ptr<Texture2D>  container2 = Texture2D::Create("assets/Texture2D/container2.png");
	std::shared_ptr<Texture2D>  SpecularMap = Texture2D::Create("assets/Texture2D/SpecularMap.png");
	std::shared_ptr<Texture2D>  emission = Texture2D::Create("assets/Texture2D/emission.jpg");
	defaultTexture->Bind(0);
	container2->Bind(1);
	SpecularMap->Bind(2);
	emission->Bind(3);
	m_Texture2Ds.insert({ "defaultTexture",defaultTexture });
	m_Texture2Ds.insert({ "container2",container2 });
	m_Texture2Ds.insert({ "SpecularMap",SpecularMap });
	m_Texture2Ds.insert({ "emission",emission });
	//Set Environment value
	auto environment_temp = std::make_shared<Environment>();
	std::vector<lightSource>lightSources_temp;
	lightSource u_DirLight = lightSource();
	lightSource u_FlashLight= lightSource();
	lightSource u_PointLight[4]=
	{
		lightSource(),
		lightSource(),
		lightSource(),
		lightSource()
	
	};
	u_PointLight[0].position = glm::vec3(0.0f, 0.0f, 0.0f);
	u_PointLight[0].ambient = glm::vec3(0.02f, 0.06f, 0.08f);
	u_PointLight[0].diffuse = glm::vec3(0.1f, 0.3f, 0.4f);
	u_PointLight[0].specular = glm::vec3(0.2f, 0.6f, 0.8f);
	u_PointLight[0].radius = 10.0f;
	u_PointLight[0].intensity = 25.0f;

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
	lightSources_temp.push_back(u_PointLight[0]);
	lightSources_temp.push_back(u_PointLight[1]);
	lightSources_temp.push_back(u_PointLight[2]);
	lightSources_temp.push_back(u_PointLight[3]);
	lightSources_temp.push_back(u_DirLight);
	lightSources_temp.push_back(u_FlashLight);

	environment_temp->SetLightSources(lightSources_temp);

	//Set Shaders and Materials
	Ref(Shader) Basic_shader = std::make_shared<Shader>("assets/shaders/cube.vert", "assets/shaders/cube.frag");
	m_ShaderLibrary->Add("Basic_shader", Basic_shader);
	Ref(Shader) Light_shader = std::make_shared<Shader>("assets/shaders/light.vert", "assets/shaders/light.frag");
	m_ShaderLibrary->Add("Light_shader", Light_shader);
	Ref(Material) u_mapMaterial = std::make_shared<Material>("u_mapMaterial");
	Ref(Material) u_lightMaterial[4] =
	{
		std::make_shared<Material>("u_lightMaterial"),
		std::make_shared<Material>("u_lightMaterial"),
		std::make_shared<Material>("u_lightMaterial"),
		std::make_shared<Material>("u_lightMaterial")
	};

	u_mapMaterial->shininess = 32.0f;
	u_mapMaterial->diffuseMapID = 1;
	u_mapMaterial->specularMapID = 2;
	u_mapMaterial->emissionMapID = 3;
	u_mapMaterial->SetShader(Basic_shader);
	m_Materials.insert({ "u_mapMaterial",u_mapMaterial});

	u_lightMaterial[0]->colorAmbient  = glm::vec3(0.02f, 0.06f, 0.08f);
	u_lightMaterial[0]->colorDiffuse  = glm::vec3(0.1f, 0.3f, 0.4f);
	u_lightMaterial[0]->colorSpecular = glm::vec3(0.2f, 0.6f, 0.8f);
	u_lightMaterial[0]->SetShader(Light_shader);
	m_Materials.insert({ "u_lightMaterial0",u_lightMaterial[0]});

	u_lightMaterial[1]->colorAmbient  = glm::vec3(0.04f, 0.02f, 0.08f);
	u_lightMaterial[1]->colorDiffuse  = glm::vec3(0.4f, 0.2f, 0.8f);
	u_lightMaterial[1]->colorSpecular = glm::vec3(0.4f, 0.2f, 0.8f);
	u_lightMaterial[1]->SetShader(Light_shader);
	m_Materials.insert({ "u_lightMaterial1",u_lightMaterial[1] });

	u_lightMaterial[2]->colorAmbient  = glm::vec3(0.03f, 0.00f, 0.00f);
	u_lightMaterial[2]->colorDiffuse  = glm::vec3(0.6f, 0.6f, 0.6f);
	u_lightMaterial[2]->colorSpecular = glm::vec3(0.4f, 0.0f, 0.0f);
	u_lightMaterial[2]->SetShader(Light_shader);
	m_Materials.insert({ "u_lightMaterial2",u_lightMaterial[2] });

	u_lightMaterial[3]->colorAmbient  = glm::vec3(0.04f, 0.04f, 0.04f);
	u_lightMaterial[3]->colorDiffuse  = glm::vec3(0.6f, 0.6f, 0.6f);
	u_lightMaterial[3]->colorSpecular = glm::vec3(0.5f, 0.5f, 0.5f);
	u_lightMaterial[3]->SetShader(Light_shader);
	m_Materials.insert({ "u_lightMaterial3",u_lightMaterial[3] });

	

	//Set Meshes Data
	std::vector<Vertex> vertices = {
		// positions          // normals           // texture coords
		//back
		{ glm::vec3(-0.5f, -0.5f, -0.5f),glm::vec3(0.0f,  0.0f, -1.0f),  glm::vec2(0.0f, 0.0f)},//0
		{ glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(0.0f,  0.0f, -1.0f),  glm::vec2(1.0f, 0.0f)},//1
		{ glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec3(0.0f,  0.0f, -1.0f),  glm::vec2(1.0f, 1.0f)},//2
		{ glm::vec3(-0.5f,  0.5f, -0.5f),  glm::vec3(0.0f,  0.0f, -1.0f),  glm::vec2(0.0f, 1.0f)},//3
		//front
		{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0.0f,  0.0f, 1.0f),	  glm::vec2(0.0f, 0.0f)},//4
		{ glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3(0.0f,  0.0f, 1.0f),	  glm::vec2(1.0f, 0.0f)},//5
		{ glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3(0.0f,  0.0f, 1.0f),	  glm::vec2(1.0f, 1.0f)},//6
		{ glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0.0f,  0.0f, 1.0f),	  glm::vec2(0.0f, 1.0f)},//7
		//left
		{ glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(1.0f, 0.0f)},//8
		{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(1.0f, 1.0f)},//9
		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(0.0f, 1.0f)},//10
		{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(0.0f, 0.0f)},//11
		//right
		{ glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec3(1.0f,  0.0f,  0.0f),  glm::vec2(1.0f, 0.0f)},//12
		{ glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec3(1.0f,  0.0f,  0.0f),  glm::vec2(1.0f, 1.0f)},//13
		{ glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(1.0f,  0.0f,  0.0f),  glm::vec2(0.0f, 1.0f)},//14
		{ glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec3(1.0f,  0.0f,  0.0f),  glm::vec2(0.0f, 0.0f)},//15
		 //bottom
		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f,  0.0f),  glm::vec2(0.0f, 1.0f)},//16
		{ glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f,  0.0f),  glm::vec2(1.0f, 1.0f)},//17
		{ glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3(0.0f, -1.0f,  0.0f),  glm::vec2(1.0f, 0.0f)},//18
		{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0.0f, -1.0f,  0.0f),  glm::vec2(0.0f, 0.0f)},//19
		//top
		{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0.0f,  1.0f,  0.0f),  glm::vec2(0.0f, 1.0f)},//20
		{ glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3(0.0f,  1.0f,  0.0f),  glm::vec2(1.0f, 1.0f)},//21
		{ glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3(0.0f,  1.0f,  0.0f),  glm::vec2(1.0f, 0.0f)},//22
		{ glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0.0f,  1.0f,  0.0f),  glm::vec2(0.0f, 0.0f)}//23
	};
	std::vector<unsigned int> indices = {
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
	m_Meshs.emplace("cube",std::make_shared<Mesh>(vertices, indices));
	//Transform Position Data
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
	//Set Basic Transforms
	m_Transforms.emplace_back(glm::translate(glm::mat4(1.0f), cubePositions[0]));
	m_Transforms.emplace_back(glm::translate(glm::mat4(1.0f), cubePositions[1]));
	m_Transforms.emplace_back(glm::translate(glm::mat4(1.0f), cubePositions[2]));
	m_Transforms.emplace_back(glm::translate(glm::mat4(1.0f), cubePositions[3]));
	m_Transforms.emplace_back(glm::translate(glm::mat4(1.0f), cubePositions[4]));
	m_Transforms.emplace_back(glm::translate(glm::mat4(1.0f), cubePositions[5]));
	m_Transforms.emplace_back(glm::translate(glm::mat4(1.0f), cubePositions[6]));
	m_Transforms.emplace_back(glm::translate(glm::mat4(1.0f), cubePositions[7]));
	m_Transforms.emplace_back(glm::translate(glm::mat4(1.0f), cubePositions[8]));
	m_Transforms.emplace_back(glm::translate(glm::mat4(1.0f), cubePositions[9]));

	m_Renderer3D = std::make_shared<Renderer3D>(m_Cameras["myCamera"], environment_temp);


}
void ExampleLayer::OnAttach()
{

}

void ExampleLayer::OnDetach()
{
}

void ExampleLayer::OnUpdate(float deltatime)
{
	if (m_Cameras.find("myCamera") == m_Cameras.end())
	{
		printf("myCamera doesn't exist!");
		__debugbreak();
	}
	if (m_CameraControllers.find("myCamera") == m_CameraControllers.end())
	{
		printf("myCamera's controller doesn't exist!");
		__debugbreak();
	}
	if (m_Meshs.find("cube") == m_Meshs.end())
	{
		printf("cube mesh doesn't exist!");
		__debugbreak();
	}
	if (m_Materials.find("u_mapMaterial") == m_Materials.end())
	{
		printf("u_mapMaterial doesn't exist!");
		__debugbreak();
	}
	if (m_Materials.find("u_lightMaterial0") == m_Materials.end())
	{
		printf("u_lightMaterial doesn't exist!");
		__debugbreak();
	}
	if (m_Materials.find("u_lightMaterial1") == m_Materials.end())
	{
		printf("u_lightMaterial doesn't exist!");
		__debugbreak();
	}
	if (m_Materials.find("u_lightMaterial2") == m_Materials.end())
	{
		printf("u_lightMaterial doesn't exist!");
		__debugbreak();
	}
	if (m_Materials.find("u_lightMaterial3") == m_Materials.end())
	{
		printf("u_lightMaterial doesn't exist!");
		__debugbreak();
	}
	
	m_Renderer3D->BeginScene();
	m_CameraControllers["myCamera"]->OnUpdate(deltatime);
	m_Renderer3D->GetEnvironment()->GetLightSources()[5].position = m_Renderer3D->GetCamera()->Position;
	m_Renderer3D->GetEnvironment()->GetLightSources()[5].direction = m_Renderer3D->GetCamera()->Front;
	for (int i = 0;i < 10;i++)
	{
		if (i % 3 != 0)
			m_Renderer3D->SubmitMesh(m_Meshs["cube"], m_Materials["u_mapMaterial"], m_Transforms[i]);
	}
	for (int i = 0;i < 4;i++)
	{
		m_Renderer3D->SubmitMesh(m_Meshs["cube"], m_Materials["u_lightMaterial" + std::to_string(i)], m_Transforms[i * 3]);
	}
	m_Renderer3D->EndScene();


}

void ExampleLayer::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
	if (!event.Handled)
	{
		if (m_CameraControllers.find("myCamera") == m_CameraControllers.end())
		{
			printf("myCamera doesn't exist!");
			__debugbreak();
		}
		m_CameraControllers["myCamera"]->OnEvent(event);
	}
}

void ExampleLayer::OnKeyPressedEvent(KeyPressedEvent& event)
{
	if (event.GetKeyCode() == GLFW_KEY_F)
	{
		if (m_Renderer3D->GetEnvironment()->GetLightSources()[5].enableLight == true)
			m_Renderer3D->GetEnvironment()->GetLightSources()[5].enableLight = false;
		else
			m_Renderer3D->GetEnvironment()->GetLightSources()[5].enableLight = true;
	}
}
