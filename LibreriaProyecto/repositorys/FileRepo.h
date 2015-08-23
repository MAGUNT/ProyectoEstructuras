#pragma once
#include "..\lists\ClinkedList.h"
#include "IRepo.h"
#include <fstream>
#include <sstream>

template<typename T, typename List= ClinkedList<T, std::function<int(T,T)>>>
class FileRepo : public IRepo<T, List>
{
private:
	
	std::string path;
	const static char delimiter = 30;
public:


	FileRepo(const std::string& path);
	FileRepo(std::string&& path);
	~FileRepo() override{}

	void update(const List& salvar) override;
	void save(const T&) override;
	void readALL(List&, std::function<void(List&, T)>) override;
};

template<typename T, typename List>
FileRepo<T, List>::FileRepo(const std::string& ppath):path(ppath) {}
template<typename T, typename List>
FileRepo<T, List>::FileRepo(std::string&& ppath) :path(std::move(ppath)) {}

template<typename T, typename List>
void FileRepo<T, List>::update(const List& salvar)
{
	std::ofstream out(path);
	salvar.foreach([&out](const T& e){out << e << delimiter; });
}
template<typename T, typename List>
void FileRepo<T, List>::save(const T& e)
{
	std::ofstream out(path, std::ofstream::app);
	out << e << delimiter;
}
template<typename T, typename List>
void FileRepo<T, List>::readALL(List& list, std::function<void(List&, T)> func)
{
	std::ifstream in(path);
	std::string object;

	while (getline(in, object, delimiter))
	{
		T element;
		std::istringstream in(object);
		in >> element;
		func(list, element);
	}
}