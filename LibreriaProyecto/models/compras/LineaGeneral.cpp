/*
 * LineaGeneral.cpp
 *
 *  Created on: Aug 2, 2015
 *      Author: daniel
 */

#include "LineaGeneral.h"

LineaGeneral::LineaGeneral(int _codigo, std::string _nombre): codigo(_codigo), nombre(_nombre) {
	this->lineasEspecificas = new ClinkedList<LineaEspecifica*>();
}

LineaGeneral::~LineaGeneral() {
	delete this->lineasEspecificas;
}

int LineaGeneral::getCodigo() const {
	return codigo;
}

const std::string& LineaGeneral::getNombre() const {
	return nombre;
}

void LineaGeneral::setNombre(const std::string& nombre) {
	this->nombre = nombre;
}

ClinkedList<LineaEspecifica*>* LineaGeneral::getLineasEspecificas() {
	return lineasEspecificas;
}
