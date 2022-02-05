#pragma once

using doctor_time_t = size_t;

enum TimeIntervalType_t
{
	SCHEDULE,
	UNAVAILABLE,
	BREAKS,
	BUSY,
	REQUEST,
	REJECTED,
	FREE,
};