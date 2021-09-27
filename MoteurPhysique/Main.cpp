#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "Vector3D.h"
#include "Particule.h"


int main()
{
	/*
	Vector3D x = Vector3D(1, 0, 0);
	Vector3D y = Vector3D(0, 1, 0);
	Vector3D truc = x + y;
	Particule bouboule = Particule(10, 1, x, y, truc);
	bouboule.integrer(1);
	*/
	
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "test", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create a GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	




	return 0;
}