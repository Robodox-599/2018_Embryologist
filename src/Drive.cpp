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

	shifter = new DoubleSolenoid(Shifter_Solenoid_Channel_A, Shifter_Solenoid_Channel_B);
	//rightShifter = new DoubleSolenoid(Right_Shifter_Solenoid_Channel_A, Right_Shifter_Solenoid_Channel_B);

	shifter->Set(DoubleSolenoid::kReverse);
	//rightShifter->Set(DoubleSolenoid::kReverse);
	//navX->ZeroYaw();

	//gyroValue = navX->GetYaw();

	fwdSpeed = 0;
	turnSpeed = 0;
	toggle = 0;
	velocityFwd = 0;
	velocityTurn = 0;
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

void Drive::PIDset()
{
	//EMMA LOW GEAR
	rearLeftMotor->Config_kF(0, 0.314, 10);
	rearLeftMotor->Config_kP(0, 0, 10);
	rearLeftMotor->Config_kI(0, 0, 10);
	rearLeftMotor->Config_kD(0, 0, 10);

	rearRightMotor->Config_kF(0, 0.314, 10);
	rearRightMotor->Config_kP(0, 0, 10);
	rearRightMotor->Config_kI(0, 0, 10);
	rearRightMotor->Config_kD(0, 0, 10);

	//MOD
	/*frontLeftMotor->Config_kF(0, 1.7, 10);
	frontLeftMotor->Config_kP(0, 2.25, 10);
	frontLeftMotor->Config_kI(0, 0.01, 10);
	frontLeftMotor->Config_kD(0, 0, 10);
	rearRightMotor->Config_kF(0, 1.7, 10);
	rearRightMotor->Config_kP(0, 2.25, 10);
	rearRightMotor->Config_kI(0, 0.01, 10);
	rearRightMotor->Config_kD(0, 0, 10);*/

	rearLeftMotor->ConfigSelectedFeedbackSensor(QuadEncoder, 0, 10);
	rearLeftMotor->SetSensorPhase(false);
	rearLeftMotor->SetInverted(true);
	frontLeftMotor->SetInverted(true);

	rearRightMotor->ConfigSelectedFeedbackSensor(QuadEncoder, 0, 10);
	rearRightMotor->SetSensorPhase(true);
	rearRightMotor->SetInverted(false);
	frontRightMotor->SetInverted(false);
}

void Drive::velocityDrive(float xAxis, float yAxis)
{
	joystickFwdSet(yAxis);
	joystickTurnSet(xAxis);

	rearLeftMotor->Set(ControlMode::Velocity, velocityFwd + velocityTurn);
	frontLeftMotor->Set(ControlMode::Follower, Drive_Rear_Left_Motor_Channel);

	rearRightMotor->Set(ControlMode::Velocity, velocityFwd - velocityTurn);
	frontRightMotor->Set(ControlMode::Follower, Drive_Rear_Right_Motor_Channel);

	SmartDashboard::PutNumber("Encoder Right", rearLeftMotor->GetSelectedSensorPosition(FeedbackDevice::QuadEncoder));
	SmartDashboard::PutNumber("Encoder Velocity Right", rearLeftMotor->GetSelectedSensorVelocity(FeedbackDevice::QuadEncoder));
	SmartDashboard::PutNumber("PID Error Left", rearLeftMotor->GetClosedLoopError(0));
	SmartDashboard::PutNumber("Motor Output Percent Front Left", frontLeftMotor->GetMotorOutputPercent());
	SmartDashboard::PutNumber("Motor Output Percent Rear Left", rearLeftMotor->GetMotorOutputPercent());

	SmartDashboard::PutNumber("Velocity Forward", velocityFwd);
	SmartDashboard::PutNumber("Velocity Turn", velocityTurn);

	SmartDashboard::PutNumber("Motor Output Percent Front Right", frontRightMotor->GetMotorOutputPercent());
	SmartDashboard::PutNumber("Motor Output Percent Rear Right", rearRightMotor->GetMotorOutputPercent());
	SmartDashboard::PutNumber("PID Error Right", rearRightMotor->GetClosedLoopError(0));
	SmartDashboard::PutNumber("Encoder Velocity Left", rearRightMotor->GetSelectedSensorVelocity(FeedbackDevice::QuadEncoder));
	SmartDashboard::PutNumber("Encoder Left", rearRightMotor->GetSelectedSensorPosition(FeedbackDevice::QuadEncoder));
}

void Drive::joystickFwdSet(float joystickY)
{
	if(joystickY > 0.1)
	{
		velocityFwd = (joystickY+0.1)*(1/.9)*254*12.82;
	}
	else if(joystickY < -0.1)
	{
		velocityFwd = (joystickY-0.1)*(1/.9)*254*12.82;
	}
	else
	{
		velocityFwd = 0;
	}
}

void Drive::joystickTurnSet(float joystickX)
{
	if(joystickX > 0.1)
	{
		velocityTurn = (joystickX+0.1)*(1/.9)*254*12.82/4;
	}
	else if(joystickX < -0.1)
	{
		velocityTurn = (joystickX-0.1)*(1/.9)*254*12.82/4;
	}
	else
	{
		velocityTurn = 0;
	}
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
			shifter->Set(DoubleSolenoid::kReverse);
			//rightShifter->Set(DoubleSolenoid::kReverse);
			Wait(.2);
			toggle = 0;
		}
		else
		{
			shifter->Set(DoubleSolenoid::kForward);
			//rightShifter->Set(DoubleSolenoid::kForward);
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
