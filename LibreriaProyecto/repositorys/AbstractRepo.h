#pragma once
#include "..\lists\ClinkedList.h"
#include <fstream>
#include <sstream>

template<typename T>
class AbstractRepo
{
private:
	std::string path;
	const static char delimiter = 30;
public:

	AbstractRepo(const std::string& path);
	AbstractRepo(std::string&& path);

	void update(const ClinkedList<T>& salvar);
	void save(const T&);
	ClinkedList<T>* readALL();
};

template<typename T>
AbstractRepo<T>::AbstractRepo(const std::string& ppath):path(ppath) {}
template<typename T>
AbstractRepo<T>::AbstractRepo(std::string&& ppath) :path(std::move(ppath)) {}

template<typename T>
void AbstractRepo<T>::update(const ClinkedList<T>& salvar)
{
	std::ofstream out(path);
	salvar.foreach([&out, delimiter](const T&){out << e << delimiter; });
}
template<typename T>
void AbstractRepo<T>::save(const T& e)
{
	std::ofstream out(path, std::ofstream::app);
	out << e << delimiter;
}
template<typename T>
ClinkedList<T>* AbstractRepo<T>::readALL()
{
	auto list = new ClinkedList<T>();
	std::ifstream in(path);
	std::string object;

	while (getline(in, object, delimiter))
	{
		T element;
		std::istringstream in(object);
		in >> element;
		list->addAscendent(element);
	}
	return list;
}