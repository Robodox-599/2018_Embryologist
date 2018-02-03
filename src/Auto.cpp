#include <Auto.h>


Auto::Auto()
{
	gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
	drive = new Drive;
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
	driveStraight(1, 10000);
	//Wait(400);
}
//
void Auto::auto1()//Left starting position, Objective: Switch
{
	if(gameData[0] == 'L')
	{
		//Put left auto code here
		dataTest = 1;
		driveStraight(1, 1000);
	}
	else
	{
		//Put right auto code here
		dataTest = 2;
		driveStraight(-1, 1000);
	}
}

void Auto::auto2()
{

}

void Auto::auto3()
{

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
