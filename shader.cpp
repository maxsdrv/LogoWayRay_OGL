#include "shader.h"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	//1.
	//Get source shader's code from FilePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	

	//Check it that object's ifstream can throw exceptions
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		//Open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		//Read data into stream
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		//Close files
		vShaderFile.close();
		fShaderFile.close();
		//Stream to array GLChar
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();

	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();

	//2.
	//Assembly shaders
	GLuint vertex, fragment;
	GLint succes;
	GLchar infoLog[512];
	
	

	//Vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	std::cout << "Compiling shader " << vertexPath << std::endl;
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &succes);
	if (!succes)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

	}

	//Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	std::cout << "Compiling shader " << fragmentPath << std::endl;
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &succes);
	if (!succes)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//Shader Program
	this->Program = glCreateProgram();
	std::cout << "Linking program" << std::endl;
	glAttachShader(this->Program, vertex);
	glAttachShader(this->Program, fragment);
	glLinkProgram(this->Program);

	glGetProgramiv(this->Program, GL_LINK_STATUS, &succes);
	if (!succes)
	{
		glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}


	//Remove shaders

	glDetachShader(this->Program,vertex);
	glDetachShader(this->Program,fragment);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::~Shader()
{
	std::cout << "-------------" << std::endl;
}

void Shader::Use()
{
	glUseProgram(this->Program);
}
