#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// OpenGL Extension Wrangler Library. 
// GLEW helps you deal with the headache that can accompany the management of extensions in OpenGL. 
// Once initialized it queries for all the available extensions on your platform, dynamically loads them and provides easy access via a single header file.

// #include <GLUT/...h>
// 'OpenGL utility library', or GLUT. 
// It provides a simplified API for window management as well as event handling, IO control and a few other services. 
// In addition, GLUT is cross platform which makes portability easier. Alternatives to GLUT include SDL and GLFW.
// GLUT is no longer being maintained and is outdated. If not using GLFW, use freeGLUT


// GLFW
#include <GLFW/glfw3.h>

// Window dimensions
const GLint WIDTH = 800, HEIGHT = 600;

// The MAIN function.
// From here we start the application and run the game loop.
int main()
{
	if (!glfwInit())
	{
		std::cout << "GLFW failed to be initialized" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	// Set GLFW Window options

	// GLF API Version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Try to set to 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1); // Try to set to 3.1

	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // CoreProfile uses just new libraries. Compat_Profile uses old ways. Max compatibility. This results in an error.

	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Mac compatibility.

	// Window-related hints
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	//glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
	//glfwWindowHint(GLFW_DECORATED, GL_FALSE);
	// hint specifies whether the window will have window decorations such as a border, a close widget, etc. This hint is ignored for full screen windows. 
	// Note that even though a window may lack a close widget, it is usually still possible for the user to generate close events.
	
	// Creates a GLFWwinow object that we can use for GLFW's functions.
	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Learn OpenGL", nullptr, nullptr);
	//GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Learn OpenGL", glfwGetPrimaryMonitor(), nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}


	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight); // Scales window to match screens with different sizes and pixel densities.

	glfwMakeContextCurrent(window);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions.
	glewExperimental = GL_TRUE;	// GLEW uses a modern approach

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glViewport(0, 0, screenWidth, screenHeight);

	// What is run when the window is open
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw opengl stuff

		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return EXIT_SUCCESS;
}