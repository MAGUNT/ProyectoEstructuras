/*
 * Pedido.h
 *
 *  Created on: Aug 1, 2015
 *      Author: daniel
 */

#ifndef LIBRERIAPROYECTO_MODELS_PEDIDO_H_
#define LIBRERIAPROYECTO_MODELS_PEDIDO_H_

#include <string>
#include "../lists/ClinkedList.h"
#include "Articulo.h"


class Pedido {

private:
	std::string nombre;
	ClinkedList<Articulo*>* articulos;
	bool pagado;


public:
	Pedido();
	virtual ~Pedido();

	void agregarArticulo(Articulo* articulo);
	void comprarPedido();
	double precioTotal();
	void verArticulos();
};


#endif /* LIBRERIAPROYECTO_MODELS_PEDIDO_H_ */
