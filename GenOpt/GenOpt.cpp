// GenOpt.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <cmath>
#include "GeneticEmulation.h"
#include "item.h"


using namespace std;

double PI = 3.141592653589793;

int main()
{
	int AMOUNT_OF_PAIRS, AMOUNT_OF_ITERATIONS;

	srand(time(NULL));
	cout << "Input amount of pairs (x,y) - ";
	cin >> AMOUNT_OF_PAIRS;
	cout << "\nInput amount of iterations - ";
	cin >> AMOUNT_OF_ITERATIONS;

	// we can create as many populations, as we need (and count it on different threads) 
	GeneticEmulation *pop = new GeneticEmulation(AMOUNT_OF_PAIRS);
	for (int i = 0;i < AMOUNT_OF_ITERATIONS;i++) {
		pop->reproduction();
		pop->mutation();
		pop->selection();
	}

	_getch();
	return 0;
}

int einOderNull() {
	return (rand() % 2);
}

double randFromZeroToTwoPi() {
	return (double)(rand()) / RAND_MAX*(2*PI);
}