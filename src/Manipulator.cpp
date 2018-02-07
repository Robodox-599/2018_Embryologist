/*
 * Intake.cpp
 *
 *  Created on: Jan 6, 2018
 *      Author: Admin
 */

#include "Manipulator.h"

Manipulator::Manipulator() //renews all booleans, digital inputs, and CANTalons in this case//
{
    leftIntakeMotor = new TalonSRX(1); //These are dummy values.//
    rightIntakeMotor = new TalonSRX(2); //These are dummy values.//
    leftmanipPiston = new DoubleSolenoid (0,1); //These are dummy values.//
    rightmanipPiston = new DoubleSolenoid (0,2); //These are dummy values.//
    cubeStop = new DigitalInput(3); //These are dummy values.//
    toggle = 0;
}

Manipulator::~Manipulator() //deletes all booleans, digital inputs, and CANTalons to "restart" them//
{
	leftIntakeMotor = nullptr;
	rightIntakeMotor = nullptr;
	leftmanipPiston = nullptr;
	rightmanipPiston = nullptr;
	cubeStop = nullptr;
	delete leftIntakeMotor;
	delete rightIntakeMotor;
	delete cubeStop;
}

void Manipulator::intakeOuttakeCube(bool intake, bool outtake) //intakes the actual cube with/without limit switch + outtake//
{
	if (intake && cubeStop->Get() == false)
	{
		leftIntakeMotor->Set(ControlMode::PercentOutput, 1); //These are dummy values.//
		rightIntakeMotor->Set(ControlMode::PercentOutput, 1); //These are dummy values.//
	}

	else if (outtake)
	{
		leftIntakeMotor->Set(ControlMode::PercentOutput, -1); //These are dummy values.//
		rightIntakeMotor->Set(ControlMode::PercentOutput, -1); //These are dummy values.//
	}

	else
	{
		leftIntakeMotor->Set(ControlMode::PercentOutput, 0);
		rightIntakeMotor->Set(ControlMode::PercentOutput, 0);
	}

}

bool Manipulator::stoppingCube() //limit switch stops intake//
{
	return cubeStop->Get();
}

void Manipulator::intakePosition(bool posButton) //piston folds in/folds out intake/outtake arms//
{
	if(posButton)
	{
		if(toggle == 1)
		{
			leftmanipPiston->Set(DoubleSolenoid::kForward);
			rightmanipPiston -> Set(DoubleSolenoid::kForward);
			Wait(.2);
			toggle = 0;
		}
		else
		{
			leftmanipPiston->Set(DoubleSolenoid::kReverse);
			rightmanipPiston -> Set(DoubleSolenoid::kReverse);
			Wait(.2);
			toggle = 1;
		}
	}
}

void Manipulator::setPos(bool pos)
{
	if(pos)
	{
		leftmanipPiston->Set(DoubleSolenoid::kForward);
		rightmanipPiston->Set(DoubleSolenoid::kForward);
	}
	else
	{
		leftmanipPiston->Set(DoubleSolenoid::kReverse);
		rightmanipPiston->Set(DoubleSolenoid::kReverse);
	}
}

void Manipulator::AutoIntake() //Intake until limit switch//
{
	while (cubeStop->Get() == false)
	{
		leftIntakeMotor->Set(ControlMode::PercentOutput, -1); //These are dummy values.//
		rightIntakeMotor->Set(ControlMode::PercentOutput, -1); //These are dummy values.//

	}
	leftIntakeMotor->Set(ControlMode::PercentOutput, 0);
	rightIntakeMotor->Set(ControlMode::PercentOutput, 0);
}

void Manipulator:: AutoOuttake() //Outtake for (Dummy Value) seconds//
{
	leftIntakeMotor->Set(ControlMode::PercentOutput, -1); //These are dummy values.//
	rightIntakeMotor->Set(ControlMode::PercentOutput, -1); //These are dummy values.//
	Wait(1);
	leftIntakeMotor->Set(ControlMode::PercentOutput, 0);
	rightIntakeMotor->Set(ControlMode::PercentOutput, 0);
}

