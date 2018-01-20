#include <iostream>
#include <memory>
#include <string>

#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Macros.h>
#include <LogFile.cpp>
#include <ctime>
class Robot: public frc::IterativeRobot {
public:
	//LogFile* logfile;
	int var;
	time_t t = time(0);
	struct tm* now = localtime(&t);
	char timestamp[16];

	void RobotInit()
	{
		/*chooser.AddDefault(autoNameDefault, autoNameDefault);
		chooser.AddObject(autoNameCustom, autoNameCustom);
		frc::SmartDashboard::PutData("Auto Modes", &chooser);*/
		//var = 2;

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

	void AutonomousPeriodic() {
		/*if (autoSelected == autoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}*/
	}

	void TeleopInit()
	{
		strftime(timestamp, 16, "%y%m%d_%H%M%S", now);
		using namespace std;
		ofstream LogFile;
		LogFile.open("//U//RoboLogs//LogFile.txt");
		LogFile << "Variable: ";
		LogFile << var << "\r\n";
		LogFile << (now->tm_year + 1900) <<'-' << (now->tm_mon+1) << '-' << now->tm_mday;
		LogFile.close();
		std::cin.get();
	}

	void TeleopPeriodic()
	{

	}

	void TestPeriodic() {

	}

private:
	frc::LiveWindow* lw = LiveWindow::GetInstance();
	/*frc::SendableChooser<std::string> chooser;
	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";
	std::string autoSelected;*/
};

START_ROBOT_CLASS(Robot)
