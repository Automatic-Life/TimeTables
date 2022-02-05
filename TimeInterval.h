#pragma once

#include <iostream>
#include "TimeIntervalType.h"


class TimeInterval
{
private:

	doctor_time_t beginTimePoint = 0;
	doctor_time_t endTimePoint = 0;
	TimeIntervalType_t timeIntervalType = BUSY;

public:

	TimeInterval()
	{
	}

	TimeInterval(doctor_time_t begin, doctor_time_t end, TimeIntervalType_t type = BUSY)
		:beginTimePoint{ begin }, endTimePoint{ end }, timeIntervalType{ type }
	{
	}

	void setIntervalBegin(doctor_time_t time);

	void setIntervalEnd(doctor_time_t time);

	void setIntervalType(TimeIntervalType_t type);

	doctor_time_t getBeginTime() const;

	doctor_time_t getEndTime() const;

	TimeIntervalType_t getIntervalType() const;

	bool isCorrect() const;
	
	bool isInside(const TimeInterval& outTimeInterval) const;
	
};

std::ostream& operator<< (std::ostream& out, const TimeInterval& timeInterval);