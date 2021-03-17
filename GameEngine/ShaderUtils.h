#pragma once
#include <GL/glew.h>
#include <string>

namespace GE {
	bool compileProgram(const GLchar* v_shader_sourcecode[], const GLchar* f_shader_sourcecode[], GLuint* programId);

	std::string loadShaderSourceCode(std::string filename);
}