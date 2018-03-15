#ifndef SRC_AUTO_H_
#define SRC_AUTO_H_

#include <Macros.h>
#include <Drive.h>
#include <Manipulator.h>
#include <Lift.h>
#include <WPILib.h>
#include <ctre/Phoenix.h>
#include <DoxUtil_Log.h>

class Auto
{
public:
	Auto();
	~Auto();

	void preCheck();
	void preCheck_Drive();
	void preCheck_Lift();
	void preCheck_Intake();

	void auto0();
	void auto1();
	void auto2();
	void auto3();
	void auto4();
	void auto5();
	void auto5_5();
	void auto6();
	void nonPreLoad_auto1();
	void nonPreLoad_auto2();
	void nonPreLoad_auto3();

	void turnRobot(float speed, float time);
	void liftTime(float speed, float time);
	void displayData();
	int dataVal();
	DigitalInput* selector;

	//parameters
	void driveStraight(float speed, int enc);
	void adjustDrive(float error, float speed);
	void setMotors(float speedL, float speedR, float time);
	void gyroTurn(float speed, int angle);
	void encTurn(float speedL, float speedR, int enc);
	void encLift(float speed, int enc);

	int autoSelector();
	bool doAuto;

private:
	std::string gameData;
	Timer* timer;
	Drive* drive;
	Manipulator* manip;
	Lift* lift;
	DoxLog* doxLog;

	int timerTime;

	int dataTest;
	int counter;
	int driveTarget;
	int driveCurrent;
	int driveError;

	double ypr[3];
};




#endif /* SRC_AUTO_H_ */
