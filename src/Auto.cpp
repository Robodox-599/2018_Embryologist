#include <Auto.h>


Auto::Auto()
{
	gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
	drive = new Drive;
	dataTest = 0;
}

Auto::~Auto()
{

}

void Auto::driveStraight(float speed, int enc)
{
	if(speed > 0)
	{
		while(drive->getLeftEnc() < enc && drive->getRightEnc() < enc)//Dummy values
		{
		drive->updateLeftMotors(speed);
		drive->updateRightMotors(speed);
		}
		drive->updateLeftMotors(0);
		drive->updateRightMotors(0);
		//drive->resetEncoder();
	}
	if(speed < 0)
	{
		while(drive->getLeftEnc() > -enc && drive->getRightEnc() > -enc)//Dummy values
		{
		drive->updateLeftMotors(speed);
		drive->updateRightMotors(speed);
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
	/*while(drive->getLeftEnc() < 1000 && drive->getRightEnc() < 1000)//Dummy values
	{
		drive->updateLeftMotors(1);
		drive->updateRightMotors(1);
	}
	drive->updateLeftMotors(0);
	drive->updateRightMotors(0);*/
	//drive->resetEncoder();
	driveStraight(1, 1000);
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

int Auto::dataVal()
{
	return dataTest;
}
