/*
 * Lift.h
 *
 *  Created on: Jan 6, 2018
 *      Author: Admin
 */

#ifndef SRC_LIFT_H_
#define SRC_LIFT_H_

#include "ctre/Phoenix.h"
//#include "WPILib.h"

//using namespace std;

class Lift
{
public:
		Lift();
		~Lift();

private:
		TalonSRX *motorOne;
		TalonSRX *motorTwo;
		TalonSRX *motorThree;
		TalonSRX *motorFour;


};


#endif /* SRC_LIFT_H_ */
