#pragma once
#include<string>
#include<iostream>
using namespace std;
class MyUnit
{
private:
	unsigned short value;
	char description[100];

public:
	//Constructor: 
	MyUnit();

	//Setters:
	void setValue(int newValue);
	void setDescription(string newDescription);

	//Getters:
	int getValue() const;
	string getDescription() const;

	friend ostream& operator<<(ostream& out, const MyUnit& obj);
};

