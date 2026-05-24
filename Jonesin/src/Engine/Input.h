#pragma once

class Input
{
public:
	static bool IsKeyPressed(int KeyCode);
	static bool IsMousePressed(int MouseCode);
	static std::pair<float,float> GetCursorPos();
	static float GetCursorPosX();
	static float GetCursorPosY();
private:
	Input* s_Input;
};


