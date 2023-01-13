#include "DieRoller.h"

DieRoller::DieRoller() {
	std::random_device rd;
	this->SeedRNG(rd());
}

void DieRoller::SeedRNG(unsigned int seedVal) {
	rng.seed(seedVal);
}

int DieRoller::RollDN(int N) {
	std::uniform_int_distribution<unsigned int> uint_distDice(1, N);
	return uint_distDice(rng);
}

int DieRoller::Roll4D6DropLowest() {
	int lowestRoll = this->RollDN(6); // first rolll
	int temp = 0;
	int result = 0;
	for (int i = 0; i < 3; i++) {
		temp = this->RollDN(6);
		if (temp < lowestRoll) {
			result += lowestRoll;
			lowestRoll = temp;
		}
		else {
			result += temp;
		}
	}
	
	return result;
}
