#version 330 core

layout(location = 0) in vec3 position; //install position attributte in 0
layout(location = 1) in vec3 color;

out vec3 ourColor;//передаём цвет во фрагментный шейдер

void main()
{
	gl_Position = vec4(position, 1.0); //напрямую передаем vec3 in vec4
	ourColor = color;
    
}