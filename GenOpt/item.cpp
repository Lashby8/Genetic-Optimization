#include "stdafx.h"
#include "item.h"
#include <cmath>

item::item(double someX, double someY)
{
	x = someX;
	y = someY;
}

item::~item()
{
}

double item::countFunction()
{
	// any function can be here
	return (sin(this->x)*cos(this->y));
}
