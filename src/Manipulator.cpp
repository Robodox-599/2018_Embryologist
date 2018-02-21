/*
 * Intake.cpp
 *
 *  Created on: Jan 6, 2018
 *      Author: Admin
 */

#include "Manipulator.h"
#include "ctre/Phoenix.h"
#include "WPILib.h"

Manipulator::Manipulator() //renews all booleans, digital inputs, and CANTalons in this case//
{
    leftIntakeMotor = new TalonSRX(5); //These are dummy values.//
    rightIntakeMotor = new TalonSRX(8); //These are dummy values.//
    leftmanipPiston = new DoubleSolenoid (2,3); //These are dummy values.//
    //rightmanipPiston = new DoubleSolenoid (0,2); //These are dummy values.//
    cubeStop = new DigitalInput(2); //These are dummy values.//
    toggle = 1;
}

Manipulator::~Manipulator() //deletes all booleans, digital inputs, and CANTalons to "restart" them//
{
	leftIntakeMotor = nullptr;
	rightIntakeMotor = nullptr;
	leftmanipPiston = nullptr;
	//rightmanipPiston = nullptr;
	cubeStop = nullptr;
	delete leftIntakeMotor;
	delete rightIntakeMotor;
	delete cubeStop;
}

void Manipulator::intakeOuttakeCube(bool intake, bool outtake) //intakes the actual cube with/without limit switch + outtake//
{
	if (intake)// && cubeStop->Get() == false)
	{
		leftIntakeMotor->Set(ControlMode::PercentOutput, -.8); //These are dummy values.//
		rightIntakeMotor->Set(ControlMode::PercentOutput, .6); //These are dummy values.//
	}

	else if (outtake)
	{
		leftIntakeMotor->Set(ControlMode::PercentOutput, 1); //These are dummy values.//
		rightIntakeMotor->Set(ControlMode::PercentOutput, -1); //These are dummy values.//
	}
	else if(cubeStop->Get())
	{
		leftIntakeMotor->Set(ControlMode::PercentOutput, -.08);
		rightIntakeMotor->Set(ControlMode::PercentOutput, .08);
	}

	else
	{
		leftIntakeMotor->Set(ControlMode::PercentOutput, 0);
		rightIntakeMotor->Set(ControlMode::PercentOutput, 0);
	}
	SmartDashboard::PutBoolean("CubeStopper: ", cubeStop->Get());
}

void Manipulator::jiggle(bool jiggButton)
{
	if(jiggButton)
	{
		leftIntakeMotor->Set(ControlMode::PercentOutput, .8); //These are dummy values.//
		rightIntakeMotor->Set(ControlMode::PercentOutput, -.8);
		Wait(.2);
		leftIntakeMotor->Set(ControlMode::PercentOutput, -.8); //These are dummy values.//
		rightIntakeMotor->Set(ControlMode::PercentOutput, .6);
		Wait(.3);
		leftIntakeMotor->Set(ControlMode::PercentOutput, 0); //These are dummy values.//
		rightIntakeMotor->Set(ControlMode::PercentOutput, 0);
	}
}

void Manipulator::diffIntake(bool left, bool right)
{
	if(left) leftIntakeMotor->Set(ControlMode::PercentOutput, -.8);
	if(right) rightIntakeMotor->Set(ControlMode::PercentOutput, .8);
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
			//rightmanipPiston -> Set(DoubleSolenoid::kForward);
			Wait(.5);
			toggle = 0;
		}
		else
		{
			leftmanipPiston->Set(DoubleSolenoid::kReverse);
			//rightmanipPiston -> Set(DoubleSolenoid::kReverse);
			leftIntakeMotor->Set(ControlMode::PercentOutput, -.8);
			rightIntakeMotor->Set(ControlMode::PercentOutput, .6);
			Wait(.5);
			leftIntakeMotor->Set(ControlMode::PercentOutput, 0);
			rightIntakeMotor->Set(ControlMode::PercentOutput, 0);
			toggle = 1;
		}
	}
}

void Manipulator::setPos(bool pos)
{
	if(pos)
	{
		leftmanipPiston->Set(DoubleSolenoid::kForward);
		//rightmanipPiston->Set(DoubleSolenoid::kForward);
	}
	else
	{
		leftmanipPiston->Set(DoubleSolenoid::kReverse);
		//rightmanipPiston->Set(DoubleSolenoid::kReverse);
	}
}

/*
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
*/

void Manipulator:: AutoOuttake() //Outtake for (Dummy Value) seconds//
{
	leftIntakeMotor->Set(ControlMode::PercentOutput, -.8); //These are dummy values.//
	rightIntakeMotor->Set(ControlMode::PercentOutput, .5); //These are dummy values.//
	Wait(1);
	leftIntakeMotor->Set(ControlMode::PercentOutput, 0);
	rightIntakeMotor->Set(ControlMode::PercentOutput, 0);
}

