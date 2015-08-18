/*
 * Pedido.cpp
 *
 *  Created on: Aug 1, 2015
 *      Author: daniel
 */

#include "Pedido.h"
#include <iostream>
#include <typeinfo>

Pedido::Pedido(Articulo* _articulo, int _cantidad): articulo(_articulo), cantidad(_cantidad) {}


const Articulo* Pedido::getArticulo() const {
	return articulo;
}

void Pedido::setArticulo(Articulo* articulo) {
	this->articulo = articulo;
}

int Pedido::getCantidad() const {
	return cantidad;
}

void Pedido::setCantidad(int cantidad) {
	this->cantidad = cantidad;
}

long double Pedido::precio() const {
	return articulo->getPrecio() * cantidad;
}
