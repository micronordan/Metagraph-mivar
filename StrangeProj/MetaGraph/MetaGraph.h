/*
Как бы локальное пространство всех объектов и их взаимодействия
*/
#include "MetaEdge.h"
#define Run(connection, edgeNum) (mainMetaGraph.RunMetaGraph(connection, edgeNum))
#define RunVertex(connection) (mainMetaGraph.RunMetaGraph(connection))


class MetaGraph : public basicObj {
public:
	MetaGraph(const std::string& Name = " ") : basicObj(Name) {}

	std::vector<MetaEdge*>* getMetaEdges() { return &MetaEdges; }
	std::vector<MetaVertex*>* getMetaVertices() { return &MetaVertices; }
	std::vector<Edge*>* getEdges() { return &Edges; }
	std::vector<Vertex*>* getVertices() { return &Vertices; }

	void pushElement(MetaVertex& MV) { MetaVertices.push_back(&MV); }
	void pushElement(Vertex& V) { Vertices.push_back(&V); }
	void pushElement(Edge& E) { Edges.push_back(&E); }

	void RunMetaGraph(std::vector < std::pair< pairOfVertex, Edge*>>& connection, int edgeNum = 0){
		auto edge = connection[edgeNum].second;
		
		if (edge->EdgeType == "Edge") {
			edge->runEdge(*connection[edgeNum].first.first, *connection[edgeNum].first.second);
		}
		else {
			MetaEdge* metaEdge = (MetaEdge*)connection[edgeNum].second;
			metaEdge->runEdge(*(MetaVertex*)connection[edgeNum].first.first, *(MetaVertex*)connection[edgeNum].first.second);
		}
	}
private:
	std::vector<MetaEdge*> MetaEdges;
	std::vector<MetaVertex*> MetaVertices;
	std::vector<Edge*> Edges;
	std::vector<Vertex*> Vertices;
};

MetaGraph mainMetaGraph;