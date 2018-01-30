#include <iostream>
#include <memory>
#include <string>

#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Drive.h>
#include <Macros.h>

class Robot: public frc::IterativeRobot {
public:
	//Compressor* comp599;
	//Compressor *comp599 = new Compressor(0);
	void RobotInit()
	{
		xbox = new Joystick(0);
		drive = new Drive();
		drive->resetEncoder();
		//comp599->SetClosedLoopControl(true);
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
		/*if (autoSelected == autoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}*/
	}

	void TeleopInit()
	{
		drive->PIDset();
	}

	void TeleopPeriodic()
	{
		//drive->velocityDrive(0, 0.4);
		drive->velocityDrive(xbox->GetRawAxis(0), xbox->GetRawAxis(1));
		//drive->drive(xbox->GetRawAxis(0), xbox->GetRawAxis(1));
		drive->shift(xbox->GetRawButton(2));//B Button
		SmartDashboard::PutNumber("Joystick Y", xbox->GetRawAxis(1));
		SmartDashboard::PutNumber("Joystick X", xbox->GetRawAxis(0));
	}

	void TestPeriodic()
	{

	}

private:
	Drive* drive;
	Joystick* xbox;
	frc::LiveWindow* lw = LiveWindow::GetInstance();
	/*frc::SendableChooser<std::string> chooser;
	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";
	std::string autoSelected;*/
};

START_ROBOT_CLASS(Robot)
