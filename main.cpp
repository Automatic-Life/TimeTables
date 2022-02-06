#include <iostream>
#include "TimeIntervalType.h"
#include "TimeInterval.h"
#include "TimeTable.h"
#include "JSONHandler.h"

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
	SimpleTimeTable schedule_table = createTimeTablefromJSON("schedule.json", SCHEDULE);
	
	SimpleTimeTable breaks_table = createTimeTablefromJSON("breaks.json", BREAKS);
	
	SimpleTimeTable busy_table = createTimeTablefromJSON("busy.json", BUSY);
	
	SimpleTimeTable request_table = createTimeTablefromJSON("request.json", REQUEST);
	
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

	createJSONFromTimeTable(rejected_table, "rejected.json");
		
	SimpleTimeTable free_table = main_table.createSimpleTable(FREE);
	createJSONFromTimeTable(free_table, "free.json");
		
	SimpleTimeTable new_busy_table = main_table.createSimpleTable(BUSY);
	createJSONFromTimeTable(new_busy_table, "new_busy.json");
		
	return 0;
}