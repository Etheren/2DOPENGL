#include "stdafx.h"
#include <glew\glew.h>
#include <freeglut\freeglut.h>
#include <CoreStructures\CoreStructures.h>
#include "texture_loader.h"
#include "shader_setup.h"


using namespace std;
using namespace CoreStructures;

static bool codeTest = false;

GLuint locT;
GLuint locT2;

GLuint shaderProgram;
GLuint shaderProgramNoTex;
GLuint sunTransformation;

float theta = 0.0f;

// Textures
GLuint gravelTex = 0;
GLuint roofTex = 1;
GLuint skyTex = 2;
GLuint groundTex = 3;
GLuint doorTex = 4;
GLuint windowTex = 5;
GLuint buildingTex = 6;
GLuint bugTex = 7;
GLuint bushTex = 8;

float x = 0.6, y = 0.6;
float bugX = 0.0f, bugY = 0.0f, bugAngle =-90.0f;
float sunAngle = 0;
bool keyUpPressed = false;
bool keyDownPressed = false;
bool keyLeftPressed = false;
bool keyRightPressed = false;


//Ground Arrays, Ground, Sky House, Window, Window Panes, Path,
static GLfloat groundVertices[] = {
	-1.0f, -1.0f,
	1.0f, -1.0f,
	1.0f, -0.4f,
	-1.0f, -0.4f,

};
static GLubyte groundColors[] = {
	0,153,0, 255,
	0,153,0, 255,
	0,102,0, 255,
	0,102,0, 255
};
static float groundTexVertices[] = {
	-3.0f, -1.5f,
	-3.0f, 1.5f,
	3.0f, 1.5f,
	3.0f, -1.5f
};
static GLubyte groundVertIndices[] = { 0, 1, 2, 3 };

GLuint groundVerticesVBO, groundColorVBO, groundTexVerticesVBO, groundVertIndicesVBO;

//Sky Arrays
static GLfloat skyVertices[] = {
	1.0f,  1.0f,
	-1.0f,  1.0f,
	-1.0f, -0.4f,
	1.0f, -0.4f,
};
static GLubyte skyColors[] = {
	102,255,255,
	102,255,255,
	51,255,255,
	51,255,255,
};
static GLfloat skyTexVertices[] = {
	1.0f, 0.0f,
	0.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 1.0f
};
static GLubyte skyVertIndices[] = { 0, 1, 2, 3 };
GLuint skyVerticesVBO, skyColorVBO, skyTexVerticesVBO, skyVertIndicesVBO;


// House Arrays
static GLfloat houseVertices[] = {
	-0.8f, -0.8f,
	0.1f, -0.8f,
	0.1f, 0.4f,
	-0.8f, 0.4f,
};
static GLubyte houseColors[] = {
	51, 25, 0, 255,
	51, 25, 0, 255,
	51, 25, 0, 255,
	51, 25, 0, 255
};
static GLfloat houseTexVertices[] = {
	-2.0f, -3.0f,
	2.0f, -3.0f,
	2.0f, 3.0f,
	-2.0f, 3.0f
};
static GLubyte houseVertIndices[] = { 0, 1, 2, 3 };

GLuint houseVerticesVBO, houseColorVBO, houseTexVerticesVBO, houseVertIndicesVBO;

static GLfloat roofVertices[] = {
	-0.35f, 0.7f,
	0.2f, 0.4f,
	-0.9f, 0.4f
};
static GLubyte roofColors[] = {
	255,0,0, 255,
	255,0,0, 255,
	255,0,0, 255
};
static GLfloat roofTexVertices[] = {
	0.5f, 1.0f,
	1.0f, 0.0f,
	0.0f, 0.0f,
};
static GLubyte roofVertIndices[] = { 0, 1, 2 };
GLuint roofVerticesVBO, roofColorVBO, roofTexVerticesVBO, roofVertIndicesVBO;

// Windows are 3 "units" wide and 4 "units" tall
static GLfloat windowOneVertices[] = {
	-0.7f, -0.6f,
	-0.4f, -0.6f,
	-0.4f, -0.2f,
	-0.7f, -0.2f,
};
static GLfloat windowTwoVertices[] = {
	-0.7f, -0.05f,
	-0.4f, -0.05f,
	-0.4f, 0.35f,
	-0.7f, 0.35f,
};
static GLfloat windowThreeVertices[] = {
	-0.3f, -0.05f,
	-0.0f, -0.05f,
	-0.0f, 0.35f,
	-0.3f, 0.35f,
};
static GLubyte windowColors[] = {
	64,64,64, 255,
	64,64,64, 255, 
	64,64,64,255,
	64,64,64,255
};

static GLfloat windowTexVertices[] = {
	1.0f,1.0f,
	0.0f,1.0f,
	0.0f,0.0f,
	1.0f,0.0f,
};
static GLubyte windowVertIndices[] = { 0, 1, 2, 3 };
GLuint windowOneVerticesVBO, windowTwoVerticesVBO, windowThreeVerticesVBO, windowColorVBO, windowTexVerticesVBO, windowVertIndicesVBO;

static GLfloat doorVertices[] = {
	-0.3f, -0.2f,
	-0.0f, -0.2f,
	-0.0f, -0.8f,
	-0.3f, -0.8f,
};

static GLubyte doorColors[] = {
	255, 225, 255, 255,
	255, 225, 255, 255,
	255, 225, 255, 255,
	255, 225, 255, 255
};
static GLfloat doorTexVertices[] = {
	0.0f, 0.0f,
	1.0f,0.0f,
	1.0f,1.0f,
	0.0f,1.0f,
};
static GLubyte doorVertIndices[] = { 0, 1, 2, 3 };
GLuint doorVerticesVBO, doorColorVBO, doorTexVerticesVBO, doorVertIndicesVBO;

static GLfloat pathVertices[] = {
	-0.3f, -1.0f,
	-0.0f, -1.0f,
	-0.0f, -0.8f,
	-0.3f, -0.8f
};
static GLubyte pathColors[] = {
	255, 178, 102, 255,
	255, 178, 102, 255,
	255, 178, 102, 255,
	255, 178, 102, 255
};
static GLfloat pathTexVertices[] = {
	-1.0f, -1.0f,
	1.0f, -1.0f,
	1.0f, 1.0f,
	-1.0f, 1.0f
};
static GLubyte pathVertIndices[] = { 0, 1, 2, 3 };
GLuint pathVerticesVBO, pathColorVBO, pathTexVerticesVBO, pathVertIndicesVBO;

static GLfloat bushVertices[] = {
	0.4f, -0.5f,
	0.7f, -0.5f,
	0.7f, 0.1f,
	0.4f, 0.1f
};
static GLubyte bushColors[] = {
	102, 255, 102, 255,
	102, 255, 102, 255,
	102, 255, 102, 255,
	102, 255, 102, 255
};
static GLfloat bushTexVertices[] = {
	1.0f, 1.0f,
	0.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 0.0f,
	
	
};
static GLubyte bushVertIndices[] = { 0, 1, 2, 3 };
GLuint bushVerticesVBO, bushColorVBO, bushTexVerticesVBO, bushVertIndicesVBO;

// Function Prototypes

void init(int argc, char* argv[]);
void report_version(void);
void display(void);
void drawBug(GLuint);
void setupBackgroundVBO(void);
void setupHouseVBO(void);
void drawBackgroundVBO(void);
void drawHouseVBO(void);
void drawSun(int);
void drawSunRotating(void);
void update(void);
void keyDown(unsigned char key, int x, int y);
void specialKeyDown(int key, int x, int y);
void specialKeyUp(int key, int x, int y);

int _tmain(int argc, char* argv[]) {

	init(argc, argv);

	glutMainLoop();

	// Shut down COM
	shutdownCOM();

	return 0;
}

void init(int argc, char* argv[]) {

	// Initialise COM so we can use Windows Imaging Component
	initCOM();

	// Initialise FreeGLUT
	glutInit(&argc, argv);

	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

	glutInitWindowSize(800, 800);
	glutInitWindowPosition(64, 64);
	glutCreateWindow("2d Scene Work");

	// Register callback functions
	glutDisplayFunc(display);
	glutIdleFunc(update);
	glutKeyboardFunc(keyDown);
	glutSpecialFunc(specialKeyDown);
	glutSpecialUpFunc(specialKeyUp);

	// Initialise GLEW library
	GLenum err = glewInit();

	// Ensure GLEW was initialised successfully before proceeding
	if (err == GLEW_OK) {

		cout << "GLEW initialised okay\n";

	}
	else {

		cout << "GLEW could not be initialised\n";
		throw;
	}

	// Example query OpenGL state (get version number)
	report_version();


	// Initialise OpenGL...

	// Setup colour to clear the window
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Set viewplane size
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0f, 1.0f, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);

	glLineWidth(4.0f);

	// Load textures
	gravelTex = fiLoadTexture("..\\Common\\Resources\\Textures\\gravel.jpg");
	buildingTex = fiLoadTexture("..\\Common\\Resources\\Textures\\bricks.jpg");
	windowTex = fiLoadTexture("..\\Common\\Resources\\Textures\\window.jpg");
	skyTex = fiLoadTexture("..\\Common\\Resources\\Textures\\sky2.jpg");
	groundTex = fiLoadTexture("..\\Common\\Resources\\Textures\\grass.jpg");
	doorTex = fiLoadTexture("..\\Common\\Resources\\Textures\\door.jpg");
	roofTex = fiLoadTexture("..\\Common\\Resources\\Textures\\roof.jpg");
	bugTex = fiLoadTexture("..\\Common\\Resources\\Textures\\bug.png");
	bushTex = fiLoadTexture("..\\Common\\Resources\\Textures\\bush.png");

	//load dem shaders
	shaderProgram = setupShaders(string("Shaders\\basic_vertex_shader.txt"), string("Shaders\\basic_fragment_shader.txt"));
	shaderProgramNoTex = setupShaders(string("Shaders\\notexture_vertex_shader.txt"), string("Shaders\\notexture_fragment_shader.txt"));

	locT = glGetUniformLocation(shaderProgram, "T");
	locT2 = glGetUniformLocation(shaderProgramNoTex, "T2");

	sunTransformation = glGetUniformLocation(shaderProgramNoTex, "sunTransform");

	setupBackgroundVBO();
	setupHouseVBO();
}

void report_version(void) {

	int majorVersion, minorVersion;

	glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
	glGetIntegerv(GL_MINOR_VERSION, &minorVersion);

	cout << "OpenGL version " << majorVersion << "." << minorVersion << "\n\n";
}

void setupBackgroundVBO(void){
	glGenBuffers(1, &groundVerticesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, groundVerticesVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(groundVertices), groundVertices, GL_STATIC_DRAW);

	glGenBuffers(1, &groundColorVBO);
	glBindBuffer(GL_ARRAY_BUFFER, groundColorVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(groundColors), groundColors, GL_STATIC_DRAW);

	glGenBuffers(1, &groundTexVerticesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, groundTexVerticesVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(groundTexVertices), groundTexVertices, GL_STATIC_DRAW);

	glGenBuffers(1, &groundVertIndicesVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, groundVertIndicesVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(groundVertIndices), groundVertIndices, GL_STATIC_DRAW);

	glGenBuffers(1, &skyVerticesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, skyVerticesVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyVertices), skyVertices, GL_STATIC_DRAW);

	glGenBuffers(1, &skyColorVBO);
	glBindBuffer(GL_ARRAY_BUFFER, skyColorVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyColors), skyColors, GL_STATIC_DRAW);

	glGenBuffers(1, &skyTexVerticesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, skyTexVerticesVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyTexVertices), skyTexVertices, GL_STATIC_DRAW);

	glGenBuffers(1, &skyVertIndicesVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyVertIndicesVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyVertIndices), skyVertIndices, GL_STATIC_DRAW);

	glGenBuffers(1, &pathVerticesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, pathVerticesVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pathVertices), pathVertices, GL_STATIC_DRAW);

	glGenBuffers(1, &pathColorVBO);
	glBindBuffer(GL_ARRAY_BUFFER, pathColorVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pathColors), pathColors, GL_STATIC_DRAW);

	glGenBuffers(1, &pathTexVerticesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, pathTexVerticesVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pathTexVertices), pathTexVertices, GL_STATIC_DRAW);

	glGenBuffers(1, &pathVertIndicesVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pathVertIndicesVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(pathVertIndices), pathVertIndices, GL_STATIC_DRAW);

	glGenBuffers(1, &bushVerticesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, bushVerticesVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bushVertices), bushVertices, GL_STATIC_DRAW);

	glGenBuffers(1, &bushColorVBO);
	glBindBuffer(GL_ARRAY_BUFFER, bushColorVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bushColors), bushColors, GL_STATIC_DRAW);

	glGenBuffers(1, &bushTexVerticesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, bushTexVerticesVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bushTexVertices), bushTexVertices, GL_STATIC_DRAW);

	glGenBuffers(1, &bushVertIndicesVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bushVertIndicesVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(bushVertIndices), bushVertIndices, GL_STATIC_DRAW);
}

void setupHouseVBO(void){
	glGenBuffers(1, &houseVerticesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, houseVerticesVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(houseVertices), houseVertices, GL_STATIC_DRAW);

	glGenBuffers(1, &houseColorVBO);
	glBindBuffer(GL_ARRAY_BUFFER, houseColorVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(houseColors), houseColors, GL_STATIC_DRAW);

	glGenBuffers(1, &houseTexVerticesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, houseTexVerticesVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(houseTexVertices), houseTexVertices, GL_STATIC_DRAW);

	glGenBuffers(1, &houseVertIndicesVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, houseVertIndicesVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(houseVertIndices), houseVertIndices, GL_STATIC_DRAW);

	glGenBuffers(1, &roofVerticesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, roofVerticesVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(roofVertices), roofVertices, GL_STATIC_DRAW);

	glGenBuffers(1, &roofColorVBO);
	glBindBuffer(GL_ARRAY_BUFFER, roofColorVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(roofColors), roofColors, GL_STATIC_DRAW);

	glGenBuffers(1, &roofTexVerticesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, roofTexVerticesVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(roofTexVertices), roofTexVertices, GL_STATIC_DRAW);

	glGenBuffers(1, &roofVertIndicesVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, roofVertIndicesVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(roofVertIndices), roofVertIndices, GL_STATIC_DRAW);

	glGenBuffers(1, &windowOneVerticesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, windowOneVerticesVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(windowOneVertices), windowOneVertices, GL_STATIC_DRAW);

	glGenBuffers(1, &windowTwoVerticesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, windowTwoVerticesVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(windowTwoVertices), windowTwoVertices, GL_STATIC_DRAW);

	glGenBuffers(1, &windowThreeVerticesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, windowThreeVerticesVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(windowThreeVertices), windowThreeVertices, GL_STATIC_DRAW);

	glGenBuffers(1, &windowColorVBO);
	glBindBuffer(GL_ARRAY_BUFFER, windowColorVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(windowColors), windowColors, GL_STATIC_DRAW);

	glGenBuffers(1, &windowTexVerticesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, windowTexVerticesVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(windowTexVertices), windowTexVertices, GL_STATIC_DRAW);

	glGenBuffers(1, &windowVertIndicesVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, windowVertIndicesVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(windowVertIndices), windowVertIndices, GL_STATIC_DRAW);

	glGenBuffers(1, &doorVerticesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, doorVerticesVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(doorVertices), doorVertices, GL_STATIC_DRAW);

	glGenBuffers(1, &doorColorVBO);
	glBindBuffer(GL_ARRAY_BUFFER, doorColorVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(doorColors), doorColors, GL_STATIC_DRAW);

	glGenBuffers(1, &doorTexVerticesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, doorTexVerticesVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(doorTexVertices), doorTexVertices, GL_STATIC_DRAW);

	glGenBuffers(1, &doorVertIndicesVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, doorVertIndicesVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(doorVertIndices), doorVertIndices, GL_STATIC_DRAW);
}

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	drawBackgroundVBO();
	glLoadIdentity();
	drawHouseVBO();
	glLoadIdentity();
	drawSunRotating();
	
	glLoadIdentity();
	glTranslatef(bugX, bugY, 0.0f);
	glRotatef(bugAngle, 0.0f, 0.0f, 1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	drawBug(bugTex);
	glDisable(GL_BLEND);

	glutSwapBuffers();
}

void drawSun(int numOfVertices)
{
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0.0f, 0.0f);
	glColor3f(255, 255, 0);
	float radius = 0.25f;
	float theta = 0.0f;
	float thetaDelta = (gu_pi * 8.0f) / float(numOfVertices);
	for (unsigned int i = 0; i <= numOfVertices; i++, theta += thetaDelta)
	{
		float x = cosf(theta) * radius;
		float y = sinf(theta) * radius;

		glVertex2f(x, y);
	}
	glEnd();
}


void drawSunRotating()
{
	glUseProgram(shaderProgramNoTex);
	GUMatrix4 R = GUMatrix4::translationMatrix(x, y, 0.0f) * GUMatrix4::rotationMatrix(0.0f, 0.0f, sunAngle);
	glUniformMatrix4fv(locT2, 1, GL_FALSE, (GLfloat*)&R);
	drawSun(30);
	glUseProgram(0);
}

void drawBug(GLuint bugTexture)
{
	glBindTexture(GL_TEXTURE_2D, bugTexture);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);

	glVertex2f(0.1f, 0.1f);
	glTexCoord2d(0.0f, 0.0f);

	glVertex2f(0.2f, 0.1f);
	glTexCoord2d(1.0f, 0.0f);

	glVertex2f(0.2f, 0.2f);
	glTexCoord2d(1.0f, 1.0f);

	glVertex2f(0.1f, 0.2f);
	glTexCoord2d(0.0f, 1.0f);

	glEnd();
}

void update(void)
{
	sunAngle = sunAngle + 0.01;
	if (keyUpPressed == true)
	{
		bugY += 0.001;
	}
	if (keyDownPressed == true)
	{
		bugY -= 0.001;
	}
	if (keyRightPressed == true)
	{
		bugX += 0.001;
	}
	if (keyLeftPressed == true)
	{
		bugX -= 0.001;
	}
	
	theta += 0.005f;
	
	
	glutPostRedisplay();
}

void drawBackgroundVBO(void){
	glUseProgram(shaderProgram);

	GUMatrix4 T = GUMatrix4::translationMatrix(0.0f, 0.0f, 0.0f);
	glUniformMatrix4fv(locT, 1, GL_FALSE, (GLfloat*)&T);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, groundTex);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture"), 0);
	glEnable(GL_TEXTURE_2D);

	glBindBuffer(GL_ARRAY_BUFFER, groundVerticesVBO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, groundColorVBO);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, groundTexVerticesVBO);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, groundVertIndicesVBO);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, (GLvoid*)0);

	
	glBindTexture(GL_TEXTURE_2D, skyTex);
	glBindBuffer(GL_ARRAY_BUFFER, skyVerticesVBO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, skyColorVBO);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(4);

	glBindBuffer(GL_ARRAY_BUFFER, skyTexVerticesVBO);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(5);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyVertIndicesVBO);

	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, (GLvoid*)0);


	glBindTexture(GL_TEXTURE_2D, gravelTex);

	glBindBuffer(GL_ARRAY_BUFFER, pathVerticesVBO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(6);

	glBindBuffer(GL_ARRAY_BUFFER, pathColorVBO);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(7);

	glBindBuffer(GL_ARRAY_BUFFER, pathTexVerticesVBO);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(8);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pathVertIndicesVBO);

	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, (GLvoid*)0);

	glBindTexture(GL_TEXTURE_2D, bushTex);

	glBindBuffer(GL_ARRAY_BUFFER, bushVerticesVBO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(9);

	glBindBuffer(GL_ARRAY_BUFFER, bushColorVBO);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(10);

	glBindBuffer(GL_ARRAY_BUFFER, bushTexVerticesVBO);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(11);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bushVertIndicesVBO);

	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, (GLvoid*)0);

	glDisable(GL_TEXTURE_2D);
}

void drawHouseVBO(void){

	glUseProgram(shaderProgram);

	GUMatrix4 T = GUMatrix4::translationMatrix(0.0f, 0.0f, 0.0f);
	glUniformMatrix4fv(locT, 1, GL_FALSE, (GLfloat*)&T);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, buildingTex);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture"), 0);
	glEnable(GL_TEXTURE_2D);

	glBindBuffer(GL_ARRAY_BUFFER, houseVerticesVBO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, houseColorVBO);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, houseTexVerticesVBO);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, houseVertIndicesVBO);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, (GLvoid*)0);

	glBindTexture(GL_TEXTURE_2D, roofTex);

	glBindBuffer(GL_ARRAY_BUFFER, roofVerticesVBO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, roofColorVBO);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(4);

	glBindBuffer(GL_ARRAY_BUFFER, roofTexVerticesVBO);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(5);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, roofVertIndicesVBO);
	glDrawElements(GL_POLYGON, 3, GL_UNSIGNED_BYTE, (GLvoid*)0);

	glBindTexture(GL_TEXTURE_2D, windowTex);

	glBindBuffer(GL_ARRAY_BUFFER, windowOneVerticesVBO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, windowColorVBO);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(4);

	glBindBuffer(GL_ARRAY_BUFFER, windowTexVerticesVBO);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(5);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, windowVertIndicesVBO);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, (GLvoid*)0);

	glBindBuffer(GL_ARRAY_BUFFER, windowTwoVerticesVBO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(6);

	glBindBuffer(GL_ARRAY_BUFFER, windowColorVBO);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(7);

	glBindBuffer(GL_ARRAY_BUFFER, windowTexVerticesVBO);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(8);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, windowVertIndicesVBO);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, (GLvoid*)0);

	glBindBuffer(GL_ARRAY_BUFFER, windowThreeVerticesVBO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(9);

	glBindBuffer(GL_ARRAY_BUFFER, windowColorVBO);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(10);

	glBindBuffer(GL_ARRAY_BUFFER, windowTexVerticesVBO);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(11);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, windowVertIndicesVBO);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, (GLvoid*)0);

	glBindTexture(GL_TEXTURE_2D, doorTex);

	glBindBuffer(GL_ARRAY_BUFFER, doorVerticesVBO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(12);

	glBindBuffer(GL_ARRAY_BUFFER, doorColorVBO);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(13);

	glBindBuffer(GL_ARRAY_BUFFER, doorTexVerticesVBO);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(14);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, doorVertIndicesVBO);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, (GLvoid*)0);

	glDisable(GL_TEXTURE_2D);
}

void keyDown(unsigned char key, int x, int y)
{
	if (key == 'r')
	{
		theta = 0.0f;
		glutPostRedisplay();

	}
}

void specialKeyDown(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_LEFT:
		keyLeftPressed = true;
		break;

	case GLUT_KEY_RIGHT:
		keyRightPressed = true;
		break;

	case GLUT_KEY_UP:
		keyUpPressed = true;
		break;

	case GLUT_KEY_DOWN:
		keyDownPressed = true;
		break;
	}
}

void specialKeyUp(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_LEFT:
		keyLeftPressed = false;
		break;

	case GLUT_KEY_RIGHT:
		keyRightPressed = false;
		break;

	case GLUT_KEY_UP:
		keyUpPressed = false;
		break;

	case GLUT_KEY_DOWN:
		keyDownPressed = false;
		break;
	}

}