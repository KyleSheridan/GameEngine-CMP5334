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

		/*
		TriangleRenderer* tr1;
		TriangleRenderer* tr2;
		TriangleRenderer* tr3;
		TriangleRenderer* tr4;
		TriangleRenderer* tr5;
		

		GLfloat vertexData1[12] = {
			-0.2f, -0.8f,
			-0.13f, 0.0f,
			-0.03f, 0.4f,
			0.1f, 0.65f,
			0.0f, 0.0f,
			-0.05f, -0.75f
		};

		GLfloat vertexData2[10] = {
			0.3f, 0.75f,
			0.1f, 0.65f,
			0.3f, 0.95f,
			0.45f, 0.8f,
			0.5f, 0.2f
		};
		
		GLfloat vertexData3[10] = {
			0.38f, 0.55f,
			0.1f, 0.65f,
			0.35f, 0.75f,
			0.5f, 0.6f,
			0.55f, 0.2f
		};
		
		GLfloat vertexData4[10] = {
			-0.18f, 0.7f,
			0.1f, 0.65f,
			-0.15f, 0.9f,
			-0.35f, 0.8f,
			-0.5f, 0.4f
		};
		
		GLfloat vertexData5[10] = {
			-0.28f, 0.4f,
			0.1f, 0.65f,
			-0.25f, 0.6f,
			-0.45f, 0.5f,
			-0.6f, 0.1f
		};*/

		ModelRenderer* mr;

		FPS* fps;

		int lastTime = 0;
		int currentTime = 0;
	};

	void displayInfoMessage(const char*);
}