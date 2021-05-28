#include "ModelRenderer.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

namespace GE {
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
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		std::string V_ShaderStr = loadShaderSourceCode("Shaders/StandardLit.vs");

		const GLchar* V_ShaderCode[] = { V_ShaderStr.c_str() };

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

		std::string F_ShaderStr = loadShaderSourceCode("Shaders/StandardLit.fs");

		const GLchar* F_ShaderCode[] = { F_ShaderStr.c_str() };

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

		fogColourId = glGetUniformLocation(programId, "fog_colour");
		fogStartId = glGetUniformLocation(programId, "fog_start");
		fogRangeId = glGetUniformLocation(programId, "fog_range");

		glUseProgram(programId);
		glUniform1f(fogStartId, 50.0f);
		glUniform1f(fogRangeId, 200.0f);

		glm::vec3 fog_colour = glm::vec3(0.5f, 0.5f, 0.5f);
		glUniform3fv(fogColourId, 1, glm::value_ptr(fog_colour));

		glUseProgram(0);

		glGenBuffers(1, &vboModel);
		glBindBuffer(GL_ARRAY_BUFFER, vboModel);

		glBufferData(GL_ARRAY_BUFFER, mesh->getNumVertices() * sizeof(Vertex), mesh->getVertices(), GL_STATIC_DRAW);
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

		glBindBuffer(GL_ARRAY_BUFFER, vboModel);
		
		glVertexAttribPointer(vertexPos3DLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, x));

		glEnableVertexAttribArray(vertexPos3DLocation);

		glVertexAttribPointer(vertexUVLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, u));

		glEnableVertexAttribArray(vertexUVLocation);


		//set texture
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(samplerId, 0);
		glBindTexture(GL_TEXTURE_2D, material->getTextureName());

		//draw model
		glDrawArrays(GL_TRIANGLES, 0, mesh->getNumVertices());

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