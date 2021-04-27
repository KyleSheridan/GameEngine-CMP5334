#include "Texture.h"

namespace GE {
	void Texture::loadTexture(std::string filename)
	{
		SDL_Surface* s = IMG_Load(filename.c_str());

		if (s == nullptr) {
			return;
		}

		width = s->w;
		height = s->h;

		format = s->format->format;

		switch (format) {
		case SDL_PIXELFORMAT_RGBA32:
			format = GL_RGBA;
			break;
		case SDL_PIXELFORMAT_RGB24:
			format = GL_RGB;
			break;

			//More formats here

		default:
			format = GL_RGB;
			break;
		}

		glGenTextures(1, &textureName);

		glBindTexture(GL_TEXTURE_2D, textureName);

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, s->pixels);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		SDL_FreeSurface(s);
	}
}