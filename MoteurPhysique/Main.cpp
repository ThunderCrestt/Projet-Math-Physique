#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
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

unsigned int myVBO[NumObjects];  
unsigned int myVAO[NumObjects];

// réajuste viewport
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

	//Première figure : triangles
	float trianglesVerts[] = {		//color
		-0.8f, -0.2f, 0.0f,		1.0f, 0.8f, 0.8f,		//premier triangle (forme la moitié du canon)
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


// dessine les formes en fonction des vertices passés dans myVAO
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



int main()
{
	// initialisation de la fenêtre d'openGL
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

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//parametrages des shaders (à mettre dans une fonction plus tard)
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

	//affichage de la fenêtre

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