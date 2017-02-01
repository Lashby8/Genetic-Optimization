#pragma once
#include "item.h"
#include <vector>
#include <iostream>

class GeneticEmulation
{
public:
	std::vector<item*> population;
	std::vector<item*> posterity; 
	std::vector<double> survFunc;

	GeneticEmulation(int);
	~GeneticEmulation();
	void reproduction();
	void mutation();
	void selection();
};

