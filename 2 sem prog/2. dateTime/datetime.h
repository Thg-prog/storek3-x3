#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <ctime>

struct Date {
	int year;
	int month;
	int day;
};

struct Time {
	int hour;
	int minute;
	int second;
};

class DateTime {
	Date date;
	Time time;
public:
	DateTime();
	DateTime(const DateTime& dt);
	DateTime(Date d, Time t);
	DateTime(DateTime&& dt);
	inline void setDate(Date d) { if (isTrueDate(d)) date = d; }
	inline void setTime(Time t) { if (isTrueTime(t)) time = t; }
	inline void setYear(int year) { date.year = year; }
	inline void setMonth(int month) { if (month >= 1 && month <= 12) date.month = month; }
	inline void setDay(int day) { int months[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; if (day >= 1 && day <= months[date.month - 1]) date.day = day; }
	inline void setHour(int hour) { if (hour >= 0 && hour <= 23) time.hour = hour; }
	inline void setMinute(int minute) { if (minute >= 0 && minute <= 59) time.minute = minute; }
	inline void setSecond(int second) { if (second >= 0 && second <= 59) time.second = second; }
	inline Date getDate() const { return date; }
	inline Time getTime() const { return time; }
	inline int getYear() const { return date.year; }
	inline int getMonth() const { return date.month; }
	inline int getDay() const { return date.day; }
	inline int getHour() const { return time.hour; }
	inline int getMinute() const { return time.minute; }
	inline int getSecond() const { return time.second; }
	static bool isTrueDate(Date d);
	static bool isTrueTime(Time t);
	static DateTime& getCurrentDateTime();
	static std::vector<std::string> split(std::string str);
	std::string convert(std::string temp) const;
	static DateTime& getDateTime(std::string dateTime, std::string temp);
	void addSecs(int s);
	void addMinutes(int m);
	void addHours(int h);
	void addDays(int d);
	void addMonth(int m);
	void addYears(int y);
	int daysTo(Date d) const;
	int secsTo(Date d) const;
};