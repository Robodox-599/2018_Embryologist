/*
 * Intake.h
 *
 *  Created on: Jan 6, 2018
 *      Author: Admin
 */

#include "CANTalon.h"

#ifndef SRC_MANIPULATOR_H_
#define SRC_MANIPULATOR_H_

class Manipulator
{
public:

	Manipulator();
	~Manipulator();

	void intake_outtake_Cube(bool button, bool Button);

	DigitalInput*CubeStopOne;
	DigitalInput*CubeStopTwo;

	bool breakone;
	bool breaktwo;

private:

	CANTalon* leftMotor;
	CANTalon* rightMotor;
};





#endif /* SRC_MANIPULATOR_H_ */
