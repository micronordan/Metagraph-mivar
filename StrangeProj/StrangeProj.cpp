#include "pch.h"
#include "MetaGraph/MetaGraph.h"

int main()
{
	MetaGraph mainMetaGraph;

	//################ TEST LOGIC AREA ####################
	Vertex TestDotA("Dot");
	TestDotA.addAttribute(5, "X");
	TestDotA.addAttribute(1, "Y");
	TestDotA.addAttribute(0, "Z");

	Vertex TestDotB("Dot");
	TestDotB.addAttribute(1, "X");
	TestDotB.addAttribute(3, "Y");
	TestDotB.addAttribute(4, "Z");

	Vertex TestDotC = TestDotA;

	MetaVertex TestVector("SuperDot");
	TestVector.addVertice(TestDotA);
	TestVector.addVertice(TestDotB);
	TestVector.addAttribute(0, "Length");

	MetaVertex TestVector2("SuperDot");
	TestVector2.addVertice(TestDotA);
	TestVector2.addVertice(TestDotB);
	TestVector2.addVertice(TestVector);
	TestVector2.addAttribute(0, "Length");

	Edge minus("minusDot", createHandler{
		for (size_t i = 0; i < consequens.length(); i++) {
			consequens[i] = (int)consequens[i] - (int)antecedens[i];
			}
	});

	MetaEdge crVertex("AddVertex", createMetaHandler{
		consequens.addVertice(antecedens);
	});

	//Добавить в MetaVertex копирование connection
	//Связь метавершин в другой метавершине добовляет их в эту метавершину

	TestVector.addEdge(TestDotA, TestDotB, minus);
	TestVector.addEdge(TestVector2, crVertex);
	mainMetaGraph.pushElement(TestVector);

	Run(TestVector, 1);
}