#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glad/glad.h>
#include "Transform.h"
#include "camera.h"



class shader
{
public:
	
	shader() { }
	shader(const std::string& filename);
	void Bind();
	void Update(const Transform& transform, camera& Camera);
	void setText(GLuint width, GLuint height);
	void SetVector2f(const GLchar * name, GLfloat x, GLfloat y, GLboolean useShader);
	void SetVector3f(const GLchar * name, glm::vec3 color);
	void SetInteger(const GLchar * name, GLint value);
	virtual ~shader();
	GLuint m_program;
private:
	shader(const shader& other) {}
	void operator = (const shader& other) {}
	static const unsigned int NUM_SHADERS = 2;

	enum
	{
		TRANSFORM_U,

		NUM_UNIFORMS
	};



	GLuint m_uniforms[NUM_UNIFORMS];
	GLuint m_shaders[NUM_SHADERS];
};

#endif SHADER_H