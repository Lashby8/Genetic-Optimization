#pragma once
#include "item.h"
#include <vector>
#include <iostream>

class GeneticEmulation {
private:
	int amountOfIndividuals;
	std::vector<item*> population;
	std::vector<item*> posterity; 
	std::vector<double> survFunc;
public:
	GeneticEmulation(int);
	~GeneticEmulation();
	void reproduction();
	void mutation();
	void selection();
};

