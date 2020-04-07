#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <vector>
#include <stdlib.h>
#include "shader.h"
#include "window.h"
#include <ft2build.h>
#include FT_FREETYPE_H











struct Character {
	GLuint TextureID;   // ID handle of the glyph texture
	glm::ivec2 Size;    // Size of glyph
	glm::ivec2 Bearing; // Offset from baseline to left/top of glyph
	GLuint Advance;     // Horizontal offset to advance to next glyph
};






class TextRenderer
{
public:

	// Holds a list of pre-compiled Characters
	std::map<GLchar, Character> Characters;
	// Shader used for text rendering
	



	TextRenderer(window * Window);
	void Load(std::string font, GLuint fontSize);
	void RenderText(std::string text, glm::vec2 position, GLfloat scale, glm::vec3 color = glm::vec3(1.0f));
	shader* TextShader;
	window* Window;
	virtual ~TextRenderer();




private:
	GLuint VAO, VBO;




};
