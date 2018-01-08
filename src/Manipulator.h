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

	void intakeCube(bool button);
	void outtakeCube(bool Button);

private:

	CANTalon* leftMotor;
	CANTalon* rightMotor;
};





#endif /* SRC_MANIPULATOR_H_ */
