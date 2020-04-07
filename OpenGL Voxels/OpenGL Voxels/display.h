#ifndef DISPLAY_H
#define DISPLAY_H
#include <string>
#include <GLFW/glfw3.h>
//#include <glad/glad.h>

class display
{
public:
	display(int width, int height, const std::string& title);
	GLFWwindow* m_window;
	bool shouldClose();





	
	virtual ~display();
private:
	display(const display& other);
	void operator=(const display& other);

	//void framebuffer_size_callback(GLFWwindow* m_window, int width, int height);

};

#endif // DISPLAY_H