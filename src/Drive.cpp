/*
 * Drive.cpp
 *
 *  Created on: Jan 6, 2018
 *      Author: Admin
 */
#include <Drive.h>
//
Drive::Drive()
{
	//navX = new AHRS(SPI::Port::kMXP);

	frontLeftMotor = new TalonSRX(Drive_Front_Left_Motor_Channel);
	rearLeftMotor = new TalonSRX(Drive_Rear_Left_Motor_Channel);
	frontRightMotor = new TalonSRX(Drive_Front_Right_Motor_Channel);
	rearRightMotor = new TalonSRX(Drive_Rear_Right_Motor_Channel);

	pGyon = new PigeonIMU(frontLeftMotor);

	shifter = new DoubleSolenoid(Shifter_Solenoid_Channel_A, Shifter_Solenoid_Channel_B);
	//rightShifter = new DoubleSolenoid(Right_Shifter_Solenoid_Channel_A, Right_Shifter_Solenoid_Channel_B);

	shifter->Set(DoubleSolenoid::kReverse);
	//rightShifter->Set(DoubleSolenoid::kReverse);
	//navX->ZeroYaw();

	//gyroValue = navX->GetYaw();
	pGyon->SetYaw(0, 0);
	pGyon->GetYawPitchRoll(ypr);
	refAngle = 0;
	fwdSpeed = 0;
	turnSpeed = 0;
	toggle = 0;
	velocityFwd = 0;
	velocityTurn = 0;
	gyroError = 0;
	targetHeading = 0;
	currentHeading = ypr[0];
	gyroTurnSpeed = 0;
	SmartDashboard::PutNumber("kF", 0);
	SmartDashboard::PutNumber("kP", 0);
	SmartDashboard::PutNumber("kI", 0);
	SmartDashboard::PutNumber("kD", 0);
	SmartDashboard::PutNumber("Velocity", 0);
}

Drive::~Drive()
{
	delete frontLeftMotor;
	delete rearLeftMotor;
	delete frontRightMotor;
	delete rearRightMotor;

	delete pGyon;

	//delete shifter;
	//delete navX;

	frontLeftMotor = nullptr;
	rearLeftMotor = nullptr;
	frontRightMotor = nullptr;
	rearRightMotor = nullptr;

	pGyon = nullptr;

	//shifter = nullptr;
	//navX = nullptr;
}

void Drive::PIDset()
{
//	//EMMA LOW GEAR
	rearLeftMotor->Config_kF(0, 0.314, 10);
	rearLeftMotor->Config_kP(0, 0, 10);
	rearLeftMotor->Config_kI(0, 0, 10);
	rearLeftMotor->Config_kD(0, 0, 10);

	rearRightMotor->Config_kF(0, 0.314, 10);
	rearRightMotor->Config_kP(0, 0, 10);
	rearRightMotor->Config_kI(0, 0, 10);
	rearRightMotor->Config_kD(0, 0, 10);
//
	rearLeftMotor->ConfigSelectedFeedbackSensor(QuadEncoder, 0, 10);
	rearLeftMotor->SetSensorPhase(false);
	rearLeftMotor->SetInverted(true);
	frontLeftMotor->SetInverted(true);

	rearRightMotor->ConfigSelectedFeedbackSensor(QuadEncoder, 0, 10);
	rearRightMotor->SetSensorPhase(true);
	rearRightMotor->SetInverted(false);
	frontRightMotor->SetInverted(false);
//

	//MOD
//	rearLeftMotor->Config_kF(0, SmartDashboard::GetNumber("kF", 0), 10);
//	rearLeftMotor->Config_kP(0, SmartDashboard::GetNumber("kP", 0), 10);
//	rearLeftMotor->Config_kI(0, SmartDashboard::GetNumber("kI", 0), 10);
//	rearLeftMotor->Config_kD(0, SmartDashboard::GetNumber("kD", 0), 10);
//	rearRightMotor->Config_kF(0, SmartDashboard::GetNumber("kF", 0), 10);
//	rearRightMotor->Config_kP(0, SmartDashboard::GetNumber("kP", 0), 10);
//	rearRightMotor->Config_kI(0, SmartDashboard::GetNumber("kI", 0), 10);
//	rearRightMotor->Config_kD(0, SmartDashboard::GetNumber("kD", 0), 10);

//	rearLeftMotor->ConfigSelectedFeedbackSensor(QuadEncoder, 0, 10);
//	rearLeftMotor->SetSensorPhase(true);
//	rearLeftMotor->SetInverted(true);
//	frontLeftMotor->SetInverted(true);
//
//	rearRightMotor->ConfigSelectedFeedbackSensor(QuadEncoder, 0, 10);
//	rearRightMotor->SetSensorPhase(false);
//	rearRightMotor->SetInverted(false);
//	frontRightMotor->SetInverted(false);
}

void Drive::testDrive()
{
	rearLeftMotor->Set(ControlMode::Velocity, 30);
	frontLeftMotor->Set(ControlMode::Follower, Drive_Rear_Left_Motor_Channel);

	rearRightMotor->Set(ControlMode::Velocity, 30);
	frontRightMotor->Set(ControlMode::Follower, Drive_Rear_Right_Motor_Channel);
	SmartDashboard::PutNumber("Encoder Right", rearLeftMotor->GetSelectedSensorPosition(FeedbackDevice::QuadEncoder));
	SmartDashboard::PutNumber("Encoder Left", rearRightMotor->GetSelectedSensorPosition(FeedbackDevice::QuadEncoder));

	SmartDashboard::PutNumber("Encoder Velocity Left", rearRightMotor->GetSelectedSensorVelocity(FeedbackDevice::QuadEncoder));
	SmartDashboard::PutNumber("Encoder Velocity Right", rearLeftMotor->GetSelectedSensorVelocity(FeedbackDevice::QuadEncoder));
}

void Drive::testPID()
{
	rearLeftMotor->Config_kF(0, SmartDashboard::GetNumber("kF", 0), 10);
	rearLeftMotor->Config_kP(0, SmartDashboard::GetNumber("kP", 0), 10);
	rearLeftMotor->Config_kI(0, SmartDashboard::GetNumber("kI", 0), 10);
	rearLeftMotor->Config_kD(0, SmartDashboard::GetNumber("kD", 0), 10);
	rearRightMotor->Config_kF(0, SmartDashboard::GetNumber("kF", 0), 10);
	rearRightMotor->Config_kP(0, SmartDashboard::GetNumber("kP", 0), 10);
	rearRightMotor->Config_kI(0, SmartDashboard::GetNumber("kI", 0), 10);
	rearRightMotor->Config_kD(0, SmartDashboard::GetNumber("kD", 0), 10);
}

void Drive::velocityDrive(float xAxis, float yAxis)
{
	joystickFwdSet(yAxis);
	joystickTurnSet(xAxis);
//MOD
//	rearLeftMotor->Set(ControlMode::Velocity, velocityFwd - velocityTurn);
//	frontLeftMotor->Set(ControlMode::Follower, Drive_Rear_Left_Motor_Channel);
//
//	rearRightMotor->Set(ControlMode::Velocity, velocityFwd + velocityTurn);
//	frontRightMotor->Set(ControlMode::Follower, Drive_Rear_Right_Motor_Channel);

	rearLeftMotor->Set(ControlMode::Velocity, velocityFwd + velocityTurn);
	frontLeftMotor->Set(ControlMode::Follower, Drive_Rear_Left_Motor_Channel);

	rearRightMotor->Set(ControlMode::Velocity, velocityFwd - velocityTurn);
	frontRightMotor->Set(ControlMode::Follower, Drive_Rear_Right_Motor_Channel);
}

void Drive::joystickFwdSet(float joystickY)
{
	if(joystickY > 0.2)
	{
		//This calculation gives max velocity @ joystick = 1
		velocityFwd = (joystickY-0.2)*1/.8*Max_Motor_Velocity;
	}
	else if(joystickY < -0.2)
	{
		velocityFwd = (joystickY+0.2)*1/.8*Max_Motor_Velocity;
	}
	else
	{
		velocityFwd = 0;
	}
}

void Drive::joystickTurnSet(float joystickX)
{
	if(joystickX > 0.2)
	{
		velocityTurn = (joystickX-0.2)*1/.8*Max_Motor_Velocity/4;
	}
	else if(joystickX < -0.2)
	{
		velocityTurn = (joystickX+0.2)*1/.8*Max_Motor_Velocity/4;
	}
	else
	{
		velocityTurn = 0;
	}

}

void Drive::smartDashboard()
{
	SmartDashboard::PutNumber("Encoder Left", rearLeftMotor->GetSelectedSensorPosition(FeedbackDevice::QuadEncoder));
	SmartDashboard::PutNumber("Encoder Velocity Left", rearLeftMotor->GetSelectedSensorVelocity(FeedbackDevice::QuadEncoder));

	SmartDashboard::PutNumber("Encoder Right", rearRightMotor->GetSelectedSensorPosition(FeedbackDevice::QuadEncoder));
	SmartDashboard::PutNumber("Encoder Velocity Right", rearRightMotor->GetSelectedSensorVelocity(FeedbackDevice::QuadEncoder));

	SmartDashboard::PutNumber("PID Error Right", rearRightMotor->GetClosedLoopError(0));
	SmartDashboard::PutNumber("PID Error Left", rearLeftMotor->GetClosedLoopError(0));

	SmartDashboard::PutNumber("Motor Output Percent Front Left", frontLeftMotor->GetMotorOutputPercent());
	SmartDashboard::PutNumber("Motor Output Percent Rear Left", rearLeftMotor->GetMotorOutputPercent());

	SmartDashboard::PutNumber("Velocity Forward", velocityFwd);
	SmartDashboard::PutNumber("Velocity Turn", velocityTurn);

	SmartDashboard::PutNumber("Motor Output Percent Front Right", frontRightMotor->GetMotorOutputPercent());
	SmartDashboard::PutNumber("Motor Output Percent Rear Right", rearRightMotor->GetMotorOutputPercent());

	SmartDashboard::PutNumber("Gyro Value", ypr[0]);
	SmartDashboard::PutNumber("Gyro Error", gyroError);
	SmartDashboard::PutNumber("Reference Angle", refAngle);
	SmartDashboard::PutNumber("Target Heading", targetHeading);
}

void Drive::setTargetHeading(float joystick)
{
	if(joystick > 0.2)
	{
		//at joystick = 1, bot turns at 180 degrees/s "4.75 = 3.6*(1/.8)"(3.6 gives 180/sec without the deadzone
		targetHeading += (joystick-0.2)*4.75;
	}
	else if(joystick < -0.2)
	{
		targetHeading += (joystick+0.2)*4.75;
	}
	//targetHeading += joystick*3.6;
}

void Drive::setGyroTurn(float joystick)
{
	getYPR();
	currentHeading = ypr[0];
	setTargetHeading(-joystick);
	gyroError = currentHeading - targetHeading;
	turnLeftandRight(gyroError);
//	SmartDashboard::PutNumber("Target Heading", targetHeading);
//	SmartDashboard::PutNumber("Gyro Value", ypr[0]);
}

void Drive::updateDrive(float xAxis, float yAxis)
{
	setGyroTurn(xAxis);
	joystickFwdSet(yAxis);

	rearLeftMotor->Set(ControlMode::Velocity, velocityFwd + gyroTurnSpeed);
	frontLeftMotor->Set(ControlMode::Follower, Drive_Rear_Left_Motor_Channel);

	rearRightMotor->Set(ControlMode::Velocity, velocityFwd - gyroTurnSpeed);
	frontRightMotor->Set(ControlMode::Follower, Drive_Rear_Right_Motor_Channel);
}

/*void Drive::turnRight(int error)
{
	error = abs(error);
		if(error > 40)
		{
			rearRightMotor->Set(ControlMode::Velocity, Max_Motor_Velocity);
			rearLeftMotor->Set(ControlMode::Velocity, -Max_Motor_Velocity);
		}
		if(error < 40)
		{
			rearRightMotor->Set(ControlMode::Velocity, Max_Motor_Velocity * (error/40.0));
			rearLeftMotor->Set(ControlMode::Velocity, -Max_Motor_Velocity * (error/40.0));
		}

		SmartDashboard::PutNumber("Velocity Math", Max_Motor_Velocity * (error/40));

}*/

/*void Drive::turnLeft(int error)
{
	error = abs(error);
		if(error > 40)
		{
			rearRightMotor->Set(ControlMode::Velocity, -Max_Motor_Velocity);
			rearLeftMotor->Set(ControlMode::Velocity, Max_Motor_Velocity);
		}
		else
		{
			rearRightMotor->Set(ControlMode::Velocity, -Max_Motor_Velocity * (error/40.0));
			rearLeftMotor->Set(ControlMode::Velocity, Max_Motor_Velocity * (error/40.0));
		}
}*/

void Drive::turnLeftandRight(int error)
{
	//slows the motors down from 40 degree error to as it approaches 0 degree error
	float motorFactor = (error/40.0);

	if (motorFactor > 1) motorFactor = 1;
	if (motorFactor < -1) motorFactor = -1;


	gyroTurnSpeed = Max_Motor_Velocity * motorFactor;
//	rearRightMotor->Set(ControlMode::Velocity, Max_Motor_Velocity * motorFactor);
//	rearLeftMotor->Set(ControlMode::Velocity, -Max_Motor_Velocity * motorFactor);
//	frontRightMotor->Set(ControlMode::Follower, Drive_Rear_Right_Motor_Channel);
//	frontLeftMotor->Set(ControlMode::Follower, Drive_Rear_Left_Motor_Channel);
}

void Drive::getYPR()
{
	pGyon->GetYawPitchRoll(ypr);
}

void Drive::autoTurn(int angle)
{
	switch(angle)
	{
		case 270 :
			targetHeading = targetHeading + 90;
			Wait(.2);
			/*pGyon->SetYaw(0, 0);
			refAngle = 90;*/
			break;
		case 180 :
			targetHeading = targetHeading + 180;
			Wait(.2);
			/*pGyon->SetYaw(0, 0);
			refAngle = 180;*/
			break;
		case 90 :
			targetHeading = targetHeading - 90;
			Wait(.2);
			/*pGyon->SetYaw(0, 0);
			refAngle = -90;*/
			break;
		case 0 :
			/*pGyon->SetYaw(0, 0);
			refAngle = 0;*/
			break;
		default :
			break;
	}
	/*do
	{
		pGyon->GetYawPitchRoll(ypr);
		gyroError = refAngle - ypr[0];
		if(refAngle < 0)
		{
		turnRight(gyroError);
		}
		else if(refAngle > 0)
		{
		turnLeft(gyroError);
		}


		turnLeftandRight(gyroError);

		SmartDashboard::PutNumber("Reference Angle", refAngle);
		SmartDashboard::PutNumber("Gyro Value", ypr[0]);
		SmartDashboard::PutNumber("Gyro Error", gyroError);
	}while(abs(gyroError) > 5);*/
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
	return rearLeftMotor->GetSelectedSensorPosition(FeedbackDevice::QuadEncoder);
}

float Drive::getRightEnc()
{
	return rearRightMotor->GetSelectedSensorPosition(FeedbackDevice::QuadEncoder);
}

void Drive::resetEncoder()
{
	rearLeftMotor->SetSelectedSensorPosition(0,0,0);
	rearRightMotor->SetSelectedSensorPosition(0,0,0);
}

void Drive::resetGyro()
{
	targetHeading = 0;
	pGyon->SetYaw(0, 0);
}
