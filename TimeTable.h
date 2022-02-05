#pragma once

#include <list>
#include "TimeIntervalType.h"
#include "TimeInterval.h"

class BaseTimeTable
{
protected:

	std::list<TimeInterval> timeIntervalList;

public:

	size_t size() const;
	
	TimeInterval getCopyTimeInterval(size_t position) const;
	
	void printTable() const;
	
};

class SimpleTimeTable : public BaseTimeTable
{

public:

	void pushBack(doctor_time_t begin, doctor_time_t end, TimeIntervalType_t type = BUSY);
	
	void pushBack(TimeInterval timeInterval);
	
	void insert(TimeInterval timeInterval, size_t position);
	
};

class CorrectTimeTable : public BaseTimeTable
{

public:

	CorrectTimeTable(TimeInterval timeInterval);
	
	int32_t findCorrectFreeInterval(const TimeInterval& timeInterval) const;

	bool insert(TimeInterval insertInterval);

	void insertSimpleTable(const SimpleTimeTable& simpleTable);

	SimpleTimeTable createSimpleTable(TimeIntervalType_t intervalType);

};