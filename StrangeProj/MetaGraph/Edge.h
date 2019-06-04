/*
Класс определяет обычное ребро. Оно создает связь между двумя вершинами.
Может быть направленно. Имеет имя.
*/
#pragma once
#include "MetaVertex.h"
#include <functional>
#define createHandler [&](MetaVertex& antecedens, MetaVertex& consequens)mutable

class Edge : public basicObj {
public:
	Edge(const std::string& name) : basicObj(name) {}

	Edge(const std::string& name, std::function<void(MetaVertex&, MetaVertex&)> handler, bool isEO = true)
		: basicObj(name), edgeHandler(handler), isEO(isEO) {}

	Edge(const std::string& name, std::function<void(MetaVertex&, MetaVertex&)> handler, Edge& preEdge, bool isEO = true)
		: basicObj(name), edgeHandler(handler), isEO(isEO) {
		preEdgeList.push_back(&preEdge);
	}
	Edge(const std::string& name, std::function<void(MetaVertex&, MetaVertex&)> handler, std::vector<Edge*> preEdge, bool isEO = true)
		: basicObj(name), edgeHandler(handler), isEO(isEO) {
		preEdgeList = preEdge;
	}

	Edge(const std::string& name, std::function<void(MetaVertex&, MetaVertex&)> handler, Edge& preEdge, Edge& afterEdge, bool isEO = true)
		: basicObj(name), edgeHandler(handler), isEO(isEO) {
		preEdgeList.push_back(&preEdge);
		afterEdgeList.push_back(&afterEdge);
	}
	Edge(const std::string& name, std::function<void(MetaVertex&, MetaVertex&)> handler, std::vector<Edge*> preEdge, std::vector<Edge*> aftEdge,  bool isEO = true)
		: basicObj(name), edgeHandler(handler), isEO(isEO) {
		preEdgeList = preEdge;
		afterEdgeList = aftEdge;
	}

	Edge(const std::string& name, std::function<void(MetaVertex&, MetaVertex&)> handler, 
		std::function<void(MetaVertex&, MetaVertex&)> reversHandler)
		: basicObj(name), edgeHandler(handler), reversEdgeHandler(reversHandler) {
		isEO = false;
	}
	~Edge(){}

  bool getIsEO() { return isEO; }
  void setIsEO(bool EO) { isEO = EO; }

  void runEdge(MetaVertex& antecedens, MetaVertex& consequens) {
	  if (!preEdgeList.empty())
		  for (auto i : preEdgeList)
			  i->runEdge(antecedens, consequens);

	  edgeHandler(antecedens, consequens); 

	  if (!afterEdgeList.empty())
		  for (auto i : afterEdgeList)
			  i->runEdge(antecedens, consequens);
  }
  void runReversEdge(MetaVertex& antecedens, MetaVertex& consequens) { if(!isEO) reversEdgeHandler(antecedens, consequens); }

  std::vector<Edge*>& getPreEdgeList() { return preEdgeList; }
  void pushPreEdge(Edge& preEdge) { preEdgeList.push_back(&preEdge); }
  std::vector<Edge*>& getAfterEdgeList() { return afterEdgeList; }
  void pushAfterEdge(Edge& afterEdge) { afterEdgeList.push_back(&afterEdge); }

private:
	bool isEO;
	std::function<void(MetaVertex&, MetaVertex&)>  edgeHandler;
	std::function<void(MetaVertex&, MetaVertex&)>  reversEdgeHandler;
	std::vector<Edge*> preEdgeList;
	std::vector<Edge*> afterEdgeList;

  //Старое
  attribute_list attributes;
};