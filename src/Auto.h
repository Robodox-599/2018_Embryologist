#ifndef SRC_AUTO_H_
#define SRC_AUTO_H_

#include <Macros.h>
#include <Drive.h>
#include <WPILib.h>
#include <ctre/Phoenix.h>

class Auto
{
public:
	Auto();
	~Auto();

	void preCheck();
	void auto0();
	void auto1();
	void auto2();
	void auto3();
	int dataVal();
	DigitalInput* selector;

	//parameters
	void driveStraight(float speed, int enc);

	int autoSelector();

private:
	std::string gameData;

	Drive* drive;

	int dataTest;
	int counter;
};




#endif /* SRC_AUTO_H_ */
