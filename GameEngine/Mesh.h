#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>

namespace GE {
	struct Vertex {
		float x, y, z;
		float u, v;

		Vertex(float _x, float _y, float _z, float _u, float _v) {
			//position
			x = _x;
			y = _y;
			z = _z;

			//colour
			u = _u;
			v = _v;
		}

		Vertex() {
			x = y = z = 0.0f;
			u = v = 0.0f;
		}
	};

	class Mesh {
	public:
		Mesh() {
			vertices = nullptr;
			numVertices = 0;
		}

		~Mesh() {
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