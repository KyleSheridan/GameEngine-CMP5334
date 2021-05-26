#pragma once

#include <GL/glew.h>
#include "CrossPlatform.h"
#include <glm/glm.hpp>
#include <string>

#include "Camera.h"
#include "Mesh.h"
#include "Texture.h"
#include "ShaderUtils.h"

namespace GE {
	class ModelRenderer {
	public:
		ModelRenderer(Mesh* m)
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

			mesh = m;
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

		void setMaterial(Texture* mat) {
			material = mat;
		}

	private:
		//stores program object that contains shaders
		GLuint programId;

		//stores attribute to select into the pipeline
		GLint vertexPos3DLocation;

		//stores attribut for colour
		GLint vertexUVLocation;

		//stores the triangle vertex buffer object containing vertices
		GLuint vboModel;

		//fog uniforms
		GLuint fogColourId;
		GLuint fogStartId;
		GLuint fogRangeId;

		float posX, posY, posZ;
		float rotX, rotY, rotZ;
		float scaleX, scaleY, scaleZ;

		GLuint transformUniformId;
		GLuint viewUniformId;
		GLuint projectionUniformId;
		GLuint samplerId;

		Mesh* mesh;

		Texture* material;
	};
}