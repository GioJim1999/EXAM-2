#include "MyCalendar.h"
//Constructors:
MyCalendar::MyCalendar()
{
	currentYear = static_cast<unsigned short>(0);
	currentDay = static_cast<unsigned short>(0);
	currentMonth = static_cast<unsigned short>(0);
}

MyCalendar::MyCalendar(int month, int day, int year)
{
	currentDay = static_cast<unsigned short>(day);
	currentMonth = static_cast<unsigned short>(month);
	currentYear = static_cast<unsigned short>(year);
}

MyCalendar::MyCalendar(const MyCalendar& obj)
{
	currentYear = static_cast<unsigned short>(obj.getCurrentYear());
	currentMonth = static_cast<unsigned short>(obj.getCurrentMonth());
	currentDay = static_cast<unsigned short>(obj.getCurrentDay());
}

//Setters:
void MyCalendar::setCurrentYear(int newYear)
{
	currentYear = static_cast<unsigned short>(newYear);
}

void MyCalendar::setCurrentMonth(int newMonth)
{
	currentMonth = static_cast<unsigned short>(newMonth);
}

void MyCalendar::setCurrentDay(int newDay)
{
	currentDay = static_cast<unsigned short>(newDay);
}

void MyCalendar::scheduleDate(int month, int day)
{
	scheduleDays[month][day].setDescription("CHRISTMAS");
	scheduleDays[month][day].setType('H');
}

//Getters:
int MyCalendar::getCurrentYear() const
{
	return static_cast<int>(currentYear);
}

int MyCalendar::getCurrentMonth() const
{
	return static_cast<int>(currentMonth);
}

int MyCalendar::getCurrentDay() const
{
	return static_cast<int>(currentDay);
}

string MyCalendar::getMonthName() const
{
	int month = this->getCurrentMonth();
	return months[month];
}

string MyCalendar::addDaySuffix() const
{
	int day = this->getCurrentDay();
	int firstNum;
	if (day > 20)
		firstNum = day % 10;
	else
		firstNum = day;

	switch (firstNum)
	{
	case 1:
		return "st"; break;
	case 2:
		return "nd"; break;
	case 3: 
		return "rd"; break;
	default:
		return "th"; break;
	}
}

MyScheduleDate MyCalendar::getScheduleDate(int month, int day) const
{

	MyScheduleDate temp;

	char type = this->scheduleDays[month][day].getType();
	string desc = this->scheduleDays[month][day].getDescription();

	temp.setType(type);
	temp.setDescription(desc);

	return temp;
}

//Methods:
string MyCalendar::getDayofWeek() const
{
	int day = this->getCurrentDay();
	int month = this->getCurrentMonth();
	int year = this->getCurrentYear();

	if (month == 1)
	{
		month = 13;
		year--;
	}

	if (month == 2)
	{
		month = 14;
		year--;
	}

	int q = day;
	int m = month;
	int k = year % 100;
	int j = year / 100;
	int h = q + 13 * (m + 1) / 5 + k + k / 4 + j / 4 + 5 * j;

	h = h % 7;

	switch (h)
	{
	case  0:
		return "Saturday"; break;
	case 1:
		return "Sunday"; break;
	case 2:
		return "Monday"; break;
	case 3:
		return "Tuesday"; break;
	case 4:
		return "Wednesday"; break;
	case 5:
		return "Thursday"; break;
	case 6:
		return "Friday"; break;
	default:
		return "Unknown";
	}
}

bool MyCalendar::isLeapYear() const
{
	if (currentYear % 400 == 0)
		return true;
	else if (currentYear % 100 == 0)
		return false;
	else if (currentYear % 4 == 0)
		return true;
	else
		return false;
}

string MyCalendar::printDateFormat2() const
{
	return getDayofWeek() + ", " + getMonthName() + " " + to_string(getCurrentDay()) + addDaySuffix() + ", " + to_string(getCurrentYear());
}

//Operators:
ostream& operator<<(ostream& out, const MyCalendar& obj)
{
	out << obj.getCurrentMonth() << "/" << obj.getCurrentDay() << "/" << obj.getCurrentYear();
	return out;
}

MyCalendar MyCalendar::operator++()
{
	currentDay++;
	if (this->isLeapYear() && currentMonth == 2)
	{
		if (currentDay > 29)
		{
			setCurrentDay(1);
			currentMonth++;
			setCurrentMonth(currentMonth);
		}
	}
	else
	{
		if (currentMonth == 2)
		{
			if (currentDay > 28)
			{
				currentMonth++;
				setCurrentMonth(currentMonth);
			}
		}
		else if (currentMonth == 1 || currentMonth == 3 || currentMonth == 5 || currentMonth == 7 || currentMonth == 8 || currentMonth == 10 || currentMonth == 12)
		{
			if (currentDay > 31)
			{
				setCurrentDay(1);
				currentMonth++;
				if (currentMonth > 12)
				{
					setCurrentMonth(1);
					currentYear++;
					if (currentYear > 9999)
					{
						setCurrentYear(1);
					}
					else
						setCurrentYear(currentYear);
				}
			}
			else
				setCurrentMonth(currentMonth);
		}
		else
		{
			if (currentDay > 30)
			{
				setCurrentDay(1);
				currentMonth++;
				setCurrentMonth(currentMonth);
			}
		}
	}

	return *this;
}

MyCalendar MyCalendar::operator++(int)
{
	MyCalendar temp(*this);

	currentDay++;
	if (this->isLeapYear() && currentMonth == 2)
	{
		if (currentDay > 29)
		{
			setCurrentDay(1);
			currentMonth++;
			setCurrentMonth(currentMonth);
		}
	}
	else
	{
		if (currentMonth == 2)
		{
			if (currentDay > 28)
			{
				setCurrentDay(1);
				currentMonth++;
				setCurrentMonth(currentMonth);
			}
		}
		else if (currentMonth == 1 || currentMonth == 3 || currentMonth == 5 || currentMonth == 7 || currentMonth == 8 || currentMonth == 10 || currentMonth == 12)
		{
			if (currentDay > 31)
			{
				setCurrentDay(1);
				currentMonth++;
				if (currentMonth > 12)
				{
					setCurrentMonth(1);
					currentYear++;
					if (currentYear > 9999)
					{
						setCurrentYear(1);
					}
					else
						setCurrentYear(currentYear);
				}
			}
			else
				setCurrentMonth(currentMonth);
		}
		else
		{
			if (currentDay > 30)
			{
				setCurrentDay(1);
				currentMonth++;
				setCurrentMonth(currentMonth);
			}
		}
	}

	return temp;
}

MyCalendar MyCalendar::operator--()
{
	currentDay--;
	if (currentDay < 1)
	{
		if (currentMonth == 1)
		{
			setCurrentDay(31);
			setCurrentMonth(12);
			currentYear--;
			if (currentYear < 1)
			{
				setCurrentYear(9999);
			}
			setCurrentYear(currentYear);
		}
		else if (this->isLeapYear() && currentMonth == 3)
		{
			setCurrentDay(29);
			currentMonth--;
			setCurrentMonth(currentMonth);
		}
		else if (currentMonth == 3)
		{
			setCurrentDay(28);
			currentMonth--;
			setCurrentMonth(currentMonth);
		}
		else if (currentMonth == 2 || currentMonth == 4 || currentMonth == 6 || currentMonth == 9 || currentMonth == 11)
		{
			setCurrentDay(31);
			currentMonth--;
			setCurrentMonth(currentMonth);
		}
		else
		{
			setCurrentDay(30);
			currentMonth--;
			setCurrentMonth(currentMonth);
		}
	}

	return *this;
}

MyCalendar MyCalendar::operator--(int)
{
	MyCalendar temp(*this);
	currentDay--;
	if (currentDay < 1)
	{
		if (currentMonth == 1)
		{
			setCurrentDay(31);
			setCurrentMonth(12);
			currentYear--;
			if (currentYear < 1)
			{
				setCurrentYear(9999);
			}
			else
				setCurrentYear(currentYear);
		}
		else if (this->isLeapYear() && currentMonth == 3)
		{
			setCurrentDay(29);
			currentMonth--;
			setCurrentMonth(currentMonth);
		}
		else if (currentMonth == 3)
		{
			setCurrentDay(28);
			currentMonth--;
			setCurrentMonth(currentMonth);
		}
		else if (currentMonth == 2 || currentMonth == 4 || currentMonth == 6 || currentMonth == 9 || currentMonth == 11)
		{
			setCurrentDay(31);
			currentMonth--;
			setCurrentMonth(currentMonth);
		}
		else
		{
			setCurrentDay(30);
			currentMonth--;
			setCurrentMonth(currentMonth);
		}
	}
	return temp;
}

MyCalendar MyCalendar::jumpForward(int n)
{
	MyCalendar temp(*this);
	for (int i = 0; i < n; i++)
	{
		temp++;
	}

	cout << "\n\tJump forward(" + to_string(n) + ")...";

	return temp;
}

MyCalendar MyCalendar::jumpBackward(int n)
{
	MyCalendar temp(*this);
	for (int i = 1; i < n; i++)
	{
		--temp;
	}

	cout << "\n\tJump backward(" + to_string(n) + ")...";
	return temp;
}