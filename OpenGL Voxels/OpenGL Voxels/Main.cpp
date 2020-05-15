#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include "shader.h"
#include "mesh.h"
#include "camera.h"
#include "Texture.h"
#include "Transform.h"
#include "window.h"
#include "ChunkHandler.h"
//#include "chunk.h"
#include "Text.h"




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


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const char* SCR_NAME = "Minecraft Rip-Off";

float previous = 0.f;

//Input Callback



	window Window(SCR_WIDTH, SCR_HEIGHT, SCR_NAME);


int main()
{
	// glfw window creation

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	/*
	Vertex block[] = {
		//front
		Vertex(glm::vec3(0,0,0), glm::vec2(1.0f / 3,1.0f)), // front bottom left
		Vertex(glm::vec3(0,1,0), glm::vec2(1.0f / 3,0.0f)), //front top left
		Vertex(glm::vec3(1,0,0), glm::vec2(2.0f / 3,1.0f)), //front bottom right

		Vertex(glm::vec3(0,1,0), glm::vec2(1.0f / 3,0)), // front top left
		Vertex(glm::vec3(1,1,0), glm::vec2(2.0f / 3,0)), //front top right
		Vertex(glm::vec3(1,0,0), glm::vec2(2.0f / 3,1)), //front bottom right
		//back

		Vertex(glm::vec3(0,0,1), glm::vec2(1.0f / 3,1.0f)), // back bottom left
		Vertex(glm::vec3(1,0,1), glm::vec2(2.0f / 3,1.0f)), // back bottom right
		Vertex(glm::vec3(0,1,1), glm::vec2(1.0f / 3,0.0f)), // back top left

		Vertex(glm::vec3(0,1,1), glm::vec2(1.0f / 3,0)),  // back top left
		Vertex(glm::vec3(1,0,1), glm::vec2(2.0f / 3,1)),  // back bottom right
		Vertex(glm::vec3(1,1,1), glm::vec2(2.0f / 3,0)),  // back top right
		//right
		Vertex(glm::vec3(1,1,0), glm::vec2(2.0f / 3,0)),   // front top right
		Vertex(glm::vec3(1,1,1), glm::vec2(1.0f / 3,0)),   // back top right
		Vertex(glm::vec3(1,0,1), glm::vec2(1.0f / 3,1)),   // back bottom right

		Vertex(glm::vec3(1,0,0), glm::vec2(2.0f / 3,1.0f)), // front bottom right
		Vertex(glm::vec3(1,1,0), glm::vec2(2.0f / 3,0.0f)), // front top right
		Vertex(glm::vec3(1,0,1), glm::vec2(1.0f / 3,1.0f)), // back bottom right
		//left
		Vertex(glm::vec3(0,0,0), glm::vec2(1.0f / 3,1.0f)), // front bottom left
		Vertex(glm::vec3(0,0,1), glm::vec2(2.0f / 3,1.0f)), // back bottom left
		Vertex(glm::vec3(0,1,0), glm::vec2(1.0f / 3,0.0f)), // front top left

		Vertex(glm::vec3(0,0,1), glm::vec2(2.0f / 3,1.0f)),    // back bottom left
		Vertex(glm::vec3(0,1,1), glm::vec2(2.0f / 3,0.0f)),    // back top left
		Vertex(glm::vec3(0,1,0), glm::vec2(1.0f / 3,0.0f)),    // front top left
		//Top

		Vertex(glm::vec3(1,1,0), glm::vec2(1 / 3.f,1)), // front top right
		Vertex(glm::vec3(0,1,1), glm::vec2(0,0)), // back top left
		Vertex(glm::vec3(1,1,1), glm::vec2(1 / 3.f,0)), // back top right

		Vertex(glm::vec3(0,1,0), glm::vec2(0,1)), // front top left
		Vertex(glm::vec3(0,1,1), glm::vec2(0,0)), // back top left
		Vertex(glm::vec3(1,1,0), glm::vec2(1/3.f,1)), // front top right
		//Bottom
		Vertex(glm::vec3(0,0,0), glm::vec2(2.0f / 3,0)), // front bottom left
		Vertex(glm::vec3(1,0,0), glm::vec2(2.0f / 3,1)), // front bottom right
		Vertex(glm::vec3(0,0,1), glm::vec2(1,0)), // back bottom left

		Vertex(glm::vec3(1,0,0), glm::vec2(2.0f / 3,1)), // front bottom right
		Vertex(glm::vec3(1,0,1), glm::vec2(2.0f / 3,0)), // back bototm right
		Vertex(glm::vec3(0,0,1), glm::vec2(1,0)), // back bottom left
	};
	*/
	chunk Chunk(glm::vec3(0, 0, 0));
	//chunk Chunk2(glm::vec3(16, 0,0));
	//chunk Chunk3(glm::vec3(0, 0, 16));
	//chunk Chunk4(glm::vec3(16, 0, 16));
	//generateChunk(glm::vec3(0, 0, 0));
	//loadChunk(glm::vec3(0, 0, 0));
	Chunk.createMesh();
	//Chunk2.createMesh();
	//Chunk3.createMesh();
	//Chunk4.createMesh();

	Mesh mesh(Chunk.vertices, Chunk.texCoords);
	//Mesh mesh2(Chunk2.vertices, Chunk2.texCoords);
	//Mesh mesh3(Chunk3.vertices, Chunk3.texCoords);
	//Mesh mesh4(Chunk4.vertices, Chunk4.texCoords);
	shader Shader("./res/basicShader");
	TextRenderer text(&Window);
	text.Load("./fonts/SourceCodePro-Regular.ttf", 45);
	Texture texture("./res/download.png");
	camera Camera(glm::vec3(0.f,0.f,-5.f), glm::radians(90.0f), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.01f, 1000.0f);
	Transform transform;
	float counter = 0.0f;











	// render loop
	while (!Window.shouldClose())
	{

		float now = glfwGetTime();
		float deltaTime = now - previous;
		previous = now;
		
		// input
		//processInput(Window);

		Window.eventHandler(Camera, Window.Window, deltaTime);
		// render
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		Camera.SetViewProjection();
		Shader.Bind();
		texture.Bind(0);



		Shader.Update(transform, Camera);
		mesh.Draw();
		//mesh2.Draw();
		//mesh3.Draw();
		//mesh4.Draw();
		std::stringstream ss;
		std::stringstream positionX;
		std::stringstream positionY;
		std::stringstream positionZ;
		positionX << Camera.m_position.x;
		positionY << Camera.m_position.y;
		positionZ << Camera.m_position.z;
		ss << 1/deltaTime;
		if (Window.DebugScreen())
		{
		text.RenderText("FPS: " + ss.str(), glm::vec2(10.f, 10.f), 1.0f);
		text.RenderText("X: " + positionX.str() + " Y : " + positionY.str() + " Z: " + positionZ.str(), glm::vec2(10.0f, 45.0f), 1.0f);
		}

		glfwPollEvents();
		Window.swapBuffers();
		//counter += 0.01f;
	}
	// glfw: terminate, clearing all previously allocated GLFW resources.
	glfwTerminate();
	return 0;
}





