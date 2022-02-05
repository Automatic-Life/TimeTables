#include <iostream>
#include "TimeIntervalType.h"
#include "TimeInterval.h"
#include "TimeTable.h"

size_t BaseTimeTable::size() const 
{
	return timeIntervalList.size();
}

TimeInterval BaseTimeTable::getCopyTimeInterval(size_t position) const
{
	if (position >= timeIntervalList.size()) { exit(1); } // error

	auto it = timeIntervalList.cbegin();
	it = std::next(it, position);

	return *it;
}

void BaseTimeTable::printTable() const
{
	for (auto& in : timeIntervalList)
	{
		std::cout << in;
	}
}

void SimpleTimeTable::pushBack(doctor_time_t begin, doctor_time_t end, TimeIntervalType_t type)
{
	timeIntervalList.push_back(TimeInterval(begin, end, type));
}

void SimpleTimeTable::pushBack(TimeInterval timeInterval)
{
	timeIntervalList.push_back(timeInterval);
}

void SimpleTimeTable::insert(TimeInterval timeInterval, size_t position)
{
	if (position > timeIntervalList.size()) { exit(1); } // error

	auto it = timeIntervalList.begin();
	it = std::next(it, position);
	timeIntervalList.insert(it, timeInterval);
}

