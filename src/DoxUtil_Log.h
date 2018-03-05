/*
 * DoxUtil_Log.h
 *
 *  Created on: Jan 22, 2018
 *      Author: Admin
 */

#ifndef SRC_DOXUTIL_LOG_H_
#define SRC_DOXUTIL_LOG_H_

#include <string>
#include <iostream>
#include <fstream>
#include <WPILib.h>
#include <ctre/Phoenix.h>

class DoxLog {
public:

	DoxLog();

	DoxLog(std::string path);

	virtual ~DoxLog();

	void LogIt(std::string message);

	void LogIt(std::string message, int level);

	bool getIsOpen();

	void setLogLevel(int level);

	void close();

private:
	std::ofstream logFile;
	bool m_isOpen = false;
	int m_level = -1;
};

#endif /* SRC_DOXUTIL_LOG_H_ */
