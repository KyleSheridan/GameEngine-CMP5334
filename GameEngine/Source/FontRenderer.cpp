#include "FontRenderer.h"

namespace GE {
    void FontRenderer::init() 
    {
        FT_Library ft;
        if(FT_Init_FreeType(&ft)) {
            std::cerr << "[Error] FREETYPE: Could not inititalise FreeType" << std::endl;
        }

        FT_Face face;
        if(FT_New_Face(ft, "Fonts/arial.ttf", 0,  &face)) {
            std::cerr << "[Error] FREETYPE: Failed to load font" << std::endl;
        }
    
        programId = glCreateProgram();

		std::string v_shader_source = loadShaderSourceCode("Shaders/Text.vs");
		std::string f_shader_source = loadShaderSourceCode("Shaders/Text.fs");

		const GLchar* v_source_array[] = { v_shader_source.c_str() };
		const GLchar* f_source_array[] = { f_shader_source.c_str() };

        if (!compileProgram(v_source_array, f_source_array, &programId)) {
			std::cerr << "Problem building Font program.  Check console log for more information." << std::endl;
		}

        glUseProgram(programId);

        textLocation = glGetUniformLocation(programId, "text");
        projectionLocation = glGetUniformLocation(programId, "projection");
        textColourLocation = glGetUniformLocation(programId, "textColour");

        FT_Set_Pixel_Sizes(face, 0, 48);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        for(unsigned char c = 32; c < 128; c++) {
            if(FT_Load_Char(face, c, FT_LOAD_RENDER)){
                std::cout << "[Error] FREETYPE: Failed to load Glyph" << std::endl;
                continue;
            }

            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            Character character = {
                texture,
                { (int)face->glyph->bitmap.width, (int)face->glyph->bitmap.rows },
                { (int)face->glyph->bitmap_left, (int)face->glyph->bitmap_top },
                static_cast<unsigned int>(face->glyph->advance.x)
            };

            charactersMap.insert(std::pair<char, Character>(c, character));
        }

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glUseProgram(0);

        FT_Done_Face(face);
        FT_Done_FreeType(ft);
    }

    void FontRenderer::RenderText(std::string text, float x, float y, float scale, glm::vec3 colour)
    {
        glUseProgram(programId);

        glm::mat4 projection = glm::ortho<float>(0, windowWidth, 0, windowHeight);
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

        glUniform3f(textColourLocation, colour.x, colour.y, colour.z);

        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(VAO);

        std::string::const_iterator c;
        for(c = text.begin(); c != text.end(); c++) {
            Character ch = charactersMap[*c];

            float xpos = x + ch.bearing[0] * scale;
            float ypos = y - (ch.size[1] - ch.bearing[1]) * scale;

            float w = ch.size[0] * scale;
            float h = ch.size[1] * scale;

            float vertices[6][4] = {
                { xpos,     ypos + h, 0.0f, 0.0f },
                { xpos,     ypos,     0.0f, 1.0f },
                { xpos + w, ypos,     1.0f, 1.0f },

                { xpos,     ypos + h, 0.0f, 0.0f },
                { xpos + w, ypos,     1.0f, 1.0f },
                { xpos + w, ypos + h, 1.0f, 0.0f }
            };

            glBindTexture(GL_TEXTURE_2D, ch.TextureID);

            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            x += (ch.Advance >> 6) * scale;
        }

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glUseProgram(0);
    }
}   
