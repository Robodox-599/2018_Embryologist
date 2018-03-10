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


//talon number for the motors//
#define Drive_Front_Left_Motor_Channel (4) //4 , 7(MOD)
#define Drive_Rear_Left_Motor_Channel (3) //3  , 10(MOD)
#define Drive_Front_Right_Motor_Channel (2) //2  , 6(MOD)
#define Drive_Rear_Right_Motor_Channel (1) //1  , 8(MOD)


//Solenoid Ports//
#define Shifter_Solenoid_Channel_A (4) //solenoid for shifter pistons on the motor
#define Shifter_Solenoid_Channel_B (5) //solenoid for shifter pistons on the motor
//#define Right_Shifter_Solenoid_Channel_A (2)
//#define Right_Shifter_Solenoid_Channel_B (3)

//Deadzones and Max Values//
#define LIFT_DEADZONE (0.3)//Deadzone for lift control
#define MAX_LIFT_VAL (30250)//27250
#define DEADZONE (.2) //deadzone for the controllers to avoid accidental movement
#define Max_Motor_Velocity (3256.28) //3256.28


//XBox One Buttons & Joysticks//
#define A_Xbox (1) //A Button
#define B_Xbox (2) //B Button
#define X_Xbox (3) //X Button
#define Y_Xbox (4) //Y Button
#define LB_Xbox (5) //LB (left bumper) Button
#define RB_Xbox (6) //RB (right bumper) Button
#define View_Xbox (7) //View (left button on the front) Button
#define Menu_Xbox (8) //Menu (right button on the front) Button
#define Left_JoyPress_Xbox (9) //Button under Left Joystick
#define Right_JoyPress_Xbox (10) //Button under Right Joystick
//----//
#define LX_Axis_Xbox (0) //Left Joystick, X Axis
#define LY_Axis_Xbox (1) //Left Joystick, Y Axis
#define LT_Axis_Xbox (2) //Left Trigger
#define RT_Axis_Xbox (3) //Right Trigger
#define RX_Axis_Xbox (4) //Right Joystick, X Axis
#define RY_Axis_Xbox (5) //Right Joystick, Y Axis

#endif /* SRC_MACROS_H_ */
