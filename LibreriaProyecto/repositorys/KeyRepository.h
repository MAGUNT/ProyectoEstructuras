#pragma once

#include "../lists/ClinkedList.h"
#include "IRepo.h"
#include "../models/compras/Articulo.h"

template <typename T>
class KeyRepository {
private:
	using KeyComparator = std::function < int(T*, T*) > ;
	

	ClinkedList<T*, KeyComparator>* elements;
	IRepo<T*>* repo;
	

public:
	KeyRepository(IRepo<T*>*);
	virtual ~KeyRepository();

	KeyRepository& saveUpdates();

	bool deleteElement(int codigo);
	bool updateElement(int codigo, T* articuloNuevo);
	bool addElement(T*);
	template<typename Predicate>
	T* find(Predicate pre);
	T* getElement(int codigo) const;
	ClinkedList<T*>* getElements();

	const ClinkedList<T*, KeyComparator>* getView();
};


template<typename T> 
KeyRepository<T>::KeyRepository(IRepo<T*>* prepo)
	: repo(prepo)
{
	auto cmp = [](T* x, T* y){return x->getCodigo() - y->getCodigo(); };
	elements = new ClinkedList<T*, KeyComparator>(cmp);
	prepo->readALL(*elements, [](ClinkedList<T*, KeyComparator>& list, T* e)
	{
		list.addAscendent(e);
		 
	});
}
template <typename T>
const ClinkedList<T*, typename KeyRepository<T>::KeyComparator>* KeyRepository<T>::getView()
{
	return elements;
}

template<typename T>
KeyRepository<T>::~KeyRepository()
{
	elements->foreach([]( T* a){delete a; });
	delete elements;
	delete repo;
}

template<typename T>
bool KeyRepository<T>::deleteElement(int codigo)
{
	T* a = nullptr;
	bool isRemove = elements->remove([codigo](T* e)
	{
		return e->getCodigo() == codigo; 
	}, a);
	if (isRemove) delete a;

	return isRemove;
}

template<typename T>
bool KeyRepository<T>::updateElement(int codigo, T* articuloNuevo)
{
	// O(3n) = O(n)
	return getElement(codigo) != nullptr
		&& addElement(articuloNuevo)
		&& deleteElement(codigo);
}

/*
* Metodos publicos
*/

template<typename T>
bool KeyRepository<T>::addElement(T* ele)
{
	if (ele == nullptr) throw std::invalid_argument("null is not suported");
	bool added = elements->addAscendent(ele);
	if (added) repo->save(ele);
	return added;
}

template <typename T>
T* KeyRepository<T>::getElement(int codigo) const{

	T* element = nullptr;
	elements->find([codigo](T* e)
	{
		return e->getCodigo() == codigo;
	}, element);

	return  element;
}

template <typename T>
ClinkedList<T*>* KeyRepository<T>::getElements(){
	
	auto copy = new ClinkedList<T*>();
	elements->foreach([copy](T* e){copy->addAscendent(e); });

	return copy;
}

template <typename T>
KeyRepository<T>& KeyRepository<T>::saveUpdates()
{
	repo->update(*elements);
	return *this;
}
template <typename T>
template<typename Predicate>
T* KeyRepository<T>::find(Predicate pre)
{
	T* element = nullptr;
	elements->find(pre, element);
	return element;
}

