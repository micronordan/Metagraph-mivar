/*
Класс определяет обычное ребро. Оно создает связь между двумя вершинами.
Может быть направленно. Имеет имя.
*/
#pragma once
#include "MetaVertex.h"
#include <functional>
#define createMetaHandler [&](MetaVertex& antecedens, MetaVertex& consequens)mutable

class MetaEdge : public Edge {
public:

	std::string EdgeType;

	MetaEdge(const std::string& name) : Edge(name) {}

	MetaEdge(const std::string& name, std::function<void(MetaVertex&, MetaVertex&)> handler, bool isEO = true)
		: Edge(name), edgeHandler(handler), isEO(isEO) {
		EdgeType = "MetaEdge";
	}

	MetaEdge(const std::string& name, std::function<void(MetaVertex&, MetaVertex&)> handler, MetaEdge& preEdge, bool isEO = true)
		: Edge(name), edgeHandler(handler), isEO(isEO) {
		preEdgeList.push_back(&preEdge);
	}
	MetaEdge(const std::string& name, std::function<void(MetaVertex&, MetaVertex&)> handler, std::vector<MetaEdge*> preEdge, bool isEO = true)
		: Edge(name), edgeHandler(handler), isEO(isEO) {
		preEdgeList = preEdge;
	}

	MetaEdge(const std::string& name, std::function<void(MetaVertex&, MetaVertex&)> handler, MetaEdge& preEdge, MetaEdge& afterEdge, bool isEO = true)
		: Edge(name), edgeHandler(handler), isEO(isEO) {
		preEdgeList.push_back(&preEdge);
		afterEdgeList.push_back(&afterEdge);
	}
	MetaEdge(const std::string& name, std::function<void(MetaVertex&, MetaVertex&)> handler, std::vector<MetaEdge*> preEdge, std::vector<MetaEdge*> aftEdge,  bool isEO = true)
		: Edge(name), edgeHandler(handler), isEO(isEO) {
		preEdgeList = preEdge;
		afterEdgeList = aftEdge;
	}

	MetaEdge(const std::string& name, std::function<void(MetaVertex&, MetaVertex&)> handler, 
		std::function<void(MetaVertex&, MetaVertex&)> reversHandler)
		: Edge(name), edgeHandler(handler), reversEdgeHandler(reversHandler) {
		isEO = false;
	}
	~MetaEdge(){}

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

  std::vector<MetaEdge*>& getPreEdgeList() { return preEdgeList; }
  void pushPreEdge(MetaEdge& preEdge) { preEdgeList.push_back(&preEdge); }
  std::vector<MetaEdge*>& getAfterEdgeList() { return afterEdgeList; }
  void pushAfterEdge(MetaEdge& afterEdge) { afterEdgeList.push_back(&afterEdge); }

private:
	bool isEO;
	std::function<void(MetaVertex&, MetaVertex&)>  edgeHandler;
	std::function<void(MetaVertex&, MetaVertex&)>  reversEdgeHandler;
	std::vector<MetaEdge*> preEdgeList;
	std::vector<MetaEdge*> afterEdgeList;

  //Старое
  attribute_list attributes;
};