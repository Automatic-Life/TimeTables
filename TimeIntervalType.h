#pragma once

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