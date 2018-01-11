/*
 * Lift.cpp
 *
 *  Created on: Jan 6, 2018
 *      Author: Admin
 */

#ifdef LIFT_CODE

#include "WPILib.h"
#include "Lift.h"


Lift::Lift()
{
	motorOne = new CANTalon(1);
	motorTwo = new CANTalon(1);
	motorThree = new CANTalon(1);
	motorFour = new CANTalon(1);
	motorFive = new CANTalon(1);
	motorSix = new CANTalon(1);
	motorSeven = new CANTalon(1);
	motorEight = new CANTalon(1);
}

Lift::~Lift()
{
	delete motorOne;
	delete motorTwo;
	delete motorThree;
	delete motorFour;
	delete motorFive;
	delete motorSix;
	delete motorSeven;
	delete motorEight;

	motorOne = nullptr;
	motorTwo = nullptr;
	motorThree = nullptr;
	motorFour = nullptr;
	motorFive = nullptr;
	motorSix = nullptr;
	motorSeven = nullptr;
	motorEight = nullptr;


}





