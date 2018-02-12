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

}

Auto::~Auto()
{
	selector = nullptr;

	delete selector;
}

void Auto::driveStraight(float speed, int enc)
{
	if(-speed > 0)
	{
		while(drive->getLeftEnc() > -enc && drive->getRightEnc() > -enc)//Dummy values
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
		while(drive->getLeftEnc() < enc && drive->getRightEnc() < enc)//Dummy values
		{
		drive->updateLeftMotors(-speed);
		drive->updateRightMotors(-speed);
		}
		drive->updateLeftMotors(0);
		drive->updateRightMotors(0);
				//drive->resetEncoder();
	}
}



void Auto::preCheck()//To be run BEFORE a match in the pit in order to test each system
{

}

void Auto::preLoad_auto0()//Drive straight to pass Auto Line.
{
	/*while(drive->getLeftEnc() > -10000 && drive->getRightEnc() > -10000)//Dummy values
	{
		drive->updateLeftMotors(1);
		drive->updateRightMotors(1);
	}
	drive->updateLeftMotors(0);
	drive->updateRightMotors(0);*/
	//drive->resetEncoder();
	driveStraight(1, 10000);
	//Wait(400);
}
//
void Auto::preLoad_auto1()//Left starting position, Objective: Switch
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
		manip->AutoIntake();
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
		manip->AutoIntake();
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

void Auto::preLoad_auto2()
{
	if(gameData[0] == 1)
	{
		manip->setPos(1);
		driveStraight(1,30000);
		drive->updateLeftMotors(1);
		drive->updateRightMotors(1);
		manip->AutoIntake();
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
		manip->AutoIntake();
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

void Auto::preLoad_auto3()
{
	if(gameData[0] == 1)
	{
		manip->setPos(1);//releases intake
		driveStraight(1,50000);
		drive->autoTurn(90); //function not final
		drive->updateLeftMotors(1);
		drive->updateRightMotors(1);
		manip->AutoIntake();
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
		manip->AutoIntake();
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
