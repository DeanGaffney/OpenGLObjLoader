#include "world.h"

void printPath(char *partialPath);

void printPath(char * partialPath)
{
	char full[_MAX_PATH];
	if (_fullpath(full, partialPath, _MAX_PATH) != NULL)
		printf("Full path is: %s\n", full);
	else
		printf("Invalid path\n");
}

int main(int argc, char* argv[])
{
	theWorld.setCmdlineParams(&argc, argv);
	theWorld.initialize(800, 600, "First World");

	theWorld.loadModel("cube.obj");
	theWorld.start();
	return 0;
}