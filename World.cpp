#include "windows.h"
#include "gl/gl.h"
#include "gl/glu.h"
#include "gl/freeglut.h"
#include "color.h"
#include <fstream>
#include "vector3.h"
#include "world.h"

using namespace std;

World* World::s_World = NULL;

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h); //set the viewportto the current window specifications
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

void World::render()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	Vector3(0, 0, -10).translate();
	theModel.render();

	glutSwapBuffers();
}

void World::keyPress(unsigned char ch)
{
	glutPostRedisplay();
}


void World::initialize(int width, int height, std::string name)
{
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow(name.c_str());

	Color::Black.renderClear();
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_LINE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, 1, 1.0, 1000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//glTranslatef(0.0f, 0.0f, -200.0f);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutDisplayFunc(renderScene);
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