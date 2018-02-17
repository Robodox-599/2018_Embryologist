/*
 * Lift.cpp
 *
 *  Created on: Jan 6, 2018
 *      Author: Admin
 */



#include "Lift.h"
//#include "WPILib.h"
#include "ctre/Phoenix.h"


Lift::Lift()
{
	frontRightLift = new TalonSRX(9);
	frontLeftLift = new TalonSRX(7);
	backRightLift = new TalonSRX(10);
	backLeftLift = new TalonSRX(6);

	lowerLimit = new DigitalInput(1);
	upperLimit  = new DigitalInput(0);

	liftPiston = new DoubleSolenoid(0,1);

	//leftClimbPiston = new Solenoid(3);
	//rightClimbPiston = new Solenoid(1);

	targetEnc = 0;
	currentLeftEnc = 0;
	currentRightEnc = 0;
	encErrorLeft = 0;
	encErrorRight = 0;
}

Lift::~Lift()
{
	delete frontRightLift;
	delete frontLeftLift;
	delete backRightLift;
	delete backLeftLift;
	delete lowerLimit;
	delete upperLimit;
	delete liftPiston;

	frontRightLift = nullptr;
	frontLeftLift = nullptr;
	backRightLift = nullptr;
	backLeftLift = nullptr;
	lowerLimit = nullptr;
	upperLimit = nullptr;
	liftPiston = nullptr;
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
		frontRightLift->Set(ControlMode::PercentOutput, liftInput*(.5));
		frontLeftLift->Set(ControlMode::PercentOutput,  liftInput*(.5));
		backRightLift->Set(ControlMode::PercentOutput,  liftInput*(.5));
		backLeftLift->Set(ControlMode::PercentOutput,  liftInput*(.5));
	}
	else if(liftInput < -LIFT_DEADZONE && !lowerLimit->Get())
	{
		frontRightLift->Set(ControlMode::PercentOutput,  -liftInput*(-.5));
		frontLeftLift->Set(ControlMode::PercentOutput, -liftInput*(-.5));
		backRightLift->Set(ControlMode::PercentOutput, -liftInput*(-.5));
		backLeftLift->Set(ControlMode::PercentOutput, -liftInput*(-.5));
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

float Lift::getAvgLiftEnc()
{
	return ((-( frontLeftLift->GetSelectedSensorPosition(FeedbackDevice::QuadEncoder))+( backRightLift->GetSelectedSensorPosition(FeedbackDevice::QuadEncoder)))/2);
}


void Lift::CalibrateLift(bool calibrateButton, bool safeCalibrate)
{
	if (calibrateButton==true && safeCalibrate == true)
	{
		while (!lowerLimit->Get())
		{
			frontRightLift->Set(ControlMode::PercentOutput,  (-.1));
			frontLeftLift->Set(ControlMode::PercentOutput, (-.1));
			backRightLift->Set(ControlMode::PercentOutput, (-.1));
			backLeftLift->Set(ControlMode::PercentOutput, (-.1));
		}
		frontLeftLift->SetSelectedSensorPosition(0,0,0);
		backRightLift->SetSelectedSensorPosition(0,0,0);
	}
}

void Lift::PistonLift(bool pistonButton, bool disengage)
{
	if(pistonButton == true)
	{
		liftPiston->Set(DoubleSolenoid::kForward);
	}
	if(disengage == true)
	{
		liftPiston->Set(DoubleSolenoid::kReverse);

	}
}

/*
void Lift::PistonClimb(bool climbButton)
{
	if(climbButton == true)
	{
		leftClimbPiston->Set(true);
		rightClimbPiston->Set(true);
	}
}
*/
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
	frontLeftLift->SetSelectedSensorPosition(0,0,0);
	backRightLift->SetSelectedSensorPosition(0,0,0);
}

//Max rightEnc val: approx. 27247
void Lift::setHeightEnc(float joystick)
{
	//if(getRightLiftEnc() < MAX_LIFT_VAL && getRightLiftEnc() >= 0)
	//{
		targetEnc += joystick*(MAX_LIFT_VAL/250);
	//}
}

void Lift::doLift()
{
	currentLeftEnc = -getLeftLiftEnc();
	currentRightEnc = currentLeftEnc;//getRightLiftEnc();
	encErrorRight = targetEnc - currentRightEnc;
	encErrorLeft = targetEnc - currentLeftEnc;
	fixErrorLeft(encErrorLeft);
	fixErrorRight(encErrorRight);
	SmartDashboard::PutNumber("Current Left Enc: ",currentLeftEnc);
	SmartDashboard::PutNumber("Current Right Enc: ",currentRightEnc);
	SmartDashboard::PutNumber("Error Right: ",encErrorRight);
	SmartDashboard::PutNumber("Error Left: ",encErrorLeft);
}

void Lift::fixErrorLeft(float error)
{
	float liftFactor = (error/1000.0);

	if(liftFactor > .5) liftFactor = .5;
	if(liftFactor < -.5) liftFactor = -.5;

	frontLeftLift->Set(ControlMode::PercentOutput, liftFactor);
	backLeftLift->Set(ControlMode::PercentOutput, liftFactor);
	SmartDashboard::PutNumber("Left Lift Factor: ",liftFactor);
}

void Lift::fixErrorRight(float error)
{
	float liftFactor = (error/1000.0);

	if(liftFactor > .5) liftFactor = .5;
	if(liftFactor < -.5) liftFactor = -.5;

	frontRightLift->Set(ControlMode::PercentOutput, liftFactor);
	backRightLift->Set(ControlMode::PercentOutput, liftFactor);
	SmartDashboard::PutNumber("Right Lift Factor: ",liftFactor);
}
