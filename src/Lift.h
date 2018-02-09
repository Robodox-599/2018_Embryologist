/*
 * Lift.h
 *
 *  Created on: Jan 6, 2018
 *      Author: Admin
 */

#ifndef SRC_LIFT_H_
#define SRC_LIFT_H_

#include "ctre/Phoenix.h"
#include "WPILib.h"
#include "Macros.h"


class Lift
{
public:
		Lift();
		~Lift();

		void liftRobot(float liftInput);
		void PistonLift(bool pistonButton);
		float getLeftLiftEnc();
		float getRightLiftEnc();
		void liftAuto(float speed, float autoLiftInput);
		void PistonClimb(bool climbButton);
		void resetLiftEncoder();
		bool lowerLimitTester();
		bool upperLimitTester();


		Solenoid *leftLiftPiston;
		Solenoid *rightLiftPiston;

		Solenoid *leftClimbPiston;
		Solenoid *rightClimbPiston;

private:
		TalonSRX *frontRightLift;
		TalonSRX *frontLeftLift;
		TalonSRX *backRightLift;
		TalonSRX *backLeftLift;

		DigitalInput *upperLimit;
		DigitalInput *lowerLimit;

};


#endif /* SRC_LIFT_H_ */
