#pragma once
#include <functional>
#include "MultiNode.h"

template<typename T>
class MultiplyList
{

public:
	using Comparator = std::function < int(const T&, const T&)>;

	MultiplyList(std::initializer_list<Comparator>);
	~MultiplyList();

	bool add(const T &); //override T&&
	
	template<typename Predicate>
	bool remove(const Predicate&); 
	bool empty() const;
	unsigned length() const;

	template<typename Func>
	void foreach(unsigned,Func);
private:
	
	Comparator* arrayCmp;
	unsigned sizeCmp;
	
	MultiNode<T>* sentinel;
	unsigned size;

	void addNodeBefore(unsigned, MultiNode<T>* newNode, MultiNode<T>* node);
	bool findTightBoundary(unsigned, const T&, MultiNode<T>*&) const;
	void deleteNode(MultiNode<T>*);

};

template<typename T>
MultiplyList<T>::MultiplyList(std::initializer_list<Comparator> cmps) 
	:sizeCmp(cmps.size()), size(0), arrayCmp(new Comparator[cmps.size()]),
	sentinel(new MultiNode<T>(cmps.size()))
{
	//if (sizeCmp == 0)
	//	throw new std::invalid_argument("there most be atleast 1 comparator");
	unsigned index = 0;
	for (const Comparator& e : cmps)
	{
		sentinel->setNext(index, sentinel);
		sentinel->setPrev(index, sentinel);
		arrayCmp[index++] = e;
	}
}

template<typename T>
MultiplyList<T>::~MultiplyList()
{
	delete[] arrayCmp;
	delete sentinel;
}
//O(sizeCmp*n)
template<typename T>
bool MultiplyList<T>::add(const T & e)
{
	MultiNode<T> *node = nullptr;
	if (!findTightBoundary(0, e, node)) return false;

	MultiNode<T> *newNode = new MultiNode<T>(sizeCmp, e);
	addNodeBefore(0, newNode, node);

	for (unsigned i = 1; i < sizeCmp; ++i)
	{	
		findTightBoundary(i, e, node);
		addNodeBefore(i, newNode, node);
	}

	++size;
	return true;
}

//O(n)
template<typename T>
template<typename Predicate>
bool MultiplyList<T>::remove(const Predicate& pre)
{
	const unsigned path = 0;

	MultiNode<T> *node= sentinel->getNext(path);
	while (node != sentinel && !pre(node->data))
		node = node->getNext(path);

	bool exist = node != sentinel;	
	if (exist)
		deleteNode(node);
	
	return exist;
}
template<typename T>
bool MultiplyList<T>::empty() const
{
	return size == 0;
}
template<typename T>
unsigned MultiplyList<T>::length() const
{
	return size;
}


template<typename T>
template<typename Func>
void MultiplyList<T>::foreach(unsigned cmpIndex, Func func)
{
	MultiNode<T> *node = sentinel->getNext(cmpIndex);
	while (node != sentinel)
	{
		func(node->data);
		node = node->getNext(cmpIndex);
	}

}

template<typename T>
void MultiplyList<T>::addNodeBefore(unsigned cmpIndex, MultiNode<T>* newNode, MultiNode<T>* node)
{
	newNode->setNext(cmpIndex, node);
	newNode->setPrev(cmpIndex, node->getPrev(cmpIndex));
	node->getPrev(cmpIndex)->setNext(cmpIndex, newNode);
	node->setPrev(cmpIndex, newNode);
}
template<typename T>
bool MultiplyList<T>::findTightBoundary(unsigned cmpIndex, const T& e, MultiNode<T>*& bound) const
{
	int c = 1;
	bound = sentinel->getNext(cmpIndex);
	while (bound != sentinel && (c = arrayCmp[cmpIndex](e, bound->data)) > 0)
		bound = bound->getNext(cmpIndex);

	return c != 0;
}

template<typename T>
void MultiplyList<T>::deleteNode(MultiNode<T>* node)
{
	for (unsigned i = 0; i < sizeCmp; ++i)
	{
		node->getPrev(i)->setNext(i, node->getNext(i));
		node->getNext(i)->setPrev(i, node->getPrev(i));
	}

	delete node;
	--size;
}