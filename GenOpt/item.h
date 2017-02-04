#pragma once
class item
{
private:
	double x;
	double y;
public:
	item(double, double);
	~item();
	item(const item & original);
	double countFunction();
	double getX();
	void setX(double newX);
	double getY();
	void setY(double newY);
};

