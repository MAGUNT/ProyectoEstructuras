/*
 * Articulo.cpp
 *
 *  Created on: Aug 1, 2015
 *      Author: daniel
 */

#include "Articulo.h"

Articulo::Articulo(int _codigo, const std::string& _nombre)
	: Articulo(_codigo, _nombre, "", 0.0 ){}

Articulo::Articulo(int _codigo, const std::string& _nombre,
    const std::string& _marca, long double _precio) 
    : codigo(_codigo), precio(_precio), nombre(_nombre), marca(_marca){}

int Articulo::getCodigo() const {
	return this->codigo;
}

void Articulo::setCodigo(int codigo) {
	this->codigo = codigo;
}

long double Articulo::getPrecio()const {
	return this->precio;
}

void Articulo::setPrecio(int codigo) {
	this->codigo = codigo;
}

const std::string& Articulo::getNombre() const{
	return this->nombre;
}

void Articulo::setNombre(const std::string& nombre) {
	this->nombre = nombre;
}

std::string Articulo::getMarca()const {
	return this->marca;
}

void Articulo::setMarca(const std::string& marca) {
	this->marca = marca;
}



