/*
 * Local.cpp
 *
 *  Created on: Aug 2, 2015
 *      Author: daniel
 */

#include "Local.h"
#include "../../repositorys/Repositorios.h"


Local::Local() {
	this->categorias = *Repositorios::repoCategoria.getElements();
}

Local::~Local() {}

void Local::imprimirEstructura() {
	categorias.foreach([](Categoria* c) {
		std::cout << c->getCodigo() << ". " << c->getNombre() << " [";
		c->getLineaGenerals().foreach([](LineaGeneral* lg) {
			std::cout<< "   " << lg->getCodigo() << ". " << lg->getNombre();
			lg->getLineasEspecificas().foreach([](LineaEspecifica* le) {
				std::cout << "      " << le->getCodigo() << ". " << le->getNombre();
				le->getArticulos().foreach([](Articulo* a) {
					std::cout << "          " << a->getCodigo() << ". " << a->getNombre();
				});
			});
		});
		std::cout << "]";
	});
}

Categoria& Local::getCategoria(int codigo) {
	return *categorias[codigo];
}

LineaGeneral& Local::getLineaGeneral(int codigo) {
	return *Repositorios::repoLineaGeneral.getElement(codigo);
}

LineaGeneral& Local::getLineaGeneral(int codigo, int categoria) {
	ClinkedList<LineaGeneral*> lineas = getLineasGenerales(categoria);
	LineaGeneral* lg = 0;

	lineas.foreach([codigo, &lg](LineaGeneral* l) {
		if(l->getCodigo() == codigo) {
			lg = l;
		}
	});

	return *lg;
}

LineaEspecifica& Local::getLineaEspecifica(int codigo) {
	return *Repositorios::repoLineaEspecifica.getElement(codigo);
}

LineaEspecifica& Local::getLineaEspecifica(LineaGeneral* lineaGeneral, int codigo) {
	ClinkedList<LineaEspecifica*> lineas = getLineasEspecificas(lineaGeneral);
	LineaEspecifica* le = 0;

	lineas.foreach([codigo, &le](LineaEspecifica* l) {
		if(l->getCodigo() == codigo) {
			le = l;
		}
	});

	return *le;
}

Articulo& Local::getArticulo(int codigo) {
	return *Repositorios::repoArticulo.getElement(codigo);
}

void Local::agregarCategoria(Categoria* categoria) {
	this->categorias.addLast(categoria);
}

Articulo& Local::getArticulo(LineaEspecifica* lineaEspecifica, int codigo) {
	ClinkedList<Articulo*> articulos = getArticulos(lineaEspecifica);
	Articulo* art = 0;

	articulos.foreach([codigo, &art](Articulo* a) {
		if(a->getCodigo() == codigo) {
			art = a;
		}
	});

	return *art;
}

const ClinkedList<LineaGeneral*>& Local::getLineasGenerales(int categoria) {
	return getCategoria(categoria).getLineaGenerals();
}

const ClinkedList<LineaEspecifica*>& Local::getLineasEspecificas(LineaGeneral* lineaGeneral) {
	return lineaGeneral->getLineasEspecificas();
}

const ClinkedList<Articulo*>& Local::getArticulos(LineaEspecifica* lineaEspecifica) {
	return lineaEspecifica->getArticulos();
}

//implementar
const ClinkedList<Categoria*>& Local::getCategorias()
{
	return ClinkedList<Categoria*>();
}