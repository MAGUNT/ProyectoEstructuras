#pragma once
#include "List.h"
#include "Node.h"
#include "Comparators.h"
#include <SDKDDKVer.h>
#include <stdexcept>



template<class T, class Func = DefaultComparator<T>>
class ClinkedList final
	:public List<T> 
{


private:
	typedef void(ClinkedList<T,Func>::*AddNode)(Node<T>*, Node<T>*);

	unsigned size;
	Node<T> *sentinel;
	Func cmp;
	
	Node<T>* findNode(Predicate) const;
	void check(unsigned,const char*) const;
	Node<T>* dirIndex(unsigned) const;

	T& getData(unsigned index) const;
	
	void resetSentinel();
	void addNodeAfter(Node<T> *, Node<T>*);
	void addNodeBefore(Node<T>*, Node<T>*);
	void deleteNode(Node<T>*);
	
	template<typename E>
	bool genericAddAcenDecen(E&&, int f);
	
	template<typename E> 
	T genericSet(unsigned, E&&);
	
	template<typename E>
	void genericAdd(unsigned, E&&);
	
	template<typename E>
	bool genericAddAB(AddNode, E&&, Predicate);

	bool findTightBoundary(int, const T&, Node<T>*&) const;


public:
	ClinkedList();
	ClinkedList(const std::initializer_list<T>&);
	ClinkedList(const Func&);

	~ClinkedList();
	void addFist(const T&)override;
	void addFist(T&&)override;
	
	void addLast(const T&)override;
	void addLast(T&&)override;

	void add(unsigned, const T&)override;
	void add(unsigned, T&&)override;

	bool addBefore(const T&, Predicate)override;
	bool addBefore(T&&, Predicate)override;

	bool addAfter(const T&, Predicate)override;
	bool addAfter(T&&, Predicate)override;

	bool addAscendent(const T&)override;
	bool addDescendent(const T&)override;

	bool remove(Predicate predicate)override;
	void remove(unsigned)override;

	void clear()override;
	bool isEmpty() const override;
	//pendiente de probar
	bool find(Predicate, T&) const override;
	T& operator[] (std::size_t index)override;
	const T& operator[] (std::size_t index) const override;
	
	//pendiente probar
	T set(unsigned, const T&)override;
	T set(unsigned, T&&)override;
	unsigned length() const override;
	
	void foreach(std::function<void(const T&)> f)
	{
		Node<T> *node = sentinel->next;
		while (node != sentinel)
		{
			f(node->data);
			node = node->next;
		}
	
	}

};

template<typename T, typename F>
void ClinkedList<T, F>::resetSentinel()
{
	sentinel->next = sentinel;
	sentinel->prev = sentinel;
}

template<typename T, typename F>
void  ClinkedList<T,F>::check(unsigned index,const char* msg) const
{
	if (index >= length())
		throw new std::out_of_range(msg);
}
template<typename T, typename F >
Node<T>* ClinkedList<T,F>::findNode(Predicate pre) const
{
	Node<T> *node = sentinel->next;
	for (unsigned i = 0; i < length(); ++i, node = node->next)
	{
		if (pre(node->data)) return node;
	}
	return sentinel;
}

template<typename T, typename F>
Node<T> * ClinkedList<T,F>::dirIndex(unsigned index) const
{
	Node<T> *nodo = sentinel;
	if ((length() / 2) > index)
	{	
		for (unsigned i = 0; i != index + 1; ++i)
			nodo = nodo->next;
	}
	else
	{
		for (unsigned i = length(); i != index; --i)
			nodo = nodo->prev;
	}
	return nodo;
}
template<typename T, typename F>
void ClinkedList<T,F>::addNodeAfter(Node<T> *nodo, Node<T>* newNode)
{
	newNode->prev = nodo;
	newNode->next = nodo->next;
	nodo->next->prev= newNode;
	nodo->next = newNode;
	++size;
}
template<typename T, typename F>
void ClinkedList<T,F>::addNodeBefore(Node<T> *nodo, Node<T>* newNode)
{
	newNode->next = nodo;
	newNode->prev = nodo->prev;
	nodo->prev->next = newNode;
	nodo->prev = newNode;
	++size;
}
template<typename T, typename F>
void ClinkedList<T,F>::deleteNode(Node<T>* node)
{
	node->prev->next = node->next;
	node->next->prev = node->prev;
	delete node;
	--size;
}
template<typename T, typename F>
ClinkedList<T, F>::ClinkedList() :ClinkedList(F()){}

template<typename T, typename F>
ClinkedList<T, F>::ClinkedList(const F& pcmp) : sentinel(new Node<T>()), size(0), cmp(pcmp)
{
	resetSentinel();
}
template<typename T, typename F>
ClinkedList<T,F>::ClinkedList(const std::initializer_list<T>& list) : ClinkedList()
{
	for (const T& e : list)
		addLast(e);
}

template<typename T, typename F>
ClinkedList<T,F>::~ClinkedList()
{
	clear();
}
template<typename T, typename F>
void ClinkedList<T,F>::addFist(const T& e)
{
	addNodeAfter(sentinel, new Node<T>(e));
}

template<typename T, typename F>
void ClinkedList<T,F>::addFist(T&& e)
{
	addNodeAfter(sentinel, new Node<T>(std::move(e)));
}
template<typename T, typename F>
void ClinkedList<T,F>::addLast(const T& e)
{
	addNodeBefore(sentinel, new Node<T>(e));
}
template<typename T, typename F>
void ClinkedList<T,F>::addLast(T&& e)
{
	addNodeBefore(sentinel, new Node<T>(std::move(e)));
}
template<typename T, typename F>
void ClinkedList<T,F>::add(unsigned index, const T& e)
{
	genericAdd(index, e);
}

template<typename T, typename F>
void ClinkedList<T,F>::add(unsigned index, T&& e)
{
	genericAdd(index, std::move(e));
}

template<typename T, typename F>
template<typename E>
void ClinkedList<T,F>::genericAdd(unsigned index, E&& e)
{
	if (index > length())
		throw new std::out_of_range("Index out of range");

	addNodeBefore(dirIndex(index), new Node<T>(std::forward<E>(e)));
}



template<typename T, typename F>
bool ClinkedList<T,F>::addBefore(const T& e, Predicate pre)
{
	return genericAddAB(&ClinkedList<T,F>::addNodeBefore, e, pre);
}

template<typename T, typename F>
bool ClinkedList<T,F>::addBefore(T&& e, Predicate pre)
{
	return genericAddAB(&ClinkedList<T,F>::addNodeBefore, std::move(e), pre);
}

template<typename T, typename F>
bool ClinkedList<T,F>::addAfter(const T& e, Predicate pre)
{
	return genericAddAB(&ClinkedList<T,F>::addNodeAfter, e, pre);
}

template<typename T, typename F>
bool ClinkedList<T,F>::addAfter(T&& e, Predicate pre)
{
	return genericAddAB(&ClinkedList<T,F>::addNodeAfter, std::move(e), pre);
}
template<typename T, typename F>
template<typename E>
bool ClinkedList<T,F>::genericAddAB(AddNode f, E&& e, Predicate pre)
{
	Node<T> *node = findNode(pre);
	bool isFound = node != sentinel;

	if (isFound)
		((*this).*f)(node, new Node<T>(std::forward<E>(e)));

	return isFound;
}


template<typename T, typename F>
template<typename E>
bool ClinkedList<T,F>::genericAddAcenDecen(E&& e, int f)
{
	Node<T> *node = nullptr;
	bool isRep = findTightBoundary(f,e, node);

	if (isRep)
		addNodeBefore(node, new Node<T>(std::forward<E>(e)));
	
	return isRep;
}

template<typename T, typename F>
bool ClinkedList<T,F>::findTightBoundary(int f, const T& e, Node<T>*& node) const
{
	int c = 1;
	node = sentinel->next;
	while (node != sentinel && (c = cmp(e, node->data)*f) > 0)
		node = node->next;

	return c != 0;
}

template<typename T, typename F>
bool ClinkedList<T,F>::addAscendent(const T& e)
{
	return genericAddAcenDecen(e, 1);
}
template<typename T, typename F>
bool ClinkedList<T,F>::addDescendent(const T& e)
{
	return genericAddAcenDecen(e, -1);
}
template<typename T, typename F>
bool ClinkedList<T,F>::remove(Predicate pre)
{
	Node<T> *node = findNode(pre);
	bool isFound = node != sentinel;

	if (isFound)
		deleteNode(node);

	return isFound;
}
template<typename T, typename F>
void ClinkedList<T,F>::remove(unsigned index)
{
	check(index,"Index out of range");
	deleteNode(dirIndex(index));
}
template<typename T, typename F>
void ClinkedList<T,F>::clear()
{
	Node<T> *node = sentinel->next;
	while (size != 0)
	{
		Node<T> *deleted = node;
		node = node->next;
		delete deleted;
		--size;
	}
	resetSentinel();
}
template<typename T, typename F>
bool ClinkedList<T,F>::isEmpty() const
{
	return length() == 0;
}


template<typename T, typename F>
bool ClinkedList<T,F>::find(Predicate pre, T& out) const
{
	Node<T> *node = findNode(pre);
	bool isFound = node != sentinel;
	if (isFound)
		out = node->data;
	
	return isFound;
}

template<typename T, typename F>
T& ClinkedList<T,F>::operator[] (std::size_t index)
{
	return getData(index);

}
template<typename T, typename F>
T& ClinkedList<T,F>::getData(unsigned index) const
{
	check(index,"index out of range");
	return dirIndex(index)->data;
}

template<typename T, typename F>
const T& ClinkedList<T,F>::operator[] (std::size_t index) const
{
	return getData(index);
}

template<typename T, typename F>
T ClinkedList<T,F>::set(unsigned index, const T& e)
{
	return genericSet(index, e);
}

template<typename T, typename F>
T ClinkedList<T,F>::set(unsigned index, T&& e)
{
	return genericSet(index, std::move(e));
}

template<typename T, typename F>
template<typename E> 
T ClinkedList<T,F>::genericSet(unsigned index, E&& e)
{
	check(index,"index out of range");
	Node<T> *node = dirIndex(index);
	T oldData = std::move(node->data);
	node->data = std::forward<E>(e);

	return oldData;
}

template<typename T, typename F>
unsigned ClinkedList<T,F>::length() const
{
	return size;
}
