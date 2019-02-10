#include "pch.h"
#include "Rule.h"

//������ �������� ����� ���������� �����, ��� ��� ������� ������� ������ ��������� �� ���� ������� ��������
// � ���������. ����� ��� ������ � ���� �� ������ ����� ���� ��������� ���������. � ������� ����� ���� ���������
// �� �������, � ������ ������� ������ ���������� Output ����������, � ����� Input
std::vector<std::vector<attribute_list>>& Rule::findRuleHandler(attribute_list & Outputs)
{
	for (auto i : Outputs) {
		//��������� ������� ���� ���������� (����� � ������)
		auto iter1 = std::find(inputRuleAttributes.begin(), inputRuleAttributes.end(), i);
		auto iter2 = std::find(outputRuleAttributes.begin(), outputRuleAttributes.end(), i);

		if (iter1 == inputRuleAttributes.end() && iter2 == outputRuleAttributes.end()) {
			std::vector<std::vector<attribute_list>> temp;
			return temp;
		}
			
	}

	//���� �� ��, ���������� ��� �� �����
	//�� ��������� ������������, ��� ���������� ��� ����������
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
