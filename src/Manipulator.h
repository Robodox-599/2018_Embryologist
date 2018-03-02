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

	void intakeAngle(float zAxis);

	DigitalInput* cubeStop;

	bool stoppingCube();


private:

	TalonSRX* leftIntakeMotor;
	TalonSRX* rightIntakeMotor;
	TalonSRX* liftIntakeMotor;
	DoubleSolenoid* leftmanipPiston;
<<<<<<< HEAD
	DoubleSolenoid* rightmanipPiston;
	float potAngle;
=======
	//DoubleSolenoid* rightmanipPiston;

>>>>>>> e88a862aae38bc7736ce35d0b89a128da322a493
	bool toggle;
};





#endif /* SRC_MANIPULATOR_H_ */
