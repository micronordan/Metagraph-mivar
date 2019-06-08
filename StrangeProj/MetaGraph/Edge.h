/*
Класс определяет обычное ребро. Оно создает связь между двумя вершинами.
Может быть направленно. Имеет имя.
*/
#pragma once
#include "Vertex.h"
#include <functional>
#define createHandler [&](Vertex& antecedens, Vertex& consequens)mutable

class Edge : public basicObj {
public:
	std::string EdgeType;

	Edge(const std::string& name) : basicObj(name) {}

	Edge(const std::string& name, std::function<void(Vertex&, Vertex&)> handler, bool isEO = true)
		: basicObj(name), edgeHandler(handler), isEO(isEO) {
		EdgeType = "Edge";
	}

	Edge(const std::string& name, std::function<void(Vertex&, Vertex&)> handler, Edge& preEdge, bool isEO = true)
		: basicObj(name), edgeHandler(handler), isEO(isEO) {
		preEdgeList.push_back(&preEdge);
	}
	Edge(const std::string& name, std::function<void(Vertex&, Vertex&)> handler, std::vector<Edge*> preEdge, bool isEO = true)
		: basicObj(name), edgeHandler(handler), isEO(isEO) {
		preEdgeList = preEdge;
	}

	Edge(const std::string& name, std::function<void(Vertex&, Vertex&)> handler, Edge& preEdge, Edge& afterEdge, bool isEO = true)
		: basicObj(name), edgeHandler(handler), isEO(isEO) {
		preEdgeList.push_back(&preEdge);
		afterEdgeList.push_back(&afterEdge);
	}
	Edge(const std::string& name, std::function<void(Vertex&, Vertex&)> handler, std::vector<Edge*> preEdge, std::vector<Edge*> aftEdge, bool isEO = true)
		: basicObj(name), edgeHandler(handler), isEO(isEO) {
		preEdgeList = preEdge;
		afterEdgeList = aftEdge;
	}

	Edge(const std::string& name, std::function<void(Vertex&, Vertex&)> handler,
		std::function<void(Vertex&, Vertex&)> reversHandler)
		: basicObj(name), edgeHandler(handler), reversEdgeHandler(reversHandler) {
		isEO = false;
	}
	~Edge() {}

	bool getIsEO() { return isEO; }
	void setIsEO(bool EO) { isEO = EO; }

	void runEdge(Vertex& antecedens, Vertex& consequens) {
		if (!preEdgeList.empty())
			for (auto i : preEdgeList)
				i->runEdge(antecedens, consequens);

		edgeHandler(antecedens, consequens);

		if (!afterEdgeList.empty())
			for (auto i : afterEdgeList)
				i->runEdge(antecedens, consequens);
	}
	void runReversEdge(Vertex& antecedens, Vertex& consequens) { if (!isEO) reversEdgeHandler(antecedens, consequens); }

	std::vector<Edge*>& getPreEdgeList() { return preEdgeList; }
	void pushPreEdge(Edge& preEdge) { preEdgeList.push_back(&preEdge); }
	std::vector<Edge*>& getAfterEdgeList() { return afterEdgeList; }
	void pushAfterEdge(Edge& afterEdge) { afterEdgeList.push_back(&afterEdge); }

private:
	bool isEO;
	std::function<void(Vertex&, Vertex&)>  edgeHandler;
	std::function<void(Vertex&, Vertex&)>  reversEdgeHandler;
	std::vector<Edge*> preEdgeList;
	std::vector<Edge*> afterEdgeList;

	
	//Старое
	attribute_list attributes;
};