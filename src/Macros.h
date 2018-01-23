/*
 /*
 * Macros.h
 *
 *  Created on: Jan 6, 2018
 *      Author: Admin
 */

#ifndef SRC_MACROS_H_
#define SRC_MACROS_H_
#include "WPILib.h"
//#include "AHRS.h"

#define Drive_Front_Left_Motor_Channel (7) //talon number for the motors
#define Drive_Rear_Left_Motor_Channel (10)
#define Drive_Front_Right_Motor_Channel (6)
#define Drive_Rear_Right_Motor_Channel (8)

//#define Shifter_Button (1) //shifts the gears on the drive for either torque or speed

#define Left_Shifter_Solenoid_Channel_A (0) //solenoid for shifter pistons on the motor
#define Left_Shifter_Solenoid_Channel_B (1) //solenoid for shifter pistons on the motor
#define Right_Shifter_Solenoid_Channel_A (2)
#define Right_Shifter_Solenoid_Channel_B (3)

#define DEADZONE (.2) //deadzone for the controllers to avoid accidental movement

#endif /* SRC_MACROS_H_ */
