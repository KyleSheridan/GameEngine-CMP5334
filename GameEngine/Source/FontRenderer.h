#include <ft2build.h>
#include FT_FREETYPE_H

#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <array>
#include <map>

#include "ShaderUtils.h"

namespace GE {
    struct Character {
        unsigned int TextureID;
        std::array<int, 2> size;
        std::array<int, 2> bearing;
        unsigned int Advance;
    };

    class FontRenderer {
    public:
        FontRenderer(int width, int height) : windowWidth(width), windowHeight(height) {};
        ~FontRenderer() {};

        void init();
        void RenderText(std::string text, float x, float y, float scale, glm::vec3 colour);

    private:
        int windowWidth, windowHeight;
        unsigned int programId, projectionLocation, textLocation, textColourLocation, VAO, VBO;

        std::map<char, Character> charactersMap;
    };
}