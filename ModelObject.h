#pragma once
#include "string"
#include "vector"
#include "iostream"
#include "Face.h"
#include "Vector3.h"

struct ModelObject
{
	std::string name;
	std::vector<Face> faces;
	std::vector <Vector3> vertices;

	ModelObject();
	ModelObject(std::istream &is);
	void render(std::vector <Vector3> &defaultTable);
};