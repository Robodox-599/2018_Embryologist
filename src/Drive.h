/*
 * Drive.h
 *
 *  Created on: Jan 6, 2018
 *      Author: Admin
 */

#ifndef SRC_DRIVE_H_
#define SRC_DRIVE_H_
#include "Macros.h"

class Drive
{
public:
	Drive();
	~Drive();

	void updateLeftMotors();
	void updateRightMotors();
	void setFwdSpeed();
	void setTurnSpeed();
	void drive();

	AHRS* navX;

private:
	CANTalon* frontLeftMotor;
	CANTalon* rearLeftMotor;
	CANTalon* frontRightMotor;
	CANTalon* rearRightMotor;

	float fwdSpeed;
	float turnSpeed;
};



#endif /* SRC_DRIVE_H_ */
