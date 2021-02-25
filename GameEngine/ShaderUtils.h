#pragma once
#include <GL/glew.h>

namespace GE {
	bool compileProgram(const GLchar* v_shader_sourcecode[], const GLchar* f_shader_sourcecode[], GLuint* programId);
}