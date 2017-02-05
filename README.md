# Genetic-Optimization
## Overview
This is pretty simple realization of Evolutionary algorithm, which solves optimization problem of maximizing a function (2 variables).
Function is *f(x) = Sin(x)Cos(y) => max* currently. x = [0, 2π], y = [0, 2π].
## Usage
Clone this repo, then launch the project. Algoritm ask you next variables:
Amount of pairs (x,y) (positive number) - amount of items in each population.
Amount of iterations (positive number) - how many times algoritm will repeat it's main cycles of Evolutionary algorithm(reproduction, mutation and selection).
## Individuals
Each individual is object of class `item.cpp`. Each individual contains *x* and *y* as members. Besides, except getters and setters, class contains the function `countFunction()`, which finds a value of function subject to definite x and y. Survival function is value of *f(x)* .
## Algoritm's options
###### Initialization
The initial population is **generated randomly**, initial population consists of [Amount of pairs (x,y)] items.
###### Reproduction
The way of selection of parents - **panmixia**.(randomness)
The way of reproduction a new individual - **single-point crossover**.
New item gets it's x and y from random parent. Therefore, two parents reproduce one new individual. Each generation should reproduce [Amount of pairs (x,y)] individuals.
###### Mutation
Probability of mutation of each individual is **1%**. I used my own method of mutatuion - algoritm takes one random individual(we'll call it donor), and mutated individual re-count it's values in accord with following formula:

			individual(x) = individual(x) * donor(x) + [random number from 0 to 2π],
			individual(y) = individual(y) * donor(y) + [random number from 0 to 2π]
###### Selection
I used the **Roulette wheel selection** (Fitness proportionate selection). I had negative numbers among values of survival function( because f(x) can take on a negative value). So, my Fitness function increase Survival function by *minimum among all individuals*. Therefore, I have the array, which consists of only positive numbers( Fitness function ). Selection defines the probability of being individual selected as parent in next generation. This probability depends on value of Fitness function(the larger the value of Fitness function is, the larger probability of selection of individual is). Only [Amount of pairs (x,y)] can be selected. The rest will be erased. 
###### Termination
Algoritm completes his works, when it iterates main cycles of Evolutionary algorithm(reproduction, mutation and selection) [Amount of iterations] times.
## Architecture
Algoritm creates new population(or several populations) in `int main()`. All cycles of Evolutionary algorithm are public methods of *GeneticEmulation* (Constructor initializes a population):
```
public:
	GeneticEmulation(int);
	~GeneticEmulation();
	void reproduction();
	void mutation();
	void selection();
 ```

 This approach allows to create many different populations and count them on different threads.
