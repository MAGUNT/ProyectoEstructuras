// LibreriaProyecto.cpp: define el punto de entrada de la aplicación de consola.
//
#include "Comparators.h"
#include "ClinkedList.h"
#include <tchar.h>
#include <tuple>
#include "MultiplyList.h"
#include <vector>
#include <algorithm>
#include <iostream>


void pruebaListaMultiply()
{

	using str = std::tuple < int, char, std::string >;
	std::tuple<int, char, std::string> foo(10, 'x', "hola");



	MultiplyList<str> list =
	{

		[](str x, str y)
		{
			if (std::get<0>(y) < std::get<0>(x))return 1;
			if (std::get<0>(x) < std::get<0>(y))return -1;
			return 0;
		},
			[](str x, str y)
		{
			if (std::get<1>(y) < std::get<1>(x))return 1;
			if (std::get<1>(x) < std::get<1>(y))return -1;
			return 0;
		},
			[](str x, str y)
		{
			if (std::get<2>(y) < std::get<2>(x))return 1;
			if (std::get<2>(x) < std::get<2>(y))return -1;
			return 0;
		}


	};

	std::vector<std::string> vecS = { "dfsf", "atsdfds", "ggg", "hhh", "qqq", "sdad", "asdda", "dsfdsf", "dsffsf" };
	std::vector<char> vecC = { 'r', 'o', 'l', 'u', 'f', 'r', 'p', 'w', 'k' };


	unsigned min = std::min(vecS.size(), vecC.size());
	for (unsigned i = 0; i < min; ++i)
	{
		int random = std::rand() % min;
		list.add(str(random + i, vecC[random], vecS[random]));
	}

	for (unsigned i = 0; i < 3; ++i)
	{
		std::cout << "Criterio # " << i << std::endl;

		list.foreach(i,
			[](str x)
		{
			std::cout << std::get<0>(x)
				<< " " << std::get<1>(x)
				<< " " << std::get<2>(x).c_str()
				<< " " << std::endl;
		});

	}

	list.remove([](str x){ return std::get<0>(x) == 6; });
	std::cout << "Despues" << std::endl << std::endl;
	for (unsigned i = 0; i < 3; ++i)
	{
		std::cout << "Criterio # " << i << std::endl;

		list.foreach(i,
			[](str x)
		{
			std::cout << std::get<0>(x)
				<< " " << std::get<1>(x)
				<< " " << std::get<2>(x).c_str()
				<< " " << std::endl;
		});

	}


	system("pause");

}

int _tmain(int argc, _TCHAR* argv[])
{
	


	
	ClinkedList<int> list;
	list.addFist(1000);
	for (unsigned i = 0; i < 20; ++i)
	{
		list.addDescendent(std::rand()%50);
	}

	std::cout << list.addDescendent(1);
	list.addFist(1000);
	list.addFist(1000);

	list.foreach([](int x){std::cout << x<<", "; });
	std::cout << std::endl;


	list.clear();
	list.foreach([](int x){std::cout << x << ", "; });
	std::cout << std::endl;
	system("pause");


}



