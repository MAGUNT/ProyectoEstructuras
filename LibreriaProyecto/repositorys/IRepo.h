#pragma once

template <typename T>
class IRepo
{
public:
	virtual ~IRepo(){}

	virtual void update(const ClinkedList<T>& salvar)=0;
	virtual void save(const T&)=0;
	virtual ClinkedList<T>* readALL()=0;
};

