/*
Правила работают в рамках одного объекта (метавершины) (значит для каждого уровня свой набор)
Правила служат для проверки правильности данных
Правила служат для связи аттрибутов внутри объекта
Правила могут менять аттрибуты объекта, но не могут менять аттрибуты встроенных объектов

Прим: треугольник - три точки с тремя координатами - его метавершинами будут три точки
но из-за того, что эта новый объект, у него появляются новые свойства
такие как длинны сторон, углы, площадь
Правило соединит аттрибуты компонентов встроенных вершин и аттрибуты треугольника
Правила могут соединять аттрибуты внутри треугольника
*/
#ifndef __INCLUDE__RULE__
#define __INCLUDE_RULE__
#include "Vertex.h"
#include <functional>
#pragma once

class Rule : basicObj {
public:
	Rule(const std::string& Name):basicObj(Name){}
	Rule(const std::string& Name, attribute_list& Input, attribute_list& Output)
		:basicObj(Name), inputRuleAttributes(Input), outputRuleAttributes(Output) {}
	Rule(const std::string& Name, std::function<void(attribute_list&, attribute_list&)> Rule) 
		:basicObj(Name), ruleHandler(Rule){}
	Rule(const std::string& Name, attribute_list& Input, attribute_list& Output, std::function<void(attribute_list&, attribute_list&)> Rule)
		:basicObj(Name), inputRuleAttributes(Input), outputRuleAttributes(Output), ruleHandler(Rule) {}

	Rule(const Rule& from) : basicObj(from) {
		operator=(from);
	}
	~Rule() {}

	Rule& operator=(const Rule& from) {
		if (this == &from) {
			return *this;
		}
		basicObj::operator=(from);
		ruleHandler = from.ruleHandler;
	}
	//Условие работы правила (нужно)

	//Указатель на функцию обработки параметров (Лямбда?), микросервис (Функция с сериализацией?)


	//Код для работы с аттрибутами правила
	attribute_list* getAttributes() { return &RuleParamets; }
	template< typename T >
	void addAttribute(TypedAttribute<T>* newAttribute) {
		RuleParamets.push_back(attribute_ptr(newAttribute));
	}

	//Код для работы с входными данными
	attribute_list& getInputs() { return inputRuleAttributes; }
	void addInputVector(attribute_list& Input) { inputRuleAttributes.insert(inputRuleAttributes.end(), Input.begin(), Input.end()); }
	void addInput(attribute_ptr element) { inputRuleAttributes.push_back(element); }
	template< typename S >
	void addInput(TypedAttribute<S>* newAttribute) {
		inputRuleAttributes.push_back(attribute_ptr(newAttribute));
	}

	//Код для работы с выходными данными
	void addOutput(attribute_ptr element) { outputRuleAttributes.push_back(element); }
	//test2
	attribute_list& getOutputs() { return outputRuleAttributes; }
	template< typename V >
	void addOutput(TypedAttribute<V>* newAttribute) {
		outputRuleAttributes.push_back(attribute_ptr(newAttribute));
	}

	void setHandler(std::function<void(attribute_list&, attribute_list&)> Rule) { ruleHandler = Rule; }
	void Run() { ruleHandler(inputRuleAttributes, outputRuleAttributes); }

	//ссылки на аттрибуты входные и выходные (для алгоритма) и мб что-то ещё
	//нужно что-то поменять, правила не должны жёстко фиксироваться на элементе объекта

	/*
	Возможная структура хранение параметров:
	Указание на метаграф работы правил
	Указание на объект метаграфа (вершину/метавершину)
	Указание на аттрибут объекта

	Требование к правилу: правила должны работать в виде:
	Среда -> объект -> аттрибут
	т.е. запрет на вложенные правила, вложенные правила необходимо генерировать как новые правила
	Метаграф один, а объектов может быть много
	В качестве метаграфа может быть использована метавершина и наоборот

	Правила могут быть замкнуты/разомкнуты - работа с аттрибутами метаграфа

	итого: 
	вектор имён на объекты входные (?)
	вектор имён на объекты выходные (?)
	вектор имён аттрибутов входных
	вектор имён аттрибутов выходных

	какая-то ссылка на обработчик правила
	*/
private:
	
	attribute_list inputRuleAttributes;
	attribute_list outputRuleAttributes;
	attribute_list RuleParamets;
	std::function<void(attribute_list&, attribute_list&)>  ruleHandler;
};

#endif