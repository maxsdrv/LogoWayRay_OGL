#ifndef SHADER_H_
#define SHADER_H_

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include <vector>

#include <GL/glew.h>

class Shader
{
public:
	GLuint Program;
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	~Shader();
	
	void Use();

private:

};

#endif // !SHADER_H_