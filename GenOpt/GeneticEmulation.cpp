#include "stdafx.h"
#include<algorithm> 
#include "GeneticEmulation.h"

extern double PI;

extern int einOderNull();
extern double randDoubleFromZeroTo(double);
extern int randFromZeroToNumber(int);


void printIndividual(item* element, double survFunc, int order) {
	std::cout << "\n("<< order <<") (" << element->getX() << ', ' << element->getY() << "), survivior function : " << survFunc;
}
double findMinInSurvFunc(std::vector<double> survFunc) {
	std::vector<double>::iterator result = std::min_element(survFunc.begin(), survFunc.end());
	return survFunc.at(std::distance(survFunc.begin(), result));
}
GeneticEmulation::GeneticEmulation(int amount) {
	population.reserve(amount);
	survFunc.reserve(2 * amount);
	amountOfIndividuals = amount;
	std::cout << "Initialization part:\n ";

	for(int i = 0; i < amount;i++) {
		item* element = new item(randDoubleFromZeroTo(2*PI), randDoubleFromZeroTo(2*PI));
		population.push_back(element);
		survFunc.push_back(element->countFunction()); // filling first part of Survivor function

		// print section
		printIndividual(element, survFunc.at(i), survFunc.size());
	}
}


GeneticEmulation::~GeneticEmulation() {
	population.clear();
	posterity.clear();
	survFunc.clear();
}

void GeneticEmulation::reproduction() {
	double possibleValues[4];
	posterity.reserve(amountOfIndividuals);
	std::cout << "\n Reproduction part (time of new generation!):\n ";


	for (int i = 0; i < amountOfIndividuals;i++) {
		item *mother = population[randFromZeroToNumber(amountOfIndividuals)];
		item *father = population[randFromZeroToNumber(amountOfIndividuals)];
		possibleValues[0] = mother->getX();
		possibleValues[1] = mother->getY();
		possibleValues[2] = father->getX();
		possibleValues[3] = mother->getY();

		item* baby = new item(possibleValues[randFromZeroToNumber(4)], possibleValues[randFromZeroToNumber(4)]);
		posterity.push_back(baby);
		survFunc.push_back(baby->countFunction()); // filling second part of Survivor function
		printIndividual(baby, survFunc.back(), survFunc.size());
	}

}

void GeneticEmulation::mutation() {
	// ToDo: merge in one function:
	// mutate population
	for (int i = 0;i < amountOfIndividuals;i++)
	{
		if (randFromZeroToNumber(100) == 1)// possibility 1%
		{
			int numOfRandPerson;
			do {
				numOfRandPerson = randFromZeroToNumber(2 * amountOfIndividuals);
			} while (numOfRandPerson == i);// if random number equals i, mutation won't happen
			item* donor;
			bool isFromPopulation;
			if (numOfRandPerson < amountOfIndividuals)
				donor = new item(*population.at(numOfRandPerson));
			else 
				donor = new item(*posterity.at(numOfRandPerson - amountOfIndividuals));

			population.at(i)->setX(population.at(i)->getX() * donor->getX() + randDoubleFromZeroTo(2 * PI));
			population.at(i)->setY(population.at(i)->getY() * donor->getY() + randDoubleFromZeroTo(2 * PI));
			survFunc.at(i) = population.at(i)->countFunction();

			std::cout << "\nI mutated! It's new me:\n";
			printIndividual(population.at(i), survFunc.at(i), i);
		}
	}
	// mutate posterity
	for (int i = 0;i < amountOfIndividuals;i++)
	{
		if (randFromZeroToNumber(100) == 1)// possibility 1%
		{
			int numOfRandPerson;
			do {
				numOfRandPerson = randFromZeroToNumber(2 * amountOfIndividuals);
			} while (numOfRandPerson == i);// if random number equals i, mutation won't happen
			item* donor;
			bool isFromPopulation;
			if (numOfRandPerson < amountOfIndividuals)
				donor = new item(*population.at(numOfRandPerson));
			else
				donor = new item(*posterity.at(numOfRandPerson - amountOfIndividuals));

			posterity.at(i)->setX(population.at(i)->getX() * donor->getX() + randDoubleFromZeroTo(2 * PI));
			posterity.at(i)->setY(population.at(i)->getY() * donor->getY() + randDoubleFromZeroTo(2 * PI));
			survFunc.at(i+ amountOfIndividuals) = population.at(i)->countFunction();

			std::cout << "\nI mutated! It's new me:\n";
			printIndividual(posterity.at(i), survFunc.at(i), i);
		}
	}
}

void GeneticEmulation::selection() {
	double maxValue = -DBL_MAX;
	int maxId = -1;
	int randNum;
	// new array of selected individuals, it's going to replace the population
	std::vector<item*> selected; // lucky bastards
	selected.reserve(amountOfIndividuals);
	std::vector<double> fitnessFunc;
	fitnessFunc.reserve(2 * amountOfIndividuals);
	std::vector<double> percantage;
	percantage.reserve(2 * amountOfIndividuals);


	// Roulette wheel selection
	double genSumOfFitnessFunc = 0; // sum of all elements from survFunc
	double minValue = findMinInSurvFunc(survFunc);

	for (int i = 0;i < survFunc.size();i++) {
		fitnessFunc.push_back(survFunc.at(i) - minValue);
		genSumOfFitnessFunc += fitnessFunc.back();
	}

	percantage.push_back((fitnessFunc[0] / genSumOfFitnessFunc) * 100); // first element
	for (int i = 1;i < fitnessFunc.size();i++) {
		percantage.push_back((percantage.at(percantage.size() - 1)) + ((fitnessFunc[i] / genSumOfFitnessFunc) * 100));
	}

	// select n individuals
	item* winner;
	std::cout << "\n************************************************\n Selected individuals:\n";

	for (int i = 0;i < amountOfIndividuals;i++) {
		randNum = randDoubleFromZeroTo(99); 
		for (int j = 0;j < percantage.size();j++) {
			if (percantage[j] > randNum) {
				int winnerId = j;
				(winnerId < amountOfIndividuals) ? winner = new item(*population.at(winnerId)) : winner = new item(*posterity.at(winnerId-amountOfIndividuals));
				selected.push_back(winner);

				printIndividual(winner, winner->countFunction(), selected.size());

				if (fitnessFunc.at(winnerId) > maxValue) { // find the best individual among selected
					maxValue = fitnessFunc.at(winnerId);
					maxId = i;
				}
				break;
			}
		}	
	}

	// Re-calculation of survFunc
	survFunc.clear();
	for (int i = 0;i < amountOfIndividuals;i++) {
		survFunc.push_back(selected.at(i)->countFunction()); // filling first part of Survivor function
	}
	std::cout << "\n\n The best result among selected: ";
	printIndividual(selected.at(maxId), maxValue + minValue, maxId); // ID among selected
	// memory cleaning section
	population.clear();
	population = selected;
	posterity.clear();
	selected.clear();
	fitnessFunc.clear();
	percantage.clear();
}
