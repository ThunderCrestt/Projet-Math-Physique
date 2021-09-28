#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "Vector3D.h"
#include "Particule.h"
#include "ParticuleSystem.h"
#include<vector>
#include"Libraries/include/ft2build.h"
#include FT_FREETYPE_H  
#include <stdlib.h>


// vertex shader basique
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

// fragment shader simple avec couleur gris clair
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.9f, 0.9f, 0.9f, 1.0f);"
"}\0";

unsigned int shaderProgram;
const int num_segments = 100;
float circleCenterX = -0.5;
float circleCenterY = -0.5;
float rCircle = 0.1;
//ParticuleSystem
//Particule
unsigned int myVBO;  
unsigned int myVAO;
FT_Face face;


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// recuperation des vertices pour dessiner plus tard 
void setupGeometries() {
	glGenVertexArrays(1, &myVAO);
	glGenBuffers(1, &myVBO);

	//figure cercle : utilisation de LINE_LOOP
	float sixVertsForLines[2 * num_segments];
	int posX = 0;
	int posY = 1;

	for (int ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle
		float x = rCircle * cosf(theta);
		float y = rCircle * sinf(theta);
		sixVertsForLines[posX] = x + circleCenterX;
		sixVertsForLines[posY] = y + circleCenterY;
		posX += 2;
		posY += 2;
	}

	//Conserve les vertices des segments du cercle pour les dessiner plus tard 
	glBindVertexArray(myVAO);
	glBindBuffer(GL_ARRAY_BUFFER, myVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sixVertsForLines), &sixVertsForLines, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


// dessine les formes en fonction des vertices passés dans myVAO
void rendScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shaderProgram);

	//dessin du crecle
	glBindVertexArray(myVAO);
	glVertexAttrib3f(1, 1.0f, 1.0f, 0.2f);		// A yellow-ish color (R, G, B values).
	glDrawArrays(GL_LINE_LOOP, 0, num_segments);

	
	
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Particule *particule = reinterpret_cast<Particule*>(glfwGetWindowUserPointer(window));
	Vector3D basePosition = Vector3D(-0.5, 0, 0);
	Vector3D initialSpeed = Vector3D(0.9, 0.9, 0);
	Vector3D acceleration;
	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
	{
		//update la particule
		acceleration = Vector3D(0, -0.981, 0);
		particule->setupVectors(basePosition, initialSpeed, acceleration);
		particule->setMass(25);
		//update la couleur
		//update le rayon
		rCircle = 0.1;
		//setupGeometric
		system("cls");
		std::wcout << "Projectile : boule de feu";
	}
	else if(key == GLFW_KEY_2 && action == GLFW_PRESS) {
		//update la particule
		acceleration = Vector3D(0, -1.2, 0);
		particule->setupVectors(basePosition, initialSpeed, acceleration);
		particule->setMass(75);
		//update la couleur
		//update le rayon
		 rCircle = 0.15;
		//setupGeometric
		 system("cls");
		 std::wcout << "Projectile : ballon";
	}
	else if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
		//update la particule
		acceleration = Vector3D(0, -1.5, 0);
		particule->setupVectors(basePosition, initialSpeed, acceleration);
		particule->setMass(130);
		//update la couleur
		//update le rayon
		 rCircle = 0.2;
		//setupGeometric
		 std::system("cls");
		 std::wcout << "Projectile : boulet de canon";
	}
}

int main()
{
	// initialisation de la fen�tre d'openGL
	//initialisation d'une particule qui sera modifié pour chaque type de projectile
	ParticuleSystem system = ParticuleSystem();
	Vector3D position = Vector3D(-0.5, 0.0, 0);
	Vector3D initialSpeed = Vector3D(0.7, 0.7, 0);
	Vector3D acceleration =Vector3D(0,-0.981,0); //acc must be different for each object
	Particule bouboule = Particule(10, 1, position, initialSpeed, acceleration,system);
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1200, 800, "test", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create a GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, &bouboule);
	glfwSetKeyCallback(window, key_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//parametrages des shaders (� mettre dans une fonction plus tard)
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glUseProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//affichage de la fen�tre

	glViewport(0, 0, 1000, 1000);

	setupGeometries();

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	std::system("cls");
	std::wcout << "Projectile : boule de feu";


	//boucle de jeu
	double currentFrame = glfwGetTime();
	double lastFrame = currentFrame;
	double deltaTime;
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		system.integerAllParticule(deltaTime);
		//for now
		circleCenterX = bouboule.getPosition().getX();
		circleCenterY = bouboule.getPosition().getY();
		setupGeometries();
		rendScene();


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	




	return 0;
}