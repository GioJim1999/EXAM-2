#include<iostream>
#include"MyUnit.h"
#include"MyCalendar.h"
#include<ctime>
#include"input.h"
#include<fstream>
#include<Windows.h>
#include<iomanip>
using namespace std;

//Function prototypes:
void displayMainMenu(const MyCalendar& date);
char menuOptions();
int editDateMenu(string option);
void setYear(MyCalendar& currentDate);
void setMonth(MyCalendar& currentDate);
void setDay(MyCalendar& currentDate);
void setCurrentCalendar(MyCalendar& currentDate);
int setCalendarMenu();
void setSchedule(MyCalendar& currentDate);
void saveDateToFile(MyCalendar& currentDate);
void setConsoleColor(int color);
MyCalendar readDateFromFile(MyCalendar& currentDate);

enum Colors { blue = 9, green = 10, white = 15, red = 4 };
string awareness[12] = {
	"Thyroid",
	"Heart Failure",
	"Multiple Sclerosis",
	"Oral Cancer",
	"Mental Health",
	"Migrane and Headache",
	"Juvenile Arthrisis",
	"Immunization",
	"Ovarian Cancer",
	"Breast Cancer",
	"Lung Cancer",
	"HIV Aids"
};


//Precondtion: number (long long int)
//Postcondition: Returns a string with the passed in integer in word foramt.
string numberToWords(long long int n);

//Precondition: N/A
//Postcondtion: returns a new MyCalendar object using the system's current time as the arguements.
MyCalendar getSystemDate();


//TODO: WRITE CODE COMMENTS FOR FUNCTIONS (PRECONDITION: POSTCONDITION:)
//MAYBE ADD CALENDAR? (big if) leaning towards nah
int main()
{
	MyCalendar date;
	date = getSystemDate();
	do
	{
		displayMainMenu(date);

		switch (menuOptions())
		{
		case 'X': 
			exit(1); break;
		case 'A':
			setYear(date); break;
		case 'B':
			setMonth(date); break;
		case 'C':
			setDay(date); break;
		case 'D':
			setCurrentCalendar(date); break;
		case 'E':
			setSchedule(date); break;
		case 'F':
			date = getSystemDate(); break;
		case 'G':
			saveDateToFile(date); break;
		case 'H':
			readDateFromFile(date); break;
		default:
			cout << "\n\tInvalid option please enter (A,B,C,D,E,F,G,H or X)...\n";
			system("pause");
			break;
		}
	} while (true);

	return EXIT_SUCCESS;
}

void displayMainMenu(const MyCalendar& date)
{
	setConsoleColor(white);
	system("cls");
	cout << "\n\tCurrent Year: ";
	setConsoleColor(blue);
	cout << setw(8) << date.getCurrentYear() << " - " << numberToWords(date.getCurrentYear());
	date.isLeapYear() ? cout << "(leap)" : cout << "(non-leap)"; 
	setConsoleColor(white);
	cout << "\n\t";
	cout << string(100, 196);
	cout << "\n\tCurrent Month:	";
	setConsoleColor(blue);
	cout << setw(4) << date.getCurrentMonth() << " - " << date.getMonthName();
	setConsoleColor(white);
	cout << "\n\tAwareness: ";
	setConsoleColor(blue);
	cout << setw(18) << awareness[date.getCurrentMonth() - 1] << " Month";
	setConsoleColor(white);
	cout << "\n\t";
	cout << string(100, 196);
	cout << "\n\tCurrent Day: ";
	setConsoleColor(blue);
	cout << setw(7) << date.getCurrentDay() << date.addDaySuffix() << " - " << date.getDayofWeek();
	setConsoleColor(white);
	cout << "\n\t\t\t  : ";
	if (date.getDateType(date.getCurrentMonth(), date.getCurrentDay()) == 'U')
		setConsoleColor(white);
	else
	{
		switch (date.getDateType(date.getCurrentMonth(), date.getCurrentDay()))
		{
		case 'H':
			setConsoleColor(BACKGROUND_GREEN);
			break;
		case 'P':
			setConsoleColor(BACKGROUND_RED);
			break;
		}
	}
	cout << date.getDateDesc(date.getCurrentMonth(), date.getCurrentDay());
	setConsoleColor(white);
	cout << "\n\t";
	cout << string(100, 196);
	cout << "\n";
	cout << "\n\tCMPR 121 Exam2: MyCalendar - OOP implementations by Giovanni Jimenez (11-16-2023)";
}

char menuOptions()
{
	cout << "\n\t" << string(100, 205);
	cout << "\n\tA. Setting Current Year";
	cout << "\n\tB. Setting Current Month";
	cout << "\n\tC. Setting Current Day";
	cout << "\n\tD. Setting Current Calendar";
	cout << "\n\tE. Schedule and Report Dates";
	cout << "\n\t" << string(100, 196);
	cout << "\n\tF. Sync to system's date";
	cout << "\n\tG. Save calendar to file";
	cout << "\n\tH. Restore calendar from file";
	cout << "\n\t" << string(100, 196);
	cout << "\n\tX. Exit";
	cout << "\n\t" << string(100, 205);

	return inputChar("\n\tOption: ");
}

MyCalendar getSystemDate()
{
	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);
	int month = 1 + newtime.tm_mon;
	int day = newtime.tm_mday;
	int year = 1900 + newtime.tm_year;

	MyCalendar systemDate(month, day, year);
	return systemDate;
}

int editDateMenu(string option)
{
	cout << "\n\tCalendar - Current " + option + " Menu";
	cout << "\n\t";
	cout << string(100, '=');
	cout << "\n\t1. Set Current " + option;
	cout << "\n\t";
	cout << string(100, '_');
	cout << "\n\t0. Return";
	cout << "\n\t";
	cout << string(100, '=');

	return inputInteger("\n\tOption: ", 0, 1);
}

void setYear(MyCalendar& currentDate)
{
	do
	{
		system("cls");
		cout << "\n\tCurrent Year: " << currentDate.getCurrentYear() << " - " << numberToWords(currentDate.getCurrentYear());
		cout << "\n";
		switch (editDateMenu("Year"))
		{
		case 1:
			currentDate.setCurrentYear(inputInteger("\n\tEnter a year (1....9999): ", 1, 9999)); break;
		case 0:
			return; break;
		}
	} while (true);

	system("pause");
}

void setMonth(MyCalendar& currentDate)
{
	do
	{
		system("cls");
		cout << "\n\tCurrent Month: " << currentDate.getCurrentMonth() << " - " << currentDate.getMonthName();
		cout << "\n";
		switch (editDateMenu("Month"))
		{
		case 1:
			currentDate.setCurrentMonth(inputInteger("\n\tEnter a month (1....12): ", 1, 12)); break;
		case 0:
			return; break;
		}
	} while (true);

	system("pause");
}

void setDay(MyCalendar& currentDate)
{
	int maxDays = 31;
	int month = currentDate.getCurrentMonth();

	if (currentDate.isLeapYear() && month == 2)
	{
		maxDays = 29;
	}
	else
	{
		if (month == 2)
			maxDays = 28;
		else if (month == 4 || month == 6 || month == 9 || month == 11)
			maxDays = 30;
	}

	do
	{
		system("cls");
		cout << "\n\tCurrent Day: " << currentDate.getCurrentDay() << currentDate.addDaySuffix();
		cout << "\n";
		switch (editDateMenu("Day"))
		{
		case 1:
			currentDate.setCurrentDay(inputInteger("\n\tEnter a day (1...." + to_string(maxDays) + "): ", 1, maxDays)); break;
		case 0:
			return; break;
		}
	} while (true);

	system("pause");
}

string numberToWords(long long int n)
{
	long long int limit = 1000000000000, curr_hun, t = 0;

	// If zero return zero
	if (n == 0)
		return ("Zero");

	// Array to store the powers of 10
	string multiplier[] = { "", "Trillion", "Billion",
							"Million", "Thousand" };

	// Array to store numbers till 20
	string first_twenty[] = {
		"",        "One",       "Two",      "Three",
		"Four",    "Five",      "Six",      "Seven",
		"Eight",   "Nine",      "Ten",      "Eleven",
		"Twelve",  "Thirteen",  "Fourteen", "Fifteen",
		"Sixteen", "Seventeen", "Eighteen", "Nineteen"
	};

	// Array to store multiples of ten
	string tens[]
		= { "",      "Twenty",  "Thirty", "Forty", "Fifty",
			"Sixty", "Seventy", "Eighty", "Ninety" };

	// If number is less than 20, return without any further
	// computation
	if (n < 20)
		return (first_twenty[n]);

	// Answer variable to store the conversion
	string answer = "";
	for (long long int i = n; i > 0;
		i %= limit, limit /= 1000) {

		// Store the value in multiplier[t], i.e n =
		// 1000000, then r = 1, for multiplier(million), 0
		// for multipliers(trillion and billion)
		curr_hun = i / limit;

		// It might be possible that the current multiplier
		// is bigger than your number
		while (curr_hun == 0) {

			// Set i as the remainder obtained when n was
			// divided by the limit
			i %= limit;

			// Divide the limit by 1000, shifts the
			// multiplier
			limit /= 1000;

			// Get the current value in hundreds, as
			// English system works in hundreds
			curr_hun = i / limit;

			// Shift the multiplier
			++t;
		}

		// If current hundred is greater than 99, Add the
		// hundreds' place
		if (curr_hun > 99)
			answer += (first_twenty[curr_hun / 100]
				+ " Hundred ");

		// Bring the current hundred to tens
		curr_hun = curr_hun % 100;

		// If the value in tens belongs to [1,19], add using
		// the first_twenty

		if (curr_hun > 0 && curr_hun < 20)
			answer += (first_twenty[curr_hun] + " ");

		// If curr_hun is now a multiple of 10, but not 0
		// Add the tens' value using the tens array
		else if (curr_hun % 10 == 0 && curr_hun != 0)
			answer += (tens[curr_hun / 10 - 1] + " ");

		// If the value belongs to [21,99], excluding the
		// multiples of 10 Get the ten's place and one's
		// place, and print using the first_twenty array

		else if (curr_hun > 20 && curr_hun < 100)
			answer += (tens[curr_hun / 10 - 1] + " "
				+ first_twenty[curr_hun % 10] + " ");

		// If Multiplier has not become less than 1000,
		// shift it
		if (t < 4)
			answer += (multiplier[++t] + " ");
	}
	return (answer);
}

void setCurrentCalendar(MyCalendar& currentDate)
{
	do
	{
		system("cls");
		cout << "\n\t" << currentDate.printDateFormat2() << "\n\t" << currentDate;
		cout << "\n";
		cout << "\n\t";
		cout << string(100, '=');
		switch (setCalendarMenu())
		{
		case 0:
			return; break;
		case 1:
			++currentDate;
			cout << "\n\tPre-increment:(++)";
			cout << "\n\t" << currentDate.printDateFormat2();
			cout << "\n\t" << currentDate << "\n";
			break;
		case 2:
			cout << "\n\tPost-increment:(++)";
			cout << "\n\t" << currentDate.printDateFormat2();
			cout << "\n\t" << currentDate << "\n";
			currentDate++; 
			break;
		case 3:
			currentDate = currentDate.jumpForward(inputInteger("\n\tEnter an integer (n): ", true)); break;
		case -1:
			--currentDate;
			cout << "\n\tPre-decrement:(--)";
			cout << "\n\t" << currentDate.printDateFormat2();
			cout << "\n\t" << currentDate << "\n";
			break;
		case -2:
			cout << "\n\tPost-decrement:(--)";
			cout << "\n\t" << currentDate.printDateFormat2();
			cout << "\n\t" << currentDate << "\n";
			currentDate--;
			break;
		case -3:
			currentDate = currentDate.jumpBackward(inputInteger("\n\tEnter an integer (n): ", true)); break;
		}

		cout << "\n";
		system("pause");
	} while (true);


}

int setCalendarMenu()
{
	cout << "\n\tMy Calendar Menu";
	cout << "\n\t1. ++ (pre-increment)";
	cout << "\n\t2. ++ (post-increment)";
	cout << "\n\t3. jump forward (+n)";
	cout << "\n\t";
	cout << string(100, '-');
	cout << "\n\t-1. -- (pre-decrement)";
	cout << "\n\t-2. -- (post-decrement)";
	cout << "\n\t-3. jump backward (-n)";
	cout << "\n\t";
	cout << string(100, '-');
	cout << "\n\t0. Return";
	cout << "\n\t";
	cout << string(100, '=');
	return inputInteger("\n\tOption: ", -3, 3);
}

void setSchedule(MyCalendar& currentDate)
{
	int scheduleMonth, scheduleDay;
	char scheduleType;
	string scheduleDesc;
	do
	{
		system("cls");
		cout << "\n\tMonth		 :" << currentDate.getMonthName();
		cout << "\n\tDay		 :" << currentDate.getCurrentDay();
		cout << "\n\tType		 :" << currentDate.getDateType(currentDate.getCurrentMonth(), currentDate.getCurrentDay());
		cout << "\n\tDescription	 :" << currentDate.getDateDesc(currentDate.getCurrentMonth(), currentDate.getCurrentDay());
		cout << "\n";
		cout << "\n\tScheduling Date: ";
		cout << "\n\t";
		cout << string(100, '=');
		cout << "\n\t1. Schedule a date";
		cout << "\n\t2. Unschedule a date";
		cout << "\n\t";
		cout << string(100, '-');
		cout << "\n\t3. Display year schedules";
		cout << "\n\t4. Display month schedules";
		cout << "\n\t5. Display day schedule";
		cout << "\n\t0. Return";
		cout << "\n\t";
		cout << string(100, '=');

		switch (inputInteger("\n\tOption: ", 0, 5))
		{
		case 0:
			return; break;
		case 1:
			scheduleMonth = inputInteger("\n\tEnter a month (1...12): ", 1, 12);
			scheduleDay = inputInteger("\n\tEnter a day (1...31): ",1,31);
			scheduleDesc = inputString("\n\tDescription: ", true);
			scheduleType = inputChar("\n\tWhat type of schedule: (R (return no schedule), A (Awareness), H (Holiday), P (Personal):  ");
			if (scheduleType == 'R')
			{
				cout << "\n\tDate has NOT been scheduled!";
				system("pause");
				break;
			}
			else
			{
				currentDate.setScheduleDate(scheduleType, scheduleDesc, scheduleMonth, scheduleDay);
				currentDate.setCurrentMonth(scheduleMonth);
				currentDate.setCurrentDay(scheduleDay);
				cout << "\n\tDate has been scheduled!\n";
				system("pause");
				break;
			}
		case 2:
			scheduleMonth = inputInteger("\n\tEnter a month (1...12): ", 1, 12);
			scheduleDay = inputInteger("\n\tEnter a day (1...31): ");
			currentDate.setScheduleDate('U', "uschedule",scheduleMonth,scheduleDay);
			cout << "\n\tDate has been unscheduled!\n";
			system("pause");
			break;
		case 3:
			currentDate.displayScheduledDays();
			system("pause");
			break;
		case 4:
			currentDate.displayScheduledDaysMonth(inputInteger("\n\tEnter a month to display (1...12): ", 1,12));
			system("pause");
			break;
		case 5:
			currentDate.displayScheduledDay(inputInteger("\n\tEnter a day (1...31): ",1,31), inputInteger("\n\tEnter a month (1...12): ",1,12));
			system("pause");
			break;
		}
	} while (true);



	system("pause");
}

void saveDateToFile(MyCalendar& currentDate)
{
	string fileName = to_string(currentDate.getCurrentYear());
	fileName += ".dat";

	fstream file;
	file.open(fileName, ios::out | ios::binary);

	file.write(reinterpret_cast<char*>(&currentDate), sizeof(currentDate));

	file.close();
	cout << "\n\tFile: " + fileName + " has been written to current program directory\n";
	system("pause");
}

MyCalendar readDateFromFile(MyCalendar& currentDate)
{
	string fileName = inputString("\n\tEnter a file to read: ", false);
	fstream file;
	file.open(fileName, ios::in | ios::binary);

	if (!file)
	{
		cout << "\n\tERROR: could not read file check spelling!\n";
		system("pause");
		return currentDate;
	}
	else
	{
		file.read(reinterpret_cast<char*>(&currentDate),sizeof(currentDate));
		return currentDate;
	}
}

void setConsoleColor(int color)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, color);
}