#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "TimeIntervalType.h"
#include "TimeInterval.h"
#include "TimeTable.h"

const size_t digitCountInPosition = 2; 

// example input 10:30:00
doctor_time_t getTimeFromString(const std::string& str) 
{
	auto strHour = str.substr(0, digitCountInPosition);
	auto strMinutes = str.substr(digitCountInPosition +1, digitCountInPosition);
	std::string strTime = strHour + strMinutes;

	doctor_time_t outTime = std::stoi(strTime);
	if (outTime > 2400) { exit(1); } // error must be in range {0 - 2400}
	
	return outTime; // example output 1030
	
}

// example input {"10:30:00" :"11:00:00"}
TimeInterval getTimeIntervalFromString(const std::string& str, TimeIntervalType_t intervalType) 
{
	auto firstPosition = str.find("\"");
	auto lastPosition = str.find("\"", (firstPosition + 1));
	auto strBeginTime = str.substr(firstPosition + 1, (lastPosition - firstPosition - 1));
	auto intBeginTime = getTimeFromString(strBeginTime);

	lastPosition = str.rfind("\"");
	firstPosition = str.rfind("\"", (lastPosition - 1));
	auto strEndTime = str.substr(firstPosition + 1, (lastPosition - firstPosition - 1));
	auto intEndTime = getTimeFromString(strEndTime);

	return TimeInterval(intBeginTime, intEndTime, intervalType);
	// example output 1030 1100
}


SimpleTimeTable createTimeTablefromJSON(const std::string& filename, TimeIntervalType_t intervalType)
{
	std::ifstream json_file(filename);
	if (!json_file)
	{
		std::cerr << "File could not be opened for reading!" << std::endl;
		exit(1);
	}

	char iterator;
	char parsePoint = '{';

	std::vector<std::string> strTimeTable;
	std::string strInterval;
	while (!json_file.eof())
	{
		iterator = json_file.get();
		if (iterator == parsePoint)
		{
			json_file.seekg(-1, std::ios::cur);
			getline(json_file, strInterval);
			strTimeTable.push_back(strInterval);
		}
	}

	json_file.close();

	SimpleTimeTable timeTable;

	for (auto& strTimeInterval : strTimeTable)
	{
		timeTable.pushBack(getTimeIntervalFromString(strTimeInterval, intervalType));
	}

	return timeTable;
}