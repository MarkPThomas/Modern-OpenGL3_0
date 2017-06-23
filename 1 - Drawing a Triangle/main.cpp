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

const GLchar *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main ()\n"
"{\n"
"gl_Position = vec4( position.x, position.y, position.z, 1.0 );\n"
"}";

const GLchar *fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4( 1.0f, 0.5f, 0.2f, 1.0f );\n"
"}";
// vec4 (r, g, b, alpha)


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

	// Define viewport definitions
	glViewport(0, 0, screenWidth, screenHeight);

	GLint success;
	GLchar infoLog[512];

	GLuint vertexShader = glCreateShader( GL_VERTEX_SHADER );
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Link shaders
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderProgram, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	GLfloat vertices[] = 
	{
		-0.5f, -0.5f, 0.0f, //bottom left
		0.5f, -0.5f,  0.0f, // bottom right
		0.0f, 0.5f, 0.0f // midde point
	};

	GLuint VAO, VBO; // Vertex Array Object, Vertex Buffer Object
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);


	// Game loop
	// What is run when the window is open
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activated (key pressed, mouse moved, etc.) and call corresponding function.
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw opengl stuff
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	// Terminate GLFW, claering any resoures allocated by GLFW
	glfwTerminate();

	return EXIT_SUCCESS;
}