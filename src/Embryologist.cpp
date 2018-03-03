#include <iostream>
#include <memory>
#include <string>

#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Drive.h>
#include <Lift.h>
#include <Macros.h>
#include <Manipulator.h>
#include "WPILib.h"

class Robot: public frc::IterativeRobot {
public:
	Joystick* atk3;
	Joystick* xbox;
	Manipulator* manip;
	Lift *lift;
	Drive *drive;
	Compressor* comp599 = new Compressor(0);
	void RobotInit()
	{
		comp599->SetClosedLoopControl(true);
		atk3 = new Joystick(1); //This value may change because it is a DUMMY VALUE.//
		manip = new Manipulator;
		lift = new Lift;
		lift->resetLiftEncoder();
		xbox = new Joystick(0);
		drive = new Drive();
		drive->resetEncoder();
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
		//drive->PIDset();
	}

	void TeleopPeriodic()
	{
		//if(false){
		//manipulator
		manip->intakeOuttakeCube(atk3->GetRawButton(4),atk3->GetRawButton(1));
		//manip->diffIntake(atk3->GetRawButton(6),atk3->GetRawButton(7));
		manip->intakePosition(atk3->GetRawButton(3));
		//SmartDashboard::GetBoolean("stopper: ", manip->stoppingCube());
		manip->jiggle(atk3->GetRawButton(5));
		SmartDashboard::PutNumber("Pot Val: ", manip->potVal());

		//lift
		lift->liftRobot(atk3->GetRawAxis(1));
		lift->PistonLift(atk3->GetRawButton(6),atk3->GetRawButton(7));
		lift->rungDeploy(atk3->GetRawButton(8), atk3->GetRawButton(9));
		//lift->doClimb(atk3->GetRawButton(10));
		//lift->setHeightEnc(atk3->GetRawAxis(1));
		//lift->doLift();
		//lift->getLeftLiftEnc();
		//lift->getRightLiftEnc();
		//lift->getAvgLiftEnc();
		//lift->CalibrateLift(atk3->GetRawButton(7), atk3->GetRawButton(10));
		SmartDashboard::PutNumber("leftValue: ", lift->getLeftLiftEnc());
		SmartDashboard::PutNumber("rightValue: ", lift->getRightLiftEnc());
		SmartDashboard::PutBoolean("upperLimit ", lift->upperLimitTester());
		SmartDashboard::PutBoolean("lowerLimit: ", lift->lowerLimitTester());
		SmartDashboard::PutNumber("Avg value:", lift->getAvgLiftEnc());
		SmartDashboard::PutBoolean("Button 7: ", atk3->GetRawButton(7));
		SmartDashboard::PutBoolean("Current lock state: ", lift->canLift);
		SmartDashboard::PutBoolean("Current rung state: ", lift->rungState);
		//}
	//	else{
		//drive
		/*double ypr[3];
		PigeonIMU::GeneralStatus genStatus;
		pGyon->GetGeneralStatus(genStatus);
		pGyon->GetYawPitchRoll(ypr);
		SmartDashboard::PutNumber("Yaw", ypr[0]);
		SmartDashboard::PutNumber("Temperature", genStatus.tempC);*/
		//drive->velocityDrive(0, 0.4);
		//drive->getYPR();
		//drive->velocityDrive(-xbox->GetRawAxis(1), -xbox->GetRawAxis(4));
		drive->shift(xbox->GetRawButton(B_Xbox));
		drive->getYPR();
		drive->velocityDrive(xbox->GetRawAxis(4), xbox->GetRawAxis(1));
		//drive->shift(xbox->GetRawButton(2));
		//drive->autoTurn(xbox->GetPOV(0));
		//}
	}

	void TestPeriodic() {
		//lw->Run();
	}

private:
	//frc::LiveWindow* lw = LiveWindow::GetInstance();
	/*frc::SendableChooser<std::string> chooser;
	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";
	std::string autoSelected;*/
};

START_ROBOT_CLASS(Robot)
