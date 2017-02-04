#include "stdafx.h"
#include "item.h"
#include <cmath>

item::item(double someX, double someY)
{
	x = someX;
	y = someY;
}

item::~item() {
}

item::item(const item & original) {
	// copy constructor
	x = original.x;
	y = original.y;
}

double item::countFunction() {
	// any function can be here
	return (sin(this->x)*cos(this->y));
}

double item::getX() {
	return x;
}

void item::setX(double newX)
{
	this->x = newX;
}

double item::getY() {
	return y;
}

void item::setY(double newY)
{
	this->y = newY;
}
