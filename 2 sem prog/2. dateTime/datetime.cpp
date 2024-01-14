#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include "datetime.h"

DateTime::DateTime() {
	date.day = 1;
	date.month = 1;
	date.year = 1;
	time.hour = 0;
	time.minute = 0;
	time.second = 0;
}

DateTime::DateTime(const DateTime& dt) {
	date = dt.date;
	time = dt.time;
}

DateTime::DateTime(Date d, Time t) {
	if (isTrueDate(d)) {
		date = d;
	}
	else {
		date.day = 1;
		date.month = 1;
		date.year = 1;
	}
	if (isTrueTime(t)) {
		time = t;
	}
	else {
		time.hour = 0;
		time.minute = 0;
		time.second = 0;
	}
}

DateTime::DateTime(DateTime&& dt) {
	date = dt.date;
	time = dt.time;
	dt.date.day = 1;
	dt.date.month = 1;
	dt.date.year = 1;
	dt.time.hour = 0;
	dt.time.minute = 0;
	dt.time.second = 0;
}

bool DateTime::isTrueDate(Date d) {
	if (d.month >= 1 && d.month <= 12) {
		if (d.day >= 1) {
			switch (d.month) {
			case 4:
			case 6:
			case 9:
			case 11:
				if (d.day <= 30) return true;
				break;
			case 2:
				if (d.day <= 28) return true;
				break;
			default:
				if (d.day <= 31) return true;
				break;
			}
		}
	}
	return false;
}

bool DateTime::isTrueTime(Time t) {
	if (t.hour >= 0 && t.hour <= 23) {
		if (t.minute >= 0 && t.minute <= 59) {
			if (t.second >= 0 && t.second <= 59) {
				return true;
			}
		}
	}
	return false;
}

DateTime& DateTime::getCurrentDateTime() {
	std::time_t time = std::time(nullptr);
	std::tm* now = std::localtime(&time);
	Date d;
	d.year = now->tm_year + 1900;
	d.month = now->tm_mon + 1;
	d.day = now->tm_mday;
	Time t;
	t.hour = now->tm_hour;
	t.minute = now->tm_min;
	t.second = now->tm_sec;
	static DateTime dt;
	dt.time = t;
	dt.date = d;
	return dt;
}

std::vector<std::string> DateTime::split(std::string str) {
	std::vector<std::string> v;
	std::string s = "";
	for (int i = 0; i < str.size(); i++) {
		if (ispunct(str[i]) || isspace(str[i])) {
			v.push_back(s);
			s = str[i];
			v.push_back(s);
			s = "";
		}
		else {
			s += str[i];
		}
	}
	v.push_back(s);
	v.push_back("\0");
	return v;
}

std::string DateTime::convert(std::string temp) const {
	std::vector<std::string> v = split(temp);
	for (int i = 0; i < v.size(); i++) {
		std::string str = "";
		for (int j = 0; j < v[i].size(); j++) {
			int devide = pow(10, v[i].size() - 1 - j);
			switch (v[i][j]) {
			case 'Y':
				str = std::to_string(date.year / devide);
				break;
			case 'M':
				str = std::to_string(date.month / devide);
				break;
			case 'D':
				str = std::to_string(date.day / devide);
				break;
			case 'h':
				str = std::to_string(time.hour / devide);
				break;
			case 'm':
				str = std::to_string(time.minute / devide);
				break;
			case 's':
				str = std::to_string(time.second / devide);
				break;
			default:
				str = v[i];
				break;
			}
		}
		v[i] = str;
	}
	std::string returnStr = "";
	for (int i = 0; i < v.size(); i++) {
		returnStr += v[i];
	}
	return returnStr;
}

DateTime& DateTime::getDateTime(std::string dateTime, std::string temp) {
	std::vector<std::string> v1 = split(temp);
	std::vector<std::string> v2 = split(dateTime);
	DateTime dt;
	for (int i = 0; i < v1.size(); i++) {
		if (v1[i] == "YYYY" || v1[i] == "YY" || v1[i] == "Y") {
			dt.date.year = std::stoi(v2[i]);
		}
		else if (v1[i] == "MM" || v1[i] == "M") {
			dt.date.month = std::stoi(v2[i]);
		}
		else if (v1[i] == "DD" || v1[i] == "D") {
			dt.date.day = std::stoi(v2[i]);
		}
		else if (v1[i] == "hh" || v1[i] == "h") {
			dt.time.hour = std::stoi(v2[i]);
		}
		else if (v1[i] == "mm" || v1[i] == "m") {
			dt.time.minute = std::stoi(v2[i]);
		}
		else if (v1[i] == "ss" || v1[i] == "s") {
			dt.time.second = std::stoi(v2[i]);
		}
	}
	return dt;
}

void DateTime::addSecs(int s) {
	int second = time.second + s;
	int minute = time.minute;
	if (second < 0 || second > 59) {
		minute = second / 60;
		second %= 60;
		addMinutes(minute);
	}
	time.second = second;
}

void DateTime::addMinutes(int m) {
	int minute = time.minute + m;
	int hour = time.hour;
	if (minute < 0 || minute > 59) {
		hour = minute / 60;
		minute %= 60;
		addHours(hour);
	}
	time.minute = minute;
}

void DateTime::addHours(int h) {
	int hour = time.hour + h;
	int day = date.day;
	if (hour < 0 || hour > 23) {
		day = hour / 24;
		hour %= 24;
		addDays(day);
	}
	time.hour = hour;
}

void DateTime::addDays(int d) {
	int day = date.day + d;
	int month = date.month;
	int months[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (day < 0 || day > months[date.month-1]) {
		month = day / months[date.month - 1];
		day %= months[date.month - 1];
		addMonth(month);
	}
	date.day = day;
}

void DateTime::addMonth(int m) {
	int month = date.month + m;
	int year = 0;
	if (month < 0 || month > 12) {
		year = month / 12;
		month %= 12;
		addYears(year);
	}
	date.month = month;
}

void DateTime::addYears(int y) {
	date.year += y;
}

int DateTime::daysTo(Date d) const {
	if (isTrueDate(d)) {
		int months[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		int month1 = 0;
		for (int i = 0; i < date.month; i++) {
			month1 += months[i];
		}
		int month2 = 0;
		for (int i = 0; i < d.month; i++) {
			month2 += months[i];
		}
		int days1 = date.year * 365 + month1 - (months[date.month - 1] - date.day);
		int days2 = d.year * 365 + month2 - (months[d.month - 1] - d.day);
		return abs(days1 - days2);
	}
	return -1;
}

int DateTime::secsTo(Date d) const {
	if (isTrueDate(d)) {
		int days = daysTo(d);
		int seconds = days * 24 * 60 * 60;
		return seconds;
	}
	return -1;
}
