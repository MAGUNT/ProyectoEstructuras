#pragma once
#include "..\lists\MultiplyList.h"
#include "IRepo.h"

template <typename T>
class MultiRepo
{
	public:
	using init_list = std::initializer_list < typename MultiplyList<T*>::Comparator > ;
	using MultiplyListFactory = std::function < MultiplyList<T*>*() > ;
private:
	MultiplyList<T*>* elements;
	IRepo<T*, MultiplyList<T*>>* repo;
	MultiplyListFactory factory;
public:
	MultiRepo(MultiplyListFactory, IRepo<T*, MultiplyList<T*>>*);
	~MultiRepo();

	const MultiplyList<T*>& getAll();
	
	template<typename Predicate>
	MultiplyList<T*>* getALL(Predicate p);

	template<typename Predicate>
	T* get(Predicate p);

	void saveALL();
	void addElement(T*);
};


template<typename T>
MultiRepo<T>::MultiRepo(MultiplyListFactory pfactory, IRepo<T*, MultiplyList<T*>>* prepo)
	: factory(pfactory), elements(pfactory()), repo(prepo)
{
	prepo->readALL(*elements, []( MultiplyList<T*> &list, T* e)
	{
		list.add(e);
	});
}
template<typename T>
MultiRepo<T>::~MultiRepo()
{
	elements->foreach([](T* e){delete e; });
	delete repo;
}
template<typename T>
const MultiplyList<T*>& MultiRepo<T>::getAll()
{
	return *elements;
}

template<typename T>
template<typename Predicate>
MultiplyList<T*>* MultiRepo<T>::getALL(Predicate p)
{
	auto mutiL = factory();
	elements->foreach([&p, mutiL](T* e){if (p(e)) mutiL->add(e); });
	return mutiL;
}
template<typename T>
template<typename Predicate>
T* MultiRepo<T>::get(Predicate p)
{
	T* element = nullptr;
	elements->find(p, element);
	return element;
}
template<typename T>
void MultiRepo<T>::saveALL()
{
	repo->update(elements);
}
template<typename T>
void MultiRepo<T>::addElement(T*e)
{
	elements->add(e);
	repo->save(e);
}