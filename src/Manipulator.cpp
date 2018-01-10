/*
 * Intake.cpp
 *
 *  Created on: Jan 6, 2018
 *      Author: Admin
 */

#include "Manipulator.h"

Manipulator::Manipulator()
{
    leftMotor = new CANTalon(1); //These are dummy values//
    rightMotor = new CANTalon(2); //These are dummy values//

    CubeStopOne = new DigitalInput(3); //These are dummy values//
    CubeStopTwo = new DigitalInput(4); //These are dummy values//

    breakone = false;
    breaktwo = false;
}

Manipulator::~Manipulator()
{
	leftMotor = nullptr;
	rightMotor = nullptr;
	CubeStopOne = nullptr;
	CubeStopTwo = nullptr;
	delete leftMotor;
	delete rightMotor;
	delete  CubeStopOne;
	delete  CubeStopTwo;
}

void Manipulator::intake_outtake_Cube(bool button, bool Button)
{
	if (button)
	{
		leftMotor->Set(1); //These are dummy values//
		rightMotor->Set(1); //These are dummy values//
	}

	else if (Button)
	{
		leftMotor->Set(-1); //These are dummy values//
		rightMotor->Set(-1); //These are dummy values//
	}

	else
	{
		leftMotor->Set(0);
		rightMotor->Set(0);
	}

}


