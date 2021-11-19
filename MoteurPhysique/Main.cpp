#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "Vector3D.h"
#include "Particule.h"
#include "ParticuleSystem.h"
#include<vector>
#include <stdlib.h>
#include "gravityForceGenerator.h"
#include "ParticuleSpring.h"
#include "ParticuleContactResolver.h"
#include "PlaneSurface2DContactGenerator.h"
#include "ParticuleCable.h"
#include "ParticuleElastique.h"
#include "Matrix3.h"

// vertex shader basique
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

// fragment shader simple avec couleur gris clair
const char* fragmentShaderSourceGrey = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.7f, 0.7f, 0.7f, 1.0f);"
"}\0";

// fragment shader simple avec couleur verte
const char* fragmentShaderSourceGreen = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.1f, 0.5f, 0.1f, 1.0f);"
"}\0";

unsigned int shaderProgramGrey;
unsigned int shaderProgramGreen;
const int num_segments = 100;
const int iFirstSquare = 0;
const int iSecondSquare = 1;
const int iPoint = 2;
unsigned int myVBO[3];
unsigned int myVAO[3];
Vector3D gravityCenter = Vector3D(0.0, 0.0, 0);
float transformMatrice[] = { 0,-1,1,0 };



void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// recuperation des vertices pour dessiner plus tard 
void setupGeometries(ParticuleWorld system) {
	glGenVertexArrays(3, &myVAO[0]);
	glGenBuffers(3, &myVBO[0]);

	
	//enregistrement des vertexes de la Figure

	//Création des 6 points de notre figure
	Vector3D vertex1 = { (float)(gravityCenter.getX() - 0.2), (float)(gravityCenter.getY() - 0.2) , 0 };
	Vector3D vertex2 = { (float)(gravityCenter.getX() - 0.2), (float)(gravityCenter.getY() + 0.2) , 0 };
	Vector3D vertex3 = { (float)(gravityCenter.getX() + 0.2), (float)(gravityCenter.getY() + 0.2) , 0 };
	Vector3D vertex4 = { (float)(gravityCenter.getX() + 0.2), (float)(gravityCenter.getY() - 0.2) , 0 };
	Vector3D vertex5 = { (float)(gravityCenter.getX() + 0.3), (float)(gravityCenter.getY() + 0.2) , 0 };
	Vector3D vertex6 = { (float)(gravityCenter.getX() + 0.3), (float)(gravityCenter.getY() + 0.1) , 0 };
	Vector3D vertex7 = { (float)(gravityCenter.getX() + 0.2), (float)(gravityCenter.getY() + 0.1) , 0 };

	// transformation de tous nos points

	Matrix3 transform = Matrix3({ {{(float)(sqrt(2)/2),(float)(-sqrt(2) / 2),0},
									{(float)(sqrt(2) / 2),(float)(sqrt(2) / 2),0},
									{0,0,1}} });

	vertex1 = transform * vertex1;
	vertex2 = transform * vertex2;
	vertex3 = transform * vertex3;
	vertex4 = transform * vertex4;
	vertex5 = transform * vertex5;
	vertex6 = transform * vertex6;
	vertex7 = transform * vertex7;

	//Carré 1
	float firstSquare[] = {
		vertex1.getX(),vertex1.getY(),
		vertex2.getX(),vertex2.getY(),
		vertex3.getX(),vertex3.getY(),
		vertex1.getX(),vertex1.getY(),
		vertex4.getX(),vertex4.getY(),
		vertex3.getX(),vertex3.getY(),
	};

	glBindVertexArray(myVAO[iFirstSquare]);
	glBindBuffer(GL_ARRAY_BUFFER, myVBO[iFirstSquare]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstSquare), firstSquare, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	//Carré 2
	float secondSquare[] = {
		vertex7.getX(),vertex7.getY(),
		vertex2.getX(),vertex2.getY(),
		vertex5.getX(),vertex5.getY(),
		vertex7.getX(),vertex7.getY(),
		vertex6.getX(),vertex6.getY(),
		vertex5.getX(),vertex5.getY(),
	};
	glBindVertexArray(myVAO[iSecondSquare]);
	glBindBuffer(GL_ARRAY_BUFFER, myVBO[iSecondSquare]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondSquare), secondSquare, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	//point de gravité
	float pointVertex[] = {
		gravityCenter.getX(), gravityCenter.getY(),
	};
	glBindVertexArray(myVAO[iPoint]);
	glBindBuffer(GL_ARRAY_BUFFER, myVBO[iPoint]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pointVertex), pointVertex, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

}


// dessine les formes en fonction des vertices passés dans myVAO
void rendScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shaderProgramGreen);

	//Dessin des plateforme:
	glBindVertexArray(myVAO[iFirstSquare]);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(myVAO[iSecondSquare]);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glUseProgram(shaderProgramGrey);

	//dessin point de gravité
	glBindVertexArray(myVAO[iPoint]);
	glDrawArrays(GL_POINTS, 0, 1);
}

//Récuperation des évenements clavier
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Particule* particule = reinterpret_cast<Particule*>(glfwGetWindowUserPointer(window));
	float addVelocity = 0.4;
	Vector3D basePosition = Vector3D(-0.5, 0, 0);
	Vector3D initialSpeed = Vector3D(0.9, 0.9, 0);
	Vector3D acceleration;
	//Tant que la flèche de droite est pressée
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{
		particule->setVelocity(particule->getVelocity() + Vector3D(addVelocity, 0, 0));
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE)
	{
		particule->setVelocity(particule->getVelocity() - Vector3D(addVelocity, 0, 0));
	}
	//Tant que la flèche de droite est pressée
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
	{
		particule->setVelocity(particule->getVelocity() + Vector3D(-addVelocity, 0, 0));
	}
	if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE)
	{
		particule->setVelocity(particule->getVelocity() - Vector3D(-addVelocity, 0, 0));
	}
}

int main()
{
	//initialisation d'une particule qui sera modifié pour chaque type de projectile
	unsigned iterationsContactResolver = 15;
	//ParticuleContactResolver resolver=ParticuleContactResolver(iterationsContactResolver);
	ParticuleWorld system = ParticuleWorld();
	system.resolver.setIterations(15);

	
	// initialisation de la fen�tre d'openGL
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
	glfwSetKeyCallback(window, key_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//parametrages des shaders (mettre dans une fonction plus tard)
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	unsigned int fragmentShaderGrey;
	fragmentShaderGrey = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderGrey, 1, &fragmentShaderSourceGrey, NULL);
	glCompileShader(fragmentShaderGrey);

	unsigned int fragmentShaderGreen;
	fragmentShaderGreen = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderGreen, 1, &fragmentShaderSourceGreen, NULL);
	glCompileShader(fragmentShaderGreen);

	shaderProgramGrey = glCreateProgram();
	glAttachShader(shaderProgramGrey, vertexShader);
	glAttachShader(shaderProgramGrey, fragmentShaderGrey);
	glLinkProgram(shaderProgramGrey);

	shaderProgramGreen = glCreateProgram();
	glAttachShader(shaderProgramGreen, vertexShader);
	glAttachShader(shaderProgramGreen, fragmentShaderGreen);
	glLinkProgram(shaderProgramGreen);

	glUseProgram(shaderProgramGreen);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShaderGrey);
	glDeleteShader(fragmentShaderGreen);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//affichage de la fen�tre

	glViewport(0, 0, 1000, 1000);

	setupGeometries(system);

	glClearColor(0.7f, 0.7f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	//boucle de jeu
	double currentFrame = glfwGetTime();
	double lastFrame = currentFrame;
	double deltaTime;
	while (!glfwWindowShouldClose(window))
	{
		//currentFrame = glfwGetTime();
		//deltaTime = currentFrame - lastFrame;
		//lastFrame = currentFrame;
		//system.runPhysic(deltaTime);
		//processInput(window);
		setupGeometries(system);
		rendScene();
		//std::cout << system.getAllParticules()[0]->getPosition().getX()<<std::endl;
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();





	return 0;
}