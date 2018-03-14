#include <iostream>
#include <memory>
#include <string>

#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Drive.h>
#include <Macros.h>
#include <Timer.h>
#include <DoxUtil_Log.h>

class Robot: public frc::IterativeRobot {
public:
	//Compressor* comp599;
	//Compressor *comp599 = new Compressor(0);
	void RobotInit()
	{
		/*pigeonTalon = new TalonSRX(9);
		pGyon = new PigeonIMU(pigeonTalon);*/
		xbox = new Joystick(0);
		drive = new Drive();
		drive->resetEncoder();
//		timer = new Timer();
//		timerTime = timer->Get();
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
//		theLog = new DoxLog();
//		timer->Reset();
//		timer->Start();
//		drive->resetEncoder();
//		frontLeftMotor = new TalonSRX(Drive_Front_Left_Motor_Channel);
//		rearLeftMotor = new TalonSRX(Drive_Rear_Left_Motor_Channel);
//		frontRightMotor = new TalonSRX(Drive_Front_Right_Motor_Channel);
//		rearRightMotor = new TalonSRX(Drive_Rear_Right_Motor_Channel);
	}

	void TeleopPeriodic()
	{
		drive->getYPR();
		drive->smartDashboard();
		drive->turnByGyro(90);
		Wait(10);
//		timerTime = timer->Get();
//		SmartDashboard::PutNumber("Timer Time", timerTime);
		/*double ypr[3];
		PigeonIMU::GeneralStatus genStatus;
		pGyon->GetGeneralStatus(genStatus);
		pGyon->GetYawPitchRoll(ypr);
		SmartDashboard::PutNumber("Yaw", ypr[0]);
		SmartDashboard::PutNumber("Temperature", genStatus.tempC);*/
		//drive->velocityDrive(0, 0.4);
//		if(false){
//		drive->getYPR();
//////		drive->testPID();
//		drive->updateDrive(xbox->GetRawAxis(4), xbox->GetRawAxis(1));
//////		drive->velocityDrive(xbox->GetRawAxis(0), xbox->GetRawAxis(1));
//////		drive->shift(xbox->GetRawButton(2));
//		drive->smartDashboard();
//		drive->autoTurn(xbox->GetPOV(0));

//		frontRightMotor->Set(ControlMode::PercentOutput, .3);
//		Wait(2);
//		frontRightMotor->Set(ControlMode::PercentOutput, 0);
//		rearRightMotor->Set(ControlMode::PercentOutput, .3);
//		Wait(2);
//		rearRightMotor->Set(ControlMode::PercentOutput, 0);
//		frontLeftMotor->Set(ControlMode::PercentOutput, .3);
//		Wait(2);
//		frontLeftMotor->Set(ControlMode::PercentOutput, 0);
//		rearLeftMotor->Set(ControlMode::PercentOutput, .3);
//		Wait(2);
//		rearLeftMotor->Set(ControlMode::PercentOutput, 0);
//		}

//		theLog->LogIt("Left Encoder Value", drive->getLeftEnc(), -1);
//		theLog->LogIt("Right Encoder Value", drive->getRightEnc(), -1);
//		if(timerTime > 1 && timerTime < 2)
//		{
//			frontLeftMotor->Set(ControlMode::PercentOutput, 1);
//			rearRightMotor->Set(ControlMode::PercentOutput, 1);
//		}
//		if(timerTime > 2 && timerTime < 3)
//		{
//			frontLeftMotor->Set(ControlMode::PercentOutput, -1);
//			rearRightMotor->Set(ControlMode::PercentOutput, -1);
//		}
//		if(timerTime > 3 && timerTime < 4)
//		{
//			frontLeftMotor->Set(ControlMode::PercentOutput, 0);
//			rearRightMotor->Set(ControlMode::PercentOutput, 0);
//		}
	}

	void DisabledInit()
	{
//		if(theLog != nullptr)
//		{
//			theLog->close();
//		}
	}

	void TestPeriodic()
	{

	}

private:
//	float timerTime;
	//PigeonIMU* pGyon;
	Drive* drive;
	Joystick* xbox;
//	DoxLog* theLog;
//	Timer* timer;
	frc::LiveWindow* lw = LiveWindow::GetInstance();
	/*frc::SendableChooser<std::string> chooser;
	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";
	std::string autoSelected;*/
//	TalonSRX* frontLeftMotor;
//	TalonSRX* rearLeftMotor;
//	TalonSRX* frontRightMotor;
//	TalonSRX* rearRightMotor;

};

START_ROBOT_CLASS(Robot)
