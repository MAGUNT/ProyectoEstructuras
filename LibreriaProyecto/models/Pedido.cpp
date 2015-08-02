/*
 * Pedido.cpp
 *
 *  Created on: Aug 1, 2015
 *      Author: daniel
 */

#include "Pedido.h"
#include <iostream>


Pedido::Pedido(): nombre(), articulos() {}

Pedido::~Pedido() {}

void Pedido::agregarArticulo(Articulo* articulo) {
	std::cout << "*En agregarArticulo de Pedido*" << std::endl;
}
