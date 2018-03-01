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

//talon number for the motors
#define Drive_Front_Left_Motor_Channel (4)
#define Drive_Rear_Left_Motor_Channel (3)
#define Drive_Front_Right_Motor_Channel (2)
#define Drive_Rear_Right_Motor_Channel (1)

//#define Shifter_Button (1) //shifts the gears on the drive for either torque or speed

#define Shifter_Solenoid_Channel_A (4) //solenoid for shifter pistons on the motor
#define Shifter_Solenoid_Channel_B (5) //solenoid for shifter pistons on the motor
//#define Right_Shifter_Solenoid_Channel_A (2)
//#define Right_Shifter_Solenoid_Channel_B (3)

#define DEADZONE (.2) //deadzone for the controllers to avoid accidental movement
#define Max_Motor_Velocity (1000) //3256.28 768

#endif /* SRC_MACROS_H_ */
