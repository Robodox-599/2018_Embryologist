#include <Auto.h>

Auto::Auto()
{
	gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
}

Auto::~Auto()
{

}

void Auto::preCheck()//To be run BEFORE a match in the pit in order to test each system
{

}

void Auto::auto0()//Drive straight to pass Auto Line.
{

}

void Auto::auto1()//Left starting position, Objective: Switch
{
	if(gameData[0] == 'L')
	{
		//Put left auto code here
	}
	else
	{
		//Put right auto code here
	}
}
