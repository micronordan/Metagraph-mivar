#include "pch.h"
#include "LogicThread.h"
#include <iostream>


LogicThread::~LogicThread()
{
}

bool LogicThread::findPath()
{
	//git push pi master
	//############# ������, ����� �������� ��������� ������, �������� ������ ������ � ��������
	std::vector<attribute_ptr>::iterator iter;
	attribute_list localKnown = Input; //�������� ��������� ���������� ������
	std::vector<int> ruleStatus(Rules.size()); // 0 - ��������������, 1 - ����� ������������, 2 - ������������
	bool ruleWasUsed;

	do {
		//�������� ���������� �� ������ ������������
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

		//�������� ��� �������, ������� ����� ������������
		for (int i = 0; i < Rules.size(); i++) {
			//������ ������� �� �������� 0 ����� ���������
			if (!ruleStatus[i])
				for (auto j : Rules[i]->getInputs()) {
					iter = std::find(localKnown.begin(), localKnown.end(), j);
					if (iter != localKnown.end()) {
						if (j == Rules[i]->getInputs().back())
							ruleStatus[i] = 1;
					}
					else break; //����������, ����� ��� �������� ������� ���� ��������
				}
		}

		//������������, ��� ������������ �������
		//TODO ��������� ��������� ������
		for (int i = 0; i < Rules.size(); i++) {
			if (ruleStatus[i] == 1) {
				for (auto j : Rules[i]->getOutputs()) {
					iter = std::find(localKnown.begin(), localKnown.end(), j);
					if (iter == localKnown.end()) {
						//��� ��������� ����� �����, ������ ���� ���� ��������� ����� ��������� ��������
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
	//���������� ��������� �������(�� ������� ����������)
	return false;
}


