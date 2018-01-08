/*
 * Intake.cpp
 *
 *  Created on: Jan 6, 2018
 *      Author: Admin
 */

#include "Manipulator.h"

Manipulator::Manipulator()
{
    leftMotor = new CANTalon (1);
    rightMotor = new CANTalon (2);
}

Manipulator::~Manipulator()
{
	leftMotor = nullptr;
	rightMotor = nullptr;
	delete leftMotor;
	delete rightMotor;
}
