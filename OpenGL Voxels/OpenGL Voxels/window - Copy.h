#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include "camera.h"




class window
{
protected:

public:
	
	window(const unsigned int SCR_WIDTH, const unsigned int SCR_HEIGHT, const char *windowName);
	void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods);
	int Width, Height;
	GLFWwindow* Window;
	// glm::vec3 tempOld;
	const char* Title;
	void createWindow();
	void swapBuffers();
	bool shouldClose();
	static void cursorPositionCallback(GLFWwindow *Window, double xPos, double yPos);
	static void eventHandler(camera& Camera, GLFWwindow* Window, float deltaTime);
	~window();
	void DebugScreen();

private:
};


