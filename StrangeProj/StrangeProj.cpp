#include "pch.h"
#include <iostream>
#include <typeinfo>
#include <string>
#include <math.h>
#include "MetaGraph/MetaGraph.h"

int main()
{
	Vertex abstractDot("Dot");
	abstractDot.addAttribute(new TypedAttribute<int>("X", 0));
	abstractDot.addAttribute(new TypedAttribute<int>("Y", 1));

	MetaVertex abstractLine("Line");
	for(int i = 0; i<2; i++) abstractLine.addVertice(new Vertex(abstractDot));
	abstractLine.addAttribute(new TypedAttribute<int>("LongOfLine", 0));
	abstractLine.addRule(new Rule("LineLong"));
	abstractLine.getRules()[0]->addOutput(abstractLine.getAttributes()[0]);
	for (int i = 0; i < 2; i++) 
		abstractLine.getRules()[0]->addInputVector(abstractLine.getVertices()[i]->getAttributes());
	abstractLine.getRules()[0]->setHandler( [&](attribute_list& input, attribute_list& output) mutable {
		auto x1 = *(int*)input[0]->getData();
		auto y1 = *(int*)input[1]->getData();
		auto x2 = *(int*)input[2]->getData();
		auto y2 = *(int*)input[3]->getData();
		auto* c = (int*)output[0]->getData();
		*c = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	});

	MetaVertex abstractAngle("Angle");
	for (int i = 0; i < 2; i++) abstractAngle.addVertice(new MetaVertex(abstractLine));
	abstractAngle.getMetaVertices()[0]->getVertices()[0] = abstractAngle.getMetaVertices()[1]->getVertices()[0];
	abstractAngle.addAttribute(new TypedAttribute<int>("AngleAtr", 0));
	abstractAngle.addRule(new Rule("Angle"));
	abstractAngle.getRules()[0]->addOutput(abstractAngle.getAttributes()[0]);
	for (int i = 0; i < 2; i++) abstractAngle.getRules()[0]->addInputVector(abstractAngle.getMetaVertices()[0]->getVertices()[i]->getAttributes());
	abstractAngle.getRules()[0]->addInputVector(abstractAngle.getMetaVertices()[1]->getVertices()[1]->getAttributes());
	abstractAngle.getRules()[0]->setHandler([&](attribute_list& input, attribute_list& output) mutable {
		auto Ax = *(int*)input[2]->getData() - *(int*)input[0]->getData();
		auto Ay = *(int*)input[3]->getData() - *(int*)input[1]->getData();
		auto Bx = *(int*)input[4]->getData() - *(int*)input[0]->getData();
		auto By = *(int*)input[5]->getData() - *(int*)input[1]->getData();
		auto C = (int*)output[0]->getData();
		auto test = acos((Ax*Bx + Ay * By) / (sqrt(pow(Ax, 2) + pow(Ay, 2))*sqrt(pow(Bx, 2) + pow(By, 2))))*180;

		*C = acos((Ax*Bx + Ay * By) / (sqrt(pow(Ax, 2) + pow(Ay, 2))*sqrt(pow(Bx, 2) + pow(By, 2))))*180.0 / 3.14;
	});

	MetaVertex abstractTriangle("Triangle");
	for (int i = 0; i < 3; i++) abstractTriangle.addVertice(new MetaVertex(abstractAngle));
	abstractTriangle.getMetaVertices()[0]->getMetaVertices()[1] = abstractTriangle.getMetaVertices()[1]->getMetaVertices()[0];
	abstractTriangle.getMetaVertices()[1]->getMetaVertices()[1] = abstractTriangle.getMetaVertices()[2]->getMetaVertices()[0];
	abstractTriangle.getMetaVertices()[2]->getMetaVertices()[1] = abstractTriangle.getMetaVertices()[0]->getMetaVertices()[0];

	//Окей, копирование метавершин - плохо, ибо не понятно, что  нужно копировать вложенные метавершины с и как вообще это делать
	MetaVertex testTriangle(abstractTriangle);

	/*
	MetaVertex testAngle(abstractAngle);
	testAngle.getMetaVertices()[0]->getVertices()[0]->getAttributes()[0]->changeData(new int(10));
	testAngle.getMetaVertices()[0]->getVertices()[0]->getAttributes()[1]->changeData(new int(20));
	testAngle.getMetaVertices()[0]->getVertices()[1]->getAttributes()[0]->changeData(new int(30));
	testAngle.getMetaVertices()[0]->getVertices()[1]->getAttributes()[1]->changeData(new int(40));
	testAngle.getMetaVertices()[1]->getVertices()[1]->getAttributes()[0]->changeData(new int(50));
	testAngle.getMetaVertices()[1]->getVertices()[1]->getAttributes()[1]->changeData(new int(60));
	testAngle.getRules()[0]->Run();
	*/

	return 0;
}
