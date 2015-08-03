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

int Articulo::getCodigo() const {
	return this->codigo;
}

void Articulo::setCodigo(int codigo) {
	this->codigo = codigo;
}

int Articulo::getPrecio()const {
	return this->precio;
}

void Articulo::setPrecio(int codigo) {
	this->codigo = codigo;
}

std::string Articulo::getNombre() const{
	return this->nombre;
}

void Articulo::setNombre(std::string nombre) {
	this->nombre = nombre;
}

std::string Articulo::getMarca()const {
	return this->marca;
}

void Articulo::setMarca(std::string marca) {
	this->marca = marca;
}



