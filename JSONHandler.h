#pragma once

#include <string>
#include "TimeIntervalType.h"
#include "TimeInterval.h"
#include "TimeTable.h"

SimpleTimeTable createTimeTablefromJSON(const std::string& filename, TimeIntervalType_t intervalType);

void createJSONFromTimeTable(const SimpleTimeTable& timeTable, const std::string& filename);

