#include "ModelObject.h"

using namespace std;

ModelObject::ModelObject()
{}

ModelObject::ModelObject(istream &is)
{
	string indicator;
	is >> name;
	bool stillGroup = true;
	do
	{
		is >> indicator;
		if (indicator == "v")
		{
			vertices.push_back(Vector3(is));
		}
		else if (indicator == "f")
		{
			faces.push_back(Face(is));
		}
		else if (indicator == "g")
		{
			stillGroup = false;
		}
		else
		{
			string buf;
			getline(is, buf);
		}
	} while (stillGroup && !is.eof());
	is.putback(indicator[0]);
}

void ModelObject::render(std::vector<Vector3> &defaultTable)
{
	cout << " rendering " << name << " with " << faces.size() << endl;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		faces[i].render(defaultTable);
	}
}