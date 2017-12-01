#pragma once
#include "Vector3.h"
#include "iostream"
#include "vector"

struct Face
{
	int vertices[3];
	int textures[3];

	Face(std::istream &is);
	void render(std::vector<Vector3> &defaultTable);
};