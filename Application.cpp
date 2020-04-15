#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtx/transform.hpp>
#include <GLM/gtc/matrix_transform.hpp>

#include <iostream>
#include <vector>
#include "shader.h"


//Using shaders and using two VBO and VAO to display primitives


int main(void)
{

	

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        
        return -1;
    }


    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 
    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1024, 768, "OpenGL-Test", nullptr, nullptr);
    if (!window)
    {
        fprintf(stderr, "Failed to open winow");
       
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);


    //Initialize GLEW
    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Failed to initialize GLEW\n");
        
        glfwTerminate();
        return -1;
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glEnable(GL_DEPTH_TEST);

    glDepthFunc(GL_LESS);



	// Create and compile our GLSL program from the shaders
	Shader shaderId("vertex.shader", "Fragment_2.shader");


	GLfloat vertices[] = {
		0.05f, 0.9f, 0.0f,
		0.9f, -0.9f, 0.0f,
		0.05f, -0.9f, 0.0f,

	};
	
	GLfloat vertices_second_triangle[] = {

		-0.05f, 0.9f, 0.0f,
		-0.9f, -0.9f, 0.0f,
		-0.05f, -0.9f, 0.0f
	};


	GLuint VBOs[2], VAOs[2];

	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);
	

	//First triangle setup
	//================================================================================================
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]); //make the buffer current
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0); // Unbind VAO
	
	//Second triangle setup
	//=================================================================================================
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_second_triangle), vertices_second_triangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	
	
	

    /* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		//Color theme
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		shaderId.Use();
		

		GLfloat timeValue = glfwGetTime();
		GLfloat greenValue = (sin(timeValue) / 2) + 0.25;
		GLint vertexColorLocation = glGetUniformLocation( shaderId.Program,"ourColor");
		glUniform4f(vertexColorLocation, 1.0f, greenValue, 0.0f, 1.0f);

		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//glUseProgram(shaderProgramYellow);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		//Swap the screen buffers
		glfwSwapBuffers(window);

	}
		// Properly de-allocate all resources once they've outlived their purpose
		glDeleteVertexArrays(2, VAOs);
		glDeleteBuffers(2, VBOs);
		

		glfwTerminate();
		return 0;
		
	

	
}
