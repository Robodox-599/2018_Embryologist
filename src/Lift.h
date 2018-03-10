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
		void PistonLift(bool pistonButton, bool disengage);
		float getLeftLiftEnc();
		float getRightLiftEnc();
		float getAvgLiftEnc();
		void liftAuto(float speed, float autoLiftInput);
		//void PistonClimb(bool climbButton);
		void CalibrateLift(bool calibrateButton, bool safeCalibrate);
		void resetLiftEncoder();
		bool lowerLimitTester();
		bool upperLimitTester();
		void rungDeploy(bool deployButton, bool otherButton);

		void setHeightEnc(float joystick);
		void doLift();
		void fixErrorLeft(float error);
		void fixErrorRight(float error);

		void autoClimb(bool autoClimbA, bool autoClimbB);
		void heightPosition(bool positionA, bool positionB);

		void doClimb(bool climbButton);

		void stopLift();

		bool canLift;
		bool rungState;
		bool climbState;

		DoubleSolenoid *liftPiston;
		//DoubleSolenoid *rightLiftPiston;

		Solenoid *rungPiston;
		TalonSRX *frontRightLift;
				TalonSRX *frontLeftLift;
				TalonSRX *backRightLift;
				TalonSRX *backLeftLift;
private:


		DigitalInput *upperLimit;
		DigitalInput *lowerLimit;

		float targetEnc;
		float encErrorRight;
		float encErrorLeft;
		float currentLeftEnc;
		float currentRightEnc;

};



#endif /* SRC_LIFT_H_ */
