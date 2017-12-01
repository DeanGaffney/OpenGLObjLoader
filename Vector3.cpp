#include "Vector3.h"

using namespace std;

Vector3 Vector3::UnitX(1.0f, 0.0f, 0.0f);
Vector3 Vector3::UnitY(0.0f, 1.0f, 0.0f);
Vector3 Vector3::UnitZ(0.0f, 0.0f, 1.0f);

Vector3::Vector3(float x, float y, float z)
	: X(x)
	, Y(y)
	, Z(z)
{}

Vector3::Vector3(float value)
	: X(value)
	, Y(value)
	, Z(value)
{}

Vector3::Vector3()
	: X(0)
	, Y(0)
	, Z(0)
{}

Vector3::Vector3(istream &is)
{
	is >> X >> Y >> Z;
}

void Vector3::render()
{
	glVertex3f(X, Y, Z);
}

void Vector3::translate()
{
	glTranslatef(X, Y, Z);
}

void Vector3::rotate(float angle)
{
	glRotatef(angle, X, Y, Z);
}