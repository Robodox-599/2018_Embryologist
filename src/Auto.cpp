#include <Auto.h>


Auto::Auto()
{
	gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
	drive = new Drive;
	manip = new Manipulator;
	lift = new Lift;
	dataTest = 0;
	selector = new DigitalInput(1);
	counter = 0;
	doAuto = 1;

	driveCurrent = drive->getLeftEnc();
	driveTarget = 0;
	driveError = 0;
}

Auto::~Auto()
{
	selector = nullptr;

	delete selector;
}

void Auto::driveStraight(float speed, int enc)
{
	//drive->resetEncoder();
//	if(-speed > 0)
//	{
//		while(drive->getLeftEnc() > -enc)// && drive->getRightEnc() > -enc)//Dummy values
//		{
//		drive->updateLeftMotors(-speed);
//		drive->updateRightMotors(-speed);
//		}
//		drive->updateLeftMotors(0);
//		drive->updateRightMotors(0);
//		//drive->resetEncoder();
//	}
//	if(-speed < 0)
//	{
//		while(drive->getLeftEnc() < enc )//&& drive->getRightEnc() < enc)//Dummy values
//		{
//		drive->updateLeftMotors(-speed);
//		drive->updateRightMotors(-speed);
//		}
//		drive->updateLeftMotors(0);
//		drive->updateRightMotors(0);
//				//drive->resetEncoder();
//	}

	if(speed > 0)
	{
		while(drive->getLeftEnc() > -enc)
		{
			float driveSpeed = ((-enc-drive->getLeftEnc())/10000);
			if(driveSpeed<speed)
			{
				drive->updateLeftMotors(-speed);
				drive->updateRightMotors(-speed);
			}
			else
			{
				drive->updateLeftMotors(-driveSpeed);
				drive->updateRightMotors(-driveSpeed);
			}
		}
		drive->updateLeftMotors(0);
		drive->updateRightMotors(0);
	}
	else
	{
		while(drive->getLeftEnc() < enc)
		{
			float driveSpeed = ((enc-drive->getLeftEnc())/10000);
			if(driveSpeed<speed)
			{
				drive->updateLeftMotors(-driveSpeed);
				drive->updateRightMotors(-driveSpeed);
			}
			else
			{
				drive->updateLeftMotors(-speed);
				drive->updateRightMotors(-speed);
			}
		}
		drive->updateLeftMotors(0);
		drive->updateRightMotors(0);
	}

//	driveTarget = -enc;
//	driveCurrent = drive->getLeftEnc();
//	driveError = driveTarget-driveCurrent;
//	adjustDrive(driveError, speed);
//	drive->updateLeftMotors(0);
//	drive->updateRightMotors(0);
}

void Auto::encTurn(float speedL, float speedR, int enc)
{
	if(speedL > speedR)
	{
		while(drive->getLeftEnc() > -(enc-1000) && drive->getRightEnc() < (enc-1000))
		{
			drive->updateLeftMotors(-speedL);
			drive->updateRightMotors(-speedR);
		}
		drive->updateLeftMotors(0);
		drive->updateRightMotors(0);
	}
	else
	{
		while(drive->getLeftEnc() < (enc-1000) && drive->getRightEnc() > -(enc-1000))
		{
			drive->updateLeftMotors(-speedL);
			drive->updateRightMotors(-speedR);
		}
		drive->updateLeftMotors(0);
		drive->updateRightMotors(0);
	}
}

void Auto::encLift(float speed, int enc)
{
	if(lift->getRightLiftEnc() < enc)
	{
		while(!lift->upperLimitTester() && lift->getRightLiftEnc() < enc)
		{
			lift->frontLeftLift->Set(ControlMode::PercentOutput, speed);
			lift->backLeftLift->Set(ControlMode::PercentOutput, speed);
			lift->frontRightLift->Set(ControlMode::PercentOutput, -speed);
			lift->backRightLift->Set(ControlMode::PercentOutput, -speed);
		}
		lift->frontLeftLift->Set(ControlMode::PercentOutput, 0.05);
		lift->backLeftLift->Set(ControlMode::PercentOutput, 0.05);
		lift->frontRightLift->Set(ControlMode::PercentOutput, -0.05);
		lift->backRightLift->Set(ControlMode::PercentOutput, -0.05);
	}
	if(lift->getRightLiftEnc() > enc)
	{
		while(!lift->lowerLimitTester() && lift->getRightLiftEnc() < enc)
		{
			lift->frontLeftLift->Set(ControlMode::PercentOutput, -speed);
			lift->backLeftLift->Set(ControlMode::PercentOutput, -speed);
			lift->frontRightLift->Set(ControlMode::PercentOutput, speed);
			lift->backRightLift->Set(ControlMode::PercentOutput, speed);
		}
		lift->frontLeftLift->Set(ControlMode::PercentOutput, 0.05);
		lift->backLeftLift->Set(ControlMode::PercentOutput, 0.05);
		lift->frontRightLift->Set(ControlMode::PercentOutput, -0.05);
		lift->backRightLift->Set(ControlMode::PercentOutput, -0.05);
	}
}

void Auto::adjustDrive(float error, float speed)
{
	float driveSpeed = (error/10000);

	if(driveSpeed > speed) driveSpeed = speed;
	if(driveSpeed < -speed) driveSpeed = -speed;

	drive->updateLeftMotors(-driveSpeed);
	drive->updateRightMotors(-driveSpeed);


}

void Auto::setMotors(float speedL, float speedR, float time)
{
	drive->updateLeftMotors(-speedL);
	drive->updateRightMotors(-speedR);
	Wait(time);
	drive->updateLeftMotors(0);
	drive->updateRightMotors(0);
}

void Auto::turnRobot(float speed, float time)
{
	drive->updateLeftMotors(speed);
	drive->updateRightMotors(-speed);
	Wait(time);
	drive->updateLeftMotors(0);
	drive->updateRightMotors(0);
}

void Auto::liftTime(float speed, float time)
{
	lift->frontLeftLift->Set(ControlMode::PercentOutput, speed);
	lift->backLeftLift->Set(ControlMode::PercentOutput, speed);
	lift->frontRightLift->Set(ControlMode::PercentOutput, -speed);
	lift->backRightLift->Set(ControlMode::PercentOutput, -speed);
	Wait(time);
	lift->frontLeftLift->Set(ControlMode::PercentOutput, .05);
	lift->backLeftLift->Set(ControlMode::PercentOutput, .05);
	lift->frontRightLift->Set(ControlMode::PercentOutput, -.05);
	lift->backRightLift->Set(ControlMode::PercentOutput, -.05);
}

void Auto::gyroTurn(float speed, int angle)
{
	while(drive->pGyon->GetYawPitchRoll(ypr) < angle +2)
	{
		drive->updateLeftMotors(-speed);
		drive->updateRightMotors(speed);
		drive->getYPR();
	}
	drive->updateLeftMotors(0);
	drive->updateRightMotors(0);
}


void Auto::preCheck()//To be run BEFORE a match in the pit in order to test each system
{

}


//
void Auto::nonPreLoad_auto1()//Left starting position, Objective: Switch
{
	if(gameData[0] == 'L')
	{
		//Put left auto code here
		//dataTest = 1;
		//driveStraight(1, 1000);

		manip->setPos(1);//releases intake
		driveStraight(1,50000);
		drive->autoTurn(270); //function not final
		drive->updateLeftMotors(1);
		drive->updateRightMotors(1);
		//manip->AutoIntake();
		drive->updateLeftMotors(0);
		drive->updateRightMotors(0);
		driveStraight(-1,5000);
		drive->autoTurn(90); //function not final
		driveStraight(1,1000);
		drive->autoTurn(270); //function not final
		driveStraight(1,1000);
		lift->liftAuto(1,5000);
		manip->AutoOuttake();


	}
	else
	{
		//Put right auto code here
		//dataTest = 2;
		//driveStraight(-1, 1000);

		manip->setPos(1);//releases intake
		driveStraight(1,50000);
		drive->autoTurn(270); //function not final
		drive->updateLeftMotors(1);
		drive->updateRightMotors(1);
		//manip->AutoIntake();
		drive->updateLeftMotors(0);
		drive->updateRightMotors(0);
		drive->autoTurn(90); //function not final
		driveStraight(1,2000);
		driveStraight(1,50000);
		drive->autoTurn(90); //function not final
		driveStraight(1,5000);
		drive->autoTurn(90); //function not final
		driveStraight(1,2000);
		lift->liftAuto(1,5000);
		manip->AutoOuttake();
	}
}

void Auto::nonPreLoad_auto2()
{
	if(gameData[0] == 'L')
	{
		manip->setPos(1);
		driveStraight(1,30000);
		drive->updateLeftMotors(1);
		drive->updateRightMotors(1);
		//manip->AutoIntake();
		drive->updateLeftMotors(0);
		drive->updateRightMotors(0);
		driveStraight(-1,2000);
		drive->autoTurn(90); //function not final
		driveStraight(1,5000);
		//drive->autoTurn(270); //function not final
		driveStraight(1,10000);
		lift->liftAuto(1,5000);
		manip->AutoOuttake();
	}
	else
	{
		manip->setPos(1);
		driveStraight(1,30000);
		drive->updateLeftMotors(1);
		drive->updateRightMotors(1);
		//manip->AutoIntake();
		drive->updateLeftMotors(0);
		drive->updateRightMotors(0);
		driveStraight(-1,2000);
		drive->autoTurn(270); //function not final
		driveStraight(1,5000);
		drive->autoTurn(90); //function not final
		driveStraight(1,10000);
		lift->liftAuto(1,5000);
		manip->AutoOuttake();
	}
}

void Auto::nonPreLoad_auto3()
{
	if(gameData[0] == 'L')
	{
		manip->setPos(1);//releases intake
		driveStraight(1,50000);
		drive->autoTurn(90); //function not final
		drive->updateLeftMotors(1);
		drive->updateRightMotors(1);
		//manip->AutoIntake();
		drive->updateLeftMotors(0);
		drive->updateRightMotors(0);
		driveStraight(-1,5000);
		drive->autoTurn(270); //function not final
		driveStraight(1,1000);
		drive->autoTurn(90); //function not final
		driveStraight(1,1000);
		lift->liftAuto(1,5000);
		manip->AutoOuttake();
	}
	else
	{
		manip->setPos(1);//releases intake
		driveStraight(1,50000);
		drive->autoTurn(90); //function not final
		drive->updateLeftMotors(1);
		drive->updateRightMotors(1);
		//manip->AutoIntake();
		drive->updateLeftMotors(0);
		drive->updateRightMotors(0);
		drive->autoTurn(270); //function not final
		driveStraight(1,2000);
		drive->autoTurn(90);
		driveStraight(1,50000);
		drive->autoTurn(270); //function not final
		driveStraight(1,5000);
		drive->autoTurn(270); //function not final
		driveStraight(1,2000);
		lift->liftAuto(1,5000);
		manip->AutoOuttake();
	}
}

void Auto::auto0()//Drive straight to pass Auto Line.
{
	/*while(drive->getLeftEnc() > -10000 && drive->getRightEnc() > -10000)//Dummy values
	{
		drive->updateLeftMotors(1);
		drive->updateRightMotors(1);
	}
	drive->updateLeftMotors(0);
	drive->updateRightMotors(0);*/
	//drive->resetEncoder();
	//driveStraight(.3, 500);
	drive->updateLeftMotors(-.4);
	drive->updateRightMotors(-.4);
	Wait(1);
	drive->updateLeftMotors(0);
	drive->updateRightMotors(0);
	doAuto = 0;
	//Wait(400);
}
//
void Auto::auto1()//Left starting position, Objective: Switch
{
	if(gameData[0] == 'L')
	{
	manip->leftIntakeMotor->Set(ControlMode::PercentOutput, .15);
	manip->rightIntakeMotor->Set(ControlMode::PercentOutput, -.15);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.08);
	//manip->pivotIntake(0,0,1);
	//driveStraight(1,10000);
	setMotors(.3,.3,3);//2.8
//	drive->updateLeftMotors(-.3);
//	drive->updateRightMotors(-.3);
//	Wait(2.8);
//	drive->updateLeftMotors(0);
//	drive->updateRightMotors(0);
	Wait(.3);
	//drive->autoTurn(270); //function not final
	turnRobot(.4, 1.1);//right turn
	Wait(.2);
	if(!lift->upperLimitTester())liftTime(.3,.8);
	Wait(.1);
	//driveStraight(1,1000);
	setMotors(.24,.24,1);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .25);
	Wait(.4);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.15);
	//manip->targetPivot = 80;
//	manip->pivotIntake(0,1,0);
//	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.08);
//	drive->updateLeftMotors(-.2);
//	drive->updateRightMotors(-.2);
//	Wait(.6);
//	drive->updateLeftMotors(0);
//	drive->updateRightMotors(0);
	//lift->liftAuto(1,5000);
	manip->AutoOuttake();
	//if(!lift->upperLimitTester())liftTime(.3,1);
	setMotors(-.25,-.25,1);
	if(!lift->lowerLimitTester())liftTime(-.1,1);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .05);
	Wait(1);
	doAuto = 0;
	}
	else auto0();

//	if(gameData[0] == 'L')
//	{
//		//Put left auto code here
//		//dataTest = 1;
//		//driveStraight(1, 1000);
//
//		//manip->setPos(1);//releases intake
//		//manip->pivotIntake(1,0,0);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .1);
//		Wait(1.5);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, 0);
//		//driveStraight(1,10000);
//		drive->updateLeftMotors(-.1);
//		drive->updateRightMotors(-.1);
//		Wait(1.4);
//		drive->updateLeftMotors(0);
//		drive->updateRightMotors(0);
//		//drive->autoTurn(270); //function not final
//		turnRobot(-.5, 1);
//		//driveStraight(1,1000);
//		drive->updateLeftMotors(-.2);
//		drive->updateRightMotors(-.2);
//		Wait(.6);
//		drive->updateLeftMotors(0);
//		drive->updateRightMotors(0);
//		doAuto = false;
//		//lift->liftAuto(1,5000);
//		//manip->AutoOuttake();
//
//
//	}
//	else
//	{
//		//Put right auto code here
//		//dataTest = 2;
//		//driveStraight(-1, 1000);
//
////		manip->setPos(1);//releases intake
////		driveStraight(1,50000);
////		drive->autoTurn(270); //function not final
////		driveStraight(1,50000);
////		drive->autoTurn(270); //function not final
////		driveStraight(1,5000);
////		drive->autoTurn(270); //function not final
////		driveStraight(1,2000);
////		lift->liftAuto(1,5000);
////		manip->AutoOuttake();
//	}
}

void Auto::auto2()
{
	//left side of switch:
//	manip->leftIntakeMotor->Set(ControlMode::PercentOutput, .15);
//	manip->rightIntakeMotor->Set(ControlMode::PercentOutput, -.15);
//	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.08);
//	setMotors(.3,.3,1.3);//2.8
//	Wait(.3);
//	turnRobot(-.4, 1);//left turn
//	setMotors(.44,.44,.7);
//	turnRobot(.4, 1);//right turn
//	Wait(.2);
//	if(!lift->upperLimitTester())liftTime(.34,.8);
//	Wait(.1);
//	setMotors(.38,.38,1);
//	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .24);
//	Wait(.3);
//	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.09);
//	manip->AutoOuttake();
//	//setMotors(-.15,-.15,1);
//	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.4);
//	if(!lift->lowerLimitTester())liftTime(-.1,3);
//	Wait(1);
//	turnRobot(.4, 1);
//	doAuto = 0;

	//or//

	if(gameData[0] == 'L')
	{
	manip->leftIntakeMotor->Set(ControlMode::PercentOutput, .15);
	manip->rightIntakeMotor->Set(ControlMode::PercentOutput, -.15);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.1);
	drive->resetEncoder();
	Wait(.1);
	driveStraight(.4, 9000);
	Wait(.3);
	//turnRobot(-.42, 1);//left turn
//	drive->autoTurn(90);
//	drive->updateDrive(0,0);
	//gyroTurn(.4,90);
	drive->resetEncoder();
	Wait(.1);
	encTurn(.4,-.4,10000);
	//setMotors(.44,.44,.7);
	//Wait(2);
	drive->resetEncoder();
	Wait(.1);
	driveStraight(.4,10000);
	//turnRobot(.42, 1);//right turn
	drive->resetEncoder();
	Wait(.1);
	encTurn(-.4,.4,12000);
	Wait(.2);
	//if(!lift->upperLimitTester())liftTime(.34,.8);
	lift->resetLiftEncoder();
	Wait(.1);
	encLift(.3,5000);
	Wait(.1);
	//setMotors(.38,.38,1);
	drive->resetEncoder();
	Wait(.1);
	driveStraight(.34,7500);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .3);
	Wait(.3);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.09);
	//manip->pivotIntake(0,1,0);
	manip->AutoOuttake();
	//setMotors(-.15,-.15,1);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.38);
	if(!lift->lowerLimitTester())liftTime(-.1,1);
	//encLift(.1,0);
	//Wait(1);
	//turnRobot(.4, 1);
	setMotors(-.4,-.4,.30);
	drive->resetEncoder();
	Wait(.1);
	encTurn(-.3,.3,7500);
	//
	setMotors(-.3,-.3,.2);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .5);
	Wait(.6);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.05);
	manip->leftIntakeMotor->Set(ControlMode::PercentOutput, .8);
	manip->rightIntakeMotor->Set(ControlMode::PercentOutput, -.5);
	drive->resetEncoder();
	Wait(.1);
	driveStraight(.3,11000);
	manip->leftIntakeMotor->Set(ControlMode::PercentOutput, .9);
	manip->rightIntakeMotor->Set(ControlMode::PercentOutput, -.6);
	Wait(.4);
	manip->leftIntakeMotor->Set(ControlMode::PercentOutput, .15);
	manip->rightIntakeMotor->Set(ControlMode::PercentOutput, -.15);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.6);
	Wait(.4);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.09);
	drive->resetEncoder();
	Wait(.1);
	driveStraight(-.3,6000);
	drive->resetEncoder();
	Wait(.1);
	encTurn(.3,-.3,8500);
	lift->resetLiftEncoder();
	Wait(.1);
	encLift(.3,10000);
	drive->resetEncoder();
	Wait(.1);
	driveStraight(.3,5000);
	manip->AutoOuttake();
	driveStraight(-.3,1000);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.38);
	if(!lift->lowerLimitTester())liftTime(-.1,1);
	//
	doAuto = 0;
	}
	else
	{
	//right side of switch:
//	manip->leftIntakeMotor->Set(ControlMode::PercentOutput, .15);
//	manip->rightIntakeMotor->Set(ControlMode::PercentOutput, -.15);
//	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.08);
//	setMotors(.3,.3,1.3);//2.8
//	Wait(.3);
//	turnRobot(.42, 1.2);//right turn
//	setMotors(.4,.4,1);
//	turnRobot(-.42, 1.1);//left turn
//	Wait(.2);
//	if(!lift->upperLimitTester())liftTime(.34,.8);
//	Wait(.1);
//	setMotors(.35,.35,1);
//	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .24);
//	Wait(.3);
//	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.09);
//	manip->AutoOuttake();
//	//setMotors(-.15,-.15,1);
//	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.4);
//	if(!lift->lowerLimitTester())liftTime(-.1,3);
//	Wait(1);
//	turnRobot(-.3, 1);
//	doAuto = 0;

	//or//
	manip->leftIntakeMotor->Set(ControlMode::PercentOutput, .15);
	manip->rightIntakeMotor->Set(ControlMode::PercentOutput, -.15);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.1);
	drive->resetEncoder();
	Wait(.1);
	driveStraight(.4, 9000);
	Wait(.3);
	//turnRobot(-.42, 1);//left turn
//	drive->autoTurn(90);
//	drive->updateDrive(0,0);
	//gyroTurn(.4,90);
	drive->resetEncoder();
	Wait(.1);
	encTurn(-.4,.4,9000);
	//setMotors(.44,.44,.7);
	//Wait(2);
	drive->resetEncoder();
	Wait(.1);
	driveStraight(.4,8000);
	//turnRobot(.42, 1);//right turn
	drive->resetEncoder();
	Wait(.1);
	encTurn(.4,-.4,13500);
	Wait(.2);
	//if(!lift->upperLimitTester())liftTime(.34,.8);
	lift->resetLiftEncoder();
	Wait(.1);
	encLift(.3,5000);
	Wait(.1);
	//setMotors(.38,.38,1);
	drive->resetEncoder();
	Wait(.1);
	driveStraight(.34,7500);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .24);
	Wait(.3);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.09);
	//manip->pivotIntake(0,1,0);
	manip->AutoOuttake();
	//setMotors(-.15,-.15,1);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.38);
	if(!lift->lowerLimitTester())liftTime(-.1,1);
	//encLift(.1,0);
	//Wait(1);
	//turnRobot(.4, 1);
	setMotors(-.4,-.4,.35);
	drive->resetEncoder();
	Wait(.1);
	encTurn(.3,-.3,6500);
	//
	setMotors(-.3,-.3,.2);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .5);
	Wait(.6);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.05);
	manip->leftIntakeMotor->Set(ControlMode::PercentOutput, .8);
	manip->rightIntakeMotor->Set(ControlMode::PercentOutput, -.5);
	drive->resetEncoder();
	Wait(.1);
	driveStraight(.3,7500);
	manip->leftIntakeMotor->Set(ControlMode::PercentOutput, .9);
	manip->rightIntakeMotor->Set(ControlMode::PercentOutput, -.6);
	Wait(.3);
	manip->leftIntakeMotor->Set(ControlMode::PercentOutput, .15);
	manip->rightIntakeMotor->Set(ControlMode::PercentOutput, -.15);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.6);
	Wait(.4);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.09);
	drive->resetEncoder();
	Wait(.1);
	driveStraight(-.3,6000);
	drive->resetEncoder();
	Wait(.1);
	encTurn(-.3,.3,8500);
	lift->resetLiftEncoder();
	Wait(.1);
	encLift(.3,10000);
	drive->resetEncoder();
	Wait(.1);
	driveStraight(.3,5000);
	manip->AutoOuttake();
	driveStraight(-.3,1000);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.38);
	if(!lift->lowerLimitTester())liftTime(-.1,1);
	//
	doAuto = 0;
	}

//	if(gameData[0] == 'L')
//	{
//		manip->setPos(1);
//		driveStraight(1,30000);
//		drive->autoTurn(90); //function not final
//		driveStraight(1,5000);
//		drive->autoTurn(270); //function not final
//		driveStraight(1,10000);
//		lift->liftAuto(1,5000);
//		manip->AutoOuttake();
//	}
//	else
//	{
//		manip->setPos(1);
//		driveStraight(1,30000);
//		drive->autoTurn(270); //function not final
//		driveStraight(1,5000);
//		drive->autoTurn(90); //function not final
//		driveStraight(1,10000);
//		lift->liftAuto(1,5000);
//		manip->AutoOuttake();
//	}
}

void Auto::auto3()
{
	if(gameData[0] == 'L')
	{
	manip->leftIntakeMotor->Set(ControlMode::PercentOutput, .15);
	manip->rightIntakeMotor->Set(ControlMode::PercentOutput, -.15);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.08);
	setMotors(.3,.3,3.2);//2.8
	Wait(.3);
	turnRobot(-.4, 1.1);//right turn
	Wait(.2);
	if(!lift->upperLimitTester())liftTime(.3,.8);
	Wait(.1);
	setMotors(.2,.2,1);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .25);
	Wait(.4);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.15);
	manip->AutoOuttake();
	setMotors(-.25,-.25,1);
	if(!lift->lowerLimitTester())liftTime(-.1,1);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .05);
	Wait(1);
	doAuto = 0;
	}
	else auto0();
//	if(gameData[0] == 'L')
//	{
//		manip->setPos(1);//releases intake
//		driveStraight(1,50000);
//		drive->autoTurn(90); //function not final
//		driveStraight(1,1000);
//		lift->liftAuto(1,5000);
//		manip->AutoOuttake();
//	}
//	else
//	{
//		manip->setPos(1);//releases intake
//		driveStraight(1,50000);
//		drive->autoTurn(90);
//		driveStraight(1,50000);
//		drive->autoTurn(90); //function not final
//		driveStraight(1,5000);
//		lift->liftAuto(1,5000);
//		manip->AutoOuttake();
//	}
}

void Auto::auto4()
{
	manip->leftIntakeMotor->Set(ControlMode::PercentOutput, .15);
	manip->rightIntakeMotor->Set(ControlMode::PercentOutput, -.15);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.1);
	drive->resetEncoder();
	Wait(.1);
	driveStraight(.5, 45000);
	Wait(.3);
	drive->resetEncoder();
	Wait(.1);
	encTurn(-.4,.4,12000);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .24);
	Wait(.3);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.09);
	lift->resetLiftEncoder();
	Wait(.1);
	encLift(.3,25000);
	drive->resetEncoder();
	Wait(.1);
	driveStraight(.2, 1000);
	manip->AutoOuttake();
	drive->resetEncoder();
	Wait(.1);
	driveStraight(-.2, 1000);
	if(!lift->lowerLimitTester())liftTime(-.4,2);
	drive->resetEncoder();
	Wait(.1);
	encTurn(.4,-.4,12000);
	drive->resetEncoder();
	Wait(.1);
	driveStraight(-.4, 20000);
	drive->resetEncoder();
	Wait(.1);
	encTurn(.4,-.4,8000);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .5);
	Wait(.6);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.05);
	manip->leftIntakeMotor->Set(ControlMode::PercentOutput, .8);
	manip->rightIntakeMotor->Set(ControlMode::PercentOutput, -.5);
	drive->resetEncoder();
	Wait(.1);
	driveStraight(.3,8500);
	manip->leftIntakeMotor->Set(ControlMode::PercentOutput, .9);
	manip->rightIntakeMotor->Set(ControlMode::PercentOutput, -.6);
	Wait(.3);
	manip->leftIntakeMotor->Set(ControlMode::PercentOutput, .15);
	manip->rightIntakeMotor->Set(ControlMode::PercentOutput, -.15);
	drive->resetEncoder();
	Wait(.1);
	driveStraight(-.3,8500);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.6);
	Wait(.4);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.09);
	drive->resetEncoder();
	Wait(.1);
	encTurn(-.4,.4,8000);
	drive->resetEncoder();
	Wait(.1);
	driveStraight(.4, 20000);
	drive->resetEncoder();
	Wait(.1);
	encTurn(.4,-.4,8000);
	lift->resetLiftEncoder();
	Wait(.1);
	encLift(.3,25000);
	drive->resetEncoder();
	Wait(.1);
	driveStraight(.2, 1000);
	manip->AutoOuttake();
//	if(gameData[1] == 'L')
//	{
//		manip->setPos(1);
//		driveStraight(.7,100000);
//		drive->autoTurn(270);
//		driveStraight(1,2000);
//		lift->liftAuto(1,7000);
//		manip->AutoOuttake();
//	}
//	else
//	{
//		manip->setPos(1);
//		driveStraight(.7,80000);
//		drive->autoTurn(270);
//		driveStraight(1,60000);
//		drive->autoTurn(90);
//		driveStraight(1,6000);
//		lift->liftAuto(1,7000);
//		manip->AutoOuttake();
//	}
}

void Auto::auto5()
{
	if(gameData[1] == 'L')
	{
		manip->setPos(1);
		driveStraight(1,15000);
		drive->autoTurn(90);
		driveStraight(1,25000);
		drive->autoTurn(270);
		driveStraight(1,90000);
		drive->autoTurn(270);
		driveStraight(1,10000);
		lift->liftAuto(1,7000);
		manip->AutoOuttake();
	}
	else
	{
		manip->setPos(1);
		driveStraight(1,15000);
		drive->autoTurn(270);
		driveStraight(1,25000);
		drive->autoTurn(90);
		driveStraight(1,90000);
		drive->autoTurn(90);
		driveStraight(1,10000);
		lift->liftAuto(1,7000);
		manip->AutoOuttake();
	}
}

void Auto::auto5_5()
{
	if(gameData[1] == 'L')
	{
		Wait(1.5);
		manip->setPos(1);
		driveStraight(1,15000);
		drive->autoTurn(90);
		driveStraight(1,25000);
		drive->autoTurn(270);
		driveStraight(1,90000);
		drive->autoTurn(270);
		driveStraight(1,10000);
		lift->liftAuto(1,7000);
		manip->AutoOuttake();
	}
	else
	{
		Wait(1.5);
		manip->setPos(1);
		driveStraight(1,15000);
		drive->autoTurn(270);
		driveStraight(1,25000);
		drive->autoTurn(90);
		driveStraight(1,90000);
		drive->autoTurn(90);
		driveStraight(1,10000);
		lift->liftAuto(1,7000);
		manip->AutoOuttake();
	}
}

void Auto::auto6()
{
	if(gameData[1] == 'L')
	{
		manip->setPos(1);
		driveStraight(.7,100000);
		drive->autoTurn(90);
		driveStraight(1,2000);
		lift->liftAuto(1,7000);
		manip->AutoOuttake();
	}
	else
	{
		manip->setPos(1);
		driveStraight(.7,80000);
		drive->autoTurn(90);
		driveStraight(1,60000);
		drive->autoTurn(270);
		driveStraight(1,6000);
		lift->liftAuto(1,7000);
		manip->AutoOuttake();
	}

}

int Auto::dataVal()
{
	return dataTest;
}

int Auto::autoSelector()
{
	if(selector && counter < 3)
	{
		counter++;
		Wait(0.3);
	}
	else if(selector && counter >= 3)
	{
		counter = 0;
	}

	return counter;
}

void Auto::displayData()
{
	if(gameData[0] == 'L')
	{
		SmartDashboard::PutString("Data Position", "L");
	}
	else
	{
		SmartDashboard::PutString("Data Position", "R");
	}
}
