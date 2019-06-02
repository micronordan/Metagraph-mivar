#pragma once
#include "MetaVertex.h"
#include "Edge.h"
using namespace std;
typedef pair< MetaVertex*, MetaVertex*> pairOfVertex;

class RuleObject
{
public:
	RuleObject() {};
	RuleObject(vector < pair< pairOfVertex, Edge*>> vector) : logicEdges(vector) {}
	RuleObject(MetaVertex* antecedens, MetaVertex* consequens, Edge* Edge) {
		addEdge(antecedens, consequens, Edge);
	}
	RuleObject(MetaVertex& antecedens, MetaVertex& consequens, Edge& Edge) {
		addEdge(&antecedens, &consequens, &Edge);
	}
	RuleObject(MetaVertex& mutator, Edge& Edge) {
		addEdge(&mutator, &mutator, &Edge);
	}

	~RuleObject() {};

	void addEdge(MetaVertex* antecedens, MetaVertex* consequens, Edge* Edge) {
		logicEdges.push_back(std::make_pair(std::make_pair(antecedens, consequens), Edge));
	}

	vector < pair< pairOfVertex, Edge*>> getVector() {
		return logicEdges;
	}

	void runEdge(int edgeNum) {
		logicEdges[edgeNum].second->runEdge(*logicEdges[edgeNum].first.first, *logicEdges[edgeNum].first.second);
	}

private:
	vector < pair< pairOfVertex, Edge*>> logicEdges;
};

