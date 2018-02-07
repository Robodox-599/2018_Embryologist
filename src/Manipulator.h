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

	void intakeOuttakeCube(bool outtake, bool intake);
	void intakePosition(bool posButton);
	void AutoIntake();
	void AutoOuttake();
	void setPos(bool pos);

	DigitalInput* cubeStop;

	bool stoppingCube();


private:

	TalonSRX* leftIntakeMotor;
	TalonSRX* rightIntakeMotor;
	DoubleSolenoid* leftmanipPiston;
	DoubleSolenoid* rightmanipPiston;

	bool toggle;
};





#endif /* SRC_MANIPULATOR_H_ */
