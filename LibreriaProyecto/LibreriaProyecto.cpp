// LibreriaProyecto.cpp: define el punto de entrada de la aplicaci�n de consola.
//
#include <tuple>
#include <vector>
#include <algorithm>
#include <iostream>
#include "utils/Comparators.h"
#include "lists/ClinkedList.h"
#include "lists/MultiplyList.h"
#include "models/compras/Articulo.h"
#include "models/compras/Pedido.h"
#include "models/compras/Inventario.h"

#include "tests/UITest.h"
using str = std::tuple < int, char, std::string >;

void pruebaListaMultiply(MultiplyList<str>* list)
{

	
	

	std::vector<std::string> vecS = { "bb","aa","ccc","dfsf", "atsdfds", "ggg", "hhh", "qqq", "sdad", "asdda", "dsfdsf", "dsffsf" };
	std::vector<char> vecC = { 'a','b','c','r', 'o', 'l', 'u', 'f', 'r', 'p', 'w', 'k' };


	unsigned min = std::min(vecS.size(), vecC.size());
	for (unsigned i = 0; i < min; ++i)
	{
		
		list->add(str(i, vecC[i], vecS[i]));
	}

	for (unsigned i = 0; i < 3; ++i)
	{
		std::cout << "Criterio # " << i << std::endl;

		list->foreach(i,
			[](str x)
		{
			std::cout << std::get<0>(x)
				<< " " << std::get<1>(x)
				<< " " << std::get<2>(x).c_str()
				<< " " << std::endl;
		});

	}
	
	list->remove([](str x){ return std::get<0>(x) == 6; });
	std::cout << "Despues" << std::endl << std::endl;
	for (unsigned i = 0; i < 3; ++i)
	{
		std::cout << "Criterio # " << i << std::endl;

		list->foreach(i,
			[](str x)
		{
			std::cout << std::get<0>(x)
				<< " " << std::get<1>(x)
				<< " " << std::get<2>(x).c_str()
				<< " " << std::endl;
		});

	}


	

}

void testClear()
{
	auto list = new MultiplyList<str>
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

	pruebaListaMultiply(list);
	list->clear();
	pruebaListaMultiply(list);
	system("pause");
}

template<typename F>
void imprimirLista(ClinkedList<Articulo*,F>* lista)
{

	lista->foreach([](Articulo* a)
	{
		std::cout << "Codigo: " << a->getCodigo()
			<< ", Nombre: " << a->getNombre() << std::endl;
	});
}

//Aprobado.
void pruebaListaCircular(ClinkedList<Articulo*>* lista)
{
	for (int i = 0; i < 20; ++i)
		lista->addLast(new Articulo(i, "dfef"));

	bool seRemovio= lista->remove([](Articulo* a){ return a->getCodigo() == 6; });
	std::cout << (seRemovio ? "Si" : "No") << std::endl;

	Articulo * a = nullptr;
	bool seRemovio2 = lista->remove([](Articulo* a){ return a->getCodigo() == 7; },a );

	std::cout << "Se elimino: " << (seRemovio ? "Si" : "No") << std::endl;
	if (seRemovio2)
	{
		std::cout << "Codigo: " << a->getCodigo()
			<< ", Nombre: " << a->getNombre() << std::endl;
	}
	imprimirLista(lista);

	
	delete lista;

}

template<typename F>
void pruebaListaCircular2(ClinkedList<Articulo*, F>* lista)
{

	for (int i = 0; i < 20; ++i)
		lista->addDescendent(new Articulo(i, std::to_string(i)));

	bool existe = lista->addDescendent(new Articulo(10, "20"));

	std::cout << "Se inserto? " << (existe ? "si" : "no") << std::endl;

	Articulo* a = new Articulo(2, "nuevo");
	bool remplasado = lista->replace(a, [](Articulo* a){return a->getNombre() == "4"; });

	std::cout << a->getNombre() << "Se remplaso? " << (remplasado ? "si" : "no") << std::endl;

	imprimirLista(lista);

}

template<typename F>
void pruebaListaCircular3(ClinkedList<Articulo*,F>* list)
{
	
}

int main()
{
	auto func = [](Articulo* a, Articulo* b)
	{
		if (a->getNombre() < b->getNombre()) return  -1;
		if (b->getNombre() < a->getNombre()) return  1;
		return 0;
	};

	auto list = new ClinkedList<Articulo*, std::function<int(Articulo*, Articulo*)>>(func);

	pruebaListaCircular2(list);
	/*
	UITest* uitest = new UITest();
	uitest->testUI();

	delete uitest;
	return 0;
	*/
	system("pause");
}



