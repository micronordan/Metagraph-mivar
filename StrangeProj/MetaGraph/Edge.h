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

	Edge(const std::string& name, std::function<void(MetaVertex&, MetaVertex&)> handler, 
		std::function<void(MetaVertex&, MetaVertex&)> reversHandler)
		: basicObj(name), edgeHandler(handler), reversEdgeHandler(reversHandler) {
		isEO = false;
	}
	~Edge(){}

  bool getIsEO() { return isEO; }
  void setIsEO(bool EO) { isEO = EO; }

  void runEdge(MetaVertex& antecedens, MetaVertex& consequens) { edgeHandler(antecedens, consequens); }
  void runReversEdge(MetaVertex& antecedens, MetaVertex& consequens) { if(!isEO) reversEdgeHandler(antecedens, consequens); }

  //Стандартный код для работы с аттрибутами
  attribute_list& getAttributes() { return attributes; }
  template< typename T >
  void addAttribute(TypedAttribute<T>* newAttribute) {
	  attributes.push_back(attribute_ptr(newAttribute));
  }

private:
	bool isEO;
	std::function<void(MetaVertex&, MetaVertex&)>  edgeHandler;
	std::function<void(MetaVertex&, MetaVertex&)>  reversEdgeHandler;
	std::vector<Edge> preEdgeList;
	std::vector<Edge> afterEdgeList;

  //Старое
  attribute_list attributes;
};