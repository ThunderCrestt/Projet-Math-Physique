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
#include "DragForceGenerator.h"
#include "Rigidbody.h"
#include "RigidBodyManager.h"
#include "ParticuleContactResolver.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "NarrowCollisionDetection.h"


const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout(location = 1) in vec3 aNormal;\n"
"out vec3 color;\n"
"uniform vec3 personaliseColor;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 proj;\n"
"void main()\n"
"{\n"
"   gl_Position = proj * view * model * vec4(aPos, 1.0);\n"
"	color = personaliseColor;\n" 
"}\0";

// fragment shader simple avec couleur gris clair
const char* fragmentShaderSource = "#version 330 core\n"
"in vec3 color;\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(color, 1.0f);"
"}\0";

unsigned int shaderProgram;

unsigned int VBO;
unsigned int VAO;
Vector3D gravityCenter = Vector3D(0.3, 0.6, 0);
float halfMedian = 0.3;


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void initShadrProgramm() {
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
}

void initGeometries(RigidBody rb)
{
	//point front face
	Vector3D fBottomLeft = { (float)rb.getPosition().getX() - halfMedian, (float)rb.getPosition().getY() - halfMedian, (float)rb.getPosition().getZ() + halfMedian };
	Vector3D fBottomRight = { (float)rb.getPosition().getX() + halfMedian, (float)rb.getPosition().getY() - halfMedian, (float)rb.getPosition().getZ() + halfMedian };
	Vector3D fUpRight = { (float)rb.getPosition().getX() + halfMedian, (float)rb.getPosition().getY() + halfMedian, (float)rb.getPosition().getZ() + halfMedian };
	Vector3D fUpLeft = { (float)rb.getPosition().getX() - halfMedian, (float)rb.getPosition().getY() + halfMedian, (float)rb.getPosition().getZ() + halfMedian };
	//point back face
	Vector3D bUpLeft = { (float)rb.getPosition().getX() - halfMedian, (float)rb.getPosition().getY() + halfMedian, (float)rb.getPosition().getZ() - halfMedian };
	Vector3D bBottomLeft = { (float)rb.getPosition().getX() - halfMedian, (float)rb.getPosition().getY() - halfMedian, (float)rb.getPosition().getZ() - halfMedian };
	Vector3D bBottomRight = { (float)rb.getPosition().getX() + halfMedian, (float)rb.getPosition().getY() - halfMedian, (float)rb.getPosition().getZ() - halfMedian };
	Vector3D bUpRight = { (float)rb.getPosition().getX() + halfMedian, (float)rb.getPosition().getY() + halfMedian, (float)rb.getPosition().getZ() - halfMedian };
	//Creation contour
	Vector3D up4 = { 3,3,0 };
	Vector3D up1 = { -3,3,0 };
	Vector3D down1 = { -3,-3,0 };
	Vector3D down4 = { 3,-3,0 };
	Vector3D up2 = { -2.8,3,0 };
	Vector3D up3 = { 2.8,3,0 };
	Vector3D middle1 = { -2.8, 2.8,0 };
	Vector3D middle2 = { 2.8,2.8,0 };
	Vector3D middle3 = { -2.8,-2.8,0 };
	Vector3D middle4 = { 2.8,-2.8,0 };
	Vector3D down2 = { -2.8, -3, 0 };
	Vector3D down3 = { 2.8,-3,0 };

	//transformation
	fBottomLeft = rb.getTransformMatrix() * fBottomLeft;
	fBottomRight = rb.getTransformMatrix() * fBottomRight;
	fUpRight = rb.getTransformMatrix() * fUpRight;
	fUpLeft = rb.getTransformMatrix() * fUpLeft;
	bUpLeft = rb.getTransformMatrix() * bUpLeft;
	bBottomRight = rb.getTransformMatrix() * bBottomRight;
	bBottomLeft = rb.getTransformMatrix() * bBottomLeft;
	bUpRight = rb.getTransformMatrix() * bUpRight;

	

	GLfloat vertices[] =
	{

		//right face
		bBottomLeft.getX(), bBottomLeft.getY(), bBottomLeft.getZ(),
		fBottomLeft.getX(), fBottomLeft.getY(), fBottomLeft.getZ(), 
		fUpLeft.getX(), fUpLeft.getY(), fUpLeft.getZ(),
		fUpLeft.getX(), fUpLeft.getY(), fUpLeft.getZ(),
		bUpLeft.getX(), bUpLeft.getY(), bUpLeft.getZ(),
		bBottomLeft.getX(), bBottomLeft.getY(), bBottomLeft.getZ(),
		//left face
		bBottomRight.getX(), bBottomRight.getY(), bBottomRight.getZ(),
		fBottomRight.getX(), fBottomRight.getY(), fBottomRight.getZ(), 
		fUpRight.getX(), fUpRight.getY(), fUpRight.getZ(), 
		fUpRight.getX(), fUpRight.getY(), fUpRight.getZ(), 
		bUpRight.getX(), bUpRight.getY(), bUpRight.getZ(), 
		bBottomRight.getX(), bBottomRight.getY(), bBottomRight.getZ(), 
		//down face
		fBottomLeft.getX(), fBottomLeft.getY(), fBottomLeft.getZ(), 
		fBottomRight.getX(), fBottomRight.getY(), fBottomRight.getZ(), 
		bBottomRight.getX(), bBottomRight.getY(), bBottomRight.getZ(),
		bBottomRight.getX(), bBottomRight.getY(), bBottomRight.getZ(), 
		bBottomLeft.getX(), bBottomLeft.getY(), bBottomLeft.getZ(),
		fBottomLeft.getX(), fBottomLeft.getY(), fBottomLeft.getZ(),
		//front face
		fBottomLeft.getX(), fBottomLeft.getY(), fBottomLeft.getZ(),
		fBottomRight.getX(), fBottomRight.getY(), fBottomRight.getZ(),
		fUpRight.getX(), fUpRight.getY(), fUpRight.getZ(),
		fUpRight.getX(), fUpRight.getY(), fUpRight.getZ(),
		fUpLeft.getX(), fUpLeft.getY(), fUpLeft.getZ(),
		fBottomLeft.getX(), fBottomLeft.getY(), fBottomLeft.getZ(),
		//back face
		bBottomRight.getX(), bBottomRight.getY(), bBottomRight.getZ(),
		bBottomLeft.getX(), bBottomLeft.getY(), bBottomLeft.getZ(), 
		bUpLeft.getX(), bUpLeft.getY(), bUpLeft.getZ(),
		bUpLeft.getX(), bUpLeft.getY(), bUpLeft.getZ(), 
		bUpRight.getX(), bUpRight.getY(), bUpRight.getZ(), 
		bBottomRight.getX(), bBottomRight.getY(), bBottomRight.getZ(),
		//up face
		fUpLeft.getX(), fUpLeft.getY(), fUpLeft.getZ(),
		fUpRight.getX(), fUpRight.getY(), fUpRight.getZ(), 
		bUpRight.getX(), bUpRight.getY(), bUpRight.getZ(), 
		bUpRight.getX(), bUpRight.getY(), bUpRight.getZ(),
		bUpLeft.getX(), bUpLeft.getY(), bUpLeft.getZ(), 
		fUpLeft.getX(), fUpLeft.getY(), fUpLeft.getZ(), 

		//Contour
		//rightRect
		down3.getX(), down3.getY(), down3.getZ(), 
		down4.getX(), down4.getY(), down4.getZ(),
		up4.getX(), up4.getY(), up4.getZ(),
		down3.getX(), down3.getY(), down3.getZ(),
		up3.getX(), up3.getY(), up3.getZ(), 
		up4.getX(), up4.getY(), up4.getZ(),
		//downRect
		middle3.getX(), middle3.getY(), middle3.getZ(),
		down2.getX(), down2.getY(), down2.getZ(), 
		down3.getX(), down3.getY(), down3.getZ(), 
		down3.getX(), down3.getY(), down3.getZ(), 
		middle4.getX(), middle4.getY(), middle4.getZ(),
		middle3.getX(), middle3.getY(), middle3.getZ(),
		//leftRect
		down1.getX(), down1.getY(), down1.getZ(), 
		up1.getX(), up1.getY(), up1.getZ(),
		up2.getX(), up2.getY(), up2.getZ(),
		down1.getX(), down1.getY(), down1.getZ(),
		down2.getX(), down2.getY(), down2.getZ(),
		up2.getX(), up2.getY(), up2.getZ(),
		//upRect
		middle1.getX(),middle1.getY(),middle1.getZ(), 
		up2.getX(), up2.getY(), up2.getZ(),
		up3.getX(), up3.getY(), up3.getZ(),
		middle1.getX(),middle1.getY(),middle1.getZ(),
		middle2.getX(), middle2.getY(), middle2.getZ(),
		up3.getX(), up3.getY(), up3.getZ()

	};



	glGenVertexArrays(2, &VAO);
	glGenBuffers(2, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
	proj = glm::perspective(glm::radians(122.0f), (float)(800 / 800), 0.1f, 100.0f);

	int modelLoc = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	int viewLoc = glGetUniformLocation(shaderProgram, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	int projLoc = glGetUniformLocation(shaderProgram, "proj");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

}

// dessine les formes en fonction des vertices passés dans myVAO
void rendScene() {
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Vector3D color = { 0.2f, 0.7f, 0.2f };
	int vertexColorLocation = glGetUniformLocation(shaderProgram, "personaliseColor");
	glUniform3f(vertexColorLocation, color.getX(), color.getY(), color.getZ());

	//Dessin du cube et du contour:
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 18);

	color = { 0.2f, 0.4f, 0.2f };
	glUniform3f(vertexColorLocation, color.getX(), color.getY(), color.getZ());

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 18, 18);

	color = { 0.5f, 0.5f, 0.5f };
	glUniform3f(vertexColorLocation, color.getX(), color.getY(), color.getZ());

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 36, 24);

}


int main(void)
{
	//initialisation d'une particule qui sera modifié pour chaque type de projectile
	unsigned iterationsContactResolver = 15;
	//ParticuleContactResolver resolver=ParticuleContactResolver(iterationsContactResolver);
	ParticuleWorld system = ParticuleWorld();
	system.resolver.setIterations(15);
	Vector3D gravity = Vector3D(0, -0.9, 0);
	GravityForceGenerator gravityForce = GravityForceGenerator(gravity);
	//Vector3D addVelocity = { 0.4, 0.5, 0.5 };
	float mass = 10;
	float lSquare = 0.4; //la longueur du carré
	Quaternion orientation = Quaternion(1, 0, 0, 0 );

	//Moment d'inertie d'un cube
	Matrix3 inertiaTensor = Matrix3({ {
		{(2 / 3) * mass * lSquare * lSquare,-(1 / 4) * mass * lSquare * lSquare,-(1 / 4) * mass * lSquare * lSquare},
		{-(1 / 4) * mass * lSquare * lSquare,(2 / 3) * mass * lSquare * lSquare,-(1 / 4) * mass * lSquare * lSquare},
		{-(1 / 4) * mass * lSquare * lSquare,-(1 / 4) * mass * lSquare * lSquare,(2 / 3) * mass * lSquare * lSquare}
	} });

	//creation de notre rigide body
	RigidBody rb = RigidBody(&gravityCenter, orientation, mass, 0.7, 0.7, inertiaTensor);
	Vector3D forcePousse = Vector3D(0.01, 0, 0);
	Vector3D pointForce = { (float)rb.getPosition().getX() - halfMedian, (float)rb.getPosition().getY() + halfMedian, (float)rb.getPosition().getZ() - halfMedian };
	Matrix4 offset = Matrix4();
	RigidBodyManager rbManager = RigidBodyManager();
	CollisionSphere spherePrimitive = CollisionSphere(rb, offset, 0.5);
	//Application d'une force au point superieure gauche de notre figure
	rb.addForceAtBodyPoint(forcePousse, pointForce);
	rbManager.addToRigidBodies(rb);
	rbManager.addToRegistre(spherePrimitive, gravityForce);
	//rb.setVelocity({ 10,0,0 });


	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "Moteur Jeu", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "fenetre non créée" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, 800, 800);

	initShadrProgramm();

	initGeometries(rb);
	glfwSwapBuffers(window);

	glClearColor(0.07f, 0.13f, 0.17f, 0.1f);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	double currentFrame = glfwGetTime();
	double lastFrame = currentFrame;
	double deltaTime;
	while (!glfwWindowShouldClose(window))
	{

		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		processInput(window);

		//Mise à jour de toute la physique
		rbManager.runPhysic(deltaTime);
		rb.clearAccumulator();
		initGeometries(rb);

		rendScene();

		glfwSwapBuffers(window);


		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;


}