/*
 * DoxUtil_Log.cpp
 *
 *  Created on: Mar 7, 2018
 *      Author: Admin
 */
#include <DoxUtil_Log.h>
#include <string>
#include <ctime>

DoxLog::DoxLog()
{
	std::string fileName;

	std::time_t t = std::time(nullptr);
	char buffer[100];
	if (std::strftime(buffer, sizeof(buffer), "%Y%m%d-%H%M%S", std::localtime(&t)))
	{
		fileName = buffer;
	}

	logFile.open("/home/lvuser/" + fileName + ".txt");

	m_isOpen = true;
}

DoxLog::DoxLog(std::string path)
{
	std::string fileName;

	std::time_t t = std::time(nullptr);
	char buffer[100];
	if (std::strftime(buffer, sizeof(buffer), "%Y%m%d-%H%M%S", std::localtime(&t)))
	{
		fileName = buffer;
	}

	logFile.open(path + fileName + ".txt");

	m_isOpen = true;
}

DoxLog::~DoxLog()
{
	this->close();
}

void DoxLog::LogIt(int level)
{
	if(level == 1)
	{
		LogIt("message", 0, level);
	}
	if(level == 2)
	{
		LogIt("message", 0, level);
	}
}

void DoxLog::LogIt(std::string message, float value, int level)
{
	if (!m_isOpen) { return; } // In case file's closed, no action

	if(level <= m_level || level == -1)
	{
		std::string timeStamp = "*** ";

		std::time_t t = std::time(nullptr);
		char buffer[100];
		if (std::strftime(buffer, sizeof(buffer), "%Y%m%d-%H%M%S", std::localtime(&t)))
		{
			timeStamp = buffer;
		}

		logFile << timeStamp << "\t" << level << "\t" << message << "\t" << value << "\n";
	}
}

// DoxUtil_Log

void DoxLog::close()
{
	if (m_isOpen)
	{
		logFile.close();
		m_isOpen = false;
	}
	else
	{
		// File's already closed, no action
	}
}

bool DoxLog::getIsOpen()
{
	return m_isOpen;
}
