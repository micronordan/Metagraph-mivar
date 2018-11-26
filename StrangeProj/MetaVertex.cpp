#include "pch.h"
#include "MetaGraph/MetaVertex.h"

MetaVertex& MetaVertex::operator=(MetaVertex& from) {
	if (this == &from)
		return *this;

	//Вершины либо забиваются, либо ссылаются на уже забитые
	std::vector<Vertex*>::iterator it;
	int counter = 0;
	for (auto i : from.vertices) {
		if (counter) {
			it = std::find(from.vertices.begin(), from.vertices.begin() + counter - 1, i);
			if (*it == i) {
				int index = std::distance(from.vertices.begin(), it);
				vertices.push_back(this->vertices[index]);
				continue;
			}
		}
		counter++;
		vertices.push_back(new Vertex(*i));
	}



	//Лямбда если существует вершина - возвращает её, иначе MetaVertex("null")
	std::function<MetaVertex*(MetaVertex&, std::vector<MetaVertex*>&, std::vector<MetaVertex*>&)> checkMetaVertex = [&](MetaVertex& MetaVertexToCheck, std::vector<MetaVertex*>& WhereCheck, std::vector<MetaVertex*>& localCopy) mutable -> MetaVertex* {
		int index = 0;
		for (auto& a : WhereCheck) {

			if (a == &MetaVertexToCheck) {
				//Почему-то нельзя поместить выражение в if - не работает
				int MaxElement = localCopy.size() - 1;
				if (MaxElement >= index) {
					return localCopy[index];
				}
				else
					return (new MetaVertex("null"));
			}
			auto MV = checkMetaVertex(MetaVertexToCheck, a->getMetaVertices(), localCopy[index]->getMetaVertices());
			index++;
			if ((*MV).getName() == "null") continue;
			else return MV;

		}
		return (new MetaVertex("null"));
	};

	//Забиваются МетаВершины и вершины чекаются по всем метавершинам
	int cou = 0;
	int locIndex;
	counter = 0;
	std::vector<Vertex*>::iterator iter;
	for (auto& a : from.metaVertices) {
		/*
		if (counter) {
			auto ite = std::find(from.metaVertices.begin(), from.metaVertices.begin() + counter - 1, a);
			if (*ite == a) {
				int index = std::distance(from.metaVertices.begin(), ite);
				metaVertices.push_back(this->metaVertices[index]);
				continue;
			}
		}
		*/

		auto MV = checkMetaVertex(*a, from.metaVertices, metaVertices);
		metaVertices.push_back(new MetaVertex(*a));

		//if(MV!=)

		counter++;

		int vertexCounter = 0;
		for (auto& b : a->vertices) {
			locIndex = 0;
			for (auto c = from.metaVertices.begin(); c != from.metaVertices.begin() + cou; c++) {
				iter = std::find((*c)->vertices.begin(), (*c)->vertices.end(), b);
				if (iter != (*c)->vertices.end()) {
					int index = std::distance((*c)->vertices.begin(), iter);
					this->metaVertices.back()->vertices[vertexCounter] = this->metaVertices[locIndex]->vertices[index];
					break;
				}
				locIndex++;
			}
			vertexCounter++;
		}
		cou++;
	}

	//Лямбда для копирования аттрибутов правил
	auto createConnection = [&](attribute_list& attributeToConnect) mutable {
		for (auto& j : attributeToConnect) {
			std::vector<attribute_ptr>::iterator it = std::find(from.getAttributes().begin(), from.getAttributes().end(), j);
			if (it != from.getAttributes().end()) {
				int index = std::distance(from.getAttributes().begin(), it);
				j.operator =(this->getAttributes()[index]);
				continue;
			}

			std::function<void(attribute_ptr&, MetaVertex&, MetaVertex&)> recursiveChecker = [&](attribute_ptr& attributeToConnect, MetaVertex& fromSearchArea, MetaVertex& thisSearchArea) mutable {
				int counter = 0;
				for (auto k : fromSearchArea.getVertices()) {

					it = std::find(k->getAttributes().begin(), k->getAttributes().end(), attributeToConnect);
					if (it != k->getAttributes().end()) {
						int index = std::distance(k->getAttributes().begin(), it);
						attributeToConnect.operator =(thisSearchArea.getVertices()[counter]->getAttributes()[index]);
						continue;
					}
					counter++;
				}

				counter = 0;
				for (auto& k : fromSearchArea.getMetaVertices()) {
					it = std::find(k->getAttributes().begin(), k->getAttributes().end(), attributeToConnect);
					if (it != k->getAttributes().end()) {
						int index = std::distance(k->getAttributes().begin(), it);
						attributeToConnect.operator =(thisSearchArea.getMetaVertices()[counter]->getAttributes()[index]);
						continue;
					}
					recursiveChecker(attributeToConnect, *k, *thisSearchArea.getMetaVertices()[counter]);
					counter++;

				}
			};

			recursiveChecker(j, from, *this);
		}
	};

	for (auto i : from.Rules) {
		Rules.push_back(new Rule(*i));
		Rules.back()->getInputs() = i->getInputs();
		Rules.back()->getOutputs() = i->getOutputs();

		//Согласование объектов для входных и выходных аттрибутов
		createConnection(Rules.back()->getOutputs());
		createConnection(Rules.back()->getInputs());
	}

	return *this;
}