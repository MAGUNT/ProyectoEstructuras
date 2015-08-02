/*
 * Articulo.cpp
 *
 *  Created on: Aug 1, 2015
 *      Author: daniel
 */

#include "Articulo.h"

Articulo::Articulo()
	: codigo(10), precio(500), nombre("Stuff"), marca("Volcom"){}

Articulo::~Articulo() {}

std::ostream& operator <<(std::ostream& os, Articulo& articulo) {
	os << "["
			<< articulo.codigo << ", "
			<< articulo.nombre << ", "
			<< articulo.marca << ", "
			<< articulo.precio << "]" << std::endl;

	return os;
};



