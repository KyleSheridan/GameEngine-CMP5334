#pragma once
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <iostream>

#include "FPS.h"
#include "TriangleRenderer.h"
#include "ModelRenderer.h"
#include "Camera.h"

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

		Model* m;
		Texture* mat;
		ModelRenderer* mr;

		FPS* fps;

		int lastTime = 0;
		int currentTime = 0;
	};

	void displayInfoMessage(const char*);
}