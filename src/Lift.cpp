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
	return ((( frontLeftLift->GetSelectedSensorPosition(FeedbackDevice::QuadEncoder))+( backRightLift->GetSelectedSensorPosition(FeedbackDevice::QuadEncoder)))/2);
}


void Lift::CalibrateLift(bool calibrateButton)
{
	if (calibrateButton==true)
	{
		while (!lowerLimit->Get())
		{
			frontRightLift->Set(ControlMode::PercentOutput,  (-.2));
			frontLeftLift->Set(ControlMode::PercentOutput, (-.2));
			backRightLift->Set(ControlMode::PercentOutput, (-.2));
			backLeftLift->Set(ControlMode::PercentOutput, (-.2));
		}
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
	frontRightLift->SetSelectedSensorPosition(0,0,0);
	frontLeftLift->SetSelectedSensorPosition(0,0,0);
	backRightLift->SetSelectedSensorPosition(0,0,0);
	backRightLift->SetSelectedSensorPosition(0,0,0);
}
