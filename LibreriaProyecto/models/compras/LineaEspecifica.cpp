/*
 * LineaEspecifica.cpp
 *
 *  Created on: Aug 2, 2015
 *      Author: daniel
 */

#include "LineaEspecifica.h"

LineaEspecifica::LineaEspecifica(int _codigo, std::string _nombre): codigo(_codigo), nombre(_nombre) {
	articulos = new ClinkedList<Articulo*>();
}

LineaEspecifica::~LineaEspecifica() {
	delete articulos;
}

int LineaEspecifica::getCodigo() const {
	return codigo;
}

void LineaEspecifica::setCodigo(int codigo) {
	this->codigo = codigo;
}

const std::string& LineaEspecifica::getNombre() const {
	return nombre;
}

void LineaEspecifica::setNombre(const std::string& nombre) {
	this->nombre = nombre;
}

ClinkedList<Articulo*>* LineaEspecifica::getArticulos() {
	return articulos;
}
