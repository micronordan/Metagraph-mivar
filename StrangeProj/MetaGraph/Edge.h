/*
Класс определяет обычное ребро. Оно создает связь между двумя вершинами.
Может быть направленно. Имеет имя.
*/
#ifndef __INCLUDE__EDGE__
#define __INCLUDE_EDGE__
#include "Vertex.h"

class Edge : public basicObj {
public:
	Edge(const std::string& name) : basicObj(name) {}
	Edge(const std::string& name, Vertex* v1, Vertex* v2, bool isEO = 0)
		: basicObj(name), v1(v1), v2(v2), isEO(isEO) {}
	~Edge(){}

  bool getIsEO() { return isEO; }
  Vertex* getV1() { return v1; }
  Vertex* getV2() { return v2; }

  void setIsEO(bool EO) { isEO = EO; }
  void setV1(Vertex* newV1) { v1 = newV1; }
  void setV2(Vertex* newV2) { v1 = newV2; }


  //Стандартный код для работы с аттрибутами
  attribute_list& getAttributes() { return attributes; }
  template< typename T >
  void addAttribute(TypedAttribute<T>* newAttribute) {
	  attributes.push_back(attribute_ptr(newAttribute));
  }

private:
  Vertex* v1;
  Vertex* v2;
  bool isEO;
  attribute_list attributes;
};

#endif