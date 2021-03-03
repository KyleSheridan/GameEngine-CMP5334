#pragma once
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <iostream>

#include "FPS.h"
#include "TriangleRenderer.h"
#include "Model.h"
#include "Camera.h"
#include "SkyboxRenderer.h"

namespace GE {
	class GameEngine {
	public:
		GameEngine() {}
		virtual ~GameEngine() {}

		bool init(bool);
		bool input();
		void update();
		void draw();
		void clear();

		void setWindowTitle(const char*);

	private:
		SDL_Window* window;

		SDL_GLContext glContext;	//context to represent OpenGL

		Camera* cam;

		glm::vec3 dist;

		//terrain
		Model* terrainModel;

		//Rocks
		std::vector<Model*> rockModels;

		//palm trees
		Model* palmTreeModel;

		//other trees
		Model* treeModel;

		//temple
		Model* templeModel;

		//brazier
		Model* brazierModel;
		Model* brazierModel2;

		//skybox
		SkyboxRenderer* skybox;

		FPS* fps;

		int lastTime = 0;
		int currentTime = 0;
	};

	void displayInfoMessage(const char*);
}