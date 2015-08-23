/*
 * Local.cpp
 *
 *  Created on: Aug 2, 2015
 *      Author: daniel
 */

#include "Local.h"
#include "../../repositorys/Repositorios.h"


Local::Local() {
	this->categorias = Repositorios::repoCategoria.getElements();
}

Local::~Local() {
	delete this->categorias;
}

void Local::imprimirEstructura() {
	std::ostream os;

	categorias.foreach([os](Categoria* c) {
		os << c->getCodigo() << ". " << c->getNombre() << " [";
		c->getLineaGenerals().foreach([os](LineaGeneral* lg) {
			os<< "   " << lg->getCodigo() << ". " << lg->getNombre();
			lg->getLineasEspecificas().foreach([os](LineaEspecifica* le) {
				os << "      " << lg->getCodigo() << ". " << lg->getNombre();
				le->getArticulos().foreach([os](Articulo* a) {
					os << "          " << a->getCodigo() << ". " << a->getNombre();
				});
			});
		});
		os << "]";
	});
}

Categoria& Local::getCategoria(int codigo) {
	return categorias[codigo];
}

LineaGeneral& Local::getLineaGeneral(int codigo, int categoria) {
	ClinkedList<LineaGeneral*> lineas = getLineasGenerales(categoria);

	lineas.foreach([](LineaGeneral* l) {
		if(l->getCodigo() == codigo) {
			return l;
		}
	});

	return nullptr;
}

LineaEspecifica& Local::getLineaEspecifica(LineaGeneral* lineaGeneral, int codigo) {
	ClinkedList<LineaEspecifica*> lineas = getLineasEspecificas(lineaGeneral);

	lineas.foreach([](LineaEspecifica* l) {
		if(l->getCodigo() == codigo) {
			return l;
		}
	});

	return nullptr;
}

Articulo& Local::getArticulo(LineaEspecifica* lineaEspecifica, int codigo) {
	ClinkedList<Articulo*> articulos = getArticulos(lineaEspecifica);

	articulos.foreach([](Articulo* a) {
		if(a->getCodigo() == codigo) {
			return a;
		}
	});

	return nullptr;

}

const ClinkedList<LineaGeneral*>& Local::getLineasGenerales(int categoria) {
	return &getCategoria(categoria).getLineaGenerals();
}

const ClinkedList<LineaEspecifica*>& Local::getLineasEspecificas(LineaGeneral* lineaGeneral) {
	return lineaGeneral->getLineasEspecificas();
}

const ClinkedList<Articulo*>& Local::getArticulos(LineaEspecifica* lineaEspecifica) {
	return lineaEspecifica->getArticulos();
}




