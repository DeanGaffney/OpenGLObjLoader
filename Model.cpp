#include "Model.h"
#include "string"

using namespace std;

Model::Model()
{
}

bool Model::load(istream &is)
{
	string indicator;
	while (is >> indicator)
	{
		if (indicator == "#")
		{
			string buf;
			getline(is, buf);
		}
		else if (indicator == "g")
		{
			ModelObject a(is);
			if (modelObjects.find(a.name) == modelObjects.end())
			{
				modelObjects[a.name] = a;
			}
		}
	}

	return true;
}

void Model::render()
{
	ModelMapIterator defaultIter = modelObjects.find("default");
	if (defaultIter != modelObjects.end())
	{
		ModelObject defaultObject(defaultIter->second);
		for (ModelMapIterator iter = modelObjects.begin(); iter != modelObjects.end(); iter++)
		{
			iter->second.render(defaultObject.vertices);
		}
	}
}