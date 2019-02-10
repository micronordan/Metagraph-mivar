#include "pch.h"
#include "Rule.h"

//Вектор векторов листа аттрибутов нужен, ибо для каждого правило обычно требуется не один входной аттрибут
// а несколько. Затем для одного и того же случая может быть несколько вариантов. И случаем может быть несколько
// По правилу, в начале каждого случая посылается Output комбинация, а затем Input
std::vector<std::vector<attribute_list>>& Rule::findRuleHandler(attribute_list & Outputs)
{
	for (auto i : Outputs) {
		//Проверяем наличие этой переменной (чисто в теории)
		auto iter1 = std::find(inputRuleAttributes.begin(), inputRuleAttributes.end(), i);
		auto iter2 = std::find(outputRuleAttributes.begin(), outputRuleAttributes.end(), i);

		if (iter1 == inputRuleAttributes.end() && iter2 == outputRuleAttributes.end()) {
			std::vector<std::vector<attribute_list>> temp;
			return temp;
		}
			
	}

	//Если всё ок, отправляем все на выход
	//По умолчанию предпологаем, что необходимы все переменные
	attribute_list answerList;
	for (auto i : inputRuleAttributes)
		for (auto j : Outputs)
			if (i != j) answerList.push_back(i);

	for (auto i : outputRuleAttributes)
		for (auto j : Outputs)
			if (i != j) answerList.push_back(i);

	std::vector<std::vector<attribute_list>> AllVar;

	std::vector<attribute_list> answer;
	answer.push_back(Outputs);
	answer.push_back(answerList);

	AllVar.push_back(answer);

	return AllVar;
}
