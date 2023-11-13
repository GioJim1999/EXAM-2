#include "MyUnit.h"

//Constructor:
MyUnit::MyUnit()
{
	value = 0;
	strncpy_s(description, "unknown", 90);
}

//Setters:
void MyUnit::setValue(int newValue)
{
	value = static_cast<unsigned short>(newValue);
}

void MyUnit::setDescription(string newDescription)
{
	strncpy_s(description, newDescription.c_str(), 90);
}

//Getters:
int MyUnit::getValue() const
{
	return static_cast<int>(value);
}

string MyUnit::getDescription() const
{
	return string(description);
}

//Operator:
ostream& operator<<(ostream& out, const MyUnit& obj)
{
	out << "\n\tValue: " << obj.getValue();
	out << "\n\tDescription: " << obj.getDescription();

	return out;
}