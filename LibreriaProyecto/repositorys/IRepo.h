#pragma once
#include <functional>

template <typename T, typename List = ClinkedList<T, std::function < int(T, T) >>>
class IRepo
{
public:
	virtual ~IRepo(){}

	virtual void update(const List& salvar)=0;
	virtual void save(const T&)=0;
	virtual void readALL(List&, std::function<void(List&,T)>)=0;
};

