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
    leftIntakeMotor = new TalonSRX(5);
    rightIntakeMotor = new TalonSRX(8);
    liftIntakeMotor = new TalonSRX(11); //These are dummy values.//
    leftmanipPiston = new DoubleSolenoid (2,3);
    //rightmanipPiston = new DoubleSolenoid (0,2);
    cubeStop = new DigitalInput(2); //These are dummy values.//
    toggle = 1;
    potAngle = -1;
    pot = new AnalogPotentiometer(3, 200, 0);

    currentPivot = 0;
	targetPivot = 30;
	errorPivot = 0;
}

Manipulator::~Manipulator() //deletes all booleans, digital inputs, and CANTalons to "restart" them//
{
	leftIntakeMotor = nullptr;
	rightIntakeMotor = nullptr;
	liftIntakeMotor = nullptr;
	leftmanipPiston = nullptr;
	//rightmanipPiston = nullptr;
	cubeStop = nullptr;
	delete leftIntakeMotor;
	delete rightIntakeMotor;
	delete liftIntakeMotor;
	delete cubeStop;
}

void Manipulator::intakeOuttakeCube(bool intake, bool outtake, float mod) //intakes the actual cube with/without limit switch + outtake//
{
	if (intake)// && cubeStop->Get() == false)
	{
		leftIntakeMotor->Set(ControlMode::PercentOutput, -.9);
		rightIntakeMotor->Set(ControlMode::PercentOutput, .65);
	}

	else if (outtake)
	{
		//speed modified by the z axis on the Atk3. Bound from .6 to 1
		leftIntakeMotor->Set(ControlMode::PercentOutput, .2*(-mod+4));//75 or 6
		rightIntakeMotor->Set(ControlMode::PercentOutput, -.2*(-mod+4));//75 or 6
	}
	else if(cubeStop->Get())
	{
		leftIntakeMotor->Set(ControlMode::PercentOutput, -.1);
		rightIntakeMotor->Set(ControlMode::PercentOutput, .1);
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
		leftIntakeMotor->Set(ControlMode::PercentOutput, .5);
		rightIntakeMotor->Set(ControlMode::PercentOutput, -.5);
		Wait(.1);
		leftIntakeMotor->Set(ControlMode::PercentOutput, -.8);
		rightIntakeMotor->Set(ControlMode::PercentOutput, .5);
		Wait(.3);
		leftIntakeMotor->Set(ControlMode::PercentOutput, 0);
		rightIntakeMotor->Set(ControlMode::PercentOutput, 0);
	}
}

double Manipulator::potVal()
{
	return pot->Get();
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

void Manipulator::intakePosition(bool posButton, bool unPos) //piston folds in/folds out intake/ outtake arms//
{
	if(posButton)
	{
//		if(toggle == 1)
//		{
//			leftmanipPiston->Set(DoubleSolenoid::kForward);
//			//rightmanipPiston -> Set(DoubleSolenoid::kForward);
//			Wait(.5);
//			toggle = 0;
//		}
//		else
//		{
//			leftmanipPiston->Set(DoubleSolenoid::kReverse);
//			//rightmanipPiston -> Set(DoubleSolenoid::kReverse);
//			leftIntakeMotor->Set(ControlMode::PercentOutput, -.8);
//			rightIntakeMotor->Set(ControlMode::PercentOutput, .6);
//			Wait(.5);
//			leftIntakeMotor->Set(ControlMode::PercentOutput, 0);
//			rightIntakeMotor->Set(ControlMode::PercentOutput, 0);
//			toggle = 1;
//		}
		leftmanipPiston->Set(DoubleSolenoid::kForward);
	}
	if(unPos)
	{
		leftmanipPiston->Set(DoubleSolenoid::kReverse);
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
	leftIntakeMotor->Set(ControlMode::PercentOutput, -.8);
	rightIntakeMotor->Set(ControlMode::PercentOutput, .5);
	Wait(1);
	leftIntakeMotor->Set(ControlMode::PercentOutput, 0);
	rightIntakeMotor->Set(ControlMode::PercentOutput, 0);
}


void Manipulator::intakeAngle(float zAxis)
{
	//potAngle = 0;
	if(-zAxis == -1)
	{
		if(pot->Get() > 20) liftIntakeMotor->Set(ControlMode::PercentOutput, .5);
		else liftIntakeMotor->Set(ControlMode::PercentOutput, 0);
	}
	else if(-zAxis == 1)
	{
		if(pot->Get() < 180) liftIntakeMotor->Set(ControlMode::PercentOutput, -.5);
		else liftIntakeMotor->Set(ControlMode::PercentOutput, 0);
	}
	else if(-zAxis < 1 && -zAxis > -1)
	{
		if(pot->Get() < 80) liftIntakeMotor->Set(ControlMode::PercentOutput, -.5);
		else if(pot->Get() > 120) liftIntakeMotor->Set(ControlMode::PercentOutput, .5);
		else liftIntakeMotor->Set(ControlMode::PercentOutput, .02);
	}
}

void Manipulator:: liftIntake (bool Lift, bool noLift, bool midLift, bool finalLift)
{
	if (Lift)
	{
		while(pot->Get() > 50) liftIntakeMotor->Set(ControlMode::PercentOutput, -.4);
		liftIntakeMotor->Set(ControlMode::PercentOutput, .1);
		SmartDashboard::PutString("Intake Mode: ", "Climb");
		//liftIntakeMotor->Set(ControlMode::PercentOutput,-.4); //These are dummy values.//
    }
	if (finalLift)
	{
		while(pot->Get() > 20) liftIntakeMotor->Set(ControlMode::PercentOutput, -.4);
		liftIntakeMotor->Set(ControlMode::PercentOutput, .1);
		SmartDashboard::PutString("Intake Mode: ", "Final");
		//liftIntakeMotor->Set(ControlMode::PercentOutput,-.4); //These are dummy values.//
	}
	else if (noLift)
	{
		while(pot->Get() < 100) liftIntakeMotor->Set(ControlMode::PercentOutput, .3);
		liftIntakeMotor->Set(ControlMode::PercentOutput, -.15);
		SmartDashboard::PutString("Intake Mode: ", "Cube");
		//liftIntakeMotor->Set(ControlMode::PercentOutput,.4); //These are dummy values.//
	}
	else if(midLift)
	{
		while(pot->Get() < 70 || pot->Get() > 80)
		{
			if(pot->Get() < 80) liftIntakeMotor->Set(ControlMode::PercentOutput, .4);
			else if(pot->Get() > 70) liftIntakeMotor->Set(ControlMode::PercentOutput, -.4);
		}
		liftIntakeMotor->Set(ControlMode::PercentOutput, -.15);
		SmartDashboard::PutString("Intake Mode: ", "Shoot");
	}
	else if(pot->Get() < 40)
	{
		liftIntakeMotor->Set(ControlMode::PercentOutput,0);
	}
	else if(pot->Get() > 105)
	{
		liftIntakeMotor->Set(ControlMode::PercentOutput,0);
	}
//	else if(cubeStop->Get())
//	{
//		liftIntakeMotor->Set(ControlMode::PercentOutput,-.2);
//	}
	else
	{
		liftIntakeMotor->Set(ControlMode::PercentOutput,-.15);
	}
}


void Manipulator::pivotIntake(bool down, bool shoot, bool up)
{
	if(down) targetPivot = 100;
	if(shoot) targetPivot = 40;
	if(up) targetPivot = 27;

	currentPivot = pot->Get();
	errorPivot = targetPivot-currentPivot;
	fixPivotError(errorPivot);
}

void Manipulator::fixPivotError(float error)
{
	float movePivot = (error/100);

	if(movePivot > .6) movePivot = .5;
	if(movePivot < -.6) movePivot = -.6;

	liftIntakeMotor->Set(ControlMode::PercentOutput,movePivot);
	SmartDashboard::PutNumber("Pivot Val:", movePivot);
}
