#include "ModelRenderer.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

namespace GE {
	/*
	GLfloat vertexData1[12] = {
			-0.2f, -0.8f,
			-0.13f, 0.0f,
			-0.03f, 0.4f,
			0.1f, 0.65f,
			0.0f, 0.0f,
			-0.05f, -0.75f
	};

	GLfloat vertexData2[10] = {
		0.3f, 0.75f,
		0.1f, 0.65f,
		0.3f, 0.95f,
		0.45f, 0.8f,
		0.5f, 0.2f
	};

	GLfloat vertexData3[10] = {
		0.38f, 0.55f,
		0.1f, 0.65f,
		0.35f, 0.75f,
		0.5f, 0.6f,
		0.55f, 0.2f
	};

	GLfloat vertexData4[10] = {
		-0.18f, 0.7f,
		0.1f, 0.65f,
		-0.15f, 0.9f,
		-0.35f, 0.8f,
		-0.5f, 0.4f
	};

	GLfloat vertexData5[10] = {
		-0.28f, 0.4f,
		0.1f, 0.65f,
		-0.25f, 0.6f,
		-0.45f, 0.5f,
		-0.6f, 0.1f
	}; */

	/*
	Vertex triangleVertices[] = {
		Vertex(0.1f, 0.65f, 0.0f, 0.1f, 0.01f, 0.01f, 1.0f),
		Vertex(0.0f, 0.0f, 0.0f, 0.1f, 0.01f, 0.01f, 1.0f),
		Vertex(-0.05f, -0.75f, 0.0f, 0.1f, 0.01f, 0.01f, 1.0f),
		Vertex(-0.2f, -0.8f, 0.0f, 0.1f, 0.01f, 0.01f, 1.0f),
		Vertex(-0.13f, 0.0f, 0.0f, 0.1f, 0.01f, 0.01f, 1.0f),
		Vertex(-0.03f, 0.4f, 0.0f, 0.1f, 0.01f, 0.01f, 1.0f),

		
		Vertex(0.1f, 0.65f, 0.0f, 0.1f, 0.35f, 0.01f, 1.0f),
		Vertex(0.3f, 0.95f, 0.0f, 0.1f, 0.35f, 0.01f, 1.0f),
		Vertex(0.45f, 0.8f, 0.0f, 0.1f, 0.35f, 0.01f, 1.0f),
		Vertex(0.5f, 0.2f, 0.0f, 0.1f, 0.35f, 0.01f, 1.0f),
		Vertex(0.3f, 0.75f, 0.0f, 0.1f, 0.35f, 0.01f, 1.0f),

		Vertex(0.1f, 0.65f, 0.0f, 0.1f, 0.8f, 0.01f, 1.0f),
		Vertex(0.35f, 0.75f, 0.0f, 0.1f, 0.8f, 0.01f, 1.0f),
		Vertex(0.5f, 0.6f, 0.0f, 0.1f, 0.8f, 0.01f, 1.0f),
		Vertex(0.55f, 0.2f, 0.0f, 0.1f, 0.8f, 0.01f, 1.0f),
		Vertex(0.38f, 0.55f, 0.0f, 0.1f, 0.8f, 0.01f, 1.0f),

		Vertex(0.1f, 0.65f, 0.0f, 0.1f, 0.35f, 0.01f, 1.0f),
		Vertex(-0.15f, 0.9f, 0.0f, 0.1f, 0.35f, 0.01f, 1.0f),
		Vertex(-0.35f, 0.8f, 0.0f, 0.1f, 0.35f, 0.01f, 1.0f),
		Vertex(-0.5f, 0.4f, 0.0f, 0.1f, 0.35f, 0.01f, 1.0f),
		Vertex(-0.18f, 0.7f, 0.0f, 0.1f, 0.35f, 0.01f, 1.0f),

		Vertex(0.1f, 0.65f, 0.0f, 0.1f, 0.8f, 0.01f, 1.0f),
		Vertex(-0.25f, 0.6f, 0.0f, 0.1f, 0.8f, 0.01f, 1.0f),
		Vertex(-0.45f, 0.5f, 0.0f, 0.1f, 0.8f, 0.01f, 1.0f),
		Vertex(-0.6f, 0.1f, 0.0f, 0.1f, 0.8f, 0.01f, 1.0f),
		Vertex(-0.28f, 0.4f, 0.0f, 0.1f, 0.8f, 0.01f, 1.0f)
		
	};*/

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

	void ModelRenderer::init()
	{
		//std::cout << sizeof(vertexDataA) << "    " << sizeof(vertexData) << "\n";
		//std::cout << sizeof(vertexDataA) / sizeof(vertexDataA[0]) << "    " << sizeof(*vertexData) / sizeof(vertexData[0]) << "\n";

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		const GLchar* V_ShaderCode[] = {
			"#version 140\n"
			"in vec3 vertexPos3D;\n"
			"in vec2 vUV;\n"
			"out vec2 uv;\n"
			"uniform mat4 transform;\n"
			"uniform mat4 view;\n"
			"uniform mat4 projection;\n"
			"void main() {\n"
			"vec4 v = vec4(vertexPos3D.xyz, 1);\n"
			"v = projection * view * transform * v;\n"
			"gl_Position = v;\n"
			"uv = vUV;\n"
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

		const GLchar* F_ShaderCode[] = {
			"#version 140\n"
			"in vec2 uv;\n"
			"uniform sampler2D sampler;\n"
			"out vec4 fragmentColour;\n"
			"void main() {\n"
			"fragmentColour = texture(sampler, uv).rgba;\n"
			"}\n"
		};

		//const char* test = F_ShaderCode.c_str();

		glShaderSource(fragmentShader, 1, F_ShaderCode, NULL);

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

		vertexPos3DLocation = glGetAttribLocation(programId, "vertexPos3D");

		if (vertexPos3DLocation == -1) {
			std::cerr << "Problem getting vertex3DPos" << "\n";
		}

		vertexUVLocation = glGetAttribLocation(programId, "vUV");

		if (vertexUVLocation == -1) {
			std::cerr << "Problem getting vUV" << "\n";
		}

		transformUniformId = glGetUniformLocation(programId, "transform");
		viewUniformId = glGetUniformLocation(programId, "view");
		projectionUniformId = glGetUniformLocation(programId, "projection");
		samplerId = glGetUniformLocation(programId, "sampler");

		glGenBuffers(1, &vboModel);
		glBindBuffer(GL_ARRAY_BUFFER, vboModel);

		glBufferData(GL_ARRAY_BUFFER, model->getNumVertices() * sizeof(Vertex), model->getVertices(), GL_STATIC_DRAW);
	}

	void ModelRenderer::draw(Camera* cam)
	{
		glEnable(GL_CULL_FACE);

		glm::mat4 transformationMat = glm::mat4(1.0f);

		transformationMat = glm::scale(transformationMat, glm::vec3(scaleX, scaleY , scaleZ));
		transformationMat = glm::rotate(transformationMat, glm::radians(rotX), glm::vec3(1.0f, 0.0f, 0.0f));
		transformationMat = glm::rotate(transformationMat, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));
		transformationMat = glm::rotate(transformationMat, glm::radians(rotZ), glm::vec3(0.0f, 0.0f, 1.0f));
		transformationMat = glm::translate(transformationMat, glm::vec3(posX, posY, posZ));

		glm::mat4 viewMat = cam->getViewMatrix();
		glm::mat4 projectionMat = cam->getProjectionMatrix();

		glUseProgram(programId);

		glUniformMatrix4fv(transformUniformId, 1, GL_FALSE, glm::value_ptr(transformationMat));
		glUniformMatrix4fv(viewUniformId, 1, GL_FALSE, glm::value_ptr(viewMat));
		glUniformMatrix4fv(projectionUniformId, 1, GL_FALSE, glm::value_ptr(projectionMat));

		glVertexAttribPointer(vertexPos3DLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, x));

		glEnableVertexAttribArray(vertexPos3DLocation);

		glVertexAttribPointer(vertexUVLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, u));

		glEnableVertexAttribArray(vertexUVLocation);

		glBindBuffer(GL_ARRAY_BUFFER, vboModel);

		//set texture
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(samplerId, 0);
		glBindTexture(GL_TEXTURE_2D, material->getTextureName());

		//draw model
		glDrawArrays(GL_TRIANGLES, 0, model->getNumVertices());

		glDisableVertexAttribArray(vertexPos3DLocation);
		glDisableVertexAttribArray(vertexUVLocation);

		glUseProgram(0);

		glDisable(GL_CULL_FACE);
	}

	void ModelRenderer::clear()
	{
		glDeleteProgram(programId);

		glDeleteBuffers(1, &vboModel);
	}
}