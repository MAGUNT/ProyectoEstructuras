#pragma once

template <typename, typename> class ClinkedList;

template<typename T> class Node
{
//modificarlo para registringir la amistad a solo T-T
template<typename F, typename E> friend class ClinkedList; 

private:
	T data;
	Node<T>* next;
	Node<T>* prev;

	Node();
	Node(const T&); //sobrecargar para T&&
};

template <typename T>
Node<T>::Node(const T& e) : data(e){ }

template <typename T>
Node<T>::Node() : Node(T()){ }