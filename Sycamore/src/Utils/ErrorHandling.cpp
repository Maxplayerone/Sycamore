#include"ErrorHandling.h"

void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		LOGGER_ERROR("[OpenGl error], %s", error);
		return false;
	}
	return true;
}
