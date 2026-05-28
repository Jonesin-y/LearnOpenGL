#pragma once
#define Ref(x) std::shared_ptr<x>
#define Scope(x) std::unique_ptr<x>
#define CreateRef(x) std::make_shared<x>
#define CreateScope(x) std::make_unique<x>
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
#define BIT(x) (1 << x)
#define BIND_EVENT_FN(x) std::bind(&x,this,std::placeholders::_1)