#version 330 core

layout(location = 0) in vec3 position; //Устанавливаем позицию переменной
									   //с координатами в 0
layout(location = 1) in vec3 color;    // Переменную с цветом в 1

out vec3 ourColor; //Передаём цвет во фрагментный шейдер

void main()
{
	gl_Position = vec4(position, 1.0);
	ourColor = color; //Устанавливаем значение цвета, полученное от вершинных
					  // данных

}