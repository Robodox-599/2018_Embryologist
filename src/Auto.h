#ifndef SRC_AUTO_H_
#define SRC_AUTO_H_

#include <Macros.h>
#include <Drive.h>
#include <WPILib.h>
#include <ctre/Phoenix.h>

class Auto
{
public:
	Auto();
	~Auto();

	void preCheck();
	void auto0();
	void auto1();
	int dataVal();

private:
	std::string gameData;

	Drive* drive;
	int dataTest;
};




#endif /* SRC_AUTO_H_ */
