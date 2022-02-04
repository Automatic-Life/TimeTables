#include <iostream>
#include <list>

using doctor_time_t = size_t;

enum TimeIntervalType_t
{
	SCHEDULE,
	UNAVAILABLE,
	BREAK,
	BUSY,
	REQUEST,
	REJECTED,
	FREE,
};

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

	void setIntervalBegin(doctor_time_t time) { beginTimePoint = time; }
	
	void setIntervalEnd(doctor_time_t time) { endTimePoint = time; }
	
	void setIntervalType(TimeIntervalType_t type) { timeIntervalType = type; }
	
	doctor_time_t getBeginTime() const { return beginTimePoint; }

	doctor_time_t getEndTime() const { return endTimePoint; }

	TimeIntervalType_t getIntervalType() const { return timeIntervalType; }

	bool isCorrect() const
	{
		return (getBeginTime() < getEndTime());
	}
	
	bool isInside(const TimeInterval& outTimeInterval) const
	{
		return ((this->getBeginTime() >= outTimeInterval.getBeginTime())
			&& (this->getEndTime() <= outTimeInterval.getEndTime()));
	}

};

std::ostream& operator<< (std::ostream& out, const TimeInterval& timeInterval)
{
	out << timeInterval.getBeginTime() << " : " << timeInterval.getEndTime() << '\n';
	return out;
}

class BaseTimeTable
{
protected:

	std::list<TimeInterval> timeIntervalList;

public:

	size_t size() const
	{
		return timeIntervalList.size();
	}

	TimeInterval getCopyTimeInterval(size_t position)
	{
		if (position >= timeIntervalList.size()) { exit(1); } // error

		auto it = timeIntervalList.begin();
		it = std::next(it, position);

		return *it;
	}

	void printTable()
	{
		for (auto& in : timeIntervalList)
		{
			std::cout << in;
		}
	}


};

class SimpleTimeTable: public BaseTimeTable
{

public:

	void pushBack(doctor_time_t begin, doctor_time_t end, TimeIntervalType_t type = BUSY)
	{
		timeIntervalList.push_back(TimeInterval(begin, end, type));
	}

	void pushBack(TimeInterval timeInterval)
	{
		timeIntervalList.push_back(timeInterval);
	}

	void insert(TimeInterval timeInterval, size_t position)
	{
		if (position > timeIntervalList.size()) { exit(1); } // error
		
		auto it = timeIntervalList.begin();
		it = std::next(it, position);
		timeIntervalList.insert(it, timeInterval);
	}

};

class CorrectTimeTable : public BaseTimeTable
{

public:

	CorrectTimeTable(doctor_time_t startTime, doctor_time_t endTime)
	{
		timeIntervalList.push_front(TimeInterval(startTime, endTime, FREE));
	}

	int32_t findCorrectFreeInterval(const TimeInterval& timeInterval) const
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

	bool insert(TimeInterval insertInterval)
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

	void insertSimpleTable(SimpleTimeTable& simpleTable)
	{
		for (size_t position = 0; position < simpleTable.size(); ++position)
		{
			auto interval = simpleTable.getCopyTimeInterval(position);
			this->insert(interval);
		}
	}

	SimpleTimeTable createSimpleTable(TimeIntervalType_t intervalType)
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

};


int main()
{
	
	SimpleTimeTable schedule_table;
	schedule_table.pushBack(1000, 1200, SCHEDULE);
	schedule_table.pushBack(1400, 1600, SCHEDULE);
	
	SimpleTimeTable breaks_table;
	breaks_table.pushBack(1100, 1115, BREAK);
	breaks_table.pushBack(1500, 1515, BREAK);
	
	SimpleTimeTable busy_table;
	busy_table.pushBack(1000, 1015);
	busy_table.pushBack(1015, 1045);
	busy_table.pushBack(1115, 1130);
	busy_table.pushBack(1415, 1438);
	busy_table.pushBack(1517, 1550);

	SimpleTimeTable request_table;
	request_table.pushBack(950, 1005);
	request_table.pushBack(1045, 1055);
	request_table.pushBack(1040, 1100);
	request_table.pushBack(1400, 1410);
	request_table.pushBack(1515, 1530);
	request_table.pushBack(1405, 1415);

	CorrectTimeTable main_table(1000, 1600);
	main_table.insert(TimeInterval(1200, 1400, UNAVAILABLE));
	main_table.insertSimpleTable(breaks_table);
	main_table.insertSimpleTable(busy_table);
	
	SimpleTimeTable rejected_table;

	for (size_t requestPosition = 0; requestPosition < request_table.size(); ++requestPosition)
	{
		auto requestInterval = request_table.getCopyTimeInterval(requestPosition);
		bool result = main_table.insert(requestInterval);
		if (result == false)
		{
			requestInterval.setIntervalType(REJECTED);
			rejected_table.pushBack(requestInterval);
		}
	}
		
	SimpleTimeTable free_table = main_table.createSimpleTable(FREE);
	
	SimpleTimeTable new_busy_table = main_table.createSimpleTable(BUSY);
	
	return 0;
}