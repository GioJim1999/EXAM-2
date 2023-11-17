#include "MyUnit.h"

//Constructor:
MyUnit::MyUnit()
{
	value = 0;
	strncpy_s(description, "unknown", 90);
}

//Setters:

//Precondition: newValue (int)
//Postcondition: sets the value to newValue
void MyUnit::setValue(int newValue)
{
	value = static_cast<unsigned short>(newValue);
}

//Precondition: newDescritpion (string)
//Postcondition: sets the description to newDescription
void MyUnit::setDescription(string newDescription)
{
	strncpy_s(description, newDescription.c_str(), 90);
}

//Getters:

//Precondition: N/A
//Postcondition: returns the value
int MyUnit::getValue() const
{
	return static_cast<int>(value);
}

//Precondition: N/A
//Postcondition: returns the description
string MyUnit::getDescription() const
{
	return string(description);
}

//Operators:
ostream& operator<<(ostream& out, const MyUnit& obj)
{
	out << "\n\tValue: " << obj.getValue();
	out << "\n\tDescription: " << obj.getDescription();

	return out;
}