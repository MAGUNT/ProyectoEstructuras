/*
 * Local.cpp
 *
 *  Created on: Aug 2, 2015
 *      Author: daniel
 */

#include "Local.h"
#include "../../repositorys/Repositorios.h"


Local::Local() {
	this->categorias = Repositorios::repoCategoria;
}

Local::~Local() {
	delete this->categorias;
}

void Local::imprimirEstructura() {
	LineaGeneral* lineaGeneralTemp = 0;
	LineaEspecifica* lineaEspecificaTemp = 0;
	Articulo* articuloTemp = 0;

	std::cout << "Lineas Generales = {" << std::endl;
	for (unsigned i = 0; i < this->lineasGenerales->length(); i++) {
		lineaGeneralTemp = (*lineasGenerales)[i];
		std::cout << "	*Categoria " << this->categorias[i] << "*:  " << lineaGeneralTemp->getNombre() << " = { " << std::endl;

		for (unsigned j = 0; j < lineaGeneralTemp->getLineasEspecificas().length(); ++j) 
		{
			lineaEspecificaTemp = (lineaGeneralTemp->getLineasEspecificas())[j];
			std::cout << "		" << lineaEspecificaTemp->getNombre() << " = { " << std::endl;

			for (unsigned k = 0; k < lineaEspecificaTemp->getArticulos().length(); ++k) 
			{
				articuloTemp = (lineaEspecificaTemp->getArticulos())[k];
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
	ClinkedList<LineaGeneral*>* lineas = getLineasGenerales(categoria);


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
	if(codigo > 0 && codigo <= lineaGeneral->getLineasEspecificas().length()) {
		return (lineaGeneral->getLineasEspecificas())[codigo-1];
	} else {
		return 0;
	}
}

Articulo* Local::getArticulo(LineaEspecifica* lineaEspecifica, int codigo) {
	if(codigo > 0 && codigo <= lineaEspecifica->getArticulos().length()) {
		return (lineaEspecifica->getArticulos())[codigo-1];
	} else {
		return 0;
	}

}

/*
 * 	Retorna una lista con las lineas generales de una categoria (pasillo)
 */
const ClinkedList<LineaGeneral*>& Local::getLineasGenerales(int categoria) {
	return &getCategoria(categoria)->getLineaGenerals();
}

const ClinkedList<LineaEspecifica*>& Local::getLineasEspecificas(LineaGeneral* lineaGeneral) {
	return lineaGeneral->getLineasEspecificas();
}

const ClinkedList<Articulo*>& Local::getArticulos(LineaEspecifica* lineaEspecifica) {
	return lineaEspecifica->getArticulos();
}




