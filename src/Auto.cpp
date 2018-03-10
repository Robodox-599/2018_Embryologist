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

}

Auto::~Auto()
{
	selector = nullptr;

	delete selector;
}

void Auto::driveStraight(float speed, int enc)
{
	//drive->resetEncoder();
	if(-speed > 0)
	{
		while(drive->getLeftEnc() > -enc)// && drive->getRightEnc() > -enc)//Dummy values
		{
		drive->updateLeftMotors(-speed);
		drive->updateRightMotors(-speed);
		}
		drive->updateLeftMotors(0);
		drive->updateRightMotors(0);
		//drive->resetEncoder();
	}
	if(-speed < 0)
	{
		while(drive->getLeftEnc() < enc )//&& drive->getRightEnc() < enc)//Dummy values
		{
		drive->updateLeftMotors(-speed);
		drive->updateRightMotors(-speed);
		}
		drive->updateLeftMotors(0);
		drive->updateRightMotors(0);
				//drive->resetEncoder();
	}
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
	manip->leftIntakeMotor->Set(ControlMode::PercentOutput, -.15);
	manip->rightIntakeMotor->Set(ControlMode::PercentOutput, .15);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.08);
	setMotors(.3,.3,1.5);//2.8
	Wait(.3);
	turnRobot(-.4, 1.1);//left turn
	setMotors(.2,.2,.5);
	turnRobot(.4, 1.1);//right turn
	Wait(.2);
	if(!lift->upperLimitTester())liftTime(.3,.8);
	Wait(.1);
	setMotors(.24,.24,1);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .25);
	Wait(.3);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.09);
	manip->AutoOuttake();
	setMotors(-.25,-.25,1);
	if(!lift->lowerLimitTester())liftTime(-.1,1);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .05);
	Wait(1);
	doAuto = 0;


	//right side of switch:
	manip->leftIntakeMotor->Set(ControlMode::PercentOutput, -.15);
	manip->rightIntakeMotor->Set(ControlMode::PercentOutput, .15);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.08);
	setMotors(.3,.3,1.5);//2.8
	Wait(.3);
	turnRobot(.4, 1.1);//right turn
	setMotors(.2,.2,.5);
	turnRobot(-.4, 1.1);//left turn
	Wait(.2);
	if(!lift->upperLimitTester())liftTime(.3,.8);
	Wait(.1);
	setMotors(.24,.24,1);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .25);
	Wait(.3);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.09);
	manip->AutoOuttake();
	setMotors(-.25,-.25,1);
	if(!lift->lowerLimitTester())liftTime(-.1,1);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .05);
	Wait(1);
	doAuto = 0;

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
	manip->leftIntakeMotor->Set(ControlMode::PercentOutput, -.15);
	manip->rightIntakeMotor->Set(ControlMode::PercentOutput, .15);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.08);
	setMotors(.3,.3,.3);//2.8
	Wait(.3);
	turnRobot(.4, 1.1);//right turn
	Wait(.2);
	if(!lift->upperLimitTester())liftTime(.3,.8);
	Wait(.1);
	setMotors(.24,.24,1);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .25);
	Wait(.3);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, -.09);
	manip->AutoOuttake();
	setMotors(-.25,-.25,1);
	if(!lift->lowerLimitTester())liftTime(-.1,1);
	manip->liftIntakeMotor->Set(ControlMode::PercentOutput, .05);
	Wait(1);
	doAuto = 0;
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
	if(gameData[1] == 'L')
	{
		manip->setPos(1);
		driveStraight(.7,100000);
		drive->autoTurn(270);
		driveStraight(1,2000);
		lift->liftAuto(1,7000);
		manip->AutoOuttake();
	}
	else
	{
		manip->setPos(1);
		driveStraight(.7,80000);
		drive->autoTurn(270);
		driveStraight(1,60000);
		drive->autoTurn(90);
		driveStraight(1,6000);
		lift->liftAuto(1,7000);
		manip->AutoOuttake();
	}
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
