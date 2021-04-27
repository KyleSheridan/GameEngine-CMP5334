#pragma once

/*
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <glm/glm.hpp>
#include <string>

#include "Camera.h"

namespace GE {
	class TriangleRenderer {
	public:
		TriangleRenderer()
		{
			posX = 0.0f;
			posY = 0.0f;
			posZ = 0.0f;
			rotX = 0.0f;
			rotY = 0.0f;
			rotZ = 0.0f;
			scaleX = 1.0f;
			scaleY = 1.0f;
			scaleZ = 1.0f;
		}
		virtual ~TriangleRenderer() {}

		void init(GLfloat vertexData[], int length, std::string colour);
		void update() {}
		void draw(Camera*, GLsizei);
		void clear();

		float getPosX() {
			return posX;
		}

		float getPosY() {
			return posY;
		}

		float getPosZ() {
			return posZ;
		}

		float getRotX() {
			return rotX;
		}

		float getRotY() {
			return rotY;
		}

		float getRotZ() {
			return rotZ;
		}

		float getScaleX() {
			return scaleX;
		}

		float getScaleY() {
			return scaleY;
		}

		float getScaleZ() {
			return scaleZ;
		}

		void setPos(float x, float y, float z) {
			posX = x;
			posY = y;
			posZ = z;
		}

		void setRotation(float x, float y, float z) {
			rotX = x;
			rotY = y;
			rotZ = z;
		}

		void setScale(float x, float y, float z) {
			scaleX = x;
			scaleY = y;
			scaleZ = z;
		}

	private:
		//stores program object that contains shaders
		GLuint programId;

		//stores attribute to select into the pipeline
		GLint vertexPos2DLocation;

		//stores the triangle vertex buffer object containing vertices
		GLuint vboTriangle;

		float posX, posY, posZ;
		float rotX, rotY, rotZ;
		float scaleX, scaleY, scaleZ;

		GLuint transformUniformId;
		GLuint viewUniformId;
		GLuint projectionUniformId;
	};
}*/