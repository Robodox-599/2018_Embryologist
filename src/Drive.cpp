/*
 * Drive.cpp
 *
 *  Created on: Jan 6, 2018
 *      Author: Admin
 */
#include "Drive.h"
//
Drive::Drive()
{
	//navX = new AHRS(SPI::Port::kMXP);

	frontLeftMotor = new TalonSRX(Drive_Front_Left_Motor_Channel);
	rearLeftMotor = new TalonSRX(Drive_Rear_Left_Motor_Channel);
	frontRightMotor = new TalonSRX(Drive_Front_Right_Motor_Channel);
	rearRightMotor = new TalonSRX(Drive_Rear_Right_Motor_Channel);

	leftShifter = new DoubleSolenoid(Left_Shifter_Solenoid_Channel_A, Left_Shifter_Solenoid_Channel_B);
	rightShifter = new DoubleSolenoid(Right_Shifter_Solenoid_Channel_A, Right_Shifter_Solenoid_Channel_B);

	leftShifter->Set(DoubleSolenoid::kReverse);
	rightShifter->Set(DoubleSolenoid::kReverse);
	//navX->ZeroYaw();

	//gyroValue = navX->GetYaw();

	fwdSpeed = 0;
	turnSpeed = 0;
	toggle = 0;
}

Drive::~Drive()
{
	delete frontLeftMotor;
	delete rearLeftMotor;
	delete frontRightMotor;
	delete rearRightMotor;

	//delete shifter;
	//delete navX;

	frontLeftMotor = nullptr;
	rearLeftMotor = nullptr;
	frontRightMotor = nullptr;
	rearRightMotor = nullptr;

	//shifter = nullptr;
	//navX = nullptr;
}

bool Drive::smartTest()
{
	return true;
}

//group left motors
void Drive::updateLeftMotors(float speed)
{
	frontLeftMotor->Set(ControlMode::PercentOutput, -speed);
	rearLeftMotor->Set(ControlMode::PercentOutput, -speed);
}

//group right motors
void Drive::updateRightMotors(float speed)
{
	frontRightMotor->Set(ControlMode::PercentOutput, speed);
	rearRightMotor->Set(ControlMode::PercentOutput, speed);
}

void Drive::setFwdSpeed(float fwd)
{
	if(fwd >= DEADZONE || fwd <= -DEADZONE)
	{
		fwdSpeed = fwd;
	}
	else
	{
		fwdSpeed = 0;
	}
}

void Drive::setTurnSpeed(float turn)
{
	if(turn >= DEADZONE || turn <= -DEADZONE)
	{
		turnSpeed = turn;
	}
	else
	{
		turnSpeed = 0;
	}
}

void Drive::drive(float xAxis, float yAxis)
{
	setFwdSpeed(yAxis);
	setTurnSpeed(xAxis);

	//driveStraight(yAxis, xAxis);

	updateRightMotors(fwdSpeed + turnSpeed);
	updateLeftMotors(fwdSpeed - turnSpeed);
}
/*
void Drive::driveStraight(float fwdVal, float turnVal)
{
	if(fwdVal > DEADZONE && turnVal <= DEADZONE)
	{
		gyroValue = navX->GetYaw();
		if(gyroValue > 1.5)
		{

		}
		if(gyroValue < -1.5)
		{

		}
	}
	else
	{
		gyroValue = navX->ZeroYaw;
	}
}
*/
void Drive::shift(int shifter_Button)
{
	if(shifter_Button)
	{
		if(toggle == 1)
		{
			leftShifter->Set(DoubleSolenoid::kReverse);
			rightShifter->Set(DoubleSolenoid::kReverse);
			Wait(.2);
			toggle = 0;
		}
		else
		{
			leftShifter->Set(DoubleSolenoid::kForward);
			rightShifter->Set(DoubleSolenoid::kForward);
			Wait(.2);
			toggle = 1;
		}
	}
}

//gives encoder values
float Drive::getLeftEnc()
{
	return frontLeftMotor->GetSelectedSensorPosition(FeedbackDevice::QuadEncoder);
}

float Drive::getRightEnc()
{
	return rearRightMotor->GetSelectedSensorPosition(FeedbackDevice::QuadEncoder);
}

void Drive::resetEncoder()
{
	frontLeftMotor->SetSelectedSensorPosition(0,0,0);
	rearRightMotor->SetSelectedSensorPosition(0,0,0);
}

