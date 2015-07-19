#pragma once
#include <functional>

template 
<
	class T
> 
class List
{
public:
	using Predicate = const std::function<bool(const T&)>&;

	virtual ~List(){}
	virtual void addFist(const T&)=0;
	virtual void addFist(T&&)=0;
	
	virtual void addLast(const T&)=0;
	virtual void addLast(T&&) = 0;
	
	virtual void add(unsigned, const T&) = 0;
	virtual void add(unsigned, T&&) = 0;

	virtual bool addBefore(const T&, Predicate) = 0;
	virtual bool addBefore(T&&, Predicate) = 0;

	virtual bool addAfter(const T&, Predicate) = 0;
	virtual bool addAfter(T&&, Predicate) = 0;

	virtual bool addAscendent(const T&) = 0;
	virtual bool addDescendent(const T&) = 0;

	virtual bool remove(Predicate predicate)=0;
	virtual void remove(unsigned)=0;
	virtual void clear() = 0;
	virtual bool isEmpty() const = 0;
	virtual bool find(Predicate, T&) const =0;
	virtual T& operator[] (std::size_t index) = 0;
	virtual const T& operator[] (std::size_t index) const = 0;
	virtual unsigned length() const = 0;
	virtual T set(unsigned, const T&)=0;
	virtual T set(unsigned, T&&) = 0;
	//falta cbegin, begin , cend, end
	template<typename E>friend std::ostream &operator<<(std::ostream&os, const List<E>& list)
	{
		for (const E& e : list)
			os << e << ",";
	}
};

