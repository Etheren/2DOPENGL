#include "stdafx.h"
#include <glew\glew.h>
#include <freeglut\freeglut.h>
#include <CoreStructures\CoreStructures.h>
#include "texture_loader.h"


using namespace std;
using namespace CoreStructures;


// Textures
GLuint myTexture = 0;

//Ground Arrays
static GLfloat groundVertices[] = {
	-1.0f, -1.0f,
	1.0f, -1.0f,
	1.0f, -0.4f,
	-1.0f, -0.4f,
};
static GLubyte groundColors[] = {
	0,153,0,
	0,153,0,
	0,102,0,
	0,102,0,
};
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

static GLfloat houseVertices[] = {
	-0.8f, -0.8f,
	0.1f, -0.8f,
	0.1f, 0.4f,
	-0.35f, 0.7f,
	-0.8f, 0.4f,

};

static GLubyte houseColours[] = {
	51, 25, 0,
	51, 25, 0,
	51, 25, 0,
	153, 0, 0,
	51, 25, 0,
};

static GLfloat windowOneVertices[] = {
	-0.7f, -0.6f,
	-0.4f, -0.6f,
	-0.4f, -0.2f,
	-0.7f, -0.2f,
	// Windows are 3 "units" wide and 4 "units" tall
};
//Add more window vertices here
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



// Function Prototypes

void init(int argc, char* argv[]);
void report_version(void);
void display(void);
void drawGround(void);
void drawSky(void);
void drawHouse(void);




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

	// Load demo texture...
	myTexture = fiLoadTexture("..\\Common\\Resources\\Textures\\bumblebee.png");


	// Enable Vertex Arrays

	// Tell OpenGL to expect vertex position information from an array
	glEnableClientState(GL_VERTEX_ARRAY);

	// Tell OpenGL to expect vertex colour information from an array
	glEnableClientState(GL_COLOR_ARRAY);

	// Tell OpenGL to expect texture coordinate information from an array. Remove comments if needed.
	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}


void report_version(void) {

	int majorVersion, minorVersion;

	glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
	glGetIntegerv(GL_MINOR_VERSION, &minorVersion);

	cout << "OpenGL version " << majorVersion << "." << minorVersion << "\n\n";
}



void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawGround();
	drawSky();
	drawHouse();

	glutSwapBuffers();
}



void drawGround(void) {

	glVertexPointer(2, GL_FLOAT, 0, groundVertices);
	glColorPointer(3, GL_UNSIGNED_BYTE, 0, groundColors);
	//glTexCoordPointer(2, GL_FLOAT, 0, starTextureCoords);

	glDrawArrays(GL_QUADS, 0, 4);
}
void drawSky(void){

	glVertexPointer(2, GL_FLOAT, 0, skyVertices);
	glColorPointer(3, GL_UNSIGNED_BYTE, 0, skyColours);

	glDrawArrays(GL_QUADS, 0, 4);
}
void drawHouse(void){
	glVertexPointer(2, GL_FLOAT, 0, houseVertices);
	glColorPointer(3, GL_UNSIGNED_BYTE, 0, houseColours);
	glDrawArrays(GL_POLYGON, 0, 5);

	glVertexPointer(2, GL_FLOAT, 0, windowOneVertices);
	glColorPointer(3, GL_UNSIGNED_BYTE, 0, windowColors);
	glDrawArrays(GL_POLYGON, 0, 4);
	
	glVertexPointer(2, GL_FLOAT, 0, windowTwoVertices);
	glColorPointer(3, GL_UNSIGNED_BYTE, 0, windowColors);
	glDrawArrays(GL_POLYGON, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, windowThreeVertices);
	glColorPointer(3, GL_UNSIGNED_BYTE, 0, windowColors);
	glDrawArrays(GL_POLYGON, 0, 4);

}
