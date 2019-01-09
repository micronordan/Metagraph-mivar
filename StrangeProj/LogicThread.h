
#include "MetaGraph/Rule.h"
#include <vector>
#pragma once

class LogicThread
{
public:
	LogicThread(std::vector<Rule *>& Rules, attribute_list& Input, attribute_list& Output) : Rules(Rules), Input(Input), Output(Output) {}

	~LogicThread();
	bool findPath();
	bool runSequence();

	int getPathStatus() { return pathStatus; }

private:
	std::vector<Rule *>& Rules;
	attribute_list& Input;
	attribute_list& Output;

	std::vector<int> path; //’ранитс€ последовательность команд
	int pathStatus = 0; //0 - неиспользовано; 1 - использовано, неудачно; 2 - использовано, удачно, 3 - последовательность исполнена
};

