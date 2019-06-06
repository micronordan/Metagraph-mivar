#include "pch.h"
#include "MetaGraph/MetaGraph.h"

int main()
{

	//################ TEST LOGIC AREA ####################
	Vertex TestDotA("Dot");
	TestDotA.addAttribute(5, "X");
	TestDotA.addAttribute(1, "Y");
	TestDotA.addAttribute(0, "Z");

	//Перегрузить оператор копирования для Vertex
	Vertex TestDotB("Dot");
	TestDotB.addAttribute(1, "X");
	TestDotB.addAttribute(3, "Y");
	TestDotB.addAttribute(4, "Z");

	MetaVertex TestVector("SuperDot");
	TestVector.addVertice(TestDotA);
	TestVector.addVertice(TestDotB);
	TestVector.addAttribute(0, "Length");

	MetaVertex TestVector2("SuperDot");
	TestVector2.addVertice(TestDotA);
	TestVector2.addVertice(TestDotB);
	TestVector2.addAttribute(0, "Length");

	Edge minus("minusDot", createHandler{
		for (size_t i = 0; i < consequens.length(); i++) {
			consequens[i] = (int)consequens[i] - (int)antecedens[i];
			}
	});

	MetaEdge crVertex("AddVertex", createMetaHandler{
		consequens.addVertice(antecedens);
	});


	//Внимание, вызовы ф-ций должны начинаться в оболочке метаграфа!!!!
	//Чтобы сделать выбор между createHandler и createMetaHandler
	//Значит необходимо передвинуть цепочку вызовов в оболочку -> сделать рекурсивную красоту
	TestVector.addEdge(TestDotA, TestDotB, minus);
	TestVector.addEdge(TestVector2, crVertex);

	TestVector.runEdge();

}