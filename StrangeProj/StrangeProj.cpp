#include "pch.h"
#include "MetaGraph/MetaGraph.h"

int main()
{
	//################ TEST LOGIC AREA ####################
	MetaVertex TestDot("Dot");
	TestDot.addAttribute(5);
	TestDot.addAttribute(6);
	TestDot.addAttribute(0, "SUMM");

	Edge crVertex("AddVertex", createHandler {
		consequens.addVertice(antecedens);
	});

	RuleObject testObj(TestDot, crVertex);

	testObj.runEdge(0);

	//ЗАДАЧИ
	//Реализовать в ребрах алгоритм поиска решения
	//Реализовать циклический его поиск
}