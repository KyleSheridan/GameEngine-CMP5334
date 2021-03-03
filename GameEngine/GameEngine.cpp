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

		//dist = glm::vec3(0.0f, 0.0f, -100.0f);

		//create camera
		cam = new Camera(
			glm::vec3(0.0f, 0.0f, 5.0f),
			glm::vec3(0.0f, 0.0f, 0.0f) /*+ dist*/,
			glm::vec3(0.0f, 1.0f, 0.0f),
			45.0f, 640.0f / 480.0f, 0.1f, 100.0f
		);

		//terrain
		terrainModel = new Model("Assets/Terrain.obj", "Assets/Grass.jpg");
		terrainModel->init();

		terrainModel->setScale(10.0f, 10.0f, 10.0f);
		terrainModel->setPos(0.0f, -0.5f, 0.0f);

		//create palm tree Model
		palmTreeModel = new Model("Assets/PalmTree.obj", "Assets/PalmTreeTexture.png");
		palmTreeModel->init();
		palmTreeModel->setPos(20.0f, 0.0f, 40.0f);

		//other trees
		treeModel = new Model("Assets/Tree.obj", "Assets/TreeTexture.png");
		treeModel->init();
		treeModel->setScale(0.7f, 0.7f, 0.7f);
		treeModel->setPos(-20.0, -7.0f, 50.0f);

		//temple
		templeModel = new Model("Assets/Temple.obj", "Assets/GreyStone.png");
		templeModel->init();

		templeModel->setRotation(0.0f, -90.0f, 0.0f);
		templeModel->setPos(100.0f, -10.0f, 0.0f);

		//rocks
		rockModels.push_back(new Model("Assets/Rocks/Stone_1.obj", "Assets/Rocks/Rock.jpg"));
		rockModels.back()->init();
		rockModels.back()->setPos(350.0f, -50.0f, 150.0f);
		rockModels.back()->setScale(0.1f, 0.1f, 0.3f);
		rockModels.push_back(new Model("Assets/Rocks/Stone_1.obj", "Assets/Rocks/Rock.jpg"));
		rockModels.back()->init();
		rockModels.back()->setPos(-350.0f, -50.0f, 150.0f);
		rockModels.back()->setScale(0.1f, 0.1f, 0.3f);
		rockModels.push_back(new Model("Assets/Rocks/Stone_2.obj", "Assets/Rocks/Rock.jpg"));
		rockModels.back()->init();
		rockModels.back()->setPos(350.0f, -35.0f, 30.0f);
		rockModels.back()->setScale(0.1f, 0.1f, 0.3f);
		rockModels.push_back(new Model("Assets/Rocks/Stone_2.obj", "Assets/Rocks/Rock.jpg"));
		rockModels.back()->init();
		rockModels.back()->setPos(-350.0f, -35.0f, 30.0f);
		rockModels.back()->setScale(0.1f, 0.1f, 0.3f);
		rockModels.push_back(new Model("Assets/Rocks/Stone_3.obj", "Assets/Rocks/Rock.jpg"));
		rockModels.back()->init();
		rockModels.back()->setPos(350.0f, -35.0f, -40.0f);
		rockModels.back()->setScale(0.1f, 0.1f, 0.3f);
		rockModels.push_back(new Model("Assets/Rocks/Stone_3.obj", "Assets/Rocks/Rock.jpg"));
		rockModels.back()->init();
		rockModels.back()->setPos(-350.0f, -35.0f, -40.0f);
		rockModels.back()->setScale(0.1f, 0.1f, 0.3f);
		rockModels.push_back(new Model("Assets/Rocks/Stone_1.obj", "Assets/Rocks/Rock.jpg"));
		rockModels.back()->init();
		rockModels.back()->setPos(70.0f, -50.0f, -200.0f);
		rockModels.back()->setScale(0.3f, 0.1f, 0.1f);
		rockModels.push_back(new Model("Assets/Rocks/Stone_1.obj", "Assets/Rocks/Rock.jpg"));
		rockModels.back()->init();
		rockModels.back()->setPos(-70.0f, -50.0f, -200.0f);
		rockModels.back()->setScale(0.3f, 0.1f, 0.1f);
		rockModels.push_back(new Model("Assets/Rocks/Stone_2.obj", "Assets/Rocks/Rock.jpg"));
		rockModels.back()->init();
		rockModels.back()->setPos(0.0f, -35.0f, -200.0f);
		rockModels.back()->setScale(0.3f, 0.1f, 0.1f);

		brazierModel = new Model("Assets/Brazier.obj", "Assets/GreyStone.png");
		brazierModel->init();
		brazierModel->setPos(200, -100, 1000);
		brazierModel->setScale(0.05, 0.05, 0.05);
		
		brazierModel2 = new Model("Assets/Brazier.obj", "Assets/GreyStone.png");
		brazierModel2->init();
		brazierModel2->setPos(-175, -100, 1000);
		brazierModel2->setScale(0.05, 0.05, 0.05);

		//skybox
		skybox = new SkyboxRenderer(
			"Assets/Skybox/front.png",
			"Assets/Skybox/back.png",
			"Assets/Skybox/right.png",
			"Assets/Skybox/left.png",
			"Assets/Skybox/top.png",
			"Assets/Skybox/bottom.png"
		);

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
				case SDL_SCANCODE_W:
					keyStates[UP] = true;
					break;
				case SDL_SCANCODE_S:
					keyStates[DOWN] = true;
					break;
				case SDL_SCANCODE_A:
					keyStates[LEFT] = true;
					break;
				case SDL_SCANCODE_D:
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
				case SDL_SCANCODE_W:
					keyStates[UP] = false;
					break;
				case SDL_SCANCODE_S:
					keyStates[DOWN] = false;
					break;
				case SDL_SCANCODE_A:
					keyStates[LEFT] = false;
					break;
				case SDL_SCANCODE_D:
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

		/*glm::mat4 cam_rot = glm::mat4(1.0f);

		cam_rot = glm::rotate(cam_rot, glm::radians(0.1f), glm::vec3(0.0f, 1.0f, 0.0f));

		glm::vec4 temp = glm::vec4(dist, 0.0f);

		temp = temp * cam_rot;

		dist = glm::vec3(temp.x, temp.y, temp.z);

		cam->setTarget(dist);*/
	}

	void GameEngine::draw()
	{
		glClearColor(0.1f, 0.08f, 0.5f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		skybox->draw(cam);

		terrainModel->draw(cam);

		palmTreeModel->draw(cam);
		treeModel->draw(cam);
		templeModel->draw(cam);

		brazierModel->draw(cam);
		brazierModel2->draw(cam);

		for (Model*& rock : rockModels)
			rock->draw(cam);

		SDL_GL_SwapWindow(window);
	}

	void GameEngine::clear()
	{
		palmTreeModel->clear();

		skybox->clear();

		delete skybox;
		delete palmTreeModel;
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