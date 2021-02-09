#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>

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

	class Model {
	public:
		Model() {
			vertices = nullptr;
			numVertices = 0;
		}

		~Model() {
			delete[] vertices;
		}

		bool loadFromFile(const char*);

		void* getVertices() {
			return (void*)vertices;
		}

		int getNumVertices() {
			return numVertices;
		}

	public:
		Vertex* vertices;
		int numVertices;
	};
}