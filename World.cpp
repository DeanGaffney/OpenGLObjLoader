#include "windows.h"
#include "gl/gl.h"
#include "gl/glu.h"
#include "gl/freeglut.h"
#include "color.h"
#include <fstream>
#include "vector3.h"
#include "world.h"
#include <algorithm>
#define _USE_MATH_DEFINES
#include "math.h"

using namespace std;

World* World::s_World = NULL;
static float xRot = 0.0f;
static float yRot = 0.0f;

static float worldRotX = 0.0f;
static float worldRotY = 0.0f;
static float worldZoom = 0.0f;

void timerFunc(int value);
void specialKeys(int key, int x, int y);
void splitScreen();
float clampf(float n, float lower, float upper);

void splitScreen() {
	glColor3f(255, 0, 0);
	glLineWidth(5.0f);

	//split lines into correct sections for viewport
	glBegin(GL_LINE_STRIP);
	glVertex3f(0.0f, -(glutGet(GLUT_WINDOW_HEIGHT)), -10.0f);
	glVertex3f(0.0f, glutGet(GLUT_WINDOW_HEIGHT), -10.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3f(-(glutGet(GLUT_WINDOW_WIDTH)), 0, -10.0f);
	glVertex3f(glutGet(GLUT_WINDOW_WIDTH), 0, -10.0f);
	glEnd();
}

void specialKeys(int key, int x, int y) {
	if (key == GLUT_KEY_UP) worldZoom += 0.1;
	if (key == GLUT_KEY_DOWN) worldZoom -= 0.1;
	glutPostRedisplay();
}

void timerFunc(int value) {
	yRot -= 2;
	glutTimerFunc(33, timerFunc, 1);
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	
	glViewport(0, 0, (GLsizei)w, (GLsizei)h); //set the viewport to the current window specifications
	
	glMatrixMode(GL_PROJECTION); //set the matrix to projection

	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 1000.0); //set the perspective (angle of sight, width, height, ,depth)
	glMatrixMode(GL_MODELVIEW); //set the matrix back to model
}

void renderScene(void)
{
	World::GetInstance().render();
}

void keyboard(unsigned char key, int x, int y)
{
	World::GetInstance().keyPress(key);
}

World& World::GetInstance()
{
	if (s_World == NULL)
	{
		s_World = new World();
	}
	return *s_World;
}

void World::setCmdlineParams(int*argc, char **argv)
{
	this->argc = argc;
	this->argv = argv;
}

float clampf(float n, float lower, float upper) {
	return max(lower, min(n, upper));		//clmp the float
}

void World::drawScene() {

	worldZoom = clampf(worldZoom, 1.0f, 4.0f);		//clamp the zoom level
	glLoadIdentity();

	glPushMatrix();
		glRotatef(worldRotX, 1.0f, 0.0f, 0.0f);		//rotate the viewport
		glRotatef(worldRotY, 0.0f, 1.0f, 0.0f);
		splitScreen();					//split the viewport into sections
		glTranslatef(0, 0, -10);		
		glRotatef(xRot, 1.0f, 0.0f, 0.0f);		//rotate the model
		glRotatef(yRot, 0.0f, 1.0f, 0.0f);
		glScalef(worldZoom, worldZoom, worldZoom);		//scale the	model
		theModel.render();			//render the model
	glPopMatrix();
}

void World::render()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glColor3f(255, 0, 0);

	glLoadIdentity();
	glLineWidth(1.0f);

	glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH) * 0.5, glutGet(GLUT_WINDOW_HEIGHT) * 0.5);		//bottom left
	drawScene();

	glViewport(glutGet(GLUT_WINDOW_WIDTH) * 0.5, 0, glutGet(GLUT_WINDOW_WIDTH) * 0.5, glutGet(GLUT_WINDOW_HEIGHT) * 0.5);	//bottom right
	drawScene();

	glViewport(glutGet(GLUT_WINDOW_WIDTH) * 0.5, glutGet(GLUT_WINDOW_HEIGHT) * 0.5, glutGet(GLUT_WINDOW_WIDTH) * 0.5, glutGet(GLUT_WINDOW_HEIGHT) * 0.5);	//top right
	drawScene();

	glViewport(0, glutGet(GLUT_WINDOW_HEIGHT) * 0.5, glutGet(GLUT_WINDOW_WIDTH) * 0.5, glutGet(GLUT_WINDOW_HEIGHT) * 0.5);	//top left
	drawScene();

	glutSwapBuffers();
}

void World::keyPress(unsigned char key)
{
	if (key == 'a') worldRotY = (worldRotY + 1 % 360);
	if (key == 'd') worldRotY = (worldRotY - 1 % 360);
	if (key == 'w') worldRotX = (worldRotX + 1 % 360);
	if (key == 's') worldRotX = (worldRotX - 1 % 360);

	glutPostRedisplay();
}


void World::initialize(int width, int height, std::string name)
{
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow(name.c_str());

	Color::Black.renderClear();		//render culling and depth
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_LINE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, 1, 1.0, 1000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//setup opengl functions
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutDisplayFunc(renderScene);
	glutTimerFunc(33, timerFunc, 1);
	glutSpecialFunc(specialKeys);
}

void World::start()
{
	glutMainLoop();
}

void World::loadModel(std::string modelName)
{
	ifstream inStream;
	inStream.open(modelName.c_str(), ios::in);
	if (!inStream.fail())
	{
		theModel.load(inStream);
	}
}