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

	void intakeOuttakeCube(bool outtake, bool intake, float mod);
	void liftIntake (bool Lift, bool noLift, bool midLift, bool finalLift);
	void diffIntake(bool left, bool right);
	void intakePosition(bool posButton, bool unPos);
	void jiggle(bool jiggButton);
	void AutoIntake();
	void AutoOuttake();
	void setPos(int pos);

	void intakeAngle(float zAxis);
	void pivotIntake(bool down, bool shoot, bool up);
	void fixPivotError(float error);
	void stopManip();

	DigitalInput* cubeStop;

	bool stoppingCube();
	AnalogPotentiometer* pot;
	double potVal();

	float currentPivot;
	float targetPivot;
	float errorPivot;
	TalonSRX* liftIntakeMotor;
	TalonSRX* leftIntakeMotor;
	TalonSRX* rightIntakeMotor;
private:


	DoubleSolenoid* leftmanipPiston;

	//DoubleSolenoid* rightmanipPiston;
	float potAngle;

	//DoubleSolenoid* rightmanipPiston;



	bool toggle;
};





#endif /* SRC_MANIPULATOR_H_ */
