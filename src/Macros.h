/*
 * Macros.h
 *
 *  Created on: Jan 6, 2018
 *      Author: Admin
 */

#ifndef SRC_MACROS_H_
#define SRC_MACROS_H_

#define intake_button (4) //This is the button for intake//
#define outtake_button (5)  //This is the button for outtake//

#define LIFT_DEADZONE (0.2)
#define MAX_LIFT_VAL (30250)//27250

//talon number for the motors
#define Drive_Front_Left_Motor_Channel (4) //4 , 7(MOD)
#define Drive_Rear_Left_Motor_Channel (3) //3  , 10(MOD)
#define Drive_Front_Right_Motor_Channel (2) //2  , 6(MOD)
#define Drive_Rear_Right_Motor_Channel (1) //1  , 8(MOD)

//#define Shifter_Button (1) //shifts the gears on the drive for either torque or speed

#define Shifter_Solenoid_Channel_A (4) //solenoid for shifter pistons on the motor
#define Shifter_Solenoid_Channel_B (5) //solenoid for shifter pistons on the motor
//#define Right_Shifter_Solenoid_Channel_A (2)
//#define Right_Shifter_Solenoid_Channel_B (3)

#define DEADZONE (.2) //deadzone for the controllers to avoid accidental movement
#define Max_Motor_Velocity (3256.28) //3256.28

#endif /* SRC_MACROS_H_ */
