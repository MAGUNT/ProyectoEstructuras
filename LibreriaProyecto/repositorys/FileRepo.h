#pragma once
#include "..\lists\ClinkedList.h"
#include "IRepo.h"
#include <fstream>
#include <sstream>

template<typename T>
class FileRepo : public IRepo<T>
{
private:
	std::string path;
	const static char delimiter = 30;
public:

	FileRepo(const std::string& path);
	FileRepo(std::string&& path);
	virtual ~FileRepo() override{}

	virtual void update(const ClinkedList<T>& salvar) override;
	virtual void save(const T&) override;
	virtual ClinkedList<T>* readALL() override;
};

template<typename T>
FileRepo<T>::FileRepo(const std::string& ppath):path(ppath) {}
template<typename T>
FileRepo<T>::FileRepo(std::string&& ppath) :path(std::move(ppath)) {}

template<typename T>
void FileRepo<T>::update(const ClinkedList<T>& salvar)
{
	std::ofstream out(path);
	salvar.foreach([&out](const T& e){out << e << delimiter; });
}
template<typename T>
void FileRepo<T>::save(const T& e)
{
	std::ofstream out(path, std::ofstream::app);
	out << e << delimiter;
}
template<typename T>
ClinkedList<T>* FileRepo<T>::readALL()
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