/*
 * Carrito.cpp
 *
 *  Created on: Aug 10, 2015
 *      Author: daniel.hernandez
 */

#include <iostream>
#include "Carrito.h"

Carrito::Carrito() : nombre(), estaPago()  {
	productos = new ClinkedList<Pedido*>();
}

Carrito::~Carrito() {}

bool Carrito::isEstaPago() const {
	return estaPago;
}

void Carrito::setEstaPago(bool estaPago) {
	this->estaPago = estaPago;
}

const std::string& Carrito::getNombre() const {
	return nombre;
}

void Carrito::setNombre(const std::string& nombre) {
	this->nombre = nombre;
}

ClinkedList<Pedido*>* Carrito::getProductos() const {
	return productos;
}

double Carrito::precio() {
	double precio = 0;

	for (int i = 0; i < productos->length(); i++) {
		precio +=  (*productos)[0]->precio();
	}

	return precio;
}

void Carrito::agregarArticulo(Articulo* articulo, int cantidad) {
	if(!estaPago) {
		Pedido* nuevoPedido = new Pedido(articulo, cantidad);
		this->productos->addLast(nuevoPedido);
	} else {
		std::cout << "Este pedido ya esta pago" << std::endl;
	}

}

void Carrito::pagarCarrito() {
	if(!estaPago) {
		estaPago = true;
	} else {
		std::cout << "Este pedido ya esta pago" << std::endl;
	}
}
