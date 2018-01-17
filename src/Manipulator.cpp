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
    manipPiston = new DoubleSolenoid (0,1); //These are dummy values//
   // manipPiston->Set(DoubleSolenoid::kReverse);
    cubeStop = new DigitalInput(3); //These are dummy values//
    toggle = 0;
}

Manipulator::~Manipulator()
{
	leftIntakeMotor = nullptr;
	rightIntakeMotor = nullptr;
	manipPiston = nullptr;
	cubeStop = nullptr;
	delete leftIntakeMotor;
	delete rightIntakeMotor;
	delete manipPiston;
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

void Manipulator::intakePosition(bool posButton)
{
	if(posButton)
	{
		if(toggle == 1)
		{
			manipPiston->Set(DoubleSolenoid::kForward);
			Wait(.2);
			toggle = 0;
		}
		else
		{
			manipPiston->Set(DoubleSolenoid::kReverse);
			Wait(.2);
			toggle = 1;
		}
	}
}
}
