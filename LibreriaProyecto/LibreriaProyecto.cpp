// LibreriaProyecto.cpp: define el punto de entrada de la aplicación de consola.
//
#include "Comparators.h"
#include "ClinkedList.h"
#include <tchar.h>


int _tmain(int argc, _TCHAR* argv[])
{
	ClinkedList<int> list;

	list.add(4, 5);
	list.addAfter(10,[](int r){return true; });
	list.addAscendent(200);

	list[2] = 4;


}

