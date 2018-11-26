/*
Класс метавершины. Является основным элементом метаграфа. 
Представляет из себя метаобъект. Описывает данные некой системы объектов
*/
#ifndef __INCLUDE__METAVERTEX__
#define __INCLUDE_METAVERTEX__
#include "Vertex.h"
#include "Edge.h"
#include "Rule.h"

class MetaVertex : public Vertex {
public:
	MetaVertex(MetaVertex& from) : Vertex(from) {
		operator=(from);
	}
	MetaVertex(const std::string& Name) : Vertex(Name) {}

	~MetaVertex(){}

	void addVertice(Vertex* element) {
		vertices.push_back(element);
	}

	void addVertice(MetaVertex* element) {
		metaVertices.push_back(element);
	}

	void addRule(Rule* element) {
		Rules.push_back(element);
	}

	std::vector<MetaVertex*>& getMetaVertices() { return metaVertices; }
	std::vector<Vertex*>& getVertices() { return vertices; }
	//std::vector<Edge*>& getEdges() { return edges; }

	MetaVertex& operator=(MetaVertex& from);


	std::vector<Rule*>& getRules() { return Rules; }
private:
	std::vector<Rule*> Rules;
	std::vector<MetaVertex*> metaVertices;
	std::vector<Vertex*> vertices;
	//std::vector<Edge*> edges;
};
#endif