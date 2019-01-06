/*
Класс метавершины. Является основным элементом метаграфа. 
Представляет из себя метаобъект. Описывает данные некой системы объектов
*/
#ifndef __INCLUDE__METAVERTEX__
#define __INCLUDE_METAVERTEX__
#include "Vertex.h"
#include "Edge.h"
#include "Rule.h"
#include <map>

class MetaVertex : public Vertex {
public:
	MetaVertex(MetaVertex& from) : MetaVertex(from, false) {
		//TODO нужно что-то более красивое придумать: вызов уничтожения списка создаёт пустой экземпляр объекта
		MetaVertex(from, true);//Это очистит список
	}

	MetaVertex(const std::string& Name) : Vertex(Name) {}

	~MetaVertex(){}

	void addVertice(Vertex* element) {
		vertices.push_back(element);
	}

	void addVertice(MetaVertex* element) {
		metaVertices.push_back(element);
	}

	void addRule(Rule* element) {
		Rules.push_back(element);
	}

	std::vector<MetaVertex*>& getMetaVertices() { return metaVertices; }
	std::vector<Vertex*>& getVertices() { return vertices; }
	//std::vector<Edge*>& getEdges() { return edges; }

	MetaVertex& operator=(MetaVertex& from);


	std::vector<Rule*>& getRules() { return Rules; }
private:
	std::vector<Rule*> Rules;
	std::vector<MetaVertex*> metaVertices;
	std::vector<Vertex*> vertices;
	//std::vector<Edge*> edges;

	MetaVertex(MetaVertex& from, bool shouldStop) : Vertex(from) {
		static std::map<void *, void *> Copied_obj;

		if (shouldStop) {
			Copied_obj.clear();
			return;
		}

		//Пихаем вершины
		for (auto i : from.vertices) {
			auto it = Copied_obj.find(i);

			if (it != Copied_obj.end())
				vertices.push_back((Vertex*)it->second);
			else {
				vertices.push_back(new Vertex(*i));
				Copied_obj.insert(std::pair<void*, void*>(i, vertices.back()));
			}
		}

		//Пихаем метавершины
		for (auto i : from.metaVertices) {
			auto it = Copied_obj.find(i);

			if (it != Copied_obj.end())
				metaVertices.push_back((MetaVertex*)it->second);
			else {
				metaVertices.push_back(new MetaVertex(*i, false));
				Copied_obj.insert(std::pair<void*, void*>(i, metaVertices.back()));
			}
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

		//Пихаем правила
		for (auto i : from.Rules) {
			Rules.push_back(new Rule(*i));
			Rules.back()->getInputs() = i->getInputs();
			Rules.back()->getOutputs() = i->getOutputs();

			//Согласование объектов для входных и выходных аттрибутов
			createConnection(Rules.back()->getOutputs());
			createConnection(Rules.back()->getInputs());
		}

		Copied_obj.insert(std::pair<void*, void*>(&from, this));
	}

};
#endif