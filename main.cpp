#include <iostream>
#include <list>
#include "TimeIntervalType.h"
#include "TimeInterval.h"
#include "TimeTable.h"

//schedule table must be correct
TimeInterval getFreeIntervalFromSchedule(const SimpleTimeTable& table)
{
	auto beginInterval = table.getCopyTimeInterval(0);
	auto endInterval = table.getCopyTimeInterval(table.size() - 1);

	return TimeInterval(beginInterval.getBeginTime(), endInterval.getEndTime(), FREE);
}

//schedule table must be correct
SimpleTimeTable getUnavailableTableFromSchedule(const SimpleTimeTable& table)
{
	SimpleTimeTable unavailable_table;

	for (size_t position = 0; position < table.size() - 1; ++position)
	{
		auto firstInterval = table.getCopyTimeInterval(position);
		auto secondInterval = table.getCopyTimeInterval(position+1);
		TimeInterval unavailableInterval(firstInterval.getEndTime(), secondInterval.getBeginTime(), UNAVAILABLE);
		unavailable_table.pushBack(unavailableInterval);
	}
	
	return unavailable_table;
}

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

	CorrectTimeTable main_table(getFreeIntervalFromSchedule(schedule_table));
	main_table.insertSimpleTable(getUnavailableTableFromSchedule(schedule_table));
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