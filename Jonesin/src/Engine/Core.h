#pragma once
#include<glad/glad.h>
void APIENTRY glDebugOutput(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length, \
	const GLchar* message,
	const void* userParam);
void EnableOpenGLDebugging();


//used for event system
#define BIT(x) (1 << x);
#define JO_EVENT_FN std::bind()