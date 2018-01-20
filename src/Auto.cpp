#include <Auto.h>


Auto::Auto()
{
	gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
	//drive = new Drive;
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
	/*while(drive->getLeftEnc() < DUMMY_VAL && drive->getRightEnc() < DUMMY_VAL)//Dummy values
	{
		drive->setFwdSpeed(1);
	}
	drive->setFwdSpeed(0);
	drive->resetEncoder();*/
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
