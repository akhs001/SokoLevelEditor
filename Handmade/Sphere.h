#ifndef SPHERE_H
#define SPHERE_H

#include "Vector.h"

class Sphere
{

public:

	Sphere();

public:

	void SetRadius(int radius);
	void SetPosition(int x, int y);

public:

	bool IsColliding(const Sphere& secondSphere) const;

private:

	int m_radius;
	Vector<int> m_position;

};

#endif