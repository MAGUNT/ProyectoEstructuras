#pragma once
#include <functional>
#include "../utils/MultiNode.h"
#include <stdexcept>

template<typename T>
class MultiplyList
{

public:


	//Se le llama un comparator a una 
	//funcion que retorne 1 si el primer parametro deberia estar estar despues del segundo
	//-1 si el primero deberia estar entes del segundo y cero si son iguales.
	//Esto asumiendo un orden acedente.
	using Comparator = std::function < int(const T&, const T&)>;

	//Esto permite inicializar a lista de esta manera 
	/*

	MultiplyList<int> list =
	{
	[](int x, int y){return y-x;},
	[](int x, int y){return x-y;}
	};

	O su contra parte dinamica
	MultiplyList<int> list = new MultiList<int>
	({
	[](int x, int y){return y-x;},
	[](int x, int y){return x-y;}
	});
	*/
	MultiplyList(std::initializer_list<Comparator>, int);
	MultiplyList(std::initializer_list<Comparator>);
	~MultiplyList();

	//agrega el dato acendentemente para todos los creterios
	//especificados en el constructor.
	bool add(const T &); //override T&&

	//basicamente lo mismo que el remove de la lista normal ver List.h
	template<typename Predicate>
	bool remove(const Predicate&);

	template<typename Predicate>
	bool remove(const Predicate&, T&);

	//si esta vacia
	bool empty() const;
	unsigned length() const;

	//Se pasa un callback con la operacion que se quiere hacer sobre cada dato de la lista 
	//y por cual criterio se desea recorrer.
	//Nota: El numero de criterio depende del orden en el cual se ingresaron en el constructor
	//Ejemplo:
	// Para T= int, esto imprime todos los datos en consola
	//list.foreach(0,[](int x){std::cout << x << std::endl;});
	template<typename Func>
	void foreach(Func, unsigned index)const;

	template<typename Func>
	void foreach(Func)const;

	template<typename Predicate>
	bool find(Predicate, T&);

	void clear();

	bool hasKey();
	int paths();

	T getMax(int) const;
	T getMin(int) const;

private:

	Comparator* arrayCmp;
	unsigned sizeCmp;
	int keyIndex;

	MultiNode<T>* sentinel;
	unsigned size;

	void addNodeBefore(unsigned, MultiNode<T>* newNode, MultiNode<T>* node);
	bool findTightBoundary(unsigned, const T&, MultiNode<T>*&) const;
	void deleteNode(MultiNode<T>*);
	void resetSentinel();


};

template<typename T>
MultiplyList<T>::MultiplyList(std::initializer_list<Comparator> cmps) :MultiplyList(cmps, -1){}
template<typename T>
MultiplyList<T>::MultiplyList(std::initializer_list<Comparator> cmps, int key)
	: sizeCmp(cmps.size()), size(0), arrayCmp(new Comparator[cmps.size()]),
	sentinel(new MultiNode<T>(cmps.size() + 1)), keyIndex(key)
{
	//if (sizeCmp == 0)
	//	throw new std::invalid_argument("there most be atleast 1 comparator");
	unsigned index = 0;
	for (const Comparator& e : cmps)
		arrayCmp[index++] = e;

	resetSentinel();

	if (0 <= key && key < sizeCmp)
		std::swap(arrayCmp[key], arrayCmp[0]);
	else key = -1;
}

template<typename T>
MultiplyList<T>::~MultiplyList()
{
	clear();
	delete[] arrayCmp;
	delete sentinel;
}
//O(sizeCmp*n)
template<typename T>
bool MultiplyList<T>::add(const T & e)
{
	MultiNode<T> *node = nullptr;
	bool isUnique = findTightBoundary(0, e, node);
	if (hasKey() && !isUnique) return false;
	
	auto newNode = new MultiNode<T>(sizeCmp + 1, e);
	addNodeBefore(0, newNode, node);

	for (unsigned i = 1; i < sizeCmp; ++i)
	{
		findTightBoundary(i, e, node);
		addNodeBefore(i, newNode, node);
	}
	addNodeBefore(sizeCmp, newNode, sentinel);

	++size;

	return true;
}

//O(n)
template<typename T>
template<typename Predicate>
bool MultiplyList<T>::remove(const Predicate& pre)
{
	//escojer uno random
	T out;
	return remove(pre, out);
}
template<typename T>
template<typename Predicate>
bool MultiplyList<T>::remove(const Predicate& pre, T& out)
{
	//escojer uno random
	const unsigned path = 0;

	auto node = sentinel->getNext(path);
	while (node != sentinel && !pre(node->data))
		node = node->getNext(path);

	bool exist = node != sentinel;
	if (exist)
	{
		out = node->data;
		deleteNode(node);
	}

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
void MultiplyList<T>::foreach(Func func, unsigned cmpIndex) const
{
	auto node = sentinel->getNext(cmpIndex);
	while (node != sentinel)
	{
		func(node->data);
		node = node->getNext(cmpIndex);
	}

}

template <typename T>
template<typename Func>
void  MultiplyList<T>::foreach(Func f) const
{
	foreach(f, sizeCmp);
}

template<typename T>
template<typename Predicate>
bool MultiplyList<T>::find(Predicate pre, T& e)
{
	const unsigned index = sizeCmp;

	auto node = sentinel->getNext(index);

	while (node != sentinel && !pre(node->data))
		node = node->getNext(index);

	bool found = node != sentinel;
	if (found) e = node->data;
	return found;
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
bool MultiplyList<T>::findTightBoundary(unsigned cmpIndex, const T& e, MultiNode<T>*& node) const
{

	auto ig = 1;
	node = sentinel->getNext(cmpIndex);
	while (node != sentinel && (ig = arrayCmp[cmpIndex](e, node->data)) > 0)
		node = node->getNext(cmpIndex);
	return ig != 0;
}

template<typename T>
void MultiplyList<T>::deleteNode(MultiNode<T>* node)
{
	for (unsigned i = 0; i <= sizeCmp; ++i)
	{
		node->getPrev(i)->setNext(i, node->getNext(i));
		node->getNext(i)->setPrev(i, node->getPrev(i));
	}

	delete node;
	--size;
}

template<typename T>
void MultiplyList<T>::clear()
{
	const unsigned path = 0;
	auto node = sentinel->getNext(path);

	while (node != sentinel)
	{
		auto borrar = node;
		node = node->getNext(path);
		delete borrar;
	}
	resetSentinel();
}
template <typename T>
void  MultiplyList<T>::resetSentinel()
{
	for (unsigned i = 0; i <= sizeCmp; ++i)
	{
		sentinel->setNext(i, sentinel);
		sentinel->setPrev(i, sentinel);
	}
}
template <typename T>
bool MultiplyList<T>::hasKey()
{
	return  keyIndex >= 0;
}
template <typename T>
int MultiplyList<T>::paths()
{
	return sizeCmp + 1;
}
template<typename T> 
T MultiplyList<T>::getMax(int index) const
{
	if (empty()) throw std::underflow_error("underflow");
	return sentinel->getPrev(index)->data;
}
template<typename T>
T MultiplyList<T>::getMin(int index) const
{
	if (empty()) throw std::underflow_error("underflow");
	return sentinel->getNext(index)->data;
}