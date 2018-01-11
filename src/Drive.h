/*
 * Drive.h
 *
 *  Created on: Jan 6, 2018
 *      Author: Admin
 */

#ifndef SRC_DRIVE_H_
#define SRC_DRIVE_H_
#include "Macros.h"
#include <TalonSRX.h>
class Drive
{
public:
	Drive();
	~Drive();

	void updateLeftMotors(float speed);
	void updateRightMotors(float speed);
	void setFwdSpeed(float fwd);
	void setTurnSpeed(float turn);
	void drive(float xAxis, float yAxis);
	void shift(bool toggle);
	void driveStraight();

	float getLeftEnc();
	float getRightEnc();

	//AHRS* navX;

private:
	CANTalon *frontLeftMotor;
	CANTalon* rearLeftMotor;
	CANTalon* frontRightMotor;
	CANTalon* rearRightMotor;

	//DoubleSolenoid* shifter;

	float fwdSpeed;
	float turnSpeed;

	//float gyroValue;

	float const kp = 0.01;
};



#endif /* SRC_DRIVE_H_ */
