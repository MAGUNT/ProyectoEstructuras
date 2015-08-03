/*
 * Pedido.cpp
 *
 *  Created on: Aug 1, 2015
 *      Author: daniel
 */

#include "Pedido.h"
#include <iostream>
#include <typeinfo>

Pedido::Pedido(): nombre(), pagado() {
	this->articulos = new ClinkedList<Articulo*>();
}

Pedido::~Pedido() {
	delete this->articulos;
}

void Pedido::agregarArticulo(Articulo* articulo) {
	if(!this->pagado) {
		std::cout << "Agregando articulo" << std::endl;
		articulos->addLast(articulo);
		std::cout << (*articulos)[0] << std::endl;
	} else {
		std::cout << "Este pedido ya ha sido comprado" << std::endl;
	}
}

/*
 * Operador superscript no funciona..
 */
void Pedido::verArticulos() {
	if(!articulos->isEmpty()) {
		//Articulo* x = articulos[0];
		//std::cout << *x << std::endl;
	} else {
		std::cout << "articulos esta vacia" << std::endl;
	}

}

void Pedido::comprarPedido() {
	if(!this->pagado) {
		std::cout << "El pedido " << this->nombre << " ha sido comprado" << std::endl;
	} else {
		std::cout << "El pedidpagadoo ya ha sido comprado" << std::endl;
	}
}

double Pedido::precioTotal() {
	return 1.0;
}



