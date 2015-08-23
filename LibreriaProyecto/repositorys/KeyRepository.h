#pragma once

#include "../lists/ClinkedList.h"
#include "IRepo.h"
#include "../models/compras/Articulo.h"

template <typename T>
class KeyRepository {
private:
	ClinkedList<T*>* elements;
	IRepo<T*>* repo;

	std::function<bool(T*)> createSLambda(int) const;

public:
	KeyRepository(IRepo<T*>*);
	virtual ~KeyRepository();

	KeyRepository& saveUpdates();

	bool deleteElement(int codigo);
	bool updateElement(int codigo, T* articuloNuevo);
	bool addElement(T*);
	T* getElement(int codigo) const;
};


template<typename T> 
KeyRepository<T>::KeyRepository(IRepo<T*>* prepo)
	: repo(prepo), elements(prepo->readALL()){}

template<typename T>
KeyRepository<T>::~KeyRepository()
{
	elements->foreach([]( T* a){delete a; });
	delete repo;
}

template<typename T>
bool KeyRepository<T>::deleteElement(int codigo)
{
	Articulo* a = nullptr;
	bool isRemove = elements->remove(createSLambda(codigo), a);
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
bool KeyRepository<T>::addElement(T* articulo)
{
	bool added =elements->addAscendent(articulo);
	if (added) repo->save(articulo);
	return added;
}
template <typename T>
T* KeyRepository<T>::getElement(int codigo) const{

	T* element = nullptr;
	elements->find(createSLambda(codigo), element);

	return  element;
}
template <typename T>
std::function<bool(T*)> KeyRepository<T>::createSLambda(int codigo) const
{
	return [codigo](T* a){ return a->getCodigo() == codigo; };
}
template <typename T>
KeyRepository<T>& KeyRepository<T>::saveUpdates()
{
	repo->update(*elements);
	return *this;
}

