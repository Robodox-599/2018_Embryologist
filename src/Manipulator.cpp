/*
 * Intake.cpp
 *
 *  Created on: Jan 6, 2018
 *      Author: Admin
 */

#include "Manipulator.h"

Manipulator::Manipulator()
{
    leftMotor = new TalonSRX(1); //These are dummy values//
    rightMotor = new TalonSRX(2); //These are dummy values//
    CubeStopOne = new DigitalInput(3); //These are dummy values//
}

Manipulator::~Manipulator()
{
	leftMotor = nullptr;
	rightMotor = nullptr;
	CubeStopOne = nullptr;
	delete leftMotor;
	delete rightMotor;
	delete CubeStopOne;
}

void Manipulator::intake_outtake_Cube(bool button, bool Button)
{
	if (button)
	{
		leftMotor->Set(ControlMode::PercentOutput, 1); //These are dummy values//
		rightMotor->Set(ControlMode::PercentOutput, 1); //These are dummy values//
	}

	else if (Button)
	{
		leftMotor->Set(ControlMode::PercentOutput, -1); //These are dummy values//
		rightMotor->Set(ControlMode::PercentOutput, -1); //These are dummy values//
	}

	else
	{
		leftMotor->Set(ControlMode::PercentOutput, 0);
		rightMotor->Set(ControlMode::PercentOutput, 0);
	}

}

bool Manipulator::stoppingcubeone()
{
	return CubeStopOne->Get();
}
