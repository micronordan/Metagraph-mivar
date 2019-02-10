#include "pch.h"
#include "LogicThread.h"
#include <iostream>


LogicThread::~LogicThread()
{
}

bool LogicThread::findPath()
{
	//git push pi master
	//############# АХТУНГ, нужно добавить приоритет правил, убирание лишних правил с маршрута
	std::vector<attribute_ptr>::iterator iter;
	attribute_list localKnown = Input; //Локально известные переменные логики
	std::vector<int> ruleStatus(Rules.size()); // 0 - неиспользовано, 1 - можно использовать, 2 - использовано
	bool ruleWasUsed;

	do {
		//Проверка переменных из списка существующих
		for (auto i : Output) {
			iter = std::find(localKnown.begin(), localKnown.end(), i);
			if (iter != localKnown.end()) {
				if (i == Output.back()) {
					pathStatus = 2;
					return true;
				}
				continue;
			}
			break;
		}
		ruleWasUsed = 0;

		//Помечаем все правила, которые можно использовать
		for (int i = 0; i < Rules.size(); i++) {
			//Только правила со статусом 0 нужно проверить
			if (!ruleStatus[i])
				for (auto j : Rules[i]->getInputs()) {
					iter = std::find(localKnown.begin(), localKnown.end(), j);
					if (iter != localKnown.end()) {
						if (j == Rules[i]->getInputs().back())
							ruleStatus[i] = 1;
					}
					else break; //Необходимо, чтобы все элементы правила была известны
				}
		}

		//Притворяемся, что использовали правило
		//TODO придумать приоритет правил
		for (int i = 0; i < Rules.size(); i++) {
			if (ruleStatus[i] == 1) {
				for (auto j : Rules[i]->getOutputs()) {
					iter = std::find(localKnown.begin(), localKnown.end(), j);
					if (iter == localKnown.end()) {
						//Вся котовасия имеет смысл, только если было добавлено новое известное значение
						ruleWasUsed = 1;
						path.push_back(i);
						localKnown.push_back(j);
					}
				}
				ruleStatus[i] = 2;
			}
		}
	} while (ruleWasUsed);

	pathStatus = 1;
	return false;
}

bool LogicThread::runSequence()
{
	if (!pathStatus) findPath();
	if (pathStatus == 2) {
		for (auto i : path)
			Rules[i]->Run();
		pathStatus = 3;
		return true;
	}
	//Невозможно исполнить правило(не хватает параметров)
	return false;
}

bool LogicThread::searchNewRules(std::vector<Rule*>& Rules, attribute_list & Input, attribute_list & Output)
{
	
	std::vector < std::vector<std::vector<attribute_list>>> tempRuleList;
	for (auto i : Rules) {
		attribute_list tempList;
		//Находим все возможные переменные, которые могут входить в правило
		for (auto j : Output)
			if (std::find(i->getOutputs().begin(), i->getOutputs().end(), j) != i->getOutputs().end()
				|| std::find(i->getInputs().begin(), i->getInputs().end(), j) != i->getInputs().end())
				tempList.push_back(j);

		if (!tempList.empty()) {
			//Если правило сможет, правило вернёт лучший вариант, либо несколько лучших вариантов
			auto& temp = i->findRuleHandler(tempList);
			if (!temp.empty()) tempRuleList.push_back(temp);
		}
	}

	if (!tempRuleList.empty()) {
		
	}
	return false;
}



