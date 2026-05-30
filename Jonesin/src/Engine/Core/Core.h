#pragma once
#include<memory>
#include<functional>

void EnableOpenGLDebugging();
#define TO_STRING(x) #x

#define Ref(x) std::shared_ptr<x>
#define Scope(x) std::unique_ptr<x>

//used for event system
#define BIT(x) (1 << x)
#define BIND_EVENT_FN(x) std::bind(&x,this,std::placeholders::_1)