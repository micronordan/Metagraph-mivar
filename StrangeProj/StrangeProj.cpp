#include "pch.h"
#include "MetaGraph/MetaGraphLib.h"

int main()
{

	//################ TEST LOGIC AREA ####################
	Vertex TestDot("Dot");
	TestDot.addAttribute(5);
	TestDot.addAttribute(0, "SUMM");
	MetaVertex TestDot2("SuperDot");
	TestDot2.addVertice(TestDot);
	TestDot2.addAttribute(0);
	MetaVertex TestDot3("MegaDot");
	TestDot2.addVertice(TestDot);
	TestDot2.addAttribute(0);

	Edge crVertex("AddVertex", createHandler {
		consequens.addVertice(antecedens);
	});

	RuleObject testObj(TestDot3, TestDot2, crVertex);
	testObj.addEdge(TestDot2, searchSolution);
	testObj.runEdge();


	MetaGraph Test;
	Test.pushElement(TestDot);
	Test.pushElement(TestDot2);
	Test.pushElement(TestDot3);
	Test.pushElement(crVertex);
	Test.pushElement(searchSolution);
	Test.pushElement(testObj);
}