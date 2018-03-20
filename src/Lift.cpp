/*
 * Lift.cpp
 *
 *  Created on: Jan 6, 2018
 *      Author: Admin
 */
#include <Lift.h>
#include "WPILib.h"
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
	liftPiston->Set(DoubleSolenoid::kForward);

	ropeRelease = new DoubleSolenoid(2,3);
	ropeRelease->Set(DoubleSolenoid::kReverse);

	rungPiston = new DoubleSolenoid(6, 7);
	rungPiston->Set(DoubleSolenoid::kReverse);

	targetEnc = 0;
	currentLeftEnc = 0;
	currentRightEnc = 0;
	encErrorLeft = 0;
	encErrorRight = 0;
	canLift = false;
	canClimb = false;
	rungState = false;
	climbState = false;
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

void Lift::setLiftMotors(float speed)
{
	frontRightLift->Set(ControlMode::PercentOutput, (speed));
	frontLeftLift->Set(ControlMode::PercentOutput,  (speed));
	backRightLift->Set(ControlMode::PercentOutput,  (speed));
	backLeftLift->Set(ControlMode::PercentOutput,  (speed));
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
	if(canLift == false)
	{
		if(liftInput > LIFT_DEADZONE && (/*!upperLimit->Get() && */getRightLiftEnc() < MAX_LIFT_VAL-3000))
		{
//			frontRightLift->Set(ControlMode::PercentOutput, liftInput*(.9));
//			frontLeftLift->Set(ControlMode::PercentOutput,  liftInput*(.9));
//			backRightLift->Set(ControlMode::PercentOutput,  liftInput*(.9));
//			backLeftLift->Set(ControlMode::PercentOutput,  liftInput*(.9));
			setLiftMotors(liftInput*(.9));
		}
		else if(liftInput > LIFT_DEADZONE && (/*!upperLimit->Get() && */(getRightLiftEnc() > MAX_LIFT_VAL-3000)))//buffer range
		{
//			frontRightLift->Set(ControlMode::PercentOutput, liftInput*(.3));
//			frontLeftLift->Set(ControlMode::PercentOutput,  liftInput*(.3));
//			backRightLift->Set(ControlMode::PercentOutput,  liftInput*(.3));
//			backLeftLift->Set(ControlMode::PercentOutput,  liftInput*(.3));
			setLiftMotors(liftInput*(.3));
		}
		else if((liftInput < -LIFT_DEADZONE) && getLeftLiftEnc() > 0 &&!lowerLimit->Get() )//&& getRightLiftEnc() > 3000))
		{
//			frontRightLift->Set(ControlMode::PercentOutput,  -liftInput*(-.65));
//			frontLeftLift->Set(ControlMode::PercentOutput, -liftInput*(-.65));
//			backRightLift->Set(ControlMode::PercentOutput, -liftInput*(-.65));
//			backLeftLift->Set(ControlMode::PercentOutput, -liftInput*(-.65));
			setLiftMotors(-liftInput*(-.65));
		}
		else if((liftInput < -LIFT_DEADZONE) && getLeftLiftEnc() > 0 &&!lowerLimit->Get() && canClimb)//&& getRightLiftEnc() > 3000))
		{
//			frontRightLift->Set(ControlMode::PercentOutput,  -liftInput*(-1));
//			frontLeftLift->Set(ControlMode::PercentOutput, -liftInput*(-1));
//			backRightLift->Set(ControlMode::PercentOutput, -liftInput*(-1));
//			backLeftLift->Set(ControlMode::PercentOutput, -liftInput*(-1));
			setLiftMotors(-liftInput*(-1));
		}
//		else if (liftInput < -LIFT_DEADZONE && (!lowerLimit->Get() && getRightLiftEnc() < 3000))//buffer range
//		{
//			frontRightLift->Set(ControlMode::PercentOutput, -liftInput*(-.3));
//			frontLeftLift->Set(ControlMode::PercentOutput,  -liftInput*(-.3));
//			backRightLift->Set(ControlMode::PercentOutput,  -liftInput*(-.3));
//			backLeftLift->Set(ControlMode::PercentOutput,  -liftInput*(-.3));
//		}
		else
		{
//			frontRightLift->Set(ControlMode::PercentOutput, .05);
//			frontLeftLift->Set(ControlMode::PercentOutput, .05);
//			backRightLift->Set(ControlMode::PercentOutput, .05);
//			backLeftLift->Set(ControlMode::PercentOutput, .05);
			setLiftMotors(.05);
		}
	}
	else
	{
		Wait(.5);
//		frontRightLift->Set(ControlMode::PercentOutput, .05);
//		frontLeftLift->Set(ControlMode::PercentOutput, .05);
//		backRightLift->Set(ControlMode::PercentOutput, .05);
//		backLeftLift->Set(ControlMode::PercentOutput, .05);
		setLiftMotors(.05);
	}
	//if(lowerLimit->Get()) resetLiftEncoder();
}

/*
void Lift::doClimb(bool climbButton)
{
	if(climbButton && !climbState)
	{
		Wait(0.5);
		climbState = true;
	}
	if(climbButton && climbState)
	{
		Wait(0.5);
		climbState = false;
	}
}
void Lift::autoClimb(bool autoClimbA, bool autoClimbB)
{
	while(autoClimbA && autoClimbB)
	{
		while(lowerLimit->Get() == false)
		{
			frontRightLift->Set(ControlMode::PercentOutput,  -.5);
			frontLeftLift->Set(ControlMode::PercentOutput, -.5);
			backRightLift->Set(ControlMode::PercentOutput, -.5);
			backLeftLift->Set(ControlMode::PercentOutput, -.5);
		}
		frontRightLift->Set(ControlMode::PercentOutput, .05);
		frontLeftLift->Set(ControlMode::PercentOutput, .05);
		backRightLift->Set(ControlMode::PercentOutput, .05);
		backLeftLift->Set(ControlMode::PercentOutput, .05);
		liftPiston->Set(DoubleSolenoid::kReverse);
		Wait(30);
	}
}
void Lift::heightPosition(bool positionA, bool positionB)
{
	if(positionA)
	{
		frontRightLift->Set(ControlMode::PercentOutput,  .3);
		frontLeftLift->Set(ControlMode::PercentOutput, .3);
		backRightLift->Set(ControlMode::PercentOutput, .3);
		backLeftLift->Set(ControlMode::PercentOutput, .3);
		Wait(.2);
		frontRightLift->Set(ControlMode::PercentOutput,  0);
		frontLeftLift->Set(ControlMode::PercentOutput, 0);
		backRightLift->Set(ControlMode::PercentOutput, 0);
		backLeftLift->Set(ControlMode::PercentOutput, 0);
	}
	if(positionB && !upperLimit->Get())
	{
		while(!upperLimit->Get())
		{
			frontRightLift->Set(ControlMode::PercentOutput,  .35);
			frontLeftLift->Set(ControlMode::PercentOutput, .35);
			backRightLift->Set(ControlMode::PercentOutput, .35);
			backLeftLift->Set(ControlMode::PercentOutput, .35);
		}
	}
}
*/

void Lift::releaseRope(bool release, bool reset)
{
	if(release)
	{
		ropeRelease->Set(DoubleSolenoid::kForward);
		canClimb = true;
	}
	if(reset)
	{
		ropeRelease->Set(DoubleSolenoid::kReverse);
		canClimb = false;
	}
}
float Lift::getLeftLiftEnc()
{
	return -frontLeftLift->GetSelectedSensorPosition(FeedbackDevice::QuadEncoder);
}

float Lift::getRightLiftEnc()
{
	return backRightLift->GetSelectedSensorPosition(FeedbackDevice::QuadEncoder);
}

float Lift::getAvgLiftEnc()
{
	return ((-( frontLeftLift->GetSelectedSensorPosition(FeedbackDevice::QuadEncoder))+( backRightLift->GetSelectedSensorPosition(FeedbackDevice::QuadEncoder)))/2);
}

//unused
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
		liftPiston->Set(DoubleSolenoid::kReverse);
		canLift = true;
	}
	if(disengage == true)
	{
		liftPiston->Set(DoubleSolenoid::kForward);
		canLift = false;

	}
}

void Lift::rungDeploy(bool deployButton, bool otherButton)
{
	if(deployButton && canLift)
	{
		rungPiston->Set(DoubleSolenoid::kForward);
		rungState = true;
	}
	else if(otherButton && canLift)
	{
		rungPiston->Set(DoubleSolenoid::kReverse);
		rungState = false;
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

//unused
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

//unused
void Lift::fixErrorLeft(float error)
{
	float liftFactor = (error/1000.0);

	if(liftFactor > .5) liftFactor = .5;
	if(liftFactor < -.5) liftFactor = -.5;

	frontLeftLift->Set(ControlMode::PercentOutput, liftFactor);
	backLeftLift->Set(ControlMode::PercentOutput, liftFactor);
	SmartDashboard::PutNumber("Left Lift Factor: ",liftFactor);
}

//unused
void Lift::fixErrorRight(float error)
{
	float liftFactor = (error/1000.0);

	if(liftFactor > .5) liftFactor = .5;
	if(liftFactor < -.5) liftFactor = -.5;

	frontRightLift->Set(ControlMode::PercentOutput, liftFactor);
	backRightLift->Set(ControlMode::PercentOutput, liftFactor);
	SmartDashboard::PutNumber("Right Lift Factor: ",liftFactor);
}

void Lift::stopLift()
{
	frontRightLift->Set(ControlMode::PercentOutput, 0);
	backRightLift->Set(ControlMode::PercentOutput, 0);
	frontLeftLift->Set(ControlMode::PercentOutput, 0);
	backLeftLift->Set(ControlMode::PercentOutput, 0);
}
