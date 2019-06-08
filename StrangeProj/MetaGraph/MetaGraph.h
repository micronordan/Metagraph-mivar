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
			if (!edge->getPreEdgeList().empty())
				for (size_t i = 0; i < edge->getPreEdgeList().size(); i++) {
					std::vector< std::pair< pairOfVertex, Edge*>> test = { std::make_pair(std::make_pair(connection[edgeNum].first.first, connection[edgeNum].first.second), connection[edgeNum].second) };
					RunMetaGraph(test, i);
				}

			edge->runEdge(*connection[edgeNum].first.first, *connection[edgeNum].first.second);
			
			if (edge->EdgeType == "Edge") {
				if (!edge->getAfterEdgeList().empty())
					for (size_t i = 0; i < edge->getAfterEdgeList().size(); i++) {
						std::vector< std::pair< pairOfVertex, Edge*>> test = { std::make_pair(std::make_pair(connection[edgeNum].first.first, connection[edgeNum].first.second), connection[edgeNum].second) };
						RunMetaGraph(test, i);
					}
			}
		}
		else {
			if (!edge->getPreEdgeList().empty())
				for (size_t i = 0; i < edge->getPreEdgeList().size(); i++) {
					std::vector< std::pair< pairOfVertex, Edge*>> test = { std::make_pair(std::make_pair(connection[edgeNum].first.first, connection[edgeNum].first.second), connection[edgeNum].second) };
					RunMetaGraph(test, i);
				}

			MetaEdge* metaEdge = (MetaEdge*)connection[edgeNum].second;
			metaEdge->runEdge(*(MetaVertex*)connection[edgeNum].first.first, *(MetaVertex*)connection[edgeNum].first.second);

			if (edge->EdgeType == "Edge") {
				if (!edge->getAfterEdgeList().empty())
					for (size_t i = 0; i < edge->getAfterEdgeList().size(); i++) {
						std::vector< std::pair< pairOfVertex, Edge*>> test = { std::make_pair(std::make_pair(connection[edgeNum].first.first, connection[edgeNum].first.second), connection[edgeNum].second) };
						RunMetaGraph(test, i);
					}
			}
		}
	}
private:
	std::vector<MetaEdge*> MetaEdges;
	std::vector<MetaVertex*> MetaVertices;
	std::vector<Edge*> Edges;
	std::vector<Vertex*> Vertices;
};