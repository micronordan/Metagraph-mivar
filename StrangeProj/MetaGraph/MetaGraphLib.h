#pragma once
#include "MetaGraph/MetaGraph.h"

//Нужно нормально поработать с контейнерами, а не new и их удалением
//Для этого нужно изменить RunEdge, а для этого нужно проработать атрибуты ребер

Edge createVertex("CreateVertex", createHandler{
	//На вход подать вершину, где будет создана новая вершина
	//Создает новую вернину
	consequens.addVertice(new MetaVertex("Test"));
	});

Edge findRules("SearchSolution", createHandler{
	//На вход метаграф с RuleObject
	//На выход метаграфы, которые необходимо найти
	//Создает таблицу правил
	consequens.addVertice(antecedens);
	}, createVertex);

Edge searchTableSolution("SearchTableSolution", createHandler{
	//На вход метаграф с таблицей правил
	//На выход метаграфы, которые необходимо найти
	//Создает метаграф с последовательностью действий
	consequens.addVertice(antecedens);
	}, createVertex);

vector<Edge*> preList = { &findRules, &searchTableSolution };
Edge searchSolution("SearchSolution", createHandler{
	//На вход метаграф с RuleObject
	//На выход метаграфы, которые необходимо найти
	//Создает метаграф с последовательностью действий
	consequens.addVertice(antecedens);
	}, preList);

//ЗАДАЧИ
//Реализовать в ребрах алгоритм поиска решения
//Реализовать циклический его поиск