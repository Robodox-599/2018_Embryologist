/*
 * Drive.h
 *
 *  Created on: Jan 6, 2018
 *      Author: Admin
 */

#ifndef SRC_DRIVE_H_
#define SRC_DRIVE_H_
#include "Macros.h"
#include "ctre/Phoenix.h"
class Drive
{
public:
	Drive();
	~Drive();

	void velocityDrive(float xAxis, float yAxis);
	void PIDset();
	void joystickFwdSet(float joystickY);
	void joystickTurnSet(float joystickX);

	void autoTurn(int angle);

	void updateLeftMotors(float speed);
	void updateRightMotors(float speed);
	void setFwdSpeed(float fwd);
	void setTurnSpeed(float turn);
	void drive(float xAxis, float yAxis);
	void shift(int shifter_Button);
	void driveStraight();

	void resetEncoder();

	float getLeftEnc();
	float getRightEnc();

	bool smartTest();
	//AHRS* navX;

private:
	TalonSRX* frontLeftMotor;
	TalonSRX* rearLeftMotor;
	TalonSRX* frontRightMotor;
	TalonSRX* rearRightMotor;

	PigeonIMU * pGyro;

	DoubleSolenoid* shifter;
	//DoubleSolenoid* rightShifter;

	float fwdSpeed;
	float turnSpeed;
	bool toggle;

	float velocityFwd;
	float velocityTurn;

	//float gyroValue;

	float const kp = 0.01;
};

#endif /* SRC_DRIVE_H_ */
