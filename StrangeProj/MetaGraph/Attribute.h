/*
Здесь живёт стандартный аттрибут - элементарная сущность метаграфа.
Используется полиморфизм, чтобы можно было хранить разные типы данных.
Другими словами, это пара: имя - значение какого-то типа
*/

#ifndef __INCLUDE__ATTRIB__
#define __INCLUDE__ATTRIB__

#include <vector>
#include <memory> //нужно для работы shared_ptr в не gcc 11+
#include <typeinfo>
#include "basicObj.h"

class Attribute : public basicObj
{
public:
    Attribute(const std::string& name) : basicObj(name) {}
    virtual ~Attribute() {}

	virtual void changeData(void* newData) = 0;
	virtual void* getData() =0;
	const virtual std::type_info* GetValueType() =0;

	virtual operator int() = 0;
	virtual Attribute& operator=(int from) = 0;
	//virtual Attribute& operator=(void* from) = 0;

	Attribute& operator=(const Attribute& from) {
		if (this == &from) {
			return *this;
		}
		basicObj::operator=(from);
		return *this;
	}
};

template< typename T >
class TypedAttribute : public Attribute
{
public:
    TypedAttribute (const std::string& name, const T& data)
      : Attribute(name), m_data(data) {}

	~TypedAttribute() {}

	void changeData(void* newData) { 
		m_data = *(T*)newData;
	}


	Attribute& operator=(int from) {
		m_data = from;
		return *this;
	}

	Attribute& operator=(std::string from) {
		m_data = from;
		return *this;
	}

	void* getData() { return &m_data; }
	virtual operator int() {
		return (int)m_data;
	}

	const std::type_info* GetValueType() { return &typeid(T); }


	TypedAttribute& operator=(TypedAttribute& from) {
		if (this == &from) {
			return *this;
		}
		Attribute::operator=(from);
		m_data = from.m_data;
		return *this;
	}
private:
    T m_data;
};


#endif