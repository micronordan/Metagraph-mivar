/*
Метаребро определяет описание процесса, как метаобъет изменялся
*/
#include "MetaVertex.h"

class MetaEdge : public Edge {
public:
	MetaEdge(const std::string& Name) : Edge(Name) {}
	MetaEdge(const std::string& name, Vertex* v1, Vertex* v2, bool isEO = 0)
		: Edge(name, v1, v2, isEO) {}
	~MetaEdge() {}

	std::vector<MetaVertex*> getMetaVertices() { return metaVertices; }

private:
  std::vector <MetaVertex*> metaVertices;
};
