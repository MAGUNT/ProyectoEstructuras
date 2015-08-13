/*
 * Local.cpp
 *
 *  Created on: Aug 2, 2015
 *      Author: daniel
 */

#include "Local.h"

Local::Local() {
	this->lineasGenerales = new ClinkedList<LineaGeneral*>();
	this->categorias = {
			"1. Abarrotes",
			"2. Bebidas Alcoholicas",
			"3. Comida Preparada"
	};

	this->armarLineas();
}

Local::~Local() {
	delete this->lineasGenerales;
}

const std::vector<std::string> Local::getCategorias() {
	return this->categorias;
}

/*
 * 	Esto esta pesimo, tengo que buscar la manera de como proveer una
 * 	interfaz para construir todas las estructuras apartir de datos en strings
 */

void Local::armarLineas() {
	Articulo* articulo;
	LineaEspecifica* lineaEspecifica;

	//	Abarrotes
	string_vect lineasGeneralesAbarrotes = {"Aderezos, Salsas y Dips", "Cereales y Pastas", "Cigarros Puros y Tabaco"};

	//	Lineas especificas de Aderezos, Salsa y Dips
	string_vect lineaE1Abarrotes = {"Aderezos para Ensalada", "Antipasto", "Vinagres"};

	//	Articulos de Aderezos para Ensalada
	string_vect lineaE1Articulos1 = {"Imitacion de Tocino", "Aderezo Vinagreta", "Aderezo Chipotle"};

	//	Articulos de Antipasto
	string_vect lineaE1Articulos2 = {"Antipasto Chile Rojo"};

	//	Articulos de Vinagres
	string_vect lineaE1Articulos3 = {"Vinagre Balsamico", "Vinagre Blanco"};

	LineaGeneral* lineaG1 = new LineaGeneral(1, lineasGeneralesAbarrotes[0]);

	ClinkedList<Articulo*>* listArticulos1 = crearArticulos(lineaE1Articulos1);
	ClinkedList<Articulo*>* listArticulos2 = crearArticulos(lineaE1Articulos2);
	ClinkedList<Articulo*>* listArticulos3 = crearArticulos(lineaE1Articulos3);

	ClinkedList<LineaEspecifica*>* listLineasEspecificas = crearLineasEspecificas(lineaE1Abarrotes);

	lineaEspecifica = (*listLineasEspecificas)[0];
	articulo = (*listArticulos1)[0];
	lineaEspecifica->getArticulos()->addLast(articulo);
	articulo = (*listArticulos1)[1];
	lineaEspecifica->getArticulos()->addLast(articulo);
	articulo = (*listArticulos1)[2];
	lineaEspecifica->getArticulos()->addLast(articulo);
	lineaG1->getLineasEspecificas()->addLast(lineaEspecifica);



	lineaEspecifica = (*listLineasEspecificas)[1];
	articulo = (*listArticulos2)[0];
	lineaEspecifica->getArticulos()->addLast(articulo);
	lineaG1->getLineasEspecificas()->addLast(lineaEspecifica);



	lineaEspecifica = (*listLineasEspecificas)[2];
	articulo = (*listArticulos3)[0];
	lineaEspecifica->getArticulos()->addLast(articulo);
	articulo = (*listArticulos3)[1];
	lineaEspecifica->getArticulos()->addLast(articulo);
	lineaG1->getLineasEspecificas()->addLast(lineaEspecifica);


	this->lineasGenerales->addLast(lineaG1);

/*
 *
	string_vect lineaE2Abarrotes = {
			"Cereales con fruta", "Lasagna y Gnochi", "Pastas Largas"
	};

	string_vect lineaE3Abarrotes = {
			"Cigarros", "Puros", "Encendedores"
	};
 *
 *
 * Bebidas Alcoholicas
	string_vect lineasGeneralesAlcohol = {
			"Cerveza", "Licores y Destilados", "Otros Vinos"
	};


	//	Comida Preparada
	string_vect lineasGeneralesComidaPrep = {
			"Postres", "Cafeteria", "Congelados"
	};
*/

}

ClinkedList<LineaEspecifica*>* Local::crearLineasEspecificas(string_vect nombres) {
	ClinkedList<LineaEspecifica*>* lineasEspecificas = new ClinkedList<LineaEspecifica*>();

	for(unsigned i = 0; i < nombres.size(); i++) {
		LineaEspecifica* x = new LineaEspecifica(i, nombres[i]);
		lineasEspecificas->addLast(x);
	}

	return lineasEspecificas;
}

ClinkedList<Articulo*>* Local::crearArticulos(string_vect nombres) {
	ClinkedList<Articulo*>* listaArticulos = new ClinkedList<Articulo*>();

	for (unsigned i = 0; i < nombres.size(); i++) {
		Articulo* x = new Articulo(i, nombres[i]);
		listaArticulos->addLast(x);
	}

	return listaArticulos;
}

void Local::imprimirEstructura() {
	LineaGeneral* lineaGeneralTemp = 0;
	LineaEspecifica* lineaEspecificaTemp = 0;
	Articulo* articuloTemp = 0;

	std::cout << "Lineas Generales = {" << std::endl;
	for (unsigned i = 0; i < this->lineasGenerales->length(); i++) {
		lineaGeneralTemp = (*lineasGenerales)[i];
		std::cout << "	*Categoria " << this->categorias[i] << "*:  " << lineaGeneralTemp->getNombre() << " = { " << std::endl;

		for (unsigned j = 0; j < lineaGeneralTemp->getLineasEspecificas()->length(); ++j) {
			lineaEspecificaTemp = (*lineaGeneralTemp->getLineasEspecificas())[j];
			std::cout << "		" << lineaEspecificaTemp->getNombre() << " = { " << std::endl;

			for (unsigned k = 0; k < lineaEspecificaTemp->getArticulos()->length(); ++k) {
				articuloTemp = (*lineaEspecificaTemp->getArticulos())[k];
				std::cout << "			" << *articuloTemp << std::endl;
			}
			std::cout << "		}" << std::endl;
		}
		std::cout << "	}" << std::endl;
	}

}

/*
 * 	Codigo en realidad es el indice de la posicion de la LineaGeneral en la lista
 */
LineaGeneral* Local::getLineaGeneral(int codigo, int categoria) {
	ClinkedList<LineaGeneral*>* lineas = this->getLineasGenerales(categoria);


	if(codigo > 0 && codigo <= lineas->length()) {
		return (*lineasGenerales)[codigo-1];
	} else {
		return 0;
	}
}

/*
 * 	Codigo en realidad es el indice de la posicion de la LineaEspecifica en la lista
 */
LineaEspecifica* Local::getLineaEspecifica(LineaGeneral* lineaGeneral, int codigo) {
	if(codigo > 0 && codigo <= lineaGeneral->getLineasEspecificas()->length()) {
		return (*lineaGeneral->getLineasEspecificas())[codigo-1];
	} else {
		return 0;
	}
}

Articulo* Local::getArticulo(LineaEspecifica* lineaEspecifica, int codigo) {
	if(codigo > 0 && codigo <= lineaEspecifica->getArticulos()->length()) {
		return (*lineaEspecifica->getArticulos())[codigo-1];
	} else {
		return 0;
	}
}

/*
 * 	Retorna una lista con las lineas generales de una categoria (pasillo)
 */
ClinkedList<LineaGeneral*>* Local::getLineasGenerales(int categoria) {
	ClinkedList<LineaGeneral*>* lineas = new ClinkedList<LineaGeneral*>();

	for(unsigned i = 0; i < lineasGenerales->length(); i++) {
		if((*lineasGenerales)[i]->getCodigo() == categoria) {
			lineas->addLast((*lineasGenerales)[i]);
		}
	}

	return lineas;
}

ClinkedList<LineaEspecifica*>* Local::getLineasEspecificas(LineaGeneral* lineaGeneral) {
	return lineaGeneral->getLineasEspecificas();
}

ClinkedList<Articulo*>* Local::getArticulos(LineaEspecifica* lineaEspecifica) {
	return lineaEspecifica->getArticulos();
}




