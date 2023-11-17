#include "MyCalendar.h"
#include<Windows.h>
#include<iomanip>
//Constructors:
//Default Constructor (no args)
MyCalendar::MyCalendar()
{
	currentYear = static_cast<unsigned short>(0);
	currentDay = static_cast<unsigned short>(0);
	currentMonth = static_cast<unsigned short>(0);

	for(int i = 0; i < 12; i++)
		for (int j = 0; j < 31; j++)
		{
			this->scheduleDays[i][j].setDescription("unscheduled");
			this->scheduleDays[i][j].setType('U');
		}
}

//Precondtion: month, day, year (int int int)
//Postcondition: creates a new MyCalendar object using the passed in arguments
MyCalendar::MyCalendar(int month, int day, int year) 
{
	currentDay = static_cast<unsigned short>(day);
	currentMonth = static_cast<unsigned short>(month);
	currentYear = static_cast<unsigned short>(year);

	for (int i = 0; i < 12; i++)
		for (int j = 0; j < 31; j++)
		{
			this->scheduleDays[i][j].setDescription("unscheduled");
			this->scheduleDays[i][j].setType('U');
		}
}

//Precondition: obj (constt MyCalendar&)
//Postcondition: creates a copy of the passed in object
MyCalendar::MyCalendar(const MyCalendar& obj)
{
	currentYear = static_cast<unsigned short>(obj.getCurrentYear());
	currentMonth = static_cast<unsigned short>(obj.getCurrentMonth());
	currentDay = static_cast<unsigned short>(obj.getCurrentDay());

	for (int i = 0; i < 12; i++)
		for (int j = 0; j < 31; j++)
			scheduleDays[i][j] = obj.scheduleDays[i][j];
}

//Setters:

//Precondition: newYear (int)
//Postcondition: Sets the object's year to the newYear
void MyCalendar::setCurrentYear(int newYear)
{
	currentYear = static_cast<unsigned short>(newYear);
}

//Precondition: newMonth (int)
//Postcondition: Sets the object's month to the newMonth
void MyCalendar::setCurrentMonth(int newMonth)
{
	currentMonth = static_cast<unsigned short>(newMonth);
}

//Precondition: newDay (int)
//Postcondition: Sets the object's day to the newDay
void MyCalendar::setCurrentDay(int newDay)
{
	currentDay = static_cast<unsigned short>(newDay);
}

//Precondition: type (char), description (string), month (int), day (int)
//Postcondition: sets the object's schedule type and description to the passed in month day combo
void MyCalendar::setScheduleDate(char type, string desc, int month, int day)
{
	this->scheduleDays[month - 1][day - 1].setType(type);
	this->scheduleDays[month - 1][day - 1].setDescription(desc);
}

//Getters:

//Precondition: N/A
//Postcondition: returns the year variable
int MyCalendar::getCurrentYear() const
{
	return static_cast<int>(currentYear);
}

//Precondition: N/A
//Postcondition: returns the month variable
int MyCalendar::getCurrentMonth() const
{
	return static_cast<int>(currentMonth);
}


//Precondition: N/A
//Postcondition: returns the day vairable
int MyCalendar::getCurrentDay() const
{
	return static_cast<int>(currentDay);
}

//Precondition: N/A
//Postcondition: returns the month name depeding on the object's current month
string MyCalendar::getMonthName() const
{
	int month = this->getCurrentMonth();
	return months[month];
}

//Precondition: month (int)
//Postcondition: returns the month name depeding on the passed in month
string MyCalendar::getMonthName(int month) const
{
	return months[month];
}

//Precondition: N/A
//Postcondition: adds the suffix st, nd, rd, th depeding on the day number
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

//Precondition: N/A
//Postcondition: Displays all the scheduled days for the year
void MyCalendar::displayScheduledDays()
{
	int counter = 0;
	int totalScheduledDays = 0;
	for (int i = 0; i < 12; i++)
	{
		cout << "\n\t" << getMonthName(i + 1) << ":    ";
		for (int j = 0; j < 31; j++)
		{
			if (this->scheduleDays[i][j].getType() != 'U')
			{
				if (this->scheduleDays[i][j].getType() == 'H')
					setConsoleColor2(BACKGROUND_GREEN);
				if (this->scheduleDays[i][j].getType() == 'P')
					setConsoleColor2(BACKGROUND_RED);
				cout << "\n\t" << to_string(j + 1) << " - " << this->scheduleDays[i][j].getDescription();
				counter++;
				totalScheduledDays++;
				setConsoleColor2(white);
			}
		}
		if (counter == 0)
		{
			cout << "";
			cout << "\tNo scheduled dates for this month.\n";
		}

		counter = 0;
	}
	cout << "\n\tTotal Scheduled days for the year: " << totalScheduledDays << "\n";
}

//Preconditon: month (int)
//Postcondition: Displays all the scheduled days for the passed in month
void MyCalendar::displayScheduledDaysMonth(int month)
{
	int counter = 0;
	for (int i = 0; i < 31; i++)
	{
		if (this->scheduleDays[month - 1][i].getType() != 'U')
		{
			if (this->scheduleDays[month-1][i].getType() == 'H')
				setConsoleColor2(BACKGROUND_GREEN);
			if (this->scheduleDays[month-1][i].getType() == 'P')
				setConsoleColor2(BACKGROUND_RED);
			cout << "\n\t" << i + 1 << " - " << this->scheduleDays[month - 1][i].getDescription();
			counter++;
		}
		setConsoleColor2(white);
	}
	setConsoleColor2(white);
	if (counter == 0)
		cout << "\n\tNo scheduled days for this month.";
	else
		cout << "\n\t" << counter << " days scheduled for this month.";

	cout << "\n";
}

//Precondition: day (int), month (int)
//Postcondition: displays the schedule for the passed in day and month
void MyCalendar::displayScheduledDay(int day, int month)
{
	if (this->scheduleDays[month - 1][day - 1].getType() == 'H')
		setConsoleColor2(BACKGROUND_GREEN);
	else if (this->scheduleDays[month - 1][day - 1].getType() == 'P')
		setConsoleColor2(BACKGROUND_RED);
	cout << "\n\t" << day << " - " << this->scheduleDays[month - 1][day - 1].getDescription() << "\n";
	setConsoleColor2(white);
}

//Precondition: month (int), day (int)
//Postcondition: returns the type for the passed in month and day
char MyCalendar::getDateType(int month, int day) const
{
	return scheduleDays[month - 1][day - 1].getType();
}

//Precondition: month (int), day (int)
//Postcondition: returns the description for the passed in month day
string MyCalendar::getDateDesc(int month, int day) const
{
	return scheduleDays[month - 1][day - 1].getDescription();
}

//Methods:

//Precondition: N/A
//Postcondition: returns the day of the week corresponding to the current date 
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
	case 0:
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

//Precondition: N/A
//Postcondition: Returns true of the current year is a leap year false if not
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

//Precondition: N/A
//Postcondition: Prints out the date in format : "Monday, January 12th, 2023"
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

//Precondition: N/A
//Postconditon: pre-increments the date object by 1
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

//Precondition: int
//Postcondition: post-increments the date object by 1
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

//Precondition: N/A
//Postcondition: pre-decrements the date object by 1
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

//Precondition: int
//Postcondition: post-decrements the date object by 1
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

//Precondition: n (int)
//Postcondition: Jumps forward n number of days 
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

//Precondition: n (int)
//Postcondition: Jumps backwards n number of days
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

//Precondition: color (int)
//Postcondition: Sets the console color to the specified color 
void MyCalendar::setConsoleColor2(int color)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, color);
}