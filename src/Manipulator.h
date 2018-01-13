/*
 * Intake.h
 *
 *  Created on: Jan 6, 2018
 *      Author: Admin
 */

#include "ctre/Phoenix.h"
#include "WPILib.h"
#ifndef SRC_MANIPULATOR_H_
#define SRC_MANIPULATOR_H_

class Manipulator
{
public:

	Manipulator();
	~Manipulator();

	void intake_outtake_Cube(bool button, bool Button);

	DigitalInput*CubeStopOne;

	bool stoppingcubeone();


private:

	TalonSRX* leftMotor;
	TalonSRX* rightMotor;
};





#endif /* SRC_MANIPULATOR_H_ */
