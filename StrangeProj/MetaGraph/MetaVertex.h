/*
Класс метавершины. Является основным элементом метаграфа. 
Представляет из себя метаобъект. Описывает данные некой системы объектов
*/
#pragma once
#include "Vertex.h"
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


	std::vector<MetaVertex*>& getMetaVertices() { return metaVertices; }
	std::vector<Vertex*>& getVertices() { return vertices; }

	MetaVertex& operator=(MetaVertex& from);

private:
	std::vector<MetaVertex*> metaVertices;
	std::vector<Vertex*> vertices;

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
	}
};