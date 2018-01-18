/*
 * Lift.cpp
 *
 *  Created on: Jan 6, 2018
 *      Author: Admin
 */



#include "Lift.h"


Lift::Lift()
{
	frontRightLift = new TalonSRX(3);
	frontLeftLift = new TalonSRX(2);
	backRightLift = new TalonSRX(5);
	backLeftLift = new TalonSRX(1);

	lowerLimit = new DigitalInput(1);
	upperLimit = new DigitalInput(0);

}

Lift::~Lift()
{
	delete frontRightLift;
	delete frontLeftLift;
	delete backRightLift;
	delete backLeftLift;
	delete lowerLimit;
	delete upperLimit;

	frontRightLift = nullptr;
	frontLeftLift = nullptr;
	backRightLift = nullptr;
	backLeftLift = nullptr;
	lowerLimit = nullptr;
	upperLimit = nullptr;
}

void Lift::liftRobot(float liftInput)
{
	if(liftInput > LIFT_DEADZONE && upperLimit == false)
	{
		frontRightLift->Set(ControlMode::PercentOutput, .5);
		frontLeftLift->Set(ControlMode::PercentOutput, .5);
		backRightLift->Set(ControlMode::PercentOutput, .5);
		backLeftLift->Set(ControlMode::PercentOutput, .5);
	}
	else if(liftInput < LIFT_DEADZONE && lowerLimit == false)
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



