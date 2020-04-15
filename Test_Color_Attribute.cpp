#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtx/transform.hpp>
#include <GLM/gtc/matrix_transform.hpp>

#include <iostream>
#include <vector>
#include "shader.h"




int main()
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
   Shader programID ("vertexTCA.shader", "FragmentTCA.shader");

	//Set up vertex data  and add color to each vertex
	GLfloat vertices[] = {
		//Position				//Color
		0.05f, 0.9f, 0.0f,		1.0f, 0.0f, 0.0f, //Left
		0.9f, -0.9f, 0.0f,		0.0f, 1.0f, 0.0f, //Right
		0.05f, -0.9f, 0.0f,		0.0f, 0.0f, 1.0f //Top

	};

	//Set up vertex data and add color to each vertex by second triangle
	GLfloat vertices_second_triangle[] = {
		//Position				//Color
		-0.05f, 0.9f, 0.0f,		1.0f, 0.0f, 0.0f, //Left 
		-0.9f, -0.9f, 0.0f,		0.0f, 1.0f, 0.0f, //Right
		-0.05f, -0.9f, 0.0f,	0.0f, 0.0f, 1.0f //Top
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
	//Attributte with coord
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Attribute with color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0); // Unbind VAO
	//Second triangle setup
	//=================================================================================================
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_second_triangle), vertices_second_triangle, GL_STATIC_DRAW);
	//Attribute with coord
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Attribute with color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat))); 
	glEnableVertexAttribArray(1);
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
		programID.Use(); //Using our shader program


		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		
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

	//glDeleteProgram(programID);
	

	glfwTerminate();


	return 0;

}