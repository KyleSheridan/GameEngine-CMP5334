#include "TriangleRenderer.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

/*
namespace GE {
	
	GLfloat vertexDataA[] = {
		-0.2f, -0.8f,
		-0.13f, 0.0f,
		-0.03f, 0.4f,
		0.1f, 0.65f,
		0.0f, 0.0f,
		-0.05f, -0.75f,

		0.3f, 0.75f,
		0.1f, 0.65f,
		0.3f, 0.95f,
		0.45f, 0.8f,
		0.5f, 0.2f,

		0.38f, 0.55f,
		0.1f, 0.65f,
		0.35f, 0.75f,
		0.5f, 0.6f,
		0.55f, 0.2f,

		-0.18f, 0.7f,
		0.1f, 0.65f,
		-0.15f, 0.9f,
		-0.35f, 0.8f,
		-0.5f, 0.4f,

		-0.28f, 0.4f,
		0.1f, 0.65f,
		-0.25f, 0.6f,
		-0.45f, 0.5f,
		-0.6f, 0.1f
	};
	

	void displayShaderCompilerError(GLuint shaderId)
	{
		GLint MsgLen = 0;

		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &MsgLen);

		if (MsgLen > 1) {
			GLchar* Msg = new GLchar[MsgLen + 1];

			glGetShaderInfoLog(shaderId, MsgLen, NULL, Msg);

			std::cerr << "Error compiling shader " << Msg << "\n";

			delete[] Msg;
		}
	}

	void DisplayProgramCompilationError(GLuint programID) {
		GLint msgLen = 0;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &msgLen);
		if (msgLen > 0) {
			GLchar* msg = new GLchar[msgLen + 1];
			glGetProgramInfoLog(programID, msgLen, NULL, msg);

			std::cerr << "Error linking program: " << msg << "\n";

			delete[] msg;
		}
	}

	void TriangleRenderer::init(GLfloat vertexData[], int length, std::string colour)
	{
		//std::cout << sizeof(vertexDataA) << "    " << sizeof(vertexData) << "\n";
		//std::cout << sizeof(vertexDataA) / sizeof(vertexDataA[0]) << "    " << sizeof(*vertexData) / sizeof(vertexData[0]) << "\n";
		
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		const GLchar* V_ShaderCode[] = {
			"#version 140\n"
			"in vec2 vertexPos2D;\n"
			"uniform mat4 transform;\n"
			"uniform mat4 view;\n"
			"uniform mat4 projection;\n"
			"void main() {\n"
			"vec4 v = vec4(vertexPos2D.x, vertexPos2D.y, 0, 1);\n"
			"v = projection * view * transform * v;\n"
			"gl_Position = v;\n"
			"}\n"
		};

		glShaderSource(vertexShader, 1, V_ShaderCode, NULL);

		glCompileShader(vertexShader);

		GLint isShaderCompiledOK = GL_FALSE;

		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isShaderCompiledOK);

		if (isShaderCompiledOK != GL_TRUE) {
			std::cerr << "Unable to compile vertex shader" << "\n";

			displayShaderCompilerError(vertexShader);

			return;
		}

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		std::string F_ShaderCode = {
			"#version 140\n"
			"out vec4 fragmentColour;\n"
			"void main() {\n"
			"fragmentColour = vec4(" + colour + ");\n"
			"}\n"
		};

		const char* test = F_ShaderCode.c_str();

		glShaderSource(fragmentShader, 1, &test, NULL);

		glCompileShader(fragmentShader);

		isShaderCompiledOK = GL_FALSE;

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isShaderCompiledOK);

		if (isShaderCompiledOK != GL_TRUE) {
			std::cerr << "Unable to compile fragment shader" << "\n";

			displayShaderCompilerError(fragmentShader);

			return;
		}

		programId = glCreateProgram();

		glAttachShader(programId, vertexShader);
		glAttachShader(programId, fragmentShader);

		glLinkProgram(programId);

		GLint isProgramLinked = GL_FALSE;
		glGetProgramiv(programId, GL_LINK_STATUS, &isProgramLinked);
		if (isProgramLinked != GL_TRUE) {
			std::cerr << "Failed to link program" << "\n";

			DisplayProgramCompilationError(programId);

			return;
		}

		vertexPos2DLocation = glGetAttribLocation(programId, "vertexPos2D");

		if (vertexPos2DLocation == -1) {
			std::cerr << "Problem getting vertex2DPos" << "\n";
		}

		transformUniformId = glGetUniformLocation(programId, "transform");
		viewUniformId = glGetUniformLocation(programId, "view");
		projectionUniformId = glGetUniformLocation(programId, "projection");

		glGenBuffers(1, &vboTriangle);
		glBindBuffer(GL_ARRAY_BUFFER, vboTriangle);
		
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData) * length, vertexData, GL_STATIC_DRAW);
	}

	void TriangleRenderer::draw(Camera* cam, GLsizei num)
	{
		glm::mat4 transformationMat = glm::mat4(1.0f);

		transformationMat = glm::scale(transformationMat, glm::vec3(1, 1, 1));
		transformationMat = glm::rotate(transformationMat, glm::radians(rotX), glm::vec3(1.0f, 0.0f, 0.0f));
		transformationMat = glm::rotate(transformationMat, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));
		transformationMat = glm::rotate(transformationMat, glm::radians(rotZ), glm::vec3(0.0f, 0.0f, 1.0f));
		transformationMat = glm::translate(transformationMat, glm::vec3(0, 0, 0));

		glm::mat4 viewMat = cam->getViewMatrix();
		glm::mat4 projectionMat = cam->getProjectionMatrix();

		glUseProgram(programId);

		glUniformMatrix4fv(transformUniformId, 1, GL_FALSE, glm::value_ptr(transformationMat));
		glUniformMatrix4fv(viewUniformId, 1, GL_FALSE, glm::value_ptr(viewMat));
		glUniformMatrix4fv(projectionUniformId, 1, GL_FALSE, glm::value_ptr(projectionMat));

		glVertexAttribPointer(vertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);

		glEnableVertexAttribArray(vertexPos2DLocation);

		glBindBuffer(GL_ARRAY_BUFFER, vboTriangle);

		glDrawArrays(GL_POLYGON, 0, num);
		
		glDisableVertexAttribArray(vertexPos2DLocation);

		glUseProgram(0);
	}

	void TriangleRenderer::clear()
	{
		glDeleteProgram(programId);

		glDeleteBuffers(1, &vboTriangle);
	}
}*/