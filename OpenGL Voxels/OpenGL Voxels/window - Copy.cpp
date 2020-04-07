#include "window.h"


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
	return true;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

static glm::vec3 cursorPos = glm::vec3(0.0f, 0.0f, 0.0f);
static glm::vec3 cursorPosOld = glm::vec3(0.0f, 0.0f, 0.0f);
static glm::vec3 tempOld = glm::vec3(0.0f, 0.0f, 0.0f);
static const float MOVEMENT_SPEED = 8.0f;
static const float MOUSE_SENSITIVITY = .2f;



window::window(const unsigned int SCR_WIDTH, const unsigned int SCR_HEIGHT, const char *windowName)
{
	Width = SCR_WIDTH;
	Height = SCR_HEIGHT;
	Title = windowName;
	createWindow();
	

}

void window::createWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	GLFWmonitor* primary = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(primary);


	Window = glfwCreateWindow(mode->width, mode->height, Title, glfwGetPrimaryMonitor(), NULL);
	if (Window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

	}
	glfwMakeContextCurrent(Window);
	//glfwSetFramebufferSizeCallback(Window, framebuffer_size_callback);

	glfwSetCursorPosCallback(Window, cursorPositionCallback);
	glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetWindowMonitor(Window, primary, 0, 0, mode->width, mode->height, GLFW_DONT_CARE);
	glfwSetKeyCallback(Window, key_callback);

}




void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}



void window::swapBuffers()
{
	glfwSwapBuffers(Window);
}

bool window::shouldClose()
{
	return glfwWindowShouldClose(Window);
}

void window::cursorPositionCallback(GLFWwindow * Window, double xPos, double yPos)
{
	cursorPos = glm::vec3(float(xPos), float(-yPos), 0.f);

}


void window::eventHandler(camera& Camera, GLFWwindow* Window, float deltaTime)
{
	//Looking around
	//std::cout << float(cursorPos.x) << "     " << float(cursorPos.y) << "    " << (cursorPos.x - cursorPosOld.x) << "    " << (cursorPos.y - cursorPosOld.y) << std::endl;
	glm::vec3 deltaPos = cursorPos - cursorPosOld;
	//std::cout << float(deltaPos.x) << "     " << float(deltaPos.y) << std::endl;
	cursorPosOld = cursorPos;
	float Pitch = (deltaPos.y * MOUSE_SENSITIVITY * deltaTime);
	float Yaw = (deltaPos.x * MOUSE_SENSITIVITY * deltaTime);
	Camera.fPitch = 1.2 * Pitch;
	Camera.fYaw = -Yaw;


	
	
	//Movement
	glm::vec3 vForward = glm::normalize(glm::vec3(Camera.m_forward.x, 0.f, Camera.m_forward.z)) * deltaTime * MOVEMENT_SPEED;
	if (glfwGetKey(Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(Window, true);
	if (glfwGetKey(Window, GLFW_KEY_W) == GLFW_PRESS)
		Camera.m_position += vForward;
	if (glfwGetKey(Window, GLFW_KEY_S) == GLFW_PRESS)
		Camera.m_position -= vForward;
	if (glfwGetKey(Window, GLFW_KEY_A) == GLFW_PRESS)
		Camera.m_position -= glm::cross(vForward, Camera.m_up);
	if (glfwGetKey(Window, GLFW_KEY_D) == GLFW_PRESS)
		Camera.m_position += glm::cross(vForward, Camera.m_up);
	if (glfwGetKey(Window, GLFW_KEY_SPACE) == GLFW_PRESS)
		Camera.m_position += Camera.m_up * deltaTime * MOVEMENT_SPEED;
	if (glfwGetKey(Window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		Camera.m_position -= Camera.m_up * deltaTime * MOVEMENT_SPEED;


}
void window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
		DebugScreen();
}

void window::DebugScreen()
{
	unsigned char string[] = " Position XYZ";
	int w;



}




window::~window()
{
}

