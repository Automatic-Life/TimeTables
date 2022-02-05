#include "TimeIntervalType.h"
#include "TimeInterval.h"
#include "TimeTable.h"

CorrectTimeTable::CorrectTimeTable(TimeInterval timeInterval)
{
	timeIntervalList.push_front(timeInterval);
}

int32_t CorrectTimeTable::findCorrectFreeInterval(const TimeInterval& timeInterval) const
{
	size_t freePosition = 0;
	for (auto it = timeIntervalList.begin(); it != timeIntervalList.end(); ++it, ++freePosition)
	{
		if (it->getIntervalType() == FREE)
		{
			if (timeInterval.getBeginTime() <= it->getEndTime())
			{
				if ((timeInterval.getBeginTime() < it->getBeginTime())
					|| (timeInterval.getEndTime() > it->getEndTime())
					|| (timeInterval.getBeginTime() == it->getEndTime()))
				{
					return -1;
				}
				else
				{
					return freePosition;
				}
			}
			else
			{
				continue;
			}

		}
	}

	return -1;
}

bool CorrectTimeTable::insert(TimeInterval insertInterval)
{
	if (insertInterval.getIntervalType() == FREE) { return false; }

	int32_t freePosition = findCorrectFreeInterval(insertInterval);
	if (freePosition < 0) { return false; }

	auto startInterval = timeIntervalList.begin();
	auto freeInterval = std::next(startInterval, freePosition);
	if (insertInterval.getBeginTime() == freeInterval->getBeginTime())
	{
		if (insertInterval.getEndTime() == freeInterval->getEndTime())
		{
			freeInterval->setIntervalType(insertInterval.getIntervalType());
		}
		else
		{
			timeIntervalList.insert(freeInterval, insertInterval);
			freeInterval->setIntervalBegin(insertInterval.getEndTime());
		}
	}
	else
	{
		if (insertInterval.getEndTime() == freeInterval->getEndTime())
		{
			timeIntervalList.insert(freeInterval,
				TimeInterval(freeInterval->getBeginTime(), insertInterval.getBeginTime(), FREE));

			freeInterval->setIntervalBegin(insertInterval.getBeginTime());
			freeInterval->setIntervalType(insertInterval.getIntervalType());

		}
		else
		{
			TimeInterval newInterval(freeInterval->getBeginTime(), insertInterval.getBeginTime(), FREE);

			freeInterval->setIntervalBegin(insertInterval.getEndTime());

			timeIntervalList.insert(freeInterval, newInterval);
			timeIntervalList.insert(freeInterval, insertInterval);
		}
	}

	return true;
}

void CorrectTimeTable::insertSimpleTable(const SimpleTimeTable& simpleTable)
{
	for (size_t position = 0; position < simpleTable.size(); ++position)
	{
		auto interval = simpleTable.getCopyTimeInterval(position);
		this->insert(interval);
	}
}

SimpleTimeTable CorrectTimeTable::createSimpleTable(TimeIntervalType_t intervalType)
{
	SimpleTimeTable newTable;

	for (size_t position = 0; position < this->size(); ++position)
	{
		auto interval = this->getCopyTimeInterval(position);
		if (interval.getIntervalType() == intervalType)
		{
			newTable.pushBack(interval);
		}
	}

	return newTable;
}

	
