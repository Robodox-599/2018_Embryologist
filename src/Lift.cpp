/*
 * Lift.cpp
 *
 *  Created on: Jan 6, 2018
 *      Author: Admin
 */



#include "Lift.h"


Lift::Lift()
{
	motorOne = new TalonSRX(3);
	motorTwo = new TalonSRX(2);
	motorThree = new TalonSRX(5);
	motorFour = new TalonSRX(1);

}

Lift::~Lift()
{
	delete motorOne;
	delete motorTwo;
	delete motorThree;
	delete motorFour;

	motorOne = nullptr;
	motorTwo = nullptr;
	motorThree = nullptr;
	motorFour = nullptr;

}



