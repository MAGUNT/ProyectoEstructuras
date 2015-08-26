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
#include "repositorys\FileRepo.h"
#include "repositorys\Repositorios.h"
#include "models\compras\LineaEspecifica.h"
#include "Gestores\GestorUsuarios.h"
#include "Gestores\GestorLineasDeAriculos.h"
#include "ui/InterfazGrafica.h"

using str = std::tuple < int, char, std::string >;

void pruebaListaMultiply(MultiplyList<str>* list)
{

	
	

	std::vector<std::string> vecS = { "bb","aa","ccc","dfsf", "atsdfds", "ggg", "hhh", "qqq", "sdad", "asdda", "dsfdsf", "dsffsf" };
	std::vector<char> vecC = { 'a','b','c','r', 'o', 'l', 'u', 'f', 'r', 'p', 'w', 'k' };


	unsigned min = std::min(vecS.size(), vecC.size());
	for (unsigned i = min-1; i !=0; --i)
	{
		
		list->add(str(i, vecC[i], vecS[i]));
	}

	for (unsigned i = 0; i < 4; ++i)
	{
		std::cout << "Criterio # " << i << std::endl;

		list->foreach(
			[](str x)
		{
			std::cout << std::get<0>(x)
				<< " " << std::get<1>(x)
				<< " " << std::get<2>(x).c_str()
				<< " " << std::endl;
		},i);

	}
	
	list->remove([](str x){ return std::get<0>(x) == 6; });
	std::cout << "Despues" << std::endl << std::endl;
	for (unsigned i = 0; i < 3; ++i)
	{
		std::cout << "Criterio # " << i << std::endl;

		list->foreach(
			[](str x)
		{
			std::cout << std::get<0>(x)
				<< " " << std::get<1>(x)
				<< " " << std::get<2>(x).c_str()
				<< " " << std::endl;
		},i);

	}


	

}

void testClear()
{
	auto list = new MultiplyList<str>
	({

		
		[](str x, str y)
		{
			if (std::get<1>(y) < std::get<1>(x))return 1;
			if (std::get<1>(x) < std::get<1>(y))return -1;
			return 0;
		},
			[](str x, str y)
		{
			if (std::get<0>(y) < std::get<0>(x))return 1;
			if (std::get<0>(x) < std::get<0>(y))return -1;
			return 0;
		},
		[](str x, str y)
		{
			if (std::get<2>(y) < std::get<2>(x))return 1;
			if (std::get<2>(x) < std::get<2>(y))return -1;
			return 0;
		}


	},1);

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

//	for (int i = 0; i < 20; ++i)
//		lista->addDescendent(new Articulo(i, std::to_string(i)));

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
	
	
	InterfazGrafica* ui = new InterfazGrafica();
	ui->inicializar();
	
	delete ui;
	
	/*
	GestorUsuarios g;

	GestorLineasDeAriculos gA;

	std::cout << gA.getCategoria(23);
	*/
	/*
	 * 	testClear();
	GestorUsuarios e;
	e.crearUsuario(new Usuario(1, "melvin", "43243", "porahi", "34243", Rol::CLIENTE));
	e.crearCarrito(new Carrito(3, 1, "Compras de la abuela"));
	
	MultiplyList<Carrito*>* list= e.getCarritosDeCliente(1);

	list->foreach([](Carrito* c){ std::cout << c; });
	*/
	/*
	MultiRepo<Articulo> fuck(
	{
		[](Articulo* a, Articulo *b){ return 2; }
	} 
	, new FileRepo<Articulo*, MultiplyList<Articulo*>>("fyckk"));

	fuck.addElement(new Articulo());
	fuck.get([](Articulo*a){return a->getCodigo() == 0; });
	**/
	/*

	auto func = [](Articulo* a, Articulo* b)
	{
		if (a->getNombre() < b->getNombre()) return  -1;
		if (b->getNombre() < a->getNombre()) return  1;
		return 0;
	};

	auto list = new ClinkedList<Articulo*, std::function<int(Articulo*, Articulo*)>>(func);

	pruebaListaCircular2(list);
	*/
	/*
	UITest* uitest = new UITest();
	uitest->testUI();

	delete uitest;
	return 0;
	*/

	/*
	FileRepo<Articulo*> articulos("articulos");

	ClinkedList<Articulo*> lista = {
		new Articulo(34, "Tuncado", "fuck face buejajaj", 12.033),
		new Articulo(1, "shiitt", "shit shit shit", 66.45435)
	};
	articulos.update(lista);
	*/
//	MultiplyList<Carrito*> carrito = Repositorios::getCarritosCriterio();
	
	//GestorLineasDeAriculos g;

	//g.eliminarArticulo(4);
	
	/*
	Articulo *s1, *s2, *s3, *s4, *s5;
	Repositorios::repoArticulo.addElement(s1=new Articulo(2, "Sopa", "Nodules", 1000.8));
	Repositorios::repoArticulo.addElement(s2=new Articulo(3, "Risoto", "BAMBINO", 1000.8));
	Repositorios::repoArticulo.addElement(s3=new Articulo(4, "Cervesa", "IMPERIAL", 1000.8));
	Repositorios::repoArticulo.addElement(s4=new Articulo(5, "Cervesa", "PILSEN", 1000.8));
	Repositorios::repoArticulo.addElement(s5=new Articulo(6, "Cervesa", "QUILMES", 1000.8));


	LineaEspecifica *linea1 = new LineaEspecifica(44, "Cervesas");
	LineaEspecifica *linea2 = new LineaEspecifica(43, "Comidas");

	linea2->agregarArticulo(s1);
	linea2->agregarArticulo(s2);
	linea1->agregarArticulo(s3);
	linea1->agregarArticulo(s4);
	linea1->agregarArticulo(s5);

	Repositorios::repoLineaEspecifica.addElement(linea1);
	Repositorios::repoLineaEspecifica.addElement(linea2);

	
	LineaGeneral *genral = new LineaGeneral(22,"Alimentos");
	Categoria *cat = new Categoria(23, 1,"Comestibles");

	genral->agregarLineaEspecifica(linea1);
	genral->agregarLineaEspecifica(linea2);

	Repositorios::repoLineaGeneral.addElement(genral);
	cat->agregarLineaGeneral(genral);
	Repositorios::repoCategoria.addElement(cat);
	*/
	/*
	Repositorios::repoUsuario.addElement(new Usuario(6, "MikeTyson", "12345", "MGMGRAND", "eatchildren", Rol::ADMIN));
	Repositorios::repoUsuario.addElement(new Usuario(8, "PEPE", "12345", "PORAHI", "hola", Rol::DEPENDIENTE));
	*/
	system("pause");
}



