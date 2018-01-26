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
		void resetLiftEncoder();

		DigitalInput *upperLimit;
		DigitalInput *lowerLimit;

		Solenoid *leftLiftPiston;
		Solenoid *rightLiftPiston;

private:
		TalonSRX *frontRightLift;
		TalonSRX *frontLeftLift;
		TalonSRX *backRightLift;
		TalonSRX *backLeftLift;


};


#endif /* SRC_LIFT_H_ */
