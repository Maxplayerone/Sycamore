#include"ErrorHandling.h"

#include"../smpch.h"

#include"Logger.h"

void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::stringstream ss;
		ss << "[OpenGL error] " << error;
		LOGGER_ERROR(ss.str());
		return false;
	}
	return true;
}
