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
"   FragColor = vec4(0.6f, 0.6f, 0.6f, 1.0f);"
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
const int iCircle = 0;
const int iFirstSquare = 1;
const int iSecondSquare = 2;
const int iThirdSquare = 3;
float circleCenterX = -0.5;
float circleCenterY = 0.5;
float rCircle = 0.03;
unsigned int myVBO[4];
unsigned int myVAO[4];



void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// recuperation des vertices pour dessiner plus tard 
void setupGeometries(ParticuleSystem system) {
	glGenVertexArrays(4, &myVAO[0]);
	glGenBuffers(4, &myVBO[0]);

	//figure cercle pour les blobs
	float sixVertsForLines[10 * num_segments];
	int posX = 0;
	int posY = 1;
	Registre registre = system.getRegistry().getRegistre();

	//Injection des points du premier blob (blob central)
	for (int ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle
		float x = rCircle * cosf(theta);
		float y = rCircle * sinf(theta);
		sixVertsForLines[posX] = x + system.getRegistry().getEnregistrementAtPos(0).particule->getPosition().getX();
		sixVertsForLines[posY] = y + system.getRegistry().getEnregistrementAtPos(0).particule->getPosition().getY();
		posX += 2;
		posY += 2;
	}

	//Deuxième blob
	for (int ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle
		float x = rCircle * cosf(theta);
		float y = rCircle * sinf(theta);
		sixVertsForLines[posX] = x + system.getRegistry().getEnregistrementAtPos(1).particule->getPosition().getX();
		sixVertsForLines[posY] = y + system.getRegistry().getEnregistrementAtPos(1).particule->getPosition().getY();
		posX += 2;
		posY += 2;
	}

	//Troisième blob
	for (int ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle
		float x = rCircle * cosf(theta);
		float y = rCircle * sinf(theta);
		sixVertsForLines[posX] = x + system.getRegistry().getEnregistrementAtPos(2).particule->getPosition().getX();
		sixVertsForLines[posY] = y + system.getRegistry().getEnregistrementAtPos(2).particule->getPosition().getY();
		posX += 2;
		posY += 2;
	}

	//Quatrième blob
	for (int ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle
		float x = rCircle * cosf(theta);
		float y = rCircle * sinf(theta);
		sixVertsForLines[posX] = x + system.getRegistry().getEnregistrementAtPos(3).particule->getPosition().getX();
		sixVertsForLines[posY] = y + system.getRegistry().getEnregistrementAtPos(3).particule->getPosition().getY();
		posX += 2;
		posY += 2;
	}

	//Cinquième blob
	for (int ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle
		float x = rCircle * cosf(theta);
		float y = rCircle * sinf(theta);
		sixVertsForLines[posX] = x + system.getRegistry().getEnregistrementAtPos(4).particule->getPosition().getX();
		sixVertsForLines[posY] = y + system.getRegistry().getEnregistrementAtPos(4).particule->getPosition().getY();
		posX += 2;
		posY += 2;
	}

	//Conservation de tout les cercles
	glBindVertexArray(myVAO[iCircle]);
	glBindBuffer(GL_ARRAY_BUFFER, myVBO[iCircle]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sixVertsForLines), &sixVertsForLines, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);


	// figure première plateforme
	float firstSquare[] = {
		-1.0f, -0.2f,
		-0.3f, -0.2f,
		-0.3f, -1.0f,
		-1.0f, -0.2f,
		-1.0f, -1.0f,
		-0.3f, -1.0f,
	};
	glBindVertexArray(myVAO[iFirstSquare]);
	glBindBuffer(GL_ARRAY_BUFFER, myVBO[iFirstSquare]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstSquare), firstSquare, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	//Figure deuxième plateforme
	float secondSquare[] = {
		-0.3f, -1.0f,
		0.3f, -1.0f,
		0.3f, -0.5f,
		-0.3f, -1.0f,
		-0.3f, -0.5f,
		0.3f, -0.5f,
	};
	glBindVertexArray(myVAO[iSecondSquare]);
	glBindBuffer(GL_ARRAY_BUFFER, myVBO[iSecondSquare]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondSquare), secondSquare, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	//Figure troisième plateforme
	float thirdSquare[] = {
		0.3f, -0.7f,
		1.0f, -0.7f,
		1.0f, -1.0f,
		0.3f, -0.7f,
		0.3f, -1.0f,
		1.0f, -1.0f,
	};
	glBindVertexArray(myVAO[iThirdSquare]);
	glBindBuffer(GL_ARRAY_BUFFER, myVBO[iThirdSquare]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(thirdSquare), thirdSquare, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


// dessine les formes en fonction des vertices passés dans myVAO
void rendScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shaderProgramGreen);

	//dessin des blobs:
	glBindVertexArray(myVAO[iCircle]);
	glDrawArrays(GL_LINE_LOOP, 0, num_segments);
	glDrawArrays(GL_LINE_LOOP, num_segments, num_segments);
	glDrawArrays(GL_LINE_LOOP, 2 * num_segments, num_segments);
	glDrawArrays(GL_LINE_LOOP, 3 * num_segments, num_segments);
	glDrawArrays(GL_LINE_LOOP, 4 * num_segments, num_segments);

	glUseProgram(shaderProgramGrey);

	//Dessin des plateforme:
	glBindVertexArray(myVAO[iFirstSquare]);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(myVAO[iSecondSquare]);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(myVAO[iThirdSquare]);
	glDrawArrays(GL_TRIANGLES, 0, 6);

}

//Récuperation des évenements clavier
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Particule* particule = reinterpret_cast<Particule*>(glfwGetWindowUserPointer(window));
	Vector3D basePosition = Vector3D(-0.5, 0, 0);
	Vector3D initialSpeed = Vector3D(0.9, 0.9, 0);
	Vector3D acceleration;
	//Tant que la flèche de droite est pressée
	if (key == GLFW_KEY_RIGHT && action == GLFW_REPEAT)
	{
		circleCenterX += 0.01;
	}
	//Tant que la flèche de droite est pressée
	else if (key == GLFW_KEY_LEFT && action == GLFW_REPEAT)
	{
		circleCenterX -= 0.01;
	}
}

int main()
{
	//initialisation d'une particule qui sera modifié pour chaque type de projectile
	unsigned iterationsContactResolver = 15;
	//ParticuleContactResolver resolver=ParticuleContactResolver(iterationsContactResolver);
	ParticuleSystem system = ParticuleSystem();
	system.resolver.setIterations(15);
	Vector3D positionB1 = Vector3D(-0.5, 0.5, 0);
	Vector3D positionB2 = Vector3D(-0.43, 0.5, 0);
	Vector3D positionB3 = Vector3D(-0.57, 0.5, 0);
	Vector3D positionB4 = Vector3D(-0.5, 0.57, 0);
	Vector3D positionB5 = Vector3D(-0.5, 0.43, 0);
	//Vector3D initialSpeed = Vector3D(0.7, 0.7, 0);
	//Vector3D acceleration =Vector3D(0,-0.981,0); //acc must be different for each object
	Particule blob1 = Particule(1, 1, positionB1, 0, 0,rCircle);
	Particule blob2 = Particule(1, 1, positionB2, 0, 0, rCircle);
	Particule blob3 = Particule(1, 1, positionB3, 0, 0, rCircle);
	Particule blob4 = Particule(1, 1, positionB4, 0, 0, rCircle);
	Particule blob5 = Particule(1, 1, positionB5, 0, 0, rCircle);
	//les particules doivent être ajouter au système aussi
	system.addParticule(blob1);
	system.addParticule(blob2);
	system.addParticule(blob3);
	system.addParticule(blob4);
	system.addParticule(blob5);


	//Ajout de la premiere particule avec un generateur de force gravité
	Vector3D gravity = Vector3D(0, -1, 0);
	GravityForceGenerator gravityGenerator = GravityForceGenerator(gravity);
	system.addToRegistreForce(blob1, gravityGenerator);
	system.addToRegistreForce(blob2, gravityGenerator);
	system.addToRegistreForce(blob3, gravityGenerator);
	system.addToRegistreForce(blob4, gravityGenerator);
	system.addToRegistreForce(blob5, gravityGenerator);

	//Ajout des ressort entre le blob 1 et les autres
	
	ParticuleSpring ressortGeneratorb1b2 = ParticuleSpring(&blob2, 4.5, 0.07);
	system.addToRegistreForce(blob1, ressortGeneratorb1b2);
	ParticuleSpring ressortGeneratorb1b3 = ParticuleSpring(&blob3, 4.5, 0.07);
	system.addToRegistreForce(blob1, ressortGeneratorb1b3);
	ParticuleSpring ressortGeneratorb1b4 = ParticuleSpring(&blob4, 4.5, 0.07);
	system.addToRegistreForce(blob1, ressortGeneratorb1b4);
	ParticuleSpring ressortGeneratorb1b5 = ParticuleSpring(&blob5, 4.5, 0.07);
	system.addToRegistreForce(blob1, ressortGeneratorb1b5);
	ParticuleSpring ressortGeneratorb2b1 = ParticuleSpring(&blob1, 4.5, 0.07);
	system.addToRegistreForce(blob2, ressortGeneratorb2b1);
	ParticuleSpring ressortGeneratorb3b1 = ParticuleSpring(&blob1, 4.5, 0.07);
	system.addToRegistreForce(blob3, ressortGeneratorb3b1);
	ParticuleSpring ressortGeneratorb4b1 = ParticuleSpring(&blob1, 4.5, 0.07);
	system.addToRegistreForce(blob4, ressortGeneratorb4b1);
	ParticuleSpring ressortGeneratorb5b1 = ParticuleSpring(&blob1, 4.5, 0.07);
	system.addToRegistreForce(blob5, ressortGeneratorb5b1);
	
	system.registreContactGenerator.push_back(new PlaneSurface2DContactGenerator(Vector3D(-0.9 - 0.9, 0), Vector3D(-0.9, 0.9, 0), system.getAllParticules(), 0.2));
	system.registreContactGenerator.push_back(new PlaneSurface2DContactGenerator(Vector3D(0.9, -0.9, 0), Vector3D(0.9, 0.9, 0), system.getAllParticules(), 0.2));
	system.registreContactGenerator.push_back(new PlaneSurface2DContactGenerator(Vector3D(-1,-0.2,0),Vector3D(-0.3,-0.2,0),system.getAllParticules(),0.2));
	system.registreContactGenerator.push_back(new PlaneSurface2DContactGenerator(Vector3D(-0.3,-0.2,0),Vector3D(-0.3,-0.5,0),system.getAllParticules(),0.2));
	system.registreContactGenerator.push_back(new PlaneSurface2DContactGenerator(Vector3D(-0.3, -0.5, 0), Vector3D(0.3, -0.5, 0), system.getAllParticules(),0.2));
	system.registreContactGenerator.push_back(new PlaneSurface2DContactGenerator(Vector3D(0.3, -0.5, 0), Vector3D(0.3, -0.7, 0), system.getAllParticules(),0.2));
	system.registreContactGenerator.push_back(new PlaneSurface2DContactGenerator(Vector3D(0.3, -0.7, 0), Vector3D(1, -0.7, 0), system.getAllParticules(),0.2));

	system.registreContactGenerator.push_back(new ParticuleCable(&blob1, &blob2, 0.09, 0.1));
	system.registreContactGenerator.push_back(new ParticuleCable(&blob1, &blob3, 0.09, 0.1));
	system.registreContactGenerator.push_back(new ParticuleCable(&blob1, &blob4, 0.09, 0.1));
	system.registreContactGenerator.push_back(new ParticuleCable(&blob1, &blob5, 0.09, 0.1));
	
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
	glfwSetWindowUserPointer(window, &blob1);
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
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		system.runPhysic(deltaTime);
		processInput(window);
		setupGeometries(system);
		rendScene();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();





	return 0;
}