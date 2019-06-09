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

	Vertex TestDotB = TestDotA;
	Vertex TestDotC = TestDotA;

	MetaVertex TestVector("SuperDot");
	TestVector.addVertice(TestDotA);
	TestVector.addVertice(TestDotB);
	TestVector.addAttribute(0, "Length");


	MetaVertex MegaMetaVertex("MegaDot");
	MegaMetaVertex.addVertice(TestVector);
	MegaMetaVertex.addVertice(TestDotC);
	MegaMetaVertex.addAttribute(0, "smCounter");


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
	TestVector.addEdge(TestVector, crVertex);
	MegaMetaVertex.addEdge(TestVector, TestDotC, minus);

	MetaVertex miniWorld = MegaMetaVertex;

	mainMetaGraph.pushElement(TestVector);

	Run(TestVector, 1);
}