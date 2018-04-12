#include <Auto.h>


Auto::Auto()
{
	drive = new Drive;
	manip = new Manipulator;
	lift = new Lift;
	doxLog = new DoxLog;
	timer = new Timer;
	dataTest = 0;
	counter = 0;
	doAuto = 1;
	startAuto = 0;

	driveCurrent = drive->getLeftEnc();
	driveTarget = 0;
	driveError = 0;
	timerTime = 0;

	encCount = 0;
	encDistance = 0;
	encErrorL = 0;
	encErrorR = 0;
	autoTimer = 0;
	gyroError = 0;

	time = Timer::GetMatchTime();
}

void Auto::setGameData(std::string data)
{
	gameData = data;
}

Auto::~Auto()
{
//	selector = nullptr;
//
//	delete selector;

}

void Auto::driveStraight(float speed, int enc)
{
	if(speed > 0)
	{
		while(drive->getRightEnc() < enc)
		{
			float driveSpeed = ((-enc-drive->getRightEnc())/10000);
			if(driveSpeed<speed)
			{
				drive->updateDriveMotors(speed, speed);
				Wait(.01);
			}
			else
			{
				drive->updateDriveMotors(driveSpeed, driveSpeed);
				Wait(.01);
			}
		}
		drive->updateDriveMotors(0,0);
	}
	else
	{
		while(drive->getRightEnc() > -enc)
		{
			float driveSpeed = ((enc-drive->getRightEnc())/10000);
			if(driveSpeed<speed)
			{
				drive->updateDriveMotors(driveSpeed, driveSpeed);
				Wait(.01);
			}
			else
			{
				drive->updateDriveMotors(speed, speed);
				Wait(.01);
			}
		}
		drive->updateDriveMotors(0,0);
	}
}

void Auto::encTurn(float speedL, float speedR, int enc)
{
	if(speedL > speedR)
	{
		while((drive->getLeftEnc()) < (enc))// && drive->getRightEnc() > (-enc-1000))
		{
			drive->updateDriveMotors(-speedL, -speedR);
			Wait(.01);
		}
		drive->updateDriveMotors(0,0);
	}
	else
	{
		while((drive->getLeftEnc()) > (-enc))// && drive->getRightEnc() < -(-enc-1000))
		{
			drive->updateDriveMotors(-speedL, -speedR);
			Wait(.01);
		}
		drive->updateDriveMotors(0,0);
	}
}

void Auto::encLift(float speed, int enc)
{
	if(lift->getRightLiftEnc() < enc)
	{
		while(!lift->upperLimitTester() && lift->getRightLiftEnc() < enc)
		{
			lift->setLiftMotors(speed);
			Wait(.01);
		}
		lift->setLiftMotors(.05);
	}
	if(lift->getRightLiftEnc() > enc)
	{
		while(!lift->lowerLimitTester() && lift->getRightLiftEnc() < enc)
		{
			lift->setLiftMotors(-speed);
			Wait(.01);
		}
		lift->setLiftMotors(.05);
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
	drive->updateDriveMotors(speedL, speedR);
	Wait(time);
	drive->updateDriveMotors(0,0);
}

void Auto::turnRobot(float speed, float time)
{
	drive->updateDriveMotors(speed, speed);
	Wait(time);
	drive->updateDriveMotors(0,0);
}

void Auto::liftTime(float speed, float time)
{
	lift->setLiftMotors(speed);
	Wait(time);
	lift->setLiftMotors(.05);
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
	preCheck_Drive();
	preCheck_Lift();
	preCheck_Intake();
}

void Auto::preCheck_Drive()
{
//	doxLog->LogIt("Left Encoder Value", drive->getLeftEnc(), 0);
//	doxLog->LogIt("Right Encoder Value", drive->getRightEnc(), 0);
//	doxLog->LogIt("Shifter", drive->shifter->Get(), 0);
////	doxLog->LogIt("Front Left Motor Power Output", frontLeftMotor->GetMotorOutputVoltage(), 0);
////	doxLog->LogIt("Rear Left Motor Power Output", rearLeftMotor->GetMotorOutputVoltage(), 0);
////	doxLog->LogIt("Front Right Motor Power Output", frontRightMotor->GetMotorOutputVoltage(), 0);
////	doxLog->LogIt("Rear Right Motor Power Output", rearRightMotor->GetMotorOutputVoltage(), 0);
//	if(timerTime > 1 && timerTime < 2)
//	{
//		drive->frontLeftMotor->Set(ControlMode::Velocity, 30);
//	}
//	if(timerTime > 2 && timerTime < 3)
//	{
//		drive->frontRightMotor->Set(ControlMode::Velocity, 30);
//	}
//	if(timerTime > 3 && timerTime < 4)
//	{
//		drive->rearRightMotor->Set(ControlMode::Velocity, 30);
//	}
//	if(timerTime > 4 && timerTime < 5)
//	{
//		drive->rearLeftMotor->Set(ControlMode::Velocity, 30);
//	}
//	if(timerTime > 5 && timerTime < 6)
//	{
//		drive->shifter->Set(DoubleSolenoid::kReverse);
//	}
//	if(timerTime > 6 && timerTime < 7)
//	{
//		drive->shifter->Set(DoubleSolenoid::kForward);
//	}
}

void Auto::preCheck_Lift()
{
//	doxLog->LogIt("Left Lift Encoder", lift->getLeftLiftEnc(), 0);
//	doxLog->LogIt("Right Lift Encoder", lift->getRightLiftEnc(), 0);
//	doxLog->LogIt("Upper Limit Switch", lift->upperLimitTester(), 0);
//	doxLog->LogIt("Lower Limit Switch", lift->lowerLimitTester(), 0);
//	doxLog->LogIt("Lift Piston", lift->liftPiston->Get(), 0);
//	doxLog->LogIt("Rung Piston", lift->rungPiston->Get(), 0);
//	if(timerTime > 1 && timerTime < 2)
//	{
//
//	}
//	if(timerTime > 2 && timerTime < 3)
//	{
//
//	}
//	if(timerTime > 3 && timerTime < 4)
//	{
//
//	}
//	if(timerTime > 4 && timerTime < 5)
//	{
//
//	}
//	if(timerTime > 5 && timerTime < 6)
//	{
//
//	}
//	if(timerTime > 6 && timerTime < 7)
//	{
//
//	}
}

void Auto::preCheck_Intake()
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

		//manip->setPos(1);//releases intake
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

		//manip->setPos(1);//releases intake
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
		//manip->setPos(1);
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
		//manip->setPos(1);
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
		//manip->setPos(1);//releases intake
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
		//manip->setPos(1);//releases intake
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
	startAuto = 1;
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
	if(gameData.length() <= 0)
	{
		return;
	}

	if(gameData[0] == 'L')
	{
	manip->leftIntakeMotor->Set(ControlMode::PercentOutput, -.15);
	manip->rightIntakeMotor->Set(ControlMode::PercentOutput, .15);
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
	//------left side of switch:
	startAuto = 1;
	if(gameData.length() <= 0)
	{
		return;
	}


	//----Time:

//	if(gameData[0] == 'L')
//	{
//		printf("starting auto 2");
//		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, -.15);
//		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, .15);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.1);
//		setMotors(.4, .4, .63);
//		Wait(.3);
//		turnRobot(.35, 1);//left turn
//		setMotors(.4, -.4, 1);
//		turnRobot(-.42, .8);//right turn
//		Wait(.2);
//		//if(!lift->upperLimitTester())liftTime(.34,.7);
//		lift->resetLiftEncoder();
//		Wait(.1);
//		encLift(.3,5000);
//		Wait(.1);
//		setMotors(.38,.38,1);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .24);
//		Wait(.3);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.09);
//		//manip->pivotIntake(0,1,0);
//		manip->AutoOuttake();
//		//setMotors(-.15,-.15,1);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.38);
//		if(!lift->lowerLimitTester())liftTime(-.2,1);
//		//
//		//Second cube
//		//
//		setMotors(-.4,-.4,.4);
//		turnRobot(-.4, 1);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .5);
//		Wait(.6);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.05);
//		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, .8);
//		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, -.5);
//		drive->resetEncoder();
//		Wait(.1);
//		setMotors(.4,.4,.4);
//		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, .9);
//		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, -.6);
//		Wait(.3);
//		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, .15);
//		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, -.15);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.6);
//		Wait(.4);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.09);
//		drive->resetEncoder();
//		Wait(.1);
//		setMotors(-.3,-.3,.4);
//		Wait(.5);
//		turnRobot(.4, 1);
//		lift->resetLiftEncoder();
//		Wait(.1);
//		encLift(.3,5000);
//		//if(!lift->upperLimitTester())liftTime(.34,.8);
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(.3,3500);
//		//setMotors(.3,.3,.4);
//		manip->AutoOuttake();
//		drive->resetEncoder();
//		Wait(.1);
//		//driveStraight(-.3,3500);
//		encTurn(.4,0,12000);
//		//setMotors(-.3,-.3,.2);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.38);
//		if(!lift->lowerLimitTester())liftTime(-.2,1);
//		//
//		//Third
//		//
//		drive->resetEncoder();
//		Wait(.1);
//		//driveStraight(-.2,1000);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .5);
//		Wait(.6);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.05);
//		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, .8);
//		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, -.5);
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(.4,12000);
//		//setMotors(.4,.4,.4);
//		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, .9);
//		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, -.6);
//		Wait(.3);
//		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, .15);
//		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, -.15);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.6);
//		Wait(.4);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.09);
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(-.35,6000);
//		//setMotors(-.3,-.3,.4);
//		Wait(.5);
//		drive->resetEncoder();
//		Wait(.1);
//		encTurn(-.4,.4,3000);
//		//turnRobot(.4, 1);
//		lift->resetLiftEncoder();
//		Wait(.1);
//		encLift(.3,5000);
//		//if(!lift->upperLimitTester())liftTime(.34,.8);
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(.3,4500);
//		//setMotors(.3,.3,.4);
//		manip->AutoOuttake();
//		driveStraight(-.3,2000);
//		//setMotors(-.3,-.3,.2);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.38);
//		if(!lift->lowerLimitTester())liftTime(-.1,1);
//		//
//		doAuto = 0;
//	}


	//----Encoder:

//	if(gameData[0] == 'L')
//	{
//		printf("starting auto 2");
//		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, -.15);
//		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, .15);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.1);
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(.4, 1800);
//		Wait(.3);
//		drive->resetEncoder();
//		Wait(.1);
//		encTurn(-.4,.4,3800);
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(.35,20000);
//		Wait(.5);
//		drive->resetEncoder();
//		Wait(.1);
//		encTurn(.3,-.3,1500);//13500
//		Wait(.2);
//		lift->resetLiftEncoder();
//		Wait(.1);
//		encLift(.3,5000);
//		Wait(.1);
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(.3,2800);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .24);
//		Wait(.3);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.09);
//		manip->AutoOuttake();
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.4);
//		if(!lift->lowerLimitTester())liftTime(-.2,1);
//		//
//		//Second cube
//		//
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(-.3,3500);
//		Wait(.1);
//		drive->resetEncoder();
//		Wait(.1);
//		encTurn(.32,-.32,4700);
//		drive->resetEncoder();
//		Wait(.1);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .5);
//		Wait(.6);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.05);
//		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, .8);
//		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, -.5);
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(.45,9000);
//		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, .9);
//		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, -.6);
//		Wait(.3);
//		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, .15);
//		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, -.15);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.6);
//		Wait(.4);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.09);
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(-.3,5000);
//		Wait(.5);
//		drive->resetEncoder();
//		Wait(.1);
//		encTurn(-.4,.4,1500);
//		lift->resetLiftEncoder();
//		Wait(.1);
//		encLift(.3,8000);
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(.3,3500);
//		manip->AutoOuttake();
//		drive->resetEncoder();
//		Wait(.1);
//		encTurn(.4,0,12000);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.38);
//		if(!lift->lowerLimitTester())liftTime(-.2,1);
//		//
//		//Third
//		//
//		drive->resetEncoder();
//		Wait(.1);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .5);
//		Wait(.6);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.05);
//		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, .8);
//		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, -.5);
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(.4,12000);
//		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, .9);
//		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, -.6);
//		Wait(.3);
//		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, .15);
//		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, -.15);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.6);
//		Wait(.4);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.09);
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(-.35,6000);
//		Wait(.5);
//		drive->resetEncoder();
//		Wait(.1);
//		encTurn(-.4,.4,3000);
//		lift->resetLiftEncoder();
//		Wait(.1);
//		encLift(.3,5000);
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(.3,4500);
//		manip->AutoOuttake();
//		driveStraight(-.3,2000);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.38);
//		if(!lift->lowerLimitTester())liftTime(-.1,1);
//		//
//		doAuto = 0;
//	}

	//----Gyro:

	if(gameData[0] == 'L')
	{
		printf("starting auto 2");
		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, -.15);
		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, .15);
		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.1);
		drive->resetEncoder();
		Wait(.1);
		driveStraight(.5, 2000);
		drive->pGyon->GetYawPitchRoll(ypr);
		Wait(.1);
		sGyroTurn(38,.5);
		drive->resetEncoder();
		Wait(.1);
		driveStraight(.54,18000);
		Wait(.15);
		sGyroTurn(-38,.5);
		//Wait(.2);
		lift->resetLiftEncoder();
		Wait(.1);
		encLift(.55,6500);
		Wait(.1);
		drive->resetEncoder();
		Wait(.1);
		driveStraight(.48,5650);
		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .24);
		Wait(.28);
		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.1);
		manip->AutoOuttake();
		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.55);
		if(!lift->lowerLimitTester())liftTime(-.3,.5);
		//
		//Second cube
		//
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(-.35,2700);
//		Wait(.1);
//		sGyroTurn(-50,.4);
//		drive->resetEncoder();
//		Wait(.1);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .5);
//		Wait(.6);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.05);
//		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, -1);
//		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, .7);
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(.28,7500);
//		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, -1);
//		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, 1);
//		Wait(.5);
//		driveStraight(.23,3500);
//		Wait(.5);
//		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, -.15);
//		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, .15);
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(-.3,1000);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.7);
//		Wait(.32);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.25);
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(-.3,5000);
//		lift->setLiftMotors(.31);
//		Wait(.1);
//		sGyroTurn(45,.4);
//		lift->resetLiftEncoder();
//		Wait(.1);
//		//encLift(.3,5500);
//		lift->setLiftMotors(.06);
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(.3,3000);
//		manip->AutoOuttake();
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(-.5,2500);
//		drive->resetEncoder();
//		Wait(.1);
//		sGyroTurn(-55,.4);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.38);
//		if(!lift->lowerLimitTester())liftTime(-.2,1);
		doAuto = 0;
		//
		//Third
		//
//		drive->resetEncoder();
//		Wait(.1);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .5);
//		Wait(.6);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.05);
//		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, -1);
//		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, .7);
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(.3,12000);
//		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, -1);
//		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, 1);
//		Wait(.4);
//		driveStraight(.23,3900);
//		Wait(.2);
//		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, -.15);
//		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, .15);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.7);
//		Wait(.32);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.25);
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(-.5,8000);
//		Wait(.5);
//		sGyroTurn(50,.35);
//		lift->resetLiftEncoder();
//		Wait(.1);
//		encLift(.5,5500);
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(.3,4500);
//		manip->AutoOuttake();
//		driveStraight(-.3,2000);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.38);
//		if(!lift->lowerLimitTester())liftTime(-.1,1);
//		//
//		doAuto = 0;
	}

	else if(gameData[0] == 'R')
	//right side of switch:


	//----Time:
//	{
//	manip->leftIntakeMotor->Set(ControlMode::PercentOutput, -.15);
//	manip->rightIntakeMotor->Set(ControlMode::PercentOutput, .15);
//	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.1);
//	drive->resetEncoder();
//	Wait(.1);
//	setMotors(.4, .4, .65);
//	Wait(.3);
//	turnRobot(-.35, 1);//left turn
//	setMotors(.5,.5,1.2);
//	//Wait(2);
//	turnRobot(.3, .8);//right turn
//	Wait(.2);
//	if(!lift->upperLimitTester())liftTime(.34,.8);
//	Wait(.1);
//	setMotors(.38,.38,1);
//	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .24);
//	Wait(.3);
//	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.09);
//	manip->AutoOuttake();
//	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.38);
//	if(!lift->lowerLimitTester())liftTime(-.1,1);
//	setMotors(-.4,-.4,.35);
//	turnRobot(.4, 1.1);
//	setMotors(-.3,-.3,.2);
//	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .5);
//	Wait(.6);
//	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.05);
//	manip->leftIntakeMotor->Set(ControlMode::PercentOutput, .8);
//	manip->rightIntakeMotor->Set(ControlMode::PercentOutput, -.5);
//	setMotors(.4,.4,.4);
//	manip->leftIntakeMotor->Set(ControlMode::PercentOutput, .9);
//	manip->rightIntakeMotor->Set(ControlMode::PercentOutput, -.6);
//	Wait(.3);
//	manip->leftIntakeMotor->Set(ControlMode::PercentOutput, .15);
//	manip->rightIntakeMotor->Set(ControlMode::PercentOutput, -.15);
//	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.6);
//	Wait(.4);
//	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.09);
//	setMotors(-.3,-.3,.4);
//	turnRobot(-.4, 1);
//	if(!lift->upperLimitTester())liftTime(.34,.8);
//	setMotors(.3,.3,.4);
//	manip->AutoOuttake();
//	setMotors(-.3,-.3,.2);
//	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.38);
//	if(!lift->lowerLimitTester())liftTime(-.1,1);
//	//
//	doAuto = 0;
//	}

	//----Encoder:

//	{
//		printf("starting auto 2");
//		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, -.15);
//		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, .15);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.1);
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(.3, 2000);
//		Wait(.3);
//		drive->resetEncoder();
//		Wait(.1);
//		encTurn(.4,-.4,1000);
//		Wait(.1);
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(.3,8500);
//		Wait(.5);
//		drive->resetEncoder();
//		Wait(.2);
//		encTurn(-.25,.25,3900);//13500
//		Wait(.2);
//		lift->resetLiftEncoder();
//		Wait(.1);
//		encLift(.3,5000);
//		Wait(.1);
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(.4,4200);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .24);
//		Wait(.3);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.09);
//		manip->AutoOuttake();
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.38);
//		if(!lift->lowerLimitTester())liftTime(-.2,1);
//		//
//		//Second cube
//		//
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(-.3,2800);
//		Wait(.1);
//		drive->resetEncoder();
//		Wait(.1);
//		encTurn(-.25,.25,800);
//		drive->resetEncoder();
//		Wait(.1);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .5);
//		Wait(.6);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.05);
//		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, .8);
//		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, -.5);
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(.3,7500);
//		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, .9);
//		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, -.6);
//		Wait(.3);
//		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, .15);
//		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, -.15);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.6);
//		Wait(.4);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.09);
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(-.3,5000);
//		Wait(.5);
//		drive->resetEncoder();
//		Wait(.1);
//		encTurn(.3,-.3,4400);
//		lift->resetLiftEncoder();
//		Wait(.1);
//		encLift(.3,5000);
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(.3,3800);
//		manip->AutoOuttake();
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(.2,500);
//		drive->resetEncoder();
//		Wait(.1);
//		//encTurn(0,.4,10000);
//		while((drive->getRightEnc()) < (12000))
//		{
//			drive->updateDriveMotors(0, -.4);
//			Wait(.01);
//		}
//		drive->updateDriveMotors(0,0);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.38);
//		if(!lift->lowerLimitTester())liftTime(-.2,1);
//		//
//		//Third
//		//
//		drive->resetEncoder();
//		Wait(.1);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .5);
//		Wait(.6);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.05);
//		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, .8);
//		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, -.5);
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(.4,10000);
//		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, .9);
//		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, -.6);
//		Wait(.3);
//		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, .15);
//		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, -.15);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.6);
//		Wait(.4);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.09);
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(-.35,6000);
//		Wait(.5);
//		drive->resetEncoder();
//		Wait(.1);
//		encTurn(.4,-.4,4000);
//		lift->resetLiftEncoder();
//		Wait(.1);
//		encLift(.3,5000);
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(.3,4500);
//		manip->AutoOuttake();
//		driveStraight(-.2,1000);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.38);
//		if(!lift->lowerLimitTester())liftTime(-.1,1);
//		//
//		doAuto = 0;
//	}

	//----Gyro:

	{
		printf("starting auto 2");
		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, -.15);
		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, .15);
		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.1);
		drive->resetEncoder();
		Wait(.1);
		driveStraight(.5, 2000);
				drive->pGyon->GetYawPitchRoll(ypr);
				Wait(.1);
				sGyroTurn(-38,.5);
				drive->resetEncoder();
				Wait(.1);
				driveStraight(.54,18000);
				Wait(.15);
				sGyroTurn(38,.5);
				//Wait(.2);
				lift->resetLiftEncoder();
				Wait(.1);
				encLift(.55,6500);
				Wait(.1);
				drive->resetEncoder();
				Wait(.1);
				driveStraight(.48,5650);
		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .3);
		Wait(.3);
		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.25);
		manip->AutoOuttake();
		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.55);
		if(!lift->lowerLimitTester())liftTime(-.3,.5);
		//
		//Second cube
		//
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(-.35,2700);
//		Wait(.1);
//		sGyroTurn(50,.4);
//		drive->resetEncoder();
//		Wait(.1);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .5);
//		Wait(.6);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.05);
//		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, -1);
//		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, .7);
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(.28,7500);
//		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, -1);
//		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, 1);
//		Wait(.5);
//		driveStraight(.23,3500);
//		Wait(.5);
//		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, -.15);
//		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, .15);
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(-.3,1000);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .3);
//		Wait(.3);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.25);
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(-.3,5000);
//		lift->setLiftMotors(.31);
//		Wait(.1);
//		sGyroTurn(-45,.4);
//		lift->resetLiftEncoder();
//		Wait(.1);
//		//encLift(.3,5500);
//		lift->setLiftMotors(.06);
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(.3,3000);
//		manip->AutoOuttake();
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(-.5,2500);
//		drive->resetEncoder();
//		Wait(.1);
//		sGyroTurn(55,.4);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.38);
//		if(!lift->lowerLimitTester())liftTime(-.2,1);
		doAuto = 0;
		//
		//Third
		//
//		drive->resetEncoder();
//		Wait(.1);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .5);
//		Wait(.6);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.05);
//		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, -1);
//		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, .7);
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(.3,12000);
//		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, -1);
//		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, 1);
//		Wait(.4);
//		driveStraight(.23,3900);
//		Wait(.2);
//		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, -.15);
//		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, .15);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.7);
//		Wait(.32);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.25);
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(-.5,8000);
//		Wait(.5);
//		sGyroTurn(-50,.35);
//		lift->resetLiftEncoder();
//		Wait(.1);
//		encLift(.5,5500);
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(.3,4500);
//		manip->AutoOuttake();
//		driveStraight(-.3,2000);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.38);
//		if(!lift->lowerLimitTester())liftTime(-.1,1);
		//
		doAuto = 0;
	}
}

void Auto::auto3()
{
	if(gameData.length() <= 0)
	{
		return;
	}
	if(gameData[0] == 'L')
	{
	manip->leftIntakeMotor->Set(ControlMode::PercentOutput, -.15);
	manip->rightIntakeMotor->Set(ControlMode::PercentOutput, .15);
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
	if(gameData.length() <= 0)
			{
		driveStraight(.4, 20000);
				doAuto = 0;
				return;
			}
	startAuto = 1;
	if(gameData[1] == 'L')
	{
		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, -.15);
		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, .15);
		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.1);
		setMotors(.1,-.1,.1);
		drive->resetEncoder();
		Wait(.1);
		driveStraight(.8, 90000);//45000
		driveStraight(.4, 40000);
		Wait(.3);
		sGyroTurn(-90,.4);
		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .3);
		Wait(.3);
		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.25);
		lift->resetLiftEncoder();
		Wait(.1);
		encLift(.7,26000);//.7
		drive->resetEncoder();
		Wait(.1);
		driveStraight(.25, 800);
		//manip->AutoOuttake();
		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, .28);
		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, -.28);
		Wait(.8);
		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, 0);
		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, 0);
		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .1);
		drive->resetEncoder();
		Wait(.1);
		driveStraight(-.2, 800);
		if(!lift->lowerLimitTester())liftTime(-.4,.6);
		if(!lift->lowerLimitTester())liftTime(-.2,.8);
		if(!lift->lowerLimitTester())liftTime(-.1,.8);
		doAuto = 0;

		//2nd
//		drive->pGyon->SetYaw(0, 0);
//		drive->pGyon->GetYawPitchRoll(ypr);
//		sGyroTurn(-75,.5);
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(.45, 3600);
//		sGyroTurn(38,.5);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .3);
//		Wait(.6);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.05);
//		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, -1);
//		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, .7);
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(.5,10000);
//		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, -1);
//		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, 1);
//		Wait(.5);
//		driveStraight(.23,2000);
//		Wait(.5);
//		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, -.15);
//		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, .15);
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(-.3,1000);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.8);
//		Wait(.32);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .05);
//		driveStraight(-.6,8000);
//		drive->pGyon->SetYaw(0, 0);
//		drive->pGyon->GetYawPitchRoll(ypr);
//		sGyroTurn(40,.4);
////		drive->resetEncoder();
////		Wait(.1);
////		driveStraight(-.3, 3000);
////		sGyroTurn(90,.38);
//		lift->resetLiftEncoder();
//		Wait(.1);
//		encLift(.4,26000);//.7
//		drive->resetEncoder();
//		Wait(.1);
//		driveStraight(.2, 2000);
//		manip->AutoOuttake();
//		driveStraight(-.2, 500);
//		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .1);
//		if(!lift->lowerLimitTester())liftTime(-.15,3);
//		//manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .2);
//		Wait(2);
//		doAuto = 0;
	}
	else if(gameData[0] == 'L')
	{
		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, -.15);
		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, .15);
		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.1);
		//setMotors(.6,-.6,.2);
		drive->resetEncoder();
		Wait(.1);
		driveStraight(.8, 35000);//45000
		//driveStraight(.4, 30000);
		Wait(.3);
		sGyroTurn(-90,.5);
		lift->resetLiftEncoder();
		Wait(.1);
		encLift(.7,1000);//.7
		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .3);
		Wait(.4);
		manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.25);
		Wait(2);
		encLift(.7,7000);//.7
		drive->resetEncoder();
		Wait(.1);
		driveStraight(.25, 800);
		manip->AutoOuttake();
//		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, .28);
//		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, -.28);
//		Wait(.8);
//		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, 0);
//		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, 0);
		//manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .1);
		drive->resetEncoder();
		drive->resetEncoder();
		Wait(.1);
		driveStraight(-.2, 800);
		if(!lift->lowerLimitTester())liftTime(-.3,.6);
		doAuto = 0;
	}
	else
	{
		driveStraight(.4, 23000);
		doAuto = 0;
	}
}

void Auto::auto5()
{
	if(gameData.length() <= 0)
	{
		return;
	}
	if(gameData[1] == 'L')
	{
		//manip->setPos(1);
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
	//	manip->setPos(1);
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
	if(gameData.length() <= 0)
	{
		return;
	}
	if(gameData[1] == 'L')
	{
		Wait(1.5);
	//	manip->setPos(1);
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
		//manip->setPos(1);
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
	if(gameData.length() <= 0)
			{
		driveStraight(.4, 20000);
						doAuto = 0;
				return;
			}
	startAuto = 1;
		if(gameData[1] == 'R')
		{
			manip->leftIntakeMotor->Set(ControlMode::PercentOutput, -.15);
					manip->rightIntakeMotor->Set(ControlMode::PercentOutput, .15);
					manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.1);
					setMotors(-.4,.4,.1);
					drive->resetEncoder();
					Wait(.1);
					driveStraight(.8, 90000);//45000
					driveStraight(.4, 4000);
					Wait(.3);
					sGyroTurn(90,.4);
					manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .3);
							Wait(.3);
							manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.25);
					lift->resetLiftEncoder();
					Wait(.1);
					encLift(.7,26000);//.7
					drive->resetEncoder();
					Wait(.1);
					driveStraight(.25, 800);
					//manip->AutoOuttake();
					manip->leftIntakeMotor->Set(ControlMode::PercentOutput, .28);
					manip->rightIntakeMotor->Set(ControlMode::PercentOutput, -.28);
					Wait(.8);
					manip->leftIntakeMotor->Set(ControlMode::PercentOutput, 0);
					manip->rightIntakeMotor->Set(ControlMode::PercentOutput, 0);
					manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .1);
					drive->resetEncoder();
					Wait(.1);
					driveStraight(-.2, 800);
					if(!lift->lowerLimitTester())liftTime(-.4,.6);
					if(!lift->lowerLimitTester())liftTime(-.2,.8);
					if(!lift->lowerLimitTester())liftTime(-.1,.8);
					doAuto = 0;
			//2nd
//			drive->pGyon->SetYaw(0, 0);
//			drive->pGyon->GetYawPitchRoll(ypr);
//			sGyroTurn(75,.5);
//			drive->resetEncoder();
//			Wait(.1);
//			driveStraight(.45, 3600);
//			sGyroTurn(-38,.5);
//			manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .3);
//			Wait(.6);
//			manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.05);
//			manip->leftIntakeMotor->Set(ControlMode::PercentOutput, -1);
//			manip->rightIntakeMotor->Set(ControlMode::PercentOutput, .7);
//			drive->resetEncoder();
//			Wait(.1);
//			driveStraight(.5,10000);
//			manip->leftIntakeMotor->Set(ControlMode::PercentOutput, -1);
//			manip->rightIntakeMotor->Set(ControlMode::PercentOutput, 1);
//			Wait(.5);
//			driveStraight(.23,2000);
//			Wait(.5);
//			manip->leftIntakeMotor->Set(ControlMode::PercentOutput, -.15);
//			manip->rightIntakeMotor->Set(ControlMode::PercentOutput, .15);
//			drive->resetEncoder();
//			Wait(.1);
//			driveStraight(-.3,1000);
//			manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.8);
//			Wait(.32);
//			manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .05);
//			driveStraight(-.6,8000);
//			drive->pGyon->SetYaw(0, 0);
//			drive->pGyon->GetYawPitchRoll(ypr);
//			sGyroTurn(-40,.4);
//	//		drive->resetEncoder();
//	//		Wait(.1);
//	//		driveStraight(-.3, 3000);
//	//		sGyroTurn(90,.38);
//			lift->resetLiftEncoder();
//			Wait(.1);
//			encLift(.4,26000);//.7
//			drive->resetEncoder();
//			Wait(.1);
//			driveStraight(.2, 2000);
//			manip->AutoOuttake();
//			driveStraight(-.2, 500);
//			manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .1);
//			if(!lift->lowerLimitTester())liftTime(-.15,3);
//			//manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .2);
//			Wait(2);
//			doAuto = 0;
		}
	else if(gameData[0] == 'R')
		{
			manip->leftIntakeMotor->Set(ControlMode::PercentOutput, -.15);
			manip->rightIntakeMotor->Set(ControlMode::PercentOutput, .15);
			manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.1);
			//setMotors(.6,-.6,.2);
			drive->resetEncoder();
			Wait(.1);
			driveStraight(.8, 35000);//45000
			//driveStraight(.4, 30000);
			Wait(.3);
			sGyroTurn(90,.5);
			lift->resetLiftEncoder();
			Wait(.1);
			encLift(.7,1000);//.7
			manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .3);
			Wait(.4);
			manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.25);
			encLift(.7,7000);//.7
			drive->resetEncoder();
			Wait(.1);
			driveStraight(.25, 800);
			//manip->AutoOuttake();
			manip->leftIntakeMotor->Set(ControlMode::PercentOutput, .28);
			manip->rightIntakeMotor->Set(ControlMode::PercentOutput, -.28);
			Wait(.8);
			manip->leftIntakeMotor->Set(ControlMode::PercentOutput, 0);
			manip->rightIntakeMotor->Set(ControlMode::PercentOutput, 0);
			manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .1);
			drive->resetEncoder();
			drive->resetEncoder();
			Wait(.1);
			driveStraight(-.2, 800);
			if(!lift->lowerLimitTester())liftTime(-.3,.6);
			doAuto = 0;
			doAuto = 0;
		}
		else
		{
			driveStraight(.4, 23000);
			doAuto = 0;
		}
	}

//	void Auto::auto5()
//	{
//		if(gameData.length() <= 0)
//		{
//			return;
//		}
//		if(gameData[1] == 'L')
//		{
//			//manip->setPos(1);
//			driveStraight(1,15000);
//			drive->autoTurn(90);
//			driveStraight(1,25000);
//			drive->autoTurn(270);
//			driveStraight(1,90000);
//			drive->autoTurn(270);
//			driveStraight(1,10000);
//			lift->liftAuto(1,7000);
//			manip->AutoOuttake();
//		}
//		else
//		{
//		//	manip->setPos(1);
//			driveStraight(1,15000);
//			drive->autoTurn(270);
//			driveStraight(1,25000);
//			drive->autoTurn(90);
//			driveStraight(1,90000);
//			drive->autoTurn(90);
//			driveStraight(1,10000);
//			lift->liftAuto(1,7000);
//			manip->AutoOuttake();
//		}
//	}


void Auto::testAuto()
{
	drive->updateDriveMotors(.25,-.25);
}

int Auto::dataVal()
{
	return dataTest;
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


void Auto::distanceDrive(float distance)//unit determined by the unit of circumference
{
	encDistance = encCount * (distance);

	while(autoTimer < Auto_Timeout)
	{
		if(encErrorR < 3 && encErrorL < 3 && encErrorR > -3 && encErrorL > -3)
		{
			autoTimer += 1;
		}
		if(encErrorR > 3 || encErrorR < -3)
		{
			autoTimer = 0;
			float encRight = drive->getRightEnc();
			encErrorR = encDistance - encRight;
			float motorFactorR = (encErrorR/40.0);
			if (motorFactorR > 1) motorFactorR = 1;
			if (motorFactorR < -1) motorFactorR = -1;
			float speedR = Max_Motor_Velocity * motorFactorR;
			drive->rearRightMotor->Set(ControlMode::Velocity, speedR);
			drive->frontRightMotor->Set(ControlMode::Follower, Drive_Rear_Right_Motor_Channel);
		}
		if(encErrorL > 3 || encErrorL < -3)
		{
			autoTimer = 0;
			float encLeft = drive->getLeftEnc();
			encErrorL = encDistance - encLeft;
			float motorFactorL = (encErrorR/40.0);
			if (motorFactorL > 1) motorFactorL = 1;
			if (motorFactorL < -1) motorFactorL = -1;
			float speedL = Max_Motor_Velocity * motorFactorL;
			drive->rearLeftMotor->Set(ControlMode::Velocity, speedL);
			drive->frontLeftMotor->Set(ControlMode::Follower, Drive_Rear_Left_Motor_Channel);
		}
	}

}

float Auto::getEncCount(float diameter)
{
	return encCount = /*(3.1415*2*4.24)->*/26.64*diameter/390756;
}

void Auto::sGyroTurn(float heading, float speed)
{
	if(heading > 0)
	{
		while(ypr[0] < heading+2)
		{
			SmartDashboard::PutNumber("Gyro Value", ypr[0]);
			drive->pGyon->GetYawPitchRoll(ypr);
			if(ypr[0] < heading-5)
			{
				drive->updateDriveMotors(speed,-speed);
			}
			if(ypr[0] > heading-5 && ypr[0] < heading)
			{
				drive->updateDriveMotors(.25,-.25);
			}
		}
		drive->updateDriveMotors(0,0);
	}
	if(heading < 0)
	{
		while(ypr[0] > heading-2)
		{
			SmartDashboard::PutNumber("Gyro Value", ypr[0]);
			drive->pGyon->GetYawPitchRoll(ypr);
			if(ypr[0] > heading+5)
			{
				drive->updateDriveMotors(-speed,speed);
			}
			if(ypr[0] < heading+5 && ypr[0] > heading)
			{
				drive->updateDriveMotors(-.25,.25);
			}
		}
		drive->updateDriveMotors(0,0);
	}
	drive->pGyon->SetYaw(0, 0);
	Wait(.1);
}

void Auto::turnByGyro(float heading)
{
	while(autoTimer < Auto_Timeout)
	{

		drive->getYPR();
		double currentHeading = drive->ypr[0];
		gyroError = currentHeading - heading;
		SmartDashboard::PutNumber("Gyro Value", ypr[0]);
		SmartDashboard::PutNumber("Auto Timer", autoTimer);
		if(gyroError < 3 && gyroError > -3)
		{
			autoTimer += 1;
		}
		if(gyroError > 3 || gyroError < -3)
		{
			drive->getYPR();
			autoTimer = SmartDashboard::GetNumber("timer Value", 0);

			float motorFactor = (gyroError/40.0);
			if (motorFactor > 1) motorFactor = 1;
			if (motorFactor < -1) motorFactor = -1;
			float speed = Max_Motor_Velocity * motorFactor;
			SmartDashboard::PutNumber("Gyro Value", ypr[0]);
			drive->rearLeftMotor->Set(ControlMode::Velocity, -speed);
			drive->frontLeftMotor->Set(ControlMode::Follower, Drive_Rear_Left_Motor_Channel);

			drive->rearRightMotor->Set(ControlMode::Velocity, speed);
			drive->frontRightMotor->Set(ControlMode::Follower, Drive_Rear_Right_Motor_Channel);
			drive->getYPR();
		}
		Wait(.01);
	}
}
