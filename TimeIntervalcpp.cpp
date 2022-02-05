#include <iostream>
#include "TimeIntervalType.h"
#include "TimeInterval.h"

void TimeInterval::setIntervalBegin(doctor_time_t time) { beginTimePoint = time; }

void TimeInterval::setIntervalEnd(doctor_time_t time) { endTimePoint = time; }

void TimeInterval::setIntervalType(TimeIntervalType_t type) { timeIntervalType = type; }

doctor_time_t TimeInterval::getBeginTime() const { return beginTimePoint; }

doctor_time_t TimeInterval::getEndTime() const { return endTimePoint; }

TimeIntervalType_t TimeInterval::getIntervalType() const { return timeIntervalType; }

bool TimeInterval::isCorrect() const
{
	return (getBeginTime() < getEndTime());
}

bool TimeInterval::isInside(const TimeInterval& outTimeInterval) const
{
	return ((this->getBeginTime() >= outTimeInterval.getBeginTime())
		&& (this->getEndTime() <= outTimeInterval.getEndTime()));
}

std::ostream& operator<< (std::ostream& out, const TimeInterval& timeInterval)
{
	out << timeInterval.getBeginTime() << " : " << timeInterval.getEndTime() << '\n';
	return out;
}
