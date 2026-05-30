#pragma once
#include<utility>
class Input
{
public:
	static bool IsKeyPressed(int KeyCode);
	static bool IsKeyReleased(int KeyCode);
	static bool IsMousePressed(int MouseCode);
	static std::pair<float,float> GetCursorPos();
	static float GetCursorPosX();
	static float GetCursorPosY();
private:
	static Input* s_Input;
};


