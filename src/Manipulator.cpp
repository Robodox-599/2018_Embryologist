/*
 * Intake.cpp
 *
 *  Created on: Jan 6, 2018
 *      Author: Admin
 */

#include "Manipulator.h"

Manipulator::Manipulator()
{
    leftMotor = new CANTalon (1); //These are dummy values//
    rightMotor = new CANTalon (2); //These are dummy values//
}

Manipulator::~Manipulator()
{
	leftMotor = nullptr;
	rightMotor = nullptr;
	delete leftMotor;
	delete rightMotor;
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
