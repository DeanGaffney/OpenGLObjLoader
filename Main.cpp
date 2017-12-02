#include "world.h"

int main(int argc, char* argv[])
{
	theWorld.setCmdlineParams(&argc, argv);
	theWorld.initialize(800, 600, "First World");

	theWorld.loadModel("cube.obj");
	theWorld.start();
	return 0;
}