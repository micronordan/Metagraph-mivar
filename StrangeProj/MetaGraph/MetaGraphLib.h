#pragma once
#include "MetaGraph/MetaGraph.h"

//����� ��������� ���������� � ������������, � �� new � �� ���������
//��� ����� ����� �������� RunEdge, � ��� ����� ����� ����������� �������� �����

Edge createVertex("CreateVertex", createHandler{
	//�� ���� ������ �������, ��� ����� ������� ����� �������
	//������� ����� �������
	consequens.addVertice(new MetaVertex("Test"));
	});

Edge findRules("SearchSolution", createHandler{
	//�� ���� �������� � RuleObject
	//�� ����� ���������, ������� ���������� �����
	//������� ������� ������
	consequens.addVertice(antecedens);
	}, createVertex);

Edge searchTableSolution("SearchTableSolution", createHandler{
	//�� ���� �������� � �������� ������
	//�� ����� ���������, ������� ���������� �����
	//������� �������� � ������������������� ��������
	consequens.addVertice(antecedens);
	}, createVertex);

vector<Edge*> preList = { &findRules, &searchTableSolution };
Edge searchSolution("SearchSolution", createHandler{
	//�� ���� �������� � RuleObject
	//�� ����� ���������, ������� ���������� �����
	//������� �������� � ������������������� ��������
	consequens.addVertice(antecedens);
	}, preList);

//������
//����������� � ������ �������� ������ �������
//����������� ����������� ��� �����