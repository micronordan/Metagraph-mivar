/*
������� �������� � ������ ������ ������� (�����������) (������ ��� ������� ������ ���� �����)
������� ������ ��� �������� ������������ ������
������� ������ ��� ����� ���������� ������ �������
������� ����� ������ ��������� �������, �� �� ����� ������ ��������� ���������� ��������

����: ����������� - ��� ����� � ����� ������������ - ��� ������������� ����� ��� �����
�� ��-�� ����, ��� ��� ����� ������, � ���� ���������� ����� ��������
����� ��� ������ ������, ����, �������
������� �������� ��������� ����������� ���������� ������ � ��������� ������������
������� ����� ��������� ��������� ������ ������������
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
	//������� ������ ������� (�����)

	//��������� �� ������� ��������� ���������� (������?), ����������� (������� � �������������?)


	//��� ��� ������ � ����������� �������
	attribute_list* getAttributes() { return &RuleParamets; }
	template< typename T >
	void addAttribute(TypedAttribute<T>* newAttribute) {
		RuleParamets.push_back(attribute_ptr(newAttribute));
	}

	//��� ��� ������ � �������� �������
	attribute_list& getInputs() { return inputRuleAttributes; }
	void addInputVector(attribute_list& Input) { inputRuleAttributes.insert(inputRuleAttributes.end(), Input.begin(), Input.end()); }
	void addInput(attribute_ptr element) { inputRuleAttributes.push_back(element); }
	template< typename S >
	void addInput(TypedAttribute<S>* newAttribute) {
		inputRuleAttributes.push_back(attribute_ptr(newAttribute));
	}

	//��� ��� ������ � ��������� �������
	void addOutput(attribute_ptr element) { outputRuleAttributes.push_back(element); }
	//test2
	attribute_list& getOutputs() { return outputRuleAttributes; }
	template< typename V >
	void addOutput(TypedAttribute<V>* newAttribute) {
		outputRuleAttributes.push_back(attribute_ptr(newAttribute));
	}

	void setHandler(std::function<void(attribute_list&, attribute_list&)> Rule) { ruleHandler = Rule; }
	void Run() { ruleHandler(inputRuleAttributes, outputRuleAttributes); }

	//������ �� ��������� ������� � �������� (��� ���������) � �� ���-�� ���
	//����� ���-�� ��������, ������� �� ������ ����� ������������� �� �������� �������

	/*
	��������� ��������� �������� ����������:
	�������� �� �������� ������ ������
	�������� �� ������ ��������� (�������/�����������)
	�������� �� �������� �������

	���������� � �������: ������� ������ �������� � ����:
	����� -> ������ -> ��������
	�.�. ������ �� ��������� �������, ��������� ������� ���������� ������������ ��� ����� �������
	�������� ����, � �������� ����� ���� �����
	� �������� ��������� ����� ���� ������������ ����������� � ��������

	������� ����� ���� ��������/���������� - ������ � ����������� ���������

	�����: 
	������ ��� �� ������� ������� (?)
	������ ��� �� ������� �������� (?)
	������ ��� ���������� �������
	������ ��� ���������� ��������

	�����-�� ������ �� ���������� �������
	*/
private:
	
	attribute_list inputRuleAttributes;
	attribute_list outputRuleAttributes;
	attribute_list RuleParamets;
	std::function<void(attribute_list&, attribute_list&)>  ruleHandler;
};

#endif