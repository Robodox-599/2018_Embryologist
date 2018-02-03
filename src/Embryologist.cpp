#include <iostream>
#include <memory>
#include <string>

#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Drive.h>
#include <Lift.h>
//#include <Climb.h>
#include <Macros.h>
#include <Manipulator.h>
#include <Auto.h>

class Robot: public frc::IterativeRobot {
public:
		Drive* drive;
		Auto *auton;
		Joystick* xbox;
		//Compressor* comp599;

		//Compressor *comp599 = new Compressor();
	//Drive* drive;
	//Auto* auton = new Auto;
	void RobotInit() {

		xbox = new Joystick(0);
		auton = new Auto();
		drive = new Drive();
		drive->resetEncoder();
	//	comp599->SetClosedLoopControl(true);
		/*chooser.AddDefault(autoNameDefault, autoNameDefault);
		chooser.AddObject(autoNameCustom, autoNameCustom);
		frc::SmartDashboard::PutData("Auto Modes", &chooser);*/
		/*chooser.AddDefault(autoNameDefault, autoNameDefault);
		chooser.AddObject(autoNameCustom, autoNameCustom);
		frc::SmartDashboard::PutData("Auto Modes", &chooser);*/
	}

	/*
	 * This autonomous (along with the chooser code above) shows how to select
	 * between different autonomous modes using the dashboard. The sendable
	 * chooser code works with the Java SmartDashboard. If you prefer the
	 * LabVIEW Dashboard, remove all of the chooser code and uncomment the
	 * GetString line to get the auto name from the text box below the Gyro.
	 *
	 * You can add additional auto modes by adding additional comparisons to the
	 * if-else structure below with additional strings. If using the
	 * SendableChooser make sure to add them to the chooser code above as well.
	 */
	void AutonomousInit() override {
		drive->resetEncoder();
		/*autoSelected = chooser.GetSelected();
		// std::string autoSelected = SmartDashboard::GetString("Auto Selector", autoNameDefault);
		std::cout << "Auto selected: " << autoSelected << std::endl;

		if (autoSelected == autoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}*/
	}

	void AutonomousPeriodic()
	{
		//SmartDashboard::PutNumber("Left Encoder Value", drive->getLeftEnc());
		//SmartDashboard::PutNumber("Right Encoder Value", drive->getRightEnc());
		auton->auto0();

		/*if(auton->autoSelector() == 0)
		{
			auton->auto0();
		}
		else if(auton->autoSelector() == 1)
		{
			auton->auto1();
		}
		else if(auton->autoSelector() == 2)
		{
			auton->auto2();
		}
		else if(auton->autoSelector() == 3)
		{
			auton->auto3();
		}*/
		/*if (autoSelected == autoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}*/
	}

	void TeleopInit()
	{
		drive->resetEncoder();
	}

	void TeleopPeriodic()
	{
		SmartDashboard::PutNumber("Auto Position: ",auton->dataVal());
		drive->drive(xbox->GetRawAxis(0), xbox->GetRawAxis(1));
		//drive->shift(xbox->GetRawButton(2));//B Button
		SmartDashboard::PutString("test", "test2");
		SmartDashboard::PutNumber("Left Encoder Value", drive->getLeftEnc());
		SmartDashboard::PutNumber("Right Encoder Value", drive->getRightEnc());
		//SmartDashboard::PutNumber("Auto Selected: ", auton->autoSelector());


	}

	void TestPeriodic() {
		//lw->Run();
	}

private:
	frc::LiveWindow* lw = LiveWindow::GetInstance();
	/*frc::SendableChooser<std::string> chooser;
	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";
	std::string autoSelected;*/
};

START_ROBOT_CLASS(Robot)
