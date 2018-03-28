#include <iostream>
#include <memory>
#include <string>

#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
//#include <Drive.h>
//#include <Lift.h>
//#include <Climb.h>
#include <Macros.h>
//#include <Manipulator.h>
#include <Auto.h>
#include <WPILib.h>

class Robot: public frc::IterativeRobot {
public:
		//Drive* drive;
		Auto *auton;
		//Manipulator* manip;
		//Lift* lift;
		Joystick* xbox;
		Joystick* atk3;
//		std::string autoNum = SmartDashboard::GetString("Auto Number:", 0);
//		std::string auto0;
//		std::string auto1;
//		std::string auto2;
//		std::string auto3;
//		std::string auto4;
//		std::string auto5;
//		std::string Delay_auto5;
//		std::string auto6;
//		std::string nonPreLoad_auto1;
//		std::string nonPreLoad_auto2;
//		std::string nonPreLoad_auto3;
		//int autoNum;
		//Compressor* comp599;

		Compressor *comp599 = new Compressor();
		bool autoo;
	//Drive* drive;
	//Auto* auton = new Auto;
	void RobotInit() {
		//printf("robotInit Test");
		xbox = new Joystick(0);
		atk3 = new Joystick(1);
		auton = new Auto();
//		drive = new Drive();
//		lift = new Lift();
//		manip = new Manipulator();
		auton->drive->resetEncoder();
		auton->lift->resetLiftEncoder();
		auton->drive->PIDset();
		comp599->SetClosedLoopControl(true);
		autoo = true;
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
		auton->drive->resetEncoder();
		auton->setGameData(frc::DriverStation::GetInstance().GetGameSpecificMessage());
		auton->drive->pGyon->SetYaw(0, 0);
		/*autoSelected = chooser.GetSelected();
		// std::string autoSelected = SmartDashboard::GetString("Auto Selector", autoNameDefault);
		std::cout << "Auto selected: " << autoSelected << std::endl;

		if (autoSelected == autoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}*/

		//autoo = true;
	}

	void AutonomousPeriodic()
	{
		auton->drive->driveSmartDashboard();
		if(auton->doAuto)auton->auto2();
		else
		{
			 auton->drive->updateLeftMotors(0);
			 auton->drive->updateRightMotors(0);
			 auton->manip->stopManip();
			 auton->lift->stopLift();
		}

//		if(autoo)
//		{
//			auton->drive->updateLeftMotors(.5);
//			auton->drive->updateRightMotors(-.5);
//			printf("start wait");
//			Wait(1.8);
//			printf("done wait");
//
//			auton->drive->updateLeftMotors(0);
//			auton->drive->updateRightMotors(0);
//			autoo = false;
//		}
//		else
//		{
//			auton->drive->updateLeftMotors(0);
//			auton->drive->updateRightMotors(0);
//			//Wait(20);
//		}

//		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, -.1);
//		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, .1);
		// auto1();
//		if(gameData[0] == 'L')
//		{
//			SmartDashboard::PutString("Data Position", "L");
//		}
//		else
//		{
//			SmartDashboard::PutString("Data Position", "R");
//		}
		//SmartDashboard::GetNumber("Auto Number:", autoNum);

//		if(autoNum == auto0)  auto0();
//		else if(autoNum == auto1)  auto1();
//		else if(autoNum == auto2)  auto2();
//		else if(autoNum == auto3)  auto3();
//		else if(autoNum == auto4)  auto4();
//		else if(autoNum == auto5)  auto5();
//		else if(autoNum == Delay_auto5)  auto5_5();
//		else if(autoNum == auto6)  auto6();
//		else if(autoNum == nonPreLoad_auto1)  nonPreLoad_auto1();
//		else if(autoNum == nonPreLoad_auto2)  nonPreLoad_auto2();
//		else if(autoNum == nonPreLoad_auto3)  nonPreLoad_auto3();

		//std::string autoSelected = SmartDashboard::GetString("Auto Selector", );

		/*if( autoSelector() == 0)
		{
			 auto0();
		}
		else if( autoSelector() == 1)
		{
			 auto1();
		}
		else if( autoSelector() == 2)
		{
			 auto2();
		}
		else if( autoSelector() == 3)
		{
			 auto3();
		}*/
		/*if (autoSelected == autoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}*/
	}

	void TeleopInit()
	{
		//auton->drive->resetEncoder();
	}

	void TeleopPeriodic()
	{
		//manipulator
		auton->manip->intakeOuttakeCube(atk3->GetRawButton(4),atk3->GetRawButton(1),atk3->GetRawAxis(2));
		auton->manip->jiggle(atk3->GetRawButton(3));
		auton->manip->pivotIntake(atk3->GetRawButton(10), atk3->GetRawButton(2), atk3->GetRawButton(11));

		auton->manip->manipSmartDashboard();


		//lift
		auton->lift->liftRobot(atk3->GetRawAxis(1));
		auton->lift->PistonLift(atk3->GetRawButton(6),atk3->GetRawButton(7));
		auton->lift->rungDeploy(xbox->GetRawButton(A_Xbox), xbox->GetRawButton(X_Xbox));
		auton->lift->releaseRope(atk3->GetRawButton(8), atk3->GetRawButton(9));

		auton->lift->liftSmartDashboard();


		//drive
		auton->drive->shift(xbox->GetRawButton(B_Xbox));
		auton->drive->getYPR();
		//auton->drive->updateDrive(xbox->GetRawAxis(RX_Axis_Xbox), xbox->GetRawAxis(LY_Axis_Xbox));
		auton->drive->velocityDrive(xbox->GetRawAxis(RX_Axis_Xbox), xbox->GetRawAxis(LY_Axis_Xbox));//4,1
		SmartDashboard::PutNumber("Left Drive", auton->drive->getLeftEnc());
		SmartDashboard::PutNumber("Right Drive", auton->drive->getRightEnc());

		auton->drive->driveSmartDashboard();


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
