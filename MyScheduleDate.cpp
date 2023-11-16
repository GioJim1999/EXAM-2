#include "MyScheduleDate.h"

//Constructor:
MyScheduleDate::MyScheduleDate()
{
	type = 'U';
}

//Setters:
void MyScheduleDate::setType(char newType)
{
	type = newType;
}


//Getters:
char MyScheduleDate::getType() const
{
	return type;
}

//Operator:
ostream& operator<<(ostream& out, const MyScheduleDate& obj)
{
	out << "\n\tDescription: " << obj.getDescription();
	out << "\n\tType: " << obj.getType();

	return out;
}