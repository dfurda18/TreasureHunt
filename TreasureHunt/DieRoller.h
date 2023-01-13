#pragma once

#include <random>

/**
* This is the header class for a Dice roller. It can be seeded as will and it can generate any sixe of dices.
* It also has a function that simulates throwing 4 dices with 6 faces.
*/
class DieRoller
{
private:
	/*
	* This is a private variable that generates the random number.
	* Type: std::mt19937
	*/
	std::mt19937 rng;

public:
	/*
	* Constructor that seeds the rng with a std::random_device
	* @return A new instance of the DieRoller class.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	DieRoller();
	/*
	* Seeds the rng with the seedVal
	* @param unsigned int The value of the int used to seed the random device.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	void SeedRNG(unsigned int seedVal);
	/*
	* Returns the result of an N-sided die roll (between 1 and N)
	* @param int The number of sides of the dice about to be rolled.
	* @return The result of rolling the dice.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	int RollDN(int N);
	/*
	* Rolls 4 six-sided dice and sums the top 3, dropping the lowest roll
	* @return The result of the top 3 rolls of six-sided dices.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	int Roll4D6DropLowest(); // 
};
