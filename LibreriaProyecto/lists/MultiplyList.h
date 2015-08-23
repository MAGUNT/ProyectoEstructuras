#pragma once
#include <functional>
#include "../utils/MultiNode.h"

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
	MultiplyList(std::initializer_list<Comparator>);
	~MultiplyList();

	//agrega el dato acendentemente para todos los creterios
	//especificados en el constructor.
	void add(const T &); //override T&&
	
	//basicamente lo mismo que el remove de la lista normal ver List.h
	template<typename Predicate>
	bool remove(const Predicate&); 
	
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
	void foreach(Func, unsigned index)const ;

	template<typename Func>
	void foreach(Func)const;

	template<typename Predicate>
	bool find(Predicate, T&);
	
	void clear();

private:
	
	Comparator* arrayCmp;
	unsigned sizeCmp;
	
	MultiNode<T>* sentinel;
	unsigned size;

	void addNodeBefore(unsigned, MultiNode<T>* newNode, MultiNode<T>* node);
	MultiNode<T>* findTightBoundary(unsigned, const T&) const;
	void deleteNode(MultiNode<T>*);
	void resetSentinel();
	

};

template<typename T>
MultiplyList<T>::MultiplyList(std::initializer_list<Comparator> cmps) 
	:sizeCmp(cmps.size()), size(0), arrayCmp(new Comparator[cmps.size()]),
	sentinel(new MultiNode<T>(cmps.size()+1))
{
	//if (sizeCmp == 0)
	//	throw new std::invalid_argument("there most be atleast 1 comparator");
	unsigned index = 0;
	for (const Comparator& e : cmps)
		arrayCmp[index++] = e;
	resetSentinel();
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
void MultiplyList<T>::add(const T & e)
{
	MultiNode<T> *node = nullptr, 
		*newNode = new MultiNode<T>(sizeCmp + 1, e);

	for (unsigned i = 0; i < sizeCmp; ++i)
	{	
		node = findTightBoundary(i, e);
		addNodeBefore(i, newNode, node);
	}

	addNodeBefore(sizeCmp, newNode, sentinel);

	++size;
}

//O(n)
template<typename T>
template<typename Predicate>
bool MultiplyList<T>::remove(const Predicate& pre)
{
	//escojer uno random
	const unsigned path = 0;

	auto node= sentinel->getNext(path);
	while (node != sentinel && !pre(node->data))
		node = node->getNext(path);

	bool exist = node != sentinel;	
	if (exist) deleteNode(node);
	
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
	
	if (node != sentinel) e = node->data;

	return node != sentinel;
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
MultiNode<T>* MultiplyList<T>::findTightBoundary(unsigned cmpIndex, const T& e) const
{

	auto bound = sentinel->getNext(cmpIndex);
	while (bound != sentinel && arrayCmp[cmpIndex](e, bound->data) > 0)
		bound = bound->getNext(cmpIndex);

	return bound;
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
	for (unsigned i = 0; i<=sizeCmp; ++i)
	{
		sentinel->setNext(i, sentinel);
		sentinel->setPrev(i, sentinel);
	}
}