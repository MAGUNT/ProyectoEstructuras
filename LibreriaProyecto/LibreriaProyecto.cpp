// LibreriaProyecto.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include "ClinkedList.h"

template<typename T, typename F> int comparar(const T &, const T &, F);
template<typename T, typename F>  int comparar(const T*, const T*);
template<typename T, typename F>  int comparar(T*, T*);
template<typename T, typename F>  int comparar(std::shared_ptr<T> a, std::shared_ptr<T> b, F);

void print(const char* info)
{
	std::cout << info << std::endl;
}

template<typename T>
int comparar(const T &a, const T &b)
{
	print("no un puntero");
	std::less<T> func;

	if (func(a, b)) return -1;
	if (func(b, a)) return 1;
	return 0;
}

template<typename T>
int comparar(const T* a, const T* b)
{
	print("es un puntero");
	return comparar(*a, *b);
}

template<typename T>
int comparar(T* a, T* b)
{
	print("es un puntero");
	return comparar(*a, *b);
}

template<typename T>
int comparar(std::shared_ptr<T> a, std::shared_ptr<T> b)
{
	print("es un puntero inteligente");
	return comparar(*a, *b, func);
}
int _tmain(int argc, _TCHAR* argv[])
{
	int n = 0;
	int n2 = 2;
	const int* o = &n;
	const int *e = &n2;
	const int** g = &e;
	//hola(g, g);
	comparar(o, e);
	
	/*
	ClinkedList<std::string> *list = new ClinkedList<std::string>();

	list->add(0,"cero");
	list->addLast("uno");
	list->addLast("dos");
	list->addLast("tres");
	list->addLast("cuatro");
	list->addLast("cinco");
	list->addLast("sies");
	list->addLast("siete");
	list->addLast("ocho");
	list->addLast("nueve");
	list->addLast("dies");


	std::string s= ((*list)[11]);

	std::cout << s << std::endl;
	*/
	system("pause");

}

