#pragma once
#include "MyScheduleDate.h"
class MyCalendar : public MyScheduleDate
{
	string months[13] = { "unknown", "January", "February", "March", "April", "May", "June" , "July", "August", "September", "October", "November", "December" };
private:
	unsigned short currentYear;
	unsigned short currentMonth;
	unsigned short currentDay;
	MyScheduleDate scheduleDays[12][31];

public:
	//Constructor:
	MyCalendar();
	MyCalendar(const MyCalendar& obj);
	MyCalendar(int month, int day, int year);

	//Setters:
	void setCurrentYear(int newYear);
	void setCurrentMonth(int newMonth);
	void setCurrentDay(int newDay);
	void setScheduleDate(char type, string desc, int month, int day);

	//Getters:
	int getCurrentYear() const;
	int getCurrentMonth() const;
	int getCurrentDay() const;
	MyScheduleDate getScheduleDate() const;
	string getMonthName() const;
	string getMonthName(int month) const;
	string addDaySuffix() const;
	string getDayofWeek() const;
	string printDateFormat2() const;
	bool isLeapYear() const;
	void displayScheduledDays();
	void displayScheduledDaysMonth(int month);
	void displayScheduledDay(int day, int month);

	//Methods:
	MyCalendar jumpForward(int);
	MyCalendar jumpBackward(int);

	//Operators:
	MyCalendar operator++();
	MyCalendar operator++(int);
	MyCalendar operator--();
	MyCalendar operator--(int);

	friend ostream& operator<<(ostream& out, const MyCalendar& obj);
};

