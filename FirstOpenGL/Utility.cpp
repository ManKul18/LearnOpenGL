#include <iostream>

#include "Utility.h"

void ClearGLError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool PrintGLError(const char* fileName, const char* functionName, const int lineNumber)
{
	unsigned int err;
	std::string ErrorString;
	while ((err = glGetError()) != GL_NO_ERROR) {
		switch (err) {
		case GL_INVALID_ENUM: ErrorString = "GL_INVALID_ENUM"; break;
		case GL_INVALID_VALUE: ErrorString = "GL_INVALID_VALUE"; break;
		case GL_INVALID_OPERATION: ErrorString = "GL_INVALID_OPERATION"; break;
		case GL_STACK_OVERFLOW: ErrorString = "GL_STACK_OVERFLOW"; break;
		case GL_STACK_UNDERFLOW: ErrorString = "GL_STACK_UNDERFLOW"; break;
		case GL_OUT_OF_MEMORY: ErrorString = "GL_OUT_OF_MEMORY"; break;
		case GL_INVALID_FRAMEBUFFER_OPERATION: ErrorString = "GL_INVALID_FRAMEBUFFER_OPERATION"; break;
		}
		std::cout << "Error : [ " << ErrorString << " ] File Name [ " << fileName << " ] Function [ " << functionName << " ] Line Number [ " << lineNumber << " ]" << std::endl;
		return false;
	}
	return true;
}