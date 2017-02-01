#include "stdafx.h"
#include<algorithm> 
#include "GeneticEmulation.h"
extern int einOderNull();
extern double randFromZeroToTwoPi();

void printInit(item* element, double survFunc) {
	std::cout << "\n(" << element->x << ',' << element->y << "), survivior function - " << survFunc;
}

GeneticEmulation::GeneticEmulation(int amount) {
	population.reserve(amount);
	survFunc.reserve(2 * amount);
	for(int i = 0; i < amount;i++) {
		item* element = new item(randFromZeroToTwoPi(), randFromZeroToTwoPi());
		population.push_back(element);
		survFunc.push_back(element->countFunction()); // filling first part of Survivor function

		// print section
		printInit(element, survFunc[i]);
	}
}


GeneticEmulation::~GeneticEmulation() {
	population.clear();
	posterity.clear();
	survFunc.clear();
}

void GeneticEmulation::reproduction() {
}

void GeneticEmulation::mutation() {
}

void GeneticEmulation::selection() {
}

