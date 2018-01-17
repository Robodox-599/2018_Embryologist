/*
 * Intake.cpp
 *
 *  Created on: Jan 6, 2018
 *      Author: Admin
 */

#include "Manipulator.h"

Manipulator::Manipulator()
{
    leftIntakeMotor = new TalonSRX(1); //These are dummy values//
    rightIntakeMotor = new TalonSRX(2); //These are dummy values//
    cubeStop = new DigitalInput(3); //These are dummy values//
}

Manipulator::~Manipulator()
{
	leftIntakeMotor = nullptr;
	rightIntakeMotor = nullptr;
	cubeStop = nullptr;
	delete leftIntakeMotor;
	delete rightIntakeMotor;
	delete cubeStop;
}

void Manipulator::intakeOuttakeCube(bool intake, bool outtake)
{
	if (intake)
	{
		leftIntakeMotor->Set(ControlMode::PercentOutput, 1); //These are dummy values//
		rightIntakeMotor->Set(ControlMode::PercentOutput, 1); //These are dummy values//
	}

	else if (outtake)
	{
		leftIntakeMotor->Set(ControlMode::PercentOutput, -1); //These are dummy values//
		rightIntakeMotor->Set(ControlMode::PercentOutput, -1); //These are dummy values//
	}

	else
	{
		leftIntakeMotor->Set(ControlMode::PercentOutput, 0);
		rightIntakeMotor->Set(ControlMode::PercentOutput, 0);
	}

}

bool Manipulator::stoppingCube()
{
	return cubeStop->Get();
}
