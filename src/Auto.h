#ifndef SRC_AUTO_H_
#define SRC_AUTO_H_

#include <Macros.h>
#include <Drive.h>
#include <WPILib.h>

class Auto
{
public:
	Auto();
	~Auto();

	void preCheck();
	void auto0();
	void auto1();

private:
	std::string gameData;
};




#endif /* SRC_AUTO_H_ */
