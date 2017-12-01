#include "Face.h"
#include "string"

using namespace std;

Face::Face(istream &is)
{
	char ch1;
	for (int i = 0; i < 4; i++)
	{
		string separator;
		is >> vertices[i];
		is >> ch1;
		is >> textures[i];
	}
}

void Face::render(vector<Vector3> &defaultTable)
{
	glBegin(GL_QUADS);
	for (int i = 0; i<4; i++)
	{
		glVertex3f(defaultTable[vertices[i] - 1].X,
			defaultTable[vertices[i] - 1].Y,
			defaultTable[vertices[i] - 1].Z);
		cout << defaultTable[vertices[i] - 1].X << " " << defaultTable[vertices[i] - 1].Y << " " << defaultTable[vertices[i] - 1].Z << endl;
	}
	glEnd();
}