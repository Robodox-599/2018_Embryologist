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

void Auto::preCheck()//To be run BEFORE a match in the pit in order to test each system
{

}

void Auto::auto0()//Drive straight to pass Auto Line.
{
	while(drive->getLeftEnc() < 1000 && drive->getRightEnc() < 1000)//Dummy values
	{
		drive->updateLeftMotors(1);
		drive->updateRightMotors(1);
	}
	drive->updateLeftMotors(0);
	drive->updateRightMotors(0);
	drive->resetEncoder();
	Wait(400);
}
//
void Auto::auto1()//Left starting position, Objective: Switch
{
	if(gameData[0] == 'L')
	{
		//Put left auto code here
		dataTest = 1;
	}
	else
	{
		//Put right auto code here
		dataTest = 2;
	}
}

int Auto::dataVal()
{
	return dataTest;
}
