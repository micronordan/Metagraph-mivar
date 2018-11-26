/*
����� ���������� ���������� ������������ �������. 
���������, ����� ��� ������� ��������� ����� ��� ���.
����� ������� ������ ������ ��������� *basicObj
*/
#ifndef __INCLUDE__BASICOBJ__
#define __INCLUDE__BASICOBJ__
#pragma once
#include <string>

class basicObj 
{
public:
	basicObj(const std::string& name)
		: name(name) {}

	std::string getName() { return name; }
	void changeName(std::string newName) { name = newName; }

	basicObj& operator=(const basicObj& from) {
		if (this == &from) {
			return *this;
		}

		name = from.name;
		return *this;
	}
private:
	std::string name;
};


#endif