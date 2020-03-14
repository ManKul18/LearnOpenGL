#pragma once

#include <GL/glew.h>

#define ASSERT(X) do { if(!(X) )__debugbreak();}while(0)
#define GLCall(X) ClearGLError();\
X;\
ASSERT(PrintGLError(__FILE__, #X,__LINE__));



void ClearGLError();
bool PrintGLError(const char* fileName, const char* functionName, const int lineNumber);
