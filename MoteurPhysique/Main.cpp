#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "Vector3D.h"
#include "Particule.h"
#include "ParticuleSystem.h"
#include<vector>


const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
"}\0";

unsigned int shaderProgram;
const int NumObjects = 2;
const int iLines = 0;
const int iTriangles = 1;
const int num_segments = 100;
const float circleCenterX = 0.5f;
const float circleCenterY = 0.5f;
//ParticuleSystem
//Particule
unsigned int myVBO[NumObjects];  
unsigned int myVAO[NumObjects];

// r�ajuste viewport
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// recuperation des vertices pour dessiner plus tard 
void setupGeometries() {
	glGenVertexArrays(NumObjects, &myVAO[0]);
	glGenBuffers(NumObjects, &myVBO[0]);

	//Premi�re figure : triangles
	float trianglesVerts[] = {		//color
		-0.8f, -0.2f, 0.0f,		1.0f, 0.8f, 0.8f,		//premier triangle (forme la moiti� du canon)
		-0.4f, -0.2f, 0.0f,		1.0f, 0.8f, 0.8f,
		-0.4f,  0.0f, 0.0f,		1.0f, 0.8f, 0.8f,

		-0.8f, -0.2f, 0.0f,		1.0f, 0.8f, 0.8f,		//deuxieme triangle
		-0.8f, 0.0f, 0.0f,		1.0f, 0.8f, 0.8f,
		-0.4f,  0.0f, 0.0f,		1.0f, 0.8f, 0.8f

	};
	glBindVertexArray(myVAO[iTriangles]);
	glBindBuffer(GL_ARRAY_BUFFER, myVBO[iTriangles]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(trianglesVerts), trianglesVerts, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//deuxieme figure : ligne
	//std::vector<float> sixVertsForLines = std::vector<float> ();
	float sixVertsForLines[2 * num_segments];
	int posX = 0;
	int posY = 1;

	for (int ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle
		float x = 0.5 * cosf(theta);
		float y = 0.5 * sinf(theta);
		sixVertsForLines[posX] = x + circleCenterX;
		sixVertsForLines[posY] = y + circleCenterY;
		posX += 2;
		posY += 2;
	}


	glBindVertexArray(myVAO[iLines]);
	glBindBuffer(GL_ARRAY_BUFFER, myVBO[iLines]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sixVertsForLines), &sixVertsForLines, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);



	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


// dessine les formes en fonction des vertices pass�s dans myVAO
void rendScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shaderProgram);
	//dessin des triangles
	glBindVertexArray(myVAO[iTriangles]);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//dessin du crecle
	glBindVertexArray(myVAO[iLines]);
	glVertexAttrib3f(1, 1.0f, 1.0f, 0.2f);		// A yellow-ish color (R, G, B values).
	glDrawArrays(GL_LINE_LOOP, 0, num_segments);




}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Particule *particule = reinterpret_cast<Particule*>(glfwGetWindowUserPointer(window));
	Vector3D basePosition = Vector3D(0, 0, 0);
	Vector3D initialSpeed = Vector3D(0.07, 0.07, 0);
	Vector3D acceleration;
	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
	{
		//update la particule
		acceleration = Vector3D(0, -9.81, 0);
		particule->setupVectors(basePosition, initialSpeed, acceleration);
		particule->setMass(25);
		//update la couleur
		//update le rayon
		//setupGeometric
	}
	else if(key == GLFW_KEY_2 && action == GLFW_PRESS) {
		//update la particule
		acceleration = Vector3D(0, -12, 0);
		particule->setupVectors(basePosition, initialSpeed, acceleration);
		particule->setMass(75);
		//update la couleur
		//update le rayon
		//setupGeometric
	}
	else if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
		//update la particule
		acceleration = Vector3D(0, -15, 0);
		particule->setupVectors(basePosition, initialSpeed, acceleration);
		particule->setMass(130);
		//update la couleur
		//update le rayon
		//setupGeometric
	}
}

int main()
{
	// initialisation de la fen�tre d'openGL
	//initialisation d'une particule qui sera modifié pour chaque type de projectile
	ParticuleSystem system = ParticuleSystem();
	Vector3D position = Vector3D(1, 0, 0);
	Vector3D initialSpeed = Vector3D(0.07, 0.07, 0);
	Vector3D acceleration =Vector3D(0,-9.81,0); //acc must be different for each object
	Particule bouboule = Particule(10, 1, position, initialSpeed, acceleration,system);
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

	glViewport(0, 0, 800, 800);
	void framebuffer_size_callback(GLFWwindow * window, int width, int height);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	setupGeometries();

	//boucle de jeu
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		rendScene();


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	




	return 0;
}