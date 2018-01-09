#include <Auto.h>

Auto::Auto()
{
	gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
}

Auto::~Auto()
{

}

void preCheck()
{

}

void auto1()
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
