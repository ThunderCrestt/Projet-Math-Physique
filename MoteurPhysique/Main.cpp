#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "Vector3D.h"
#include "Particule.h"
#include "ParticuleSystem.h"


int main()
{
	/*
	ParticuleSystem system = ParticuleSystem();
	Vector3D pos = Vector3D(1, 0, 0);
	Vector3D c = Vector3D(0, 1, 0);
	Vector3D acc = pos + c; //acc must be different for each object
	Particule bouboule = Particule(10, 1, pos, c, acc,system);
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