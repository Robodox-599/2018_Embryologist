/*
 * Lift.cpp
 *
 *  Created on: Jan 6, 2018
 *      Author: Admin
 */



#include "Lift.h"
//#include "WPILib.h"


Lift::Lift()
{
	frontRightLift = new TalonSRX(9);
	frontLeftLift = new TalonSRX(7);
	backRightLift = new TalonSRX(10);
	backLeftLift = new TalonSRX(6);

	lowerLimit = new DigitalInput(1);
	upperLimit  = new DigitalInput(0);

	leftLiftPiston = new Solenoid(1);
	rightLiftPiston = new Solenoid(2);

	leftClimbPiston = new Solenoid(3);
	rightClimbPiston = new Solenoid(1);

}

Lift::~Lift()
{
	delete frontRightLift;
	delete frontLeftLift;
	delete backRightLift;
	delete backLeftLift;
	delete lowerLimit;
	delete upperLimit;
	delete leftLiftPiston;
	delete rightLiftPiston;

	frontRightLift = nullptr;
	frontLeftLift = nullptr;
	backRightLift = nullptr;
	backLeftLift = nullptr;
	lowerLimit = nullptr;
	upperLimit = nullptr;
	leftLiftPiston = nullptr;
	rightLiftPiston = nullptr;
}

bool Lift::lowerLimitTester()
{
	return lowerLimit->Get();
}

bool Lift::upperLimitTester()
{
	return upperLimit->Get();
}
void Lift::liftRobot(float liftInput)
{
	if(liftInput > LIFT_DEADZONE && !upperLimit->Get())
	{
		frontRightLift->Set(ControlMode::PercentOutput, .5);
		frontLeftLift->Set(ControlMode::PercentOutput, .5);
		backRightLift->Set(ControlMode::PercentOutput, .5);
		backLeftLift->Set(ControlMode::PercentOutput, .5);
	}
	else if(liftInput < -LIFT_DEADZONE && !lowerLimit->Get())
	{
		frontRightLift->Set(ControlMode::PercentOutput, -.5);
		frontLeftLift->Set(ControlMode::PercentOutput, -.5);
		backRightLift->Set(ControlMode::PercentOutput, -.5);
		backLeftLift->Set(ControlMode::PercentOutput, -.5);
	}
	else
	{
		frontRightLift->Set(ControlMode::PercentOutput, 0);
		frontLeftLift->Set(ControlMode::PercentOutput, 0);
		backRightLift->Set(ControlMode::PercentOutput, 0);
		backLeftLift->Set(ControlMode::PercentOutput, 0);
	}
}

float Lift::getLeftLiftEnc()
{
	return frontLeftLift->GetSelectedSensorPosition(FeedbackDevice::QuadEncoder);
}

float Lift::getRightLiftEnc()
{
	return backRightLift->GetSelectedSensorPosition(FeedbackDevice::QuadEncoder);
}

void Lift::PistonLift(bool pistonButton)
{
	if(pistonButton == true)
	{
		leftLiftPiston->Set(true);
		rightLiftPiston->Set(true);
	}
}

void Lift::PistonClimb(bool climbButton)
{
	if(climbButton == true)
	{
		leftClimbPiston->Set(true);
		rightClimbPiston->Set(true);
	}
}
void Lift::liftAuto(float speed, float autoLiftInput)
{
	if(speed > 0)
	{
		while(getLeftLiftEnc() < autoLiftInput && getRightLiftEnc() < autoLiftInput)
		{
			frontRightLift->Set(ControlMode::PercentOutput, .5);
			frontLeftLift->Set(ControlMode::PercentOutput, .5);
			backRightLift->Set(ControlMode::PercentOutput, .5);
			backLeftLift->Set(ControlMode::PercentOutput, .5);
		}
		frontRightLift->Set(ControlMode::PercentOutput, 0);
		frontLeftLift->Set(ControlMode::PercentOutput, 0);
		backRightLift->Set(ControlMode::PercentOutput, 0);
		backLeftLift->Set(ControlMode::PercentOutput, 0);

}

	if(speed < 0)
	{
		while(getLeftLiftEnc() > autoLiftInput && getRightLiftEnc() > autoLiftInput)
		{
			frontRightLift->Set(ControlMode::PercentOutput, -.5);
			frontLeftLift->Set(ControlMode::PercentOutput, -.5);
			backRightLift->Set(ControlMode::PercentOutput, -.5);
			backLeftLift->Set(ControlMode::PercentOutput, -.5);
		}
		frontRightLift->Set(ControlMode::PercentOutput, 0);
		frontLeftLift->Set(ControlMode::PercentOutput, 0);
		backRightLift->Set(ControlMode::PercentOutput, 0);
		backLeftLift->Set(ControlMode::PercentOutput, 0);
	}

}

void Lift::resetLiftEncoder()
{
	frontRightLift->SetSelectedSensorPosition(0,0,0);
	frontLeftLift->SetSelectedSensorPosition(0,0,0);
	backRightLift->SetSelectedSensorPosition(0,0,0);
	backRightLift->SetSelectedSensorPosition(0,0,0);
}
