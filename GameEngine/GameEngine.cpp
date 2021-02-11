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

		//create camera
		cam = new Camera(
			glm::vec3(0.0f, 0.0f, 5.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			45.0f, 640.0f / 480.0f, 0.1f, 100.0f
		);

		//create Model
		m = new Model();

		m->loadFromFile("Assets/PalmTree.obj");

		if (m->getVertices() == nullptr) {
			std::cerr << "Failes to load model" << "\n";
		}

		mat = new Texture("Assets/Spaceship.jpg");

		//create ModelRenderer
		mr = new ModelRenderer(m);
		mr->init();

		//mr->setScale(0.3f, 0.3f, 0.3f);
		mr->setPos(0.0f, 0.0f, 20.0f);
		mr->setMaterial(mat);

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

		const float camSpeed = 0.2f;
		const float mouseSens = 0.1;

		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);

		float diffx = mouseX - cam->getOldMouseX();
		float diffy = cam->getOldMouseY() - mouseY;

		cam->setYaw((cam->getYaw() + diffx) * mouseSens);
		cam->setPitch((cam->getPitch() + diffy) * mouseSens);

		glm::vec3 direction;
		direction.x = cos(glm::radians(cam->getYaw())) * cos(glm::radians(cam->getPitch()));
		direction.y = sin(glm::radians(cam->getPitch()));
		direction.z = sin(glm::radians(cam->getYaw())) * cos(glm::radians(cam->getPitch()));
		cam->setTarget(glm::normalize(direction));

		bool keyStates[4] = { 0,0,0,0 };

		enum {
			UP = 0,
			DOWN,
			LEFT,
			RIGHT
		};
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.scancode) {
				case SDL_SCANCODE_UP:
					keyStates[UP] = true;
					break;
				case SDL_SCANCODE_DOWN:
					keyStates[DOWN] = true;
					break;
				case SDL_SCANCODE_LEFT:
					keyStates[LEFT] = true;
					break;
				case SDL_SCANCODE_RIGHT:
					keyStates[RIGHT] = true;
					break;
				default:
					break;
				}
			}

			if (e.type == SDL_KEYUP) {
				switch (e.key.keysym.scancode) {
				case SDL_SCANCODE_UP:
					keyStates[UP] = false;
					break;
				case SDL_SCANCODE_DOWN:
					keyStates[DOWN] = false;
					break;
				case SDL_SCANCODE_LEFT:
					keyStates[LEFT] = false;
					break;
				case SDL_SCANCODE_RIGHT:
					keyStates[RIGHT] = false;
					break;
				default:
					break;
				}
			}
		}

		if (keyStates[UP]) {
			cam->setPos(cam->getPos() + cam->getTarget() * camSpeed);
		}
		if (keyStates[DOWN]) {
			cam->setPos(cam->getPos() - cam->getTarget() * camSpeed);
		}
		if (keyStates[LEFT]) {
			cam->setPos(cam->getPos() - glm::normalize(glm::cross(cam->getTarget(), cam->getUpDir())) * camSpeed);
		}
		if (keyStates[RIGHT]) {
			cam->setPos(cam->getPos() + glm::normalize(glm::cross(cam->getTarget(), cam->getUpDir())) * camSpeed);
		}

		cam->setOldMouseX(640.0f / 2);
		cam->setOldMouseY(480.0f / 2);

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

		//mr->setRotation(0.0f, mr->getRotY() + 0.5f, 0.0f);
	}

	void GameEngine::draw()
	{
		glClearColor(0.1f, 0.08f, 0.5f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		mr->draw(cam);

		SDL_GL_SwapWindow(window);
	}

	void GameEngine::clear()
	{
		mr->clear();

		delete mr;
		delete m;
		delete cam;

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