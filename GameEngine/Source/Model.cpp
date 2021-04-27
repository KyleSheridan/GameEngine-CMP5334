#include "Model.h"

namespace GE {
	void Model::init()
	{
		mesh = new Mesh();
		mesh->loadFromFile(meshFile);

		if (mesh->getVertices() == nullptr) {
			std::cerr << "Failed to load model" << "\n";
		}

		texture = new Texture(textureFile);

		mr = new ModelRenderer(mesh);
		mr->init();

		mr->setMaterial(texture);
	}

	void Model::draw(Camera* cam)
	{
		mr->draw(cam);
	}

	void Model::clear()
	{
		mr->clear();
	}
}