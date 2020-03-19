#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <GL/glew.h>

#define ASSERT(X) do { if(!(X) )__debugbreak();}while(0)
#define GLCall(X) ClearGLError();\
X;\
ASSERT(PrintGLError(__FILE__, #X,__LINE__));



void ClearGLError();
bool PrintGLError(const char* fileName, const char* functionName, const int lineNumber);

#endif // !__UTILITY_H__