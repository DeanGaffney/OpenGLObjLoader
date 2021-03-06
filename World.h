#pragma once
#include <string>
#include "Model.h"

#define theWorld World::GetInstance()

class World
{
public:
	static World& GetInstance();

	float scale;

	void setCmdlineParams(int*argc, char **argv);
	void initialize(int width, int height, std::string name);
	void start();

	void render();
	void drawScene();
	void keyPress(unsigned char ch);
	void loadModel(std::string modelName);
private:
	static World* s_World;
	Model theModel;

	int   *argc;
	char **argv;
};