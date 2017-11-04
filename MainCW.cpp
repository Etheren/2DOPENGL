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
	myTexture = fiLoadTexture("..\\..\\Common\\Resources\\Textures\\bumblebee.png");


	// Enable Vertex Arrays

	// Tell OpenGL to expect vertex position information from an array
	glEnableClientState(GL_VERTEX_ARRAY);

	// Tell OpenGL to expect vertex colour information from an array
	glEnableClientState(GL_COLOR_ARRAY);

	// Tell OpenGL to expect texture coordinate information from an array
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
