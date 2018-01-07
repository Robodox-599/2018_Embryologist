/*
 * Drive.cpp
 *
 *  Created on: Jan 6, 2018
 *      Author: Admin
 */
#include "Drive.h"

Drive::Drive()
{
	frontLeftMotor = new CANTalon(Drive_Front_Left_Motor_Channel);
	rearLeftMotor = new CANTalon(Drive_Rear_Left_Motor_Channel);
	frontRightMotor = new CANTalon(Drive_Front_Right_Motor_Channel);
	rearRightMotor = new CANTalon(Drive_Rear_Right_Motor_Channel);
}

Drive::~Drive()
{
	delete frontLeftMotor;
	delete rearLeftMotor;
	delete frontRightMotor;
	delete rearRightMotor;

	frontLeftMotor = nullptr;
	rearLeftMotor = nullptr;
	frontRightMotor = nullptr;
	rearRightMotor = nullptr;
}

void updateLeftMotors(float speed);
{
	frontLeftMotor->Set(-speed);
	rearLeftMotor->Set(-speed);
}

void updateRightMotors(float speed);
{
	frontRightMotor->Set(speed);
	rearRightMotor->Set(speed);
}

void setFwdSpeed(float fwd)
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

void setTurnSpeed(float turn)
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

void drive(float xAxis, float yAxis)
{
	setFwdSpeed(yAxis);
	setTurnSpeed(xAxis);

	updateRightMotors(fwdSpeed - turnSpeed);
	updateLeftMotors(fwdSpeed + turnSpeed);
}
