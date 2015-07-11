#pragma once

template <typename> class ClinkedList;

template<typename T> class Node
{

friend class ClinkedList<T>; 

private:
	T data;
	Node<T>* next;
	Node<T>* prev;

	//esto puede ser indefinido para build in types buscar solucion.
	Node() = default;
	Node(const T&);
	Node(const T& e, Node<T>* pprev, Node<T>* pnext);
	~Node();
	T getData();
	void setData(T);
	void setNext(Node<T>*);
	void setPrev(Node<T>*);
	Node<T>* getNext();
	Node<T>* getPrev();

};


template <typename T>
Node<T>::Node(const T& e) :Node(e, nullptr, nullptr){}

template<typename T>
Node<T>::Node(const T& e, Node<T>* pnext, Node<T>* pprev)
	:data(e), next(pnext), prev(pprev){}

template <typename T>
Node<T>::~Node(){ }

template <typename T>
T Node<T>::getData()
{ 
	return data; 
}
template <typename T>
void Node<T>::setData(T pdata)
{ 
	data = pdata; 
}
template <typename T>
void Node<T>::setNext(Node<T>* node)
{ 
	next = node; 
}
template <typename T>
void Node<T>::setPrev(Node<T>* node)
{ 
	prev = node; 
}
template <typename T>
Node<T>* Node<T>::getNext()
{ 
	return next; 
}
template <typename T>
Node<T>* Node<T>::getPrev()
{ 
	return prev; 
}
