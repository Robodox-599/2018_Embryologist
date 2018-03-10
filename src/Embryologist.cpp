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
#include <WPILib.h>

class Robot: public frc::IterativeRobot {
public:
		Drive* drive;
		Auto *auton;
		Manipulator* manip;
		Lift* lift;
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
		//SmartDashboard::PutNumber("Lift Left", lift->getLeftLiftEnc());
		//auton->displayData();
		//SmartDashboard::PutNumber("Right Encoder Value", drive->getRightEnc());
//		if(auton->doAuto)auton->auto1();
//		else
//		{
//			drive->updateLeftMotors(0);
//			drive->updateRightMotors(0);
//			manip->stopManip();
//			lift->stopLift();
//		}
//		manip->leftIntakeMotor->Set(ControlMode::PercentOutput, -.1);
//		manip->rightIntakeMotor->Set(ControlMode::PercentOutput, .1);
		//auton->auto1();
//		if(gameData[0] == 'L')
//		{
//			SmartDashboard::PutString("Data Position", "L");
//		}
//		else
//		{
//			SmartDashboard::PutString("Data Position", "R");
//		}
		//SmartDashboard::GetNumber("Auto Number:", autoNum);

//		if(autoNum == auto0) auton->auto0();
//		else if(autoNum == auto1) auton->auto1();
//		else if(autoNum == auto2) auton->auto2();
//		else if(autoNum == auto3) auton->auto3();
//		else if(autoNum == auto4) auton->auto4();
//		else if(autoNum == auto5) auton->auto5();
//		else if(autoNum == Delay_auto5) auton->auto5_5();
//		else if(autoNum == auto6) auton->auto6();
//		else if(autoNum == nonPreLoad_auto1) auton->nonPreLoad_auto1();
//		else if(autoNum == nonPreLoad_auto2) auton->nonPreLoad_auto2();
//		else if(autoNum == nonPreLoad_auto3) auton->nonPreLoad_auto3();

		//std::string autoSelected = SmartDashboard::GetString("Auto Selector", );

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
		//drive->resetEncoder();
		manip->targetPivot = 90;
	}

	void TeleopPeriodic()
	{

		//if(false){
				//manipulator
				manip->intakeOuttakeCube(atk3->GetRawButton(4),atk3->GetRawButton(1),atk3->GetRawAxis(2));
				//manip->diffIntake(atk3->GetRawButton(6),atk3->GetRawButton(7));
				manip->intakePosition(atk3->GetRawButton(8), atk3->GetRawButton(9));
				//SmartDashboard::GetBoolean("stopper: ", manip->stoppingCube());
				manip->jiggle(atk3->GetRawButton(3));
				//manip->liftIntake(atk3->GetRawButton(11), atk3->GetRawButton(10), atk3->GetRawButton(2), atk3->GetRawButton(5));
				SmartDashboard::PutNumber("Z Axis:", atk3->GetRawAxis(2));
				SmartDashboard::PutNumber("Pot Val:", manip->pot->Get());
				manip->pivotIntake(atk3->GetRawButton(10), atk3->GetRawButton(2), atk3->GetRawButton(11));

				//lift
				lift->liftRobot(atk3->GetRawAxis(1));
				//lift->PistonLift(atk3->GetRawButton(6),atk3->GetRawButton(7));
				lift->rungDeploy(xbox->GetRawButton(A_Xbox), xbox->GetRawButton(X_Xbox));
				//lift->doClimb(atk3->GetRawButton(10));
				//lift->setHeightEnc(atk3->GetRawAxis(1));
				//lift->doLift();
				//lift->getLeftLiftEnc();
				//lift->getRightLiftEnc();0
				//lift->getAvgLiftEnc();
				//lift->CalibrateLift(atk3->GetRawButton(7), atk3->GetRawButton(10));
				SmartDashboard::PutNumber("leftValue: ", lift->getLeftLiftEnc());
				SmartDashboard::PutNumber("rightValue: ", lift->getRightLiftEnc());
				SmartDashboard::PutBoolean("upperLimit ", lift->upperLimitTester());
				SmartDashboard::PutBoolean("lowerLimit: ", lift->lowerLimitTester());
				SmartDashboard::PutNumber("Avg value:", lift->getAvgLiftEnc());
				//SmartDashboard::PutBoolean("Button 7: ", atk3->GetRawButton(7));
				SmartDashboard::PutBoolean("Current lock state: ", lift->canLift);
				SmartDashboard::PutBoolean("Current rung state: ", lift->rungState);
				//}
			//	else{
				//drive
				/*double ypr[3];..
				PigeonIMU::GeneralStatus genS...tatus;
				pGyon->GetGeneralStatus(gen..Status);
				pGyon->GetYawPitchRoll(ypr);
				SmartDashboard::PutNumber("Yaw", ypr[0]);
				SmartDashboard::Pu.tNumber("Temperature", genStatus.tempC);*/
				//drive->velocityDrive(0, 0.4);
				//drive->getYPR();
				//drive->velocityDrive(-xbox->GetRawAxis(1), -xbox->GetRawAxis(4));
				drive->shift(xbox->GetRawButton(B_Xbox));
				//drive->getYPR();
				drive->velocityDrive(xbox->GetRawAxis(RX_Axis_Xbox), xbox->GetRawAxis(LY_Axis_Xbox));//4,1
				//drive->shift(xbox->GetRawButton(2));
				//drive->autoTurn(xbox->GetPOV(0));
				//}


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
