#pragma once
#include "List.h"
#include "Node.h"
#include "Comparators.h"

template<typename T>
class ClinkedList final :
	public List<T>
{

private:
	unsigned size;
	Node<T> *sentinel;

	int cmp(const T&, const T&) const;
	Node<T>* findNode(Predicate) const;
	Node<T>* last() const;
	Node<T>* dirBefore(Predicate) const;
	Node<T>* dirIndex(unsigned) const;

	T& getData(unsigned index) const;

	void addNodeAfter(Node<T> *, Node<T>*);
	void addNodeBefore(Node<T>*, Node<T>*);
	void deleteNode(Node<T>*);
	bool addAcenDecen(const T&, int f);
	


public:
	ClinkedList();
	ClinkedList(std::initializer_list<T>);
	~ClinkedList();
	void addFist(const T&) override;
	void addLast(const T&) override;
	bool add(unsigned, const T&) override;
	bool addBefore(const T&, Predicate) override;
	bool addAfter(const T&, Predicate) override;
	bool addAscendent(const T&) override;
	bool addDescendent(const T&) override;
	bool remove(Predicate predicate) override;
	bool remove(unsigned) override;
	void clear() override;
	bool isEmpty() const override;
	bool find(Predicate, T&) const override;
	T& operator[] (std::size_t index) override;
	const T& operator[] (std::size_t index) const override;
	T set(unsigned, const T&) override;
	unsigned length() const override;
	
	//template<typename E>friend std::ostream &operator<<(std::ostream &, const List<E>&);

};


template<typename T>
int ClinkedList<T>::cmp(const T& e, const T& o) const
{
	return Comparators::comparar(e, o);
}

template<typename T>
Node<T>* ClinkedList<T>::findNode(Predicate pre) const
{
	Node<T> *node = sentinel->getNext();

	for (unsigned i = 0; i < length(); ++i){

		if (pre(node->getData()))
			return node;
		node = node->getNext();
	}
	return sentinel;
}
template<typename T>
Node<T> * ClinkedList<T>::last() const
{
	return sentinel->getPrev();
}
template<typename T>
Node<T> * ClinkedList<T>::dirBefore(Predicate predicate) const
{
	Node<T> *node = findNode(predicate);
	return sentinel->getPrev();
}
template<typename T>
Node<T> * ClinkedList<T>::dirIndex(unsigned index) const
{
	Node<T> *nodo = sentinel;
	if ((length() / 2) >= index + 1)
	{	
		for (unsigned i = 0; i != index + 1; ++i)
			nodo = nodo->getNext();
	}
	else
	{
		for (unsigned i = length(); i != index; --i)
			nodo = nodo->getPrev();
	}
	return nodo;
}
template<typename T>
void ClinkedList<T>::addNodeAfter(Node<T> *nodo, Node<T>* newNode)
{
	newNode->setPrev(nodo);
	newNode->setNext(nodo->getNext());
	nodo->getNext()->setPrev(newNode);
	nodo->setNext(newNode);
	++size;
}
template<typename T>
void ClinkedList<T>::addNodeBefore(Node<T> *nodo, Node<T>* newNode)
{
	newNode->setNext(nodo);
	newNode->setPrev(nodo->getPrev());
	nodo->getPrev()->setNext(newNode);
	nodo->setPrev(newNode);
	++size;
}
template<typename T>
void ClinkedList<T>::deleteNode(Node<T>* node)
{
	node->getPrev()->setNext(node->getNext());
	node->getNext()->setPrev(node->getPrev());
	delete node;
	--size;
}
template<typename T>
ClinkedList<T>::ClinkedList() : sentinel(new Node<T>()), size(0)
{
	sentinel->setNext(sentinel);
	sentinel->setPrev(sentinel);
}

template<typename T>
ClinkedList<T>::ClinkedList(std::initializer_list<T> list) : ClinkedList()
{
	for (T e : list) 
		addLast(e);
}

template<typename T>
ClinkedList<T>::~ClinkedList()
{
	clear();
}
template<typename T>
void ClinkedList<T>::addFist(const T& e)
{
	addNodeAfter(sentinel, new Node<T>(e));
}
template<typename T>
void ClinkedList<T>::addLast(const T& e)
{
	addNodeBefore(sentinel, new Node<T>(e));
}
template<typename T>
bool ClinkedList<T>::add(unsigned index, const T& e)
{
	bool inRange = index <= length();
	if (inRange)
		addNodeBefore(dirIndex(index), new Node<T>(e));
	return inRange;
}

//unir esta dos en una unica funcion
template<typename T>
bool ClinkedList<T>::addBefore(const T& e, Predicate pre)
{
	Node<T> *node = findNode(pre);
	bool isFound = node != sentinel;
	if (isFound)
		addNodeBefore(node, new Node<T>(e));

	return isFound;

}
template<typename T>
bool ClinkedList<T>::addAfter(const T& e, Predicate pre)
{
	Node<T> *node = findNode(pre);
	bool isFound = node != sentinel;
	if (isFound)
		addNodeAfter(node, new Node<T>(e));

	return isFound;
}

template<typename T>
bool ClinkedList<T>::addAcenDecen(const T& e, int f)
{
	Node<T> *node = sentinel->getNext();
	int isRep = 1;
	
	while (node != sentinel && (isRep = cmp(e, node->data)*f) < 0)
		node = node->getNext();

	bool isAdded = isRep != 0;
	if (isAdded)
		addNodeBefore(node, new Node<T>(e));

	return isAdded;
}

template<typename T>
bool ClinkedList<T>::addAscendent(const T& e)
{
	return addAcenDecen(e, 1);
}
template<typename T>
bool ClinkedList<T>::addDescendent(const T& e)
{
	return addAcenDecen(e, -1);
}
template<typename T>
bool ClinkedList<T>::remove(Predicate pre)
{
	Node<T> *node = findNode(pre);
	bool isFound = node != sentinel;

	if (isFound)
		deleteNode(node);

	return isFound;
}
template<typename T>
bool ClinkedList<T>::remove(unsigned index)
{
	bool inRange = index < length();
	if (inRange)
		deleteNode(dirIndex(index));

	return inRange;

}
template<typename T>
void ClinkedList<T>::clear()
{
	Node<T> *node = sentinel->getNext();
	while (size != 0)
	{
		Node<T> *deleted = node;
		node = node->getNext();
		delete deleted;
		--size;
	}
}
template<typename T>
bool ClinkedList<T>::isEmpty() const
{
	return length() == 0;
}


template<typename T>
bool ClinkedList<T>::find(Predicate pre, T& out) const
{
	Node<T> *node = findNode(pre);
	bool isFound = node != sentinel;
	if (isFound)
		out = node->getData();
	
	return isFound;
}

template<typename T>
T& ClinkedList<T>::operator[] (std::size_t index)
{
	return getData(index);

}
template<typename T>
T& ClinkedList<T>::getData(unsigned index) const
{
	if (index >= length())
		throw new std::out_of_range("index out of range");

	return dirIndex(index)->data;
}

template<typename T>
const T& ClinkedList<T>::operator[] (std::size_t index) const
{
	return getData(index);
}

template<typename T>
T ClinkedList<T>::set(unsigned index, const T& e)
{
	if (index >= length())
		throw new std::out_of_range("index out of range");

	Node<T> *node = dirIndex(index);
	T oldData = node->getData();
	node->setData(e);

	return oldData;
}
template<typename T>
unsigned ClinkedList<T>::length() const
{
	return size;
}