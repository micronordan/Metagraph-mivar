/*
Как бы локальное пространство всех объектов и их взаимодействия
*/
#include "MetaEdge.h"

class MetaGraph : public basicObj {
public:
	MetaGraph(const std::string& Name) : basicObj(Name) {}

	std::vector<MetaEdge*>* getMetaEdges() { return &MetaEdges; }
	std::vector<MetaVertex*>* getMetaVertices() { return &MetaVertices; }
	std::vector<Edge*>* getEdges() { return &Edges; }
	std::vector<Vertex*>* getVertices() { return &Vertices; }

private:
	std::vector<MetaEdge*> MetaEdges;
	std::vector<MetaVertex*> MetaVertices;
	std::vector<Edge*> Edges;
	std::vector<Vertex*> Vertices;
};