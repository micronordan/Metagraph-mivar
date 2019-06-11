#pragma once
#include "MetaGraph.h"

//����� ��������� ���������� � ������������, � �� new � �� ���������
//��� ����� ����� �������� RunEdge, � ��� ����� ����� ����������� �������� �����

MetaEdge createVertex("CreateVertex", createMetaHandler{
	//�� ���� ������ �������, ��� ����� ������� ����� �������
	//������� ����� �������
	antecedens.addVertice(new MetaVertex("tempVertice"));
});

MetaEdge findRules("SearchSolution", createMetaHandler{
	//�� ���� �������� � RuleObject
	//�� ����� ���������, ������� ���������� �����
	//������� ������� ������
	consequens.addVertice(antecedens);
for (auto i : antecedens.getVertices())
	for (auto j : consequens.getLogicVector()) {
			//��������� ������ �������
			antecedens.getMetaVertices().back()->getLogicVector().push_back(
				std::make_pair(std::make_pair(j.first.first, j.first.second), j.second));
			//���� �������� �������
			if (!j.second->getIsEO())
				antecedens.getMetaVertices().back()->getLogicVector().push_back(
					std::make_pair(std::make_pair(j.first.second, j.first.first), j.second->));
		}

	}, createVertex);

MetaEdge searchTableSolution("SearchTableSolution", createMetaHandler{
	//�� ���� �������� � �������� ������
	//�� ����� ���������, ������� ���������� �����
	//������� �������� � ������������������� ��������
	consequens.addVertice(antecedens);
	}, createVertex);

std::vector<MetaEdge*> preList = { &findRules, &searchTableSolution };
MetaEdge searchSolution("SearchSolution", createMetaHandler{
	//�� ���� �������� � RuleObject
	//�� ����� ���������, ������� ���������� �����
	//������� �������� � ������������������� ��������
	consequens.addVertice(antecedens);
	}, preList);

//������
//����������� � ������ �������� ������ �������
//����������� ����������� ��� �����