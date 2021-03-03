#pragma once
#include <iostream>

#include "Mesh.h"
#include "Texture.h"
#include "ModelRenderer.h"

namespace GE {
	class Model {
	public:
		Model(const char* meshFile, const char* textureFile) : meshFile(meshFile), textureFile(textureFile) {}
		~Model() {}

		void init();
		void update() {}
		void draw(Camera* cam);
		void clear();

		float getPosX() {
			return mr->getPosX();
		}

		float getPosY() {
			return mr->getPosY();
		}

		float getPosZ() {
			return mr->getPosZ();
		}

		float getRotX() {
			return mr->getRotX();
		}

		float getRotY() {
			return mr->getRotY();
		}

		float getRotZ() {
			return mr->getPosZ();
		}

		float getScaleX() {
			return mr->getScaleX();
		}

		float getScaleY() {
			return mr->getScaleY();
		}

		float getScaleZ() {
			return mr->getScaleZ();
		}

		void setPos(float x, float y, float z) {
			mr->setPos(x, y, z);
		}

		void setRotation(float x, float y, float z) {
			mr->setRotation(x, y, z);
		}

		void setScale(float x, float y, float z) {
			mr->setScale(x, y, z);
		}

	private:
		const char* meshFile;
		const char* textureFile;

		Mesh* mesh;
		Texture* texture;
		ModelRenderer* mr;
	};
}