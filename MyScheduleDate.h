#pragma once
#include "MyUnit.h"
class MyScheduleDate : public MyUnit
{
private:
	char type;

public:
	//Constructor:
	MyScheduleDate();

	//Setters:
	void setType(char newType);

	//Getters:
	char getType() const;

	friend ostream& operator<<(ostream& out, const MyScheduleDate& obj);
};

