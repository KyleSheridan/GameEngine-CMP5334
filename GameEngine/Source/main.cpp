#define SDL_MAIN_HANDLED
#include "GameEngine.h"

using namespace GE;

int main(int argc, char* args[]) {
	GameEngine ge;

	if (!ge.init(true)) {
		displayInfoMessage("Couldn't start SDL. Check console for more details");

		return 1;
	}

	while (ge.input()) {
		if (!ge.getPaused()) {
			ge.update();

			ge.draw();
		}
	}

	ge.clear();

	return 0;
}