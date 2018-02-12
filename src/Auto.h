#ifndef SRC_AUTO_H_
#define SRC_AUTO_H_

#include <Macros.h>
#include <Drive.h>
#include <Manipulator.h>
#include <Lift.h>
#include <WPILib.h>
#include <ctre/Phoenix.h>

class Auto
{
public:
	Auto();
	~Auto();

	void preCheck();
	void preLoad_auto0();
	void preLoad_auto1();
	void preLoad_auto2();
	void preLoad_auto3();
	int dataVal();
	DigitalInput* selector;

	//parameters
	void driveStraight(float speed, int enc);

	int autoSelector();

private:
	std::string gameData;

	Drive* drive;
	Manipulator* manip;
	Lift* lift;

	int dataTest;
	int counter;
};




#endif /* SRC_AUTO_H_ */
