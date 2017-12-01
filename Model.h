#pragma once
#include "map"
#include "ModelObject.h"


typedef std::map <std::string, ModelObject>  ModelMap;
typedef ModelMap::iterator ModelMapIterator;

struct Model
{
	ModelMap  modelObjects;

	Model();
	bool load(std::istream &is);
	void render();
};