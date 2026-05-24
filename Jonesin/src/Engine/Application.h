#pragma once
class GLFWwindow;
class Application
{
public:
	void OnEvent();
	void OnUpdate();


private:
	//个人项目暂时只考虑window平台，所以就不单独封装Window类了
	GLFWwindow* m_Window;
};

