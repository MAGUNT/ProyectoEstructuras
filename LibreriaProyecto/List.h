#pragma once
#include "stdafx.h"

//falta el asignment y otros
template <typename T> class List
{
protected:
	using Predicate = std::function<bool(const T&)>;
public:
	//investigar sobre pure virtual.
	virtual ~List(){}
	virtual void addFist(const T&)=0;
	virtual void addLast(const T&)=0;
	virtual bool add(unsigned, const T&) = 0;
	virtual bool addBefore(const T&, Predicate) = 0;
	virtual bool addAfter(const T&, Predicate) = 0;
	virtual bool addAscendent(const T&) = 0;
	virtual bool addDescendent(const T&) = 0;
	virtual bool remove(Predicate predicate)=0;
	virtual bool remove(unsigned)=0;
	virtual void clear() = 0;
	virtual bool isEmpty() const = 0;
	virtual bool find(Predicate, T&) const =0;
	virtual T& operator[] (std::size_t index) = 0;
	virtual const T& operator[] (std::size_t index) const = 0;
	virtual unsigned length() const = 0;
	virtual T set(unsigned, const T&)=0;
	//template<typename E>friend std::ostream &operator<<(std::ostream &, const List<E>&);
};

//template<typename E> std::ostream& operator << (std::ostream &, const List<E>&);

/*
namespace std {
	template<>
	struct less<std::shared_ptr<Dog>> {
		bool operator() (const std::shared_ptr<Dog>& lhs, const std::shared_ptr<Dog>& rhs) {
			return *lhs < *rhs;
		}
	};
*/
