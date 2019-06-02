/*
����� ������� - ����������� �� �������� ������ (�� ���� ������ ���)
������� ������ � ���� ������ ���������� � ������� ��� ������������ ��������
*/
#ifndef __INCLUDE__VERTEX__
#define __INCLUDE__VERTEX__

#include "Attribute.h"
#include "basicObj.h"

//��������� shared_ptr ��� ��������� ������ ��� ������
typedef std::shared_ptr<Attribute> attribute_ptr;
typedef std::vector<attribute_ptr> attribute_list;


class Vertex : public basicObj{
  public:
      Vertex(const std::string& Name) : basicObj(Name) {}
	  Vertex(const Vertex& from) : basicObj(from) {
		  if (this != &from) 
			  for (auto i : from.attributes) 
				  //��������, ����� ��������� ���-�� ����� �������������!!!
				  addAttribute(new TypedAttribute<int>(i->getName(), *(int*)i->getData()));
	  }
      ~Vertex(){}

	  //����������� ��� ��� ������ � �����������
	  attribute_list& getAttributes() { return attributes; }
	  template< typename T >
	  void addAttribute(TypedAttribute<T>* newAttribute) {
		  attributes.push_back(attribute_ptr(newAttribute));
	  }

	  template< typename T >
	  void addAttribute(T data, std::string name = " ") {
		  //auto temp = std::make_unique<TypedAttribute<T>>(name, data);
		  attributes.push_back(attribute_ptr(new TypedAttribute<T>(name, data)));
	  }

  protected:
    attribute_list attributes;
};

#endif