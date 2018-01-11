/*
 * Lift.h
 *
 *  Created on: Jan 6, 2018
 *      Author: Admin
 */
#include "CANTalon.h"

#ifndef SRC_LIFT_H_
#define SRC_LIFT_H_


using namespace std;

class Lift
{
public:
		Lift();
		~Lift();

private:
		CANTalon* motorOne;



};


#endif /* SRC_LIFT_H_ */
