#pragma once

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <glm/glm.hpp>
#include <string>

#include "Camera.h"

namespace GE {
	struct Vertex {
		float x, y, z;
		float r, g, b, a;

		Vertex(float _x, float _y, float _z, float _r, float _g, float _b, float _a) {
			//position
			x = _x;
			y = _y;
			z = _z;

			//colour
			r = _r;
			g = _g;
			b = _b;
			a = _a;
		}

		Vertex() {
			x = y = z = 0.0f;
			r = g = b = a = 0.0f;
		}
	};

	class ModelRenderer {
	public:
		ModelRenderer()
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
		virtual ~ModelRenderer() {}

		void init();
		void update() {}
		void draw(Camera*);
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
		GLint vertexPos3DLocation;

		//stores attribut for colour
		GLint vertexFragmentColourLocation;

		//stores the triangle vertex buffer object containing vertices
		GLuint vboTriangle;

		float posX, posY, posZ;
		float rotX, rotY, rotZ;
		float scaleX, scaleY, scaleZ;

		GLuint transformUniformId;
		GLuint viewUniformId;
		GLuint projectionUniformId;
	};
}