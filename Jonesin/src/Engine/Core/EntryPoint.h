#pragma once
#include"Application.h"
Application* app = CreateApplication();
int main()
{
	app->Run();
	delete app;
}