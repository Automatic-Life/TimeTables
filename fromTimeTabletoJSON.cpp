#include <iostream>
#include <string>
#include <fstream>
#include "TimeIntervalType.h"
#include "TimeInterval.h"
#include "TimeTable.h"

const size_t digitCount = 4; // 09:30:00 - first 4 digits
const size_t digitCountInPosition = 2;

std::string getStringFromTime(doctor_time_t intTime) // example input 930
{
	std::string strTime = std::to_string(intTime);
	
	if (strTime.size() < digitCount)
	{
		strTime.insert(0, digitCount - strTime.size(), '0'); // example output 0930
	}

	strTime.insert(digitCountInPosition, 1, ':'); // example output 09:30
	strTime.push_back(':'); // example output 09:30:
	for (size_t insertCounter = 0; insertCounter < digitCountInPosition; ++insertCounter)
	{
		strTime.push_back('0'); // example output 09:30:00
	} 
	strTime.insert(0, 1, '"');
	strTime.push_back('"');

	return strTime; // example output "09:30:00"
}

std::string getStringFromTimeInterval(const TimeInterval& timeInterval)
{
	std::string strInterval = "{";
	strInterval += getStringFromTime(timeInterval.getBeginTime());
	strInterval.push_back(' ');
	strInterval.push_back(':');
	strInterval += getStringFromTime(timeInterval.getEndTime());
	strInterval.push_back('}');

	return strInterval; // example output {"09:30:00" :"10:00:00"}
}

void createJSONFromTimeTable(const SimpleTimeTable& timeTable, const std::string& filename)
{
	std::ofstream json_file(filename);

	if (!json_file)
	{
		std::cerr << "File could not be opened for writing!" << std::endl;
		exit(1);
	}

	json_file << "[\n";

	for (size_t position = 0; position < timeTable.size(); ++position)
	{
		json_file << ' ';
		json_file << getStringFromTimeInterval(timeTable.getCopyTimeInterval(position));
		json_file << ',';
		json_file << '\n';
	}

	json_file.seekp(-3, std::ios::cur); // erease ',' in last time interval
	json_file << ' ';
	json_file << '\n';

	json_file << ']';

	json_file.close();

}