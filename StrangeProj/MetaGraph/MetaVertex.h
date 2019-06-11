/*
Класс метавершины. Является основным элементом метаграфа. 
Представляет из себя метаобъект. Описывает данные некой системы объектов
*/
#pragma once
#include "Vertex.h"
#include "Edge.h"
#include <map>
typedef std::pair< Vertex*, Vertex*> pairOfVertex;


class MetaVertex : public Vertex {
public:
	MetaVertex(MetaVertex& from) : MetaVertex(from, false) {
		//TODO нужно что-то более красивое придумать: вызов уничтожения списка создаёт пустой экземпляр объекта
		MetaVertex(from, true);//Это очистит список
	}

	MetaVertex(const std::string& Name = " ") : Vertex(Name) {}

	~MetaVertex(){}

	void addVertice(Vertex& element) {
		vertices.push_back(&element);
	}

	void addVertice(MetaVertex& element) {
		metaVertices.push_back(&element);
	}

	void addVertice(Vertex* element) {
		vertices.push_back(element);
	}

	void addVertice(MetaVertex* element) {
		metaVertices.push_back(element);
	}

	/*void addEdge(Edge& edge) {
		edges.push_back(&edge);
	}*/


	std::vector<MetaVertex*>& getMetaVertices() { return metaVertices; }
	std::vector<Vertex*>& getVertices() { return vertices; }

	MetaVertex& operator=(MetaVertex& from);


	std::vector < std::pair< pairOfVertex, Edge*>>& getLogicVector() {
		return logicConnection;
	}

	operator std::vector < std::pair< pairOfVertex, Edge*>>&() {
		return logicConnection;
	}

	void addEdge(MetaVertex& antecedens, MetaVertex& consequens, Edge& Edge) {
		metaVertices.push_back(&antecedens);
		metaVertices.push_back(&consequens);
		logicConnection.push_back(std::make_pair(std::make_pair(&antecedens, &consequens), &Edge));
	}

	void addEdge(MetaVertex& antecedens, Edge& mutator) {
		metaVertices.push_back(&antecedens);
		logicConnection.push_back(std::make_pair(std::make_pair(&antecedens, &antecedens), &mutator));
	}

	void addEdge(Vertex& antecedens, Vertex& consequens, Edge& Edge) {
		vertices.push_back(&antecedens);
		vertices.push_back(&consequens);
		logicConnection.push_back(std::make_pair(std::make_pair(&antecedens, &consequens), &Edge));
	}

	void addEdge(Vertex& antecedens, Edge& mutator) {
		vertices.push_back(&antecedens);
		logicConnection.push_back(std::make_pair(std::make_pair(&antecedens, &antecedens), &mutator));
	}

private:
	std::vector<MetaVertex*> metaVertices;
	std::vector<Vertex*> vertices;
	//std::vector<Edge*> edges;
	std::vector < std::pair< pairOfVertex, Edge*>> logicConnection;

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

		//Пихаем ребра
		/*for (auto i : from.edges) {
			auto it = Copied_obj.find(i);

			if (it != Copied_obj.end())
				edges.push_back((Edge*)it->second);
			else {
				edges.push_back(new Edge(*i));
				Copied_obj.insert(std::pair<void*, void*>(i, metaVertices.back()));
			}
		}*/

		std::function<bool(Vertex*, MetaVertex&, MetaVertex&)> createConnection = [&](Vertex* VertexToConnect, MetaVertex& fromSearchArea, MetaVertex& thisSearchArea) mutable {

			for (size_t i = 0; i < fromSearchArea.getVertices().size(); i++) {
				if (fromSearchArea.getVertices()[i] == VertexToConnect)
					VertexToConnect = thisSearchArea.getVertices()[i];
				return true;
			}

			for (size_t i = 0; i < fromSearchArea.getMetaVertices().size(); i++) {
				if (fromSearchArea.getMetaVertices()[i] == VertexToConnect)
					VertexToConnect = thisSearchArea.getMetaVertices()[i];
				return true;
			}

			for (size_t z = 0; z < fromSearchArea.getMetaVertices().size(); z++)
				if (createConnection(VertexToConnect, *fromSearchArea.getMetaVertices()[z], *thisSearchArea.getMetaVertices()[z]))
					return true;
				
			return false;
		};

		for (auto i : from.logicConnection) {
			std::pair< pairOfVertex, Edge*>* newRecord = new std::pair< pairOfVertex, Edge*>(i);

			//Согласование объектов для входных и выходных аттрибутов
			if(!createConnection(newRecord->first.first, from, *this))
				newRecord->first.first = nullptr;
			if (!createConnection(newRecord->first.second, from, *this))
				newRecord->first.second = nullptr;

			logicConnection.push_back(*newRecord);
		}
		//Вносим в базу инфу о том, что мы скопировали это
		Copied_obj.insert(std::pair<void*, void*>(&from, this));
	}
};