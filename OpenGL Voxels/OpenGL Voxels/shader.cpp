#include "shader.h"
#include <iostream>
#include <fstream>
#include <vector>


#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall())



static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}


static bool GLLogCall()
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << ")" << std::endl;
		return false;
	}
	std::cout << "No ERr" << std::endl;
	return true;
}


static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static std::string LoadShader(const std::string& fileName);
static GLuint CreateShader(const std::string& text, GLenum shadeType);





shader::shader(const std::string& filename)
{
	m_shaders[0] = CreateShader(LoadShader(filename + ".vs"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(filename + ".fs"), GL_FRAGMENT_SHADER);
	//m_shaders[0] = CreateShader(LoadShader("./res/basicShader.vs"), GL_VERTEX_SHADER);
	//m_shaders[1] = CreateShader(LoadShader("./res/basicShader.fs"), GL_FRAGMENT_SHADER);

	m_program = glCreateProgram();
	CheckShaderError(m_program, GL_INVALID_OPERATION, true, "Error: Program Compile Error");
	for (unsigned int i = 0; i < NUM_SHADERS; i++) {
		glAttachShader(m_program, m_shaders[i]);
	}
	glBindAttribLocation(m_program, 0, "position");
	glBindAttribLocation(m_program, 1, "texCoord");
	//glBindAttribLocation(m_program, 1, "rotation");

	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Program linking failed: ");

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program Validation failed: ");

	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
}



void shader::Bind()
{
	glUseProgram(m_program);
}


void shader::Update(const Transform& transform, camera& Camera)
{

	//glClear(GL_DEPTH_BUFFER_BIT);
	glm::mat4 model = Camera.GetViewProjection() * transform.GetModel();
	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
}

void shader::setText(GLuint width, GLuint height)
{
	glUseProgram(m_program);
	glm::mat4 model = glm::ortho(0.0f, static_cast<GLfloat>(width), static_cast<GLfloat>(height), 0.0f);
	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
}

void shader::SetVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader)
{
	if (useShader)
		GLCall(glUseProgram(m_program));
	glUniform2f(glGetUniformLocation(m_program, name), x, y);
}

void shader::SetVector3f(const GLchar * name, glm::vec3 color)
{
	
	glUseProgram(m_program);
	//std::cout << "Stinky" << std::endl;
	glUniform3f(glGetUniformLocation(m_program, name), color.x, color.y, color.z);
	//std::cout << "Color stuff" << color.x << "|" << color.y << "|" << color.z << std::endl;
}
void shader::SetInteger(const GLchar * name, GLint value)
{

	GLCall(glUseProgram(m_program));
	//std::cout << "Stinky" << std::endl;
	glUniform1i(glGetUniformLocation(m_program, name), value);
}

shader::~shader()
{

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}


	glDeleteProgram(m_program);
}

static GLuint CreateShader(const std::string& text, GLenum shaderType)
{
	GLCall(GLuint Shade = glCreateShader(shaderType));
	if (Shade == 0)
		std::cerr << "ErrorL Shader creation failed!" << std::endl;
	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];
	shaderSourceStringLengths[0] = text.length();
	shaderSourceStrings[0] = text.c_str();

	glShaderSource(Shade, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(Shade);


	GLint isCompiled = 0;
	glGetShaderiv(Shade, GL_COMPILE_STATUS, &isCompiled);

	
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(Shade, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(Shade, maxLength, &maxLength, &errorLog[0]);
		for (int i = 0; i < maxLength; i++)
		{
			std::cout << errorLog[i];
		}
		std::cout << "done" << std::endl;
		
		// Provide the infolog in whatever manor you deem best.
		// Exit with failure.
		glDeleteShader(Shade); // Don't leak the shader.
		//return;
	}
	else
	{
		//std::cout << "No Errors Thank Fucking God" << std::endl;
	}

	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	CheckShaderError(Shade, GL_COMPILE_STATUS, false, "Error: Shader Compilation Failed: ");
	return Shade;
}

static std::string LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());
	std::string output;
	std::string line;
	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}
	return output;


}
static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };
}
