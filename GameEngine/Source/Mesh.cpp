#include "Model.h"

namespace GE {
	bool Mesh::loadFromFile(const char* filename)
	{
		std::vector<Vertex> loadedVertices;

		Assimp::Importer imp;

		const aiScene* pScene = imp.ReadFile(filename, aiProcessPreset_TargetRealtime_Quality | aiProcess_FlipUVs);

		if (!pScene) {
			return false;
		}

		for (int meshIdx = 0; meshIdx < pScene->mNumMeshes; meshIdx++) {
			const aiMesh* mesh = pScene->mMeshes[meshIdx];

			for (int faceIdx = 0; faceIdx < mesh->mNumFaces; faceIdx++) {
				const aiFace& face = mesh->mFaces[faceIdx];

				for (int vertIdx = 0; vertIdx < 3; vertIdx++) {
					const aiVector3D* pos = &mesh->mVertices[face.mIndices[vertIdx]];

					const aiVector3D uv = mesh->mTextureCoords[0][face.mIndices[vertIdx]];

					//const aiVector3D* normal = &mesh->mNormals[meshIdx];

					loadedVertices.push_back(Vertex(pos->x, pos->y, pos->z, uv.x, uv.y));
				}
			}
		}

		numVertices = loadedVertices.size();

		vertices = new Vertex[numVertices];

		std::copy(loadedVertices.begin(), loadedVertices.end(), vertices);

		return true;
	}
}