#include "MyScheduleDate.h"

//Constructor:
MyScheduleDate::MyScheduleDate()
{
	type = 'U';
}

//Setters:

//Precondition: newType (char)
//Postcondition: sets the type to newType 
void MyScheduleDate::setType(char newType)
{
	type = newType;
}

//Getters:

//Precondition: N/A
//Postcondition: returns the type
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