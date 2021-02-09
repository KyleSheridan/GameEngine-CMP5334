#include "GameEngine.h"

namespace GE {
	//initialise SDL video subsystem
	bool GameEngine::init(bool vsync)
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			std::cerr << "Unable to initilise SDL!   SDL error: " << SDL_GetError() << "\n";

			return false;
		}

		//Set the OpenGL version
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		//set type of profile to core --- modern OpenGL
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		//create window
		window = SDL_CreateWindow("SDL OpenGL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 768, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

		if (window == nullptr) {
			std::cerr << "Unable to create window!   SDL error: " << SDL_GetError() << "\n";

			return false;
		}

		//creates context and links to window
		glContext = SDL_GL_CreateContext(window);

		if (glContext == nullptr) {
			std::cerr << "Could not create GL context!   SDL error: " << SDL_GetError() << "\n";

			return false;
		}

		//initialise GLEW
		GLenum status = glewInit();

		if (status != GLEW_OK) {
			std::cerr << "Error initialising GLEW!   Error: " << glewGetErrorString(status) << "\n";

			return false;
		}

		if (SDL_GL_SetSwapInterval(vsync) != 0) {
			std::cerr << "Warning: unable to set VSync!   Error: " << SDL_GetError() << "\n";

			return false;
		}

		//create fps object
		fps = new FPS();
		fps->init();

		/*
		GLfloat vertexData1[]{
			-0.2f, -0.8f,
			-0.13f, 0.0f,
			-0.03f, 0.4f,
			0.1f, 0.65f,
			0.0f, 0.0f,
			-0.05f, -0.75f,

			0.3f, 0.75f,
			0.1f, 0.65f,
			0.3f, 0.95f,
			0.45f, 0.8f,
			0.5f, 0.2f,

			0.38f, 0.55f,
			0.1f, 0.65f,
			0.35f, 0.75f,
			0.5f, 0.6f,
			0.55f, 0.2f,

			-0.18f, 0.7f,
			0.1f, 0.65f,
			-0.15f, 0.9f,
			-0.35f, 0.8f,
			-0.5f, 0.4f,

			-0.28f, 0.4f,
			0.1f, 0.65f,
			-0.25f, 0.6f,
			-0.45f, 0.5f,
			-0.6f, 0.1f
		};*/

		//std::cout << sizeof(vertexData1) << "\n";
		//std::cout << (sizeof(vertexData1) / sizeof(vertexData1[0])) << "\n";

		//create camera
		cam = new Camera(
			glm::vec3(0.0f, 0.0f, 5.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			45.0f, 640.0f / 480.0f, 0.1f, 100.0f
		);

		//create TriangleRenderers
		/*tr1 = new TriangleRenderer();
		tr1->init(vertexData1, 12, "0.1, 0.8, 0.01, 1.0");

		tr2 = new TriangleRenderer();
		tr2->init(vertexData2, 12, "0.1, 0.01, 0.01, 1.0");

		tr3 = new TriangleRenderer();
		tr3->init(vertexData3, 10, "0.1, 0.35, 0.01, 1.0");

		tr4 = new TriangleRenderer();
		tr4->init(vertexData4, 10, "0.1, 0.8, 0.01, 1.0");

		tr5 = new TriangleRenderer();
		tr5->init(vertexData5, 10, "0.1, 0.35, 0.01, 1.0");*/

		//create ModelRenderer
		mr = new ModelRenderer();
		mr->init();

		return true;
	}

	bool GameEngine::input()
	{
		SDL_PumpEvents();

		SDL_Event e;

		//if application closed, end loop
		if (SDL_PeepEvents(&e, 1, SDL_GETEVENT, SDL_QUIT, SDL_QUIT)) {
			return false;
		}

		return true;
	}

	void GameEngine::update()
	{
		fps->update();

		currentTime = SDL_GetTicks();

		if (currentTime - lastTime > 1000) {
			setWindowTitle(std::to_string((int)fps->getFPS()).c_str());

			lastTime = currentTime;
		}
	}

	void GameEngine::draw()
	{
		glClearColor(0.1f, 0.08f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/*glBegin(GL_TRIANGLES);
		glColor3f(0.9f, 0.1f, 1.0f);
		glVertex2f(-1.0f, 0.0f);
		glColor3f(0.9f, 0.1f, 1.0f);
		glVertex2f(1.0f, 0.0f);
		glColor3f(0.9f, 0.1f, 1.0f);
		glVertex2f(0.0f, 1.0f);

		glColor3f(0.0f, 1.0f, 0.3f);
		glVertex2f(-1.0f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.3f);
		glVertex2f(1.0f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.3f);
		glVertex2f(0.0f, -1.0f);
		glEnd();*/

		//    POLYGON
		/*glBegin(GL_POLYGON);
		    glColor3f(0.0f, 0.0f, 1.0f);
		    glVertex2f(-0.75f, -0.75f);

		    glColor3f(0.0f, 0.0f, 1.0f);
		    glVertex2f(0.75f, -0.75f);
			
			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex2f(0.75f, 0.75f);

		    glColor3f(0.0f, 0.0f, 1.0f);
		    glVertex2f(-0.75f, 0.75f);
		glEnd();*/

		//    COLOURS
	   /*glBegin(GL_TRIANGLES);
		   glColor3f(0.9f, 0.1f, 1.0f);
		   glVertex2f(-1.0f, 0.0f);
		   glColor3f(1.0f, 0.6f, 0.1f);
		   glVertex2f(0.0f, -1.0f);
		   glColor3f(0.0f, 1.0f, 1.0f);
		   glVertex2f(1.0f, 0.0f);
	   glEnd();*/

	   //    COLOURS AND PERSPECTIVE
	   /*glBegin(GL_TRIANGLES);
	       glColor3f(1.0f, 1.0f, 0.0f);
	       glVertex3f(1.0f, 0.0f, zpoint);
	       glColor3f(0.0f, 1.0f, 0.0f);
	       glVertex3f(0.0f, -1.0f, 0.0f);
	       glColor3f(0.0f, 1.0f, 1.0f);
	       glVertex3f(1.0f, -1.0f, 0.0f);

		   glColor3f(1.0f, 1.0f, 0.0f);
		   glVertex3f(-1.0f, 0.0f, zpoint2);
		   glColor3f(0.0f, 1.0f, 0.0f);
		   glVertex3f(0.0f, -1.0f, 0.0f);
		   glColor3f(0.0f, -1.0f, 1.0f);
		   glVertex3f(-1.0f, -1.0f, 0.0f);
	   glEnd();*/


		//PALM TREE
		/*
		glBegin(GL_POLYGON);
			glColor3f(0.1f, 0.01f, 0.01f);
			glVertex2f(-0.2f, -0.8f);

			glColor3f(0.1f, 0.01f, 0.01f);
			glVertex2f(-0.13f, 0.0f);

			glColor3f(0.1f, 0.01f, 0.01f);
			glVertex2f(-0.03f, 0.4f);

			glColor3f(0.1f, 0.01f, 0.01f);
			glVertex2f(0.1f, 0.65f);

			glColor3f(0.1f, 0.01f, 0.01f);
			glVertex2f(0.0f, 0.0f);

			glColor3f(0.1f, 0.01f, 0.01f);
			glVertex2f(-0.05f, -0.75f);
		glEnd();

		glBegin(GL_POLYGON);
			glColor3f(0.1f, 0.35f, 0.01f);
			glVertex2f(0.3f, 0.75f);

			glColor3f(0.1f, 0.35f, 0.01f);
			glVertex2f(0.1f, 0.65f);

			glColor3f(0.1f, 0.35f, 0.01f);
			glVertex2f(0.3f, 0.95f);

			glColor3f(0.1f, 0.35f, 0.01f);
			glVertex2f(0.45f, 0.8f);

			glColor3f(0.1f, 0.35f, 0.01f);
			glVertex2f(0.5f, 0.2f);
		glEnd();

		glBegin(GL_POLYGON);
			glColor3f(0.1f, 0.8f, 0.01f);
			glVertex2f(0.38f, 0.55f);

			glColor3f(0.1f, 0.8f, 0.01f);
			glVertex2f(0.1f, 0.65f);

			glColor3f(0.1f, 0.8f, 0.01f);
			glVertex2f(0.35f, 0.75f);

			glColor3f(0.1f, 0.8f, 0.01f);
			glVertex2f(0.5f, 0.6f);

			glColor3f(0.1f, 0.8f, 0.01f);
			glVertex2f(0.55f, 0.2f);
		glEnd();
		
		glBegin(GL_POLYGON);
			glColor3f(0.1f, 0.35f, 0.01f);
			glVertex2f(-0.18f, 0.75f);

			glColor3f(0.1f, 0.35f, 0.01f);
			glVertex2f(0.1f, 0.65f);

			glColor3f(0.1f, 0.35f, 0.01f);
			glVertex2f(-0.15f, 0.95f);

			glColor3f(0.1f, 0.35f, 0.01f);
			glVertex2f(-0.35f, 0.8f);

			glColor3f(0.1f, 0.35f, 0.01f);
			glVertex2f(-0.5f, 0.4f);
		glEnd();

		glBegin(GL_POLYGON);
			glColor3f(0.1f, 0.8f, 0.01f);
			glVertex2f(-0.28f, 0.45f);

			glColor3f(0.1f, 0.8f, 0.01f);
			glVertex2f(0.1f, 0.65f);

			glColor3f(0.1f, 0.8f, 0.01f);
			glVertex2f(-0.25f, 0.65f);

			glColor3f(0.1f, 0.8f, 0.01f);
			glVertex2f(-0.45f, 0.5f);

			glColor3f(0.1f, 0.8f, 0.01f);
			glVertex2f(-0.6f, 0.1f);
		glEnd();
		*/

		/*
	GLfloat vertexData[] = {
		-0.2f, -0.8f,
		-0.13f, 0.0f,
		-0.03f, 0.4f,
		0.1f, 0.65f,
		0.0f, 0.0f,
		-0.05f, -0.75f,

		0.3f, 0.75f,
		0.1f, 0.65f,
		0.3f, 0.95f,
		0.45f, 0.8f,
		0.5f, 0.2f,

		0.38f, 0.55f,
		0.1f, 0.65f,
		0.35f, 0.75f,
		0.5f, 0.6f,
		0.55f, 0.2f,

		-0.18f, 0.7f,
		0.1f, 0.65f,
		-0.15f, 0.9f,
		-0.35f, 0.8f,
		-0.5f, 0.4f,

		-0.28f, 0.4f,
		0.1f, 0.65f,
		-0.25f, 0.6f,
		-0.45f, 0.5f,
		-0.6f, 0.1f
	};
	*/


		/*tr2->draw(cam, 6);
		tr3->draw(cam, 5);
		tr4->draw(cam, 5);
		tr5->draw(cam, 5);
		tr1->draw(cam, 5);*/

		mr->draw(cam);

		SDL_GL_SwapWindow(window);
	}

	void GameEngine::clear()
	{
		/*
		tr1->clear();
		tr2->clear();
		tr3->clear();
		tr4->clear();
		tr5->clear();

		delete tr1;
		delete tr2;
		delete tr3;
		delete tr4;
		delete tr5;

		delete cam;*/

		SDL_DestroyWindow(window);

		window = nullptr;

		SDL_Quit();
	}

	void GameEngine::setWindowTitle(const char* title) {
		SDL_SetWindowTitle(window, title);
	}

	void displayInfoMessage(const char* msg) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Basic Game Engine", msg, nullptr);
	}
}