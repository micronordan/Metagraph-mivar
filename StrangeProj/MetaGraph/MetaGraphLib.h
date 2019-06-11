#pragma once
#include "MetaGraph.h"

//Нужно нормально поработать с контейнерами, а не new и их удалением
//Для этого нужно изменить RunEdge, а для этого нужно проработать атрибуты ребер

MetaEdge createVertex("CreateVertex", createMetaHandler{
	//На вход подать вершину, где будет создана новая вершина
	//Создает новую вернину
	antecedens.addVertice(new MetaVertex("tempVertice"));
});

MetaEdge findRules("SearchSolution", createMetaHandler{
	//На вход метаграф с RuleObject
	//На выход метаграфы, которые необходимо найти
	//Создает таблицу правил
	consequens.addVertice(antecedens);
for (auto i : antecedens.getVertices())
	for (auto j : consequens.getLogicVector()) {
			//Добавляем прямое правило
			antecedens.getMetaVertices().back()->getLogicVector().push_back(
				std::make_pair(std::make_pair(j.first.first, j.first.second), j.second));
			//Ищем обратное правило
			if (!j.second->getIsEO())
				antecedens.getMetaVertices().back()->getLogicVector().push_back(
					std::make_pair(std::make_pair(j.first.second, j.first.first), j.second->));
		}

	}, createVertex);

MetaEdge searchTableSolution("SearchTableSolution", createMetaHandler{
	//На вход метаграф с таблицей правил
	//На выход метаграфы, которые необходимо найти
	//Создает метаграф с последовательностью действий
	consequens.addVertice(antecedens);
	}, createVertex);

std::vector<MetaEdge*> preList = { &findRules, &searchTableSolution };
MetaEdge searchSolution("SearchSolution", createMetaHandler{
	//На вход метаграф с RuleObject
	//На выход метаграфы, которые необходимо найти
	//Создает метаграф с последовательностью действий
	consequens.addVertice(antecedens);
	}, preList);

//ЗАДАЧИ
//Реализовать в ребрах алгоритм поиска решения
//Реализовать циклический его поиск