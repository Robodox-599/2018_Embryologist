/*
 * Drive.cpp
 *
 *  Created on: Jan 6, 2018
 *      Author: Admin
 */
#include "Drive.h"

Drive::Drive()
{
	//navX = new AHRS(SPI::Port::kMXP);

	frontLeftMotor = new CANTalon(Drive_Front_Left_Motor_Channel);
	rearLeftMotor = new Talon(Drive_Rear_Left_Motor_Channel);
	frontRightMotor = new Talon(Drive_Front_Right_Motor_Channel);
	rearRightMotor = new Talon(Drive_Rear_Right_Motor_Channel);

	//shifter = new DoubleSolenoid(Left_Shifter_Solenoid_Channel, Right_Shifter_Solenoid_Channel);
	//shifter->Set(DoubleSolenoid::kReverse);

	//navX->ZeroYaw();

	//gyroValue = navX->GetYaw();

	fwdSpeed = 0;
	turnSpeed = 0;
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

//group left motors
void Drive::updateLeftMotors(float speed)
{
	frontLeftMotor->Set(-speed);
	rearLeftMotor->Set(-speed);
}

//group right motors
void Drive::updateRightMotors(float speed)
{
	frontRightMotor->Set(speed);
	rearRightMotor->Set(speed);
}

void Drive::setFwdSpeed(float fwd)
{
	if(fwd >= abs(DEADZONE))
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
	if(turn >= abs(DEADZONE))
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

	updateRightMotors(fwdSpeed - turnSpeed);
	updateLeftMotors(fwdSpeed + turnSpeed);
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

void Drive::shift(bool toggle)
{
	if(Shifter_Button)
	{
		if(toggle == 1)
		{
			shifter->Set(DoubleSolenoid::kReverse);
			toggle = 0;
		}
		else
		{
			shifter->Set(DoubleSolenoid::kForward);
			toggle = 1;
		}
	}
}
*/
//gives encoder values
float Drive::getLeftEnc()
{
	return frontLeftMotor->GetEncPosition();
}

float Drive::getRightEnc()
{
	return frontRightMotor->GetEncPosition();
}
