/*
 * Intake.h
 *
 *  Created on: Jan 6, 2018
 *      Author: Admin
 */


#ifndef SRC_MANIPULATOR_H_
#define SRC_MANIPULATOR_H_
#include "ctre/Phoenix.h"
#include "WPILib.h"

class Manipulator
{
public:

	Manipulator();
	~Manipulator();

	void intakeOuttakeCube(bool outtake, bool intake);
	void liftIntake (bool Lift, bool noLift);
	void diffIntake(bool left, bool right);
	void intakePosition(bool posButton);
	void jiggle(bool jiggButton);
	void AutoIntake();
	void AutoOuttake();
	void setPos(bool pos);

	DigitalInput* cubeStop;

	bool stoppingCube();


private:

	TalonSRX* leftIntakeMotor;
	TalonSRX* rightIntakeMotor;
	TalonSRX* liftIntakeMotor;
	DoubleSolenoid* leftmanipPiston;
	//DoubleSolenoid* rightmanipPiston;

	bool toggle;
};





#endif /* SRC_MANIPULATOR_H_ */
