#include "stdafx.h"
#include <glew\glew.h>
#include <freeglut\freeglut.h>
#include <CoreStructures\CoreStructures.h>
#include "texture_loader.h"
#include "shader_setup.h"


using namespace std;
using namespace CoreStructures;

GLuint locT;
GLuint locT2;

GLuint shaderProgram;
GLuint shaderProgramNoTex;

// Textures
GLuint gravelTex = 0;
GLuint roofTex = 1;
GLuint skyTex = 2;
GLuint groundTex = 3;
GLuint doorTex = 4;
GLuint windowTex = 5;
GLuint buildingTex = 6;

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
	0.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, 0.0f
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
static GLubyte skyColours[] = {
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
GLuint skyVerticesVBO, skyColorVBO, skyTexVerticesVBO;


// House Arrays
static GLfloat houseVertices[] = {
	-0.8f, -0.8f,
	0.1f, -0.8f,
	0.1f, 0.4f,
	-0.8f, 0.4f,
};
static GLubyte houseColours[] = {
	51, 25, 0,
	51, 25, 0,
	51, 25, 0,
	51, 25, 0,
};
static GLfloat houseTextureVertices[] = {
	-2.0f, -3.0f,
	2.0f, -3.0f,
	2.0f, 3.0f,
	-2.0f, 3.0f
};
GLuint houseVerticesVBO, houseColorVBO, houseTexVerticesVBO;

static GLfloat roofVertices[] = {
	-0.35f, 0.7f,
	0.2f, 0.4f,
	-0.9f, 0.4f
};
static GLubyte roofColors[] = {
	255,0,0,
	255,0,0,
	255,0,0,
};
static GLfloat roofTexVertices[] = {
	0.5f, 1.0f,
	1.0f, 0.0f,
	0.0f, 0.0f,
};
GLuint roofVerticesVBO, roofColorVBO, roofTexVerticesVBO;

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
	64,64,64,
	64,64,64,
	64,64,64,
	64,64,64,
};

static GLfloat windowTexVertices[] = {
	1.0f, 0.0f,
	0.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 1.0f
};
GLuint windowOneVerticesVBO, windowTwoVerticesVBO, windowThreeVerticesVBO, windowColorVBO, windowTexVerticesVBO;

static GLfloat doorVertices[] = {
	-0.3f, -0.2f,
	-0.0f, -0.2f,
	-0.0f, -0.8f,
	-0.3f, -0.8f,
};

static GLubyte doorColors[] = {
	255, 225, 255,
	255, 225, 255,
	255, 225, 255,
	255, 225, 255
};
static GLfloat doorTexVertices[] = {
	0.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, 0.0f,
	0.0f, 0.0f
};
GLuint doorVerticesVBO, doorColorVBO, doorTexVerticesVBO;

static GLfloat pathVertices[] = {
	-0.3f, -1.0f,
	-0.0f, -1.0f,
	-0.0f, -0.8f,
	-0.3f, -0.8f
};
static GLubyte pathColors[] = {
	255, 178, 102,
	255, 178, 102,
	255, 178, 102,
	255, 178, 102,
};
static GLfloat pathTexture[] = {
	-1.0f, -1.0f,
	1.0f, -1.0f,
	1.0f, 1.0f,
	-1.0f, 1.0f
};

GLuint pathVerticesVBO, pathColorVBO, pathTexVerticesVBO;
static GLfloat treeTrunkVertices[] = {
	0.4f, -0.6f,
	0.6f, -0.6f,
	0.6f, 0.0f,
	0.4f, 0.0f,
};

static GLubyte treeTrunkColors[] = {
	51, 25, 0,
	51, 25, 0,
	51, 25, 0,
	51, 25, 0,

};

// Function Prototypes

void init(int argc, char* argv[]);
void report_version(void);
void display(void);
void drawGround(void);
void drawSky(void);
void drawHouse(void);
void drawTree(void);
void setupBackgroundVBO(void);
void setupHouseVBO(void);
void drawBackgroundVBO(void);
void drawHouseVBO(void);

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

	//load dem shaders
	shaderProgram = setupShaders(string("Shaders\\basic_vertex_shader.txt"), string("Shaders\\basic_fragment_shader.txt"));
	shaderProgramNoTex = setupShaders(string("Shaders\\notexture_vertex_shader.txt"), string("Shaders\\notexture_fragment_shader.txt"));

	locT = glGetUniformLocation(shaderProgram, "T");
	locT2 = glGetUniformLocation(shaderProgramNoTex, "T2");

	// Enable Vertex Arrays

	// Tell OpenGL to expect vertex position information from an array
	//glEnableClientState(GL_VERTEX_ARRAY);

	// Tell OpenGL to expect vertex colour information from an array
	//glEnableClientState(GL_COLOR_ARRAY);

	// Tell OpenGL to expect texture coordinate information from an array. Remove comments if needed.
	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	setupBackgroundVBO();
	//setupHouseVBO();
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

}

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//drawGround();
	//drawSky();
	//drawHouse();
	drawBackgroundVBO();

	glutSwapBuffers();
}

void drawGround(void) {
	glEnable(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D, groundTex);
	glVertexPointer(2, GL_FLOAT, 0, groundVertices);
	glColorPointer(3, GL_UNSIGNED_BYTE, 0, groundColors);
	glTexCoordPointer(2, GL_FLOAT, 0, groundTexVertices);
	glDrawArrays(GL_QUADS, 0, 4);

	glBindTexture(GL_TEXTURE_2D, gravelTex);
	glVertexPointer(2, GL_FLOAT, 0, pathVertices);
	glColorPointer(3, GL_UNSIGNED_BYTE, 0, pathColors);
	glTexCoordPointer(2, GL_FLOAT, 0, pathTexture);
	glDrawArrays(GL_QUADS, 0, 4);

	glDisable(GL_TEXTURE_2D);
}
void drawSky(void){

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, skyTex);
	glVertexPointer(2, GL_FLOAT, 0, skyVertices);
	glColorPointer(3, GL_UNSIGNED_BYTE, 0, skyColours);
	glTexCoordPointer(2, GL_FLOAT, 0, skyTexVertices);
	glDrawArrays(GL_QUADS, 0, 4);
	
	glDisable(GL_TEXTURE_2D);
}
void drawHouse(void){
	
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, buildingTex);
	glVertexPointer(2, GL_FLOAT, 0, houseVertices);
	glColorPointer(3, GL_UNSIGNED_BYTE, 0, houseColours);
	glTexCoordPointer(2, GL_FLOAT, 0, houseTextureVertices);
	glDrawArrays(GL_QUADS, 0, 4);

	glBindTexture(GL_TEXTURE_2D, roofTex);
	glVertexPointer(2, GL_FLOAT, 0, roofVertices);
	glColorPointer(3, GL_UNSIGNED_BYTE, 0, roofColors);
	glTexCoordPointer(2, GL_FLOAT, 0, roofTexVertices);
	glDrawArrays(GL_POLYGON, 0, 4);

	glBindTexture(GL_TEXTURE_2D, windowTex);
	glVertexPointer(2, GL_FLOAT, 0, windowOneVertices);
	glColorPointer(3, GL_UNSIGNED_BYTE, 0, windowColors);
	glTexCoordPointer(2, GL_FLOAT, 0, windowTexVertices);
	glDrawArrays(GL_POLYGON, 0, 4);
	
	glBindTexture(GL_TEXTURE_2D, windowTex);
	glVertexPointer(2, GL_FLOAT, 0, windowTwoVertices);
	glColorPointer(3, GL_UNSIGNED_BYTE, 0, windowColors);
	glTexCoordPointer(2, GL_FLOAT, 0, windowTexVertices);
	glDrawArrays(GL_POLYGON, 0, 4);

	glBindTexture(GL_TEXTURE_2D, windowTex);
	glVertexPointer(2, GL_FLOAT, 0, windowThreeVertices);
	glColorPointer(3, GL_UNSIGNED_BYTE, 0, windowColors);
	glTexCoordPointer(2, GL_FLOAT, 0, windowTexVertices);
	glDrawArrays(GL_POLYGON, 0, 4);

	glBindTexture(GL_TEXTURE_2D, doorTex);
	glVertexPointer(2, GL_FLOAT, 0, doorVertices);
	glColorPointer(3, GL_UNSIGNED_BYTE, 0, doorColors);
	glDrawArrays(GL_POLYGON, 0, 4);
	
	glDisable(GL_TEXTURE_2D);
}


void drawTree(void)
{
	//glVertexPointer(2, GL_FLOAT, 0, treeTrunkVertices);
	//glColorPointer(3, GL_UNSIGNED_BYTE, 0, treeTrunkColors);
	//glDrawArrays(GL_QUADS, 0, 4);
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

	glDisable(GL_TEXTURE_2D);


}