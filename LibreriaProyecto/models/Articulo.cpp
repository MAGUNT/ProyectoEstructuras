/*
 * Articulo.cpp
 *
 *  Created on: Aug 1, 2015
 *      Author: daniel
 */

#include "Articulo.h"

Articulo::Articulo()
	: codigo(-1), precio(0), nombre("nulo"), marca("nulo"){}

Articulo::~Articulo() {}

int Articulo::getCodigo() {
	return this->codigo;
}

void Articulo::setCodigo(int codigo) {
	this->codigo = codigo;
}

int Articulo::getPrecio() {
	return this->precio;
}

void Articulo::setPrecio(int codigo) {
	this->codigo = codigo;
}

std::string Articulo::getNombre() {
	return this->nombre;
}

void Articulo::setNombre(std::string nombre) {
	this->nombre = nombre;
}

std::string Articulo::getMarca() {
	return this->marca;
}

void Articulo::setMarca(std::string marca) {
	this->marca = marca;
}

std::ostream& operator <<(std::ostream& os, Articulo& articulo) {
	os << "["
			<< articulo.codigo << ", "
			<< articulo.nombre << ", "
			<< articulo.marca << ", "
			<< articulo.precio << "]" << std::endl;

	return os;
};



