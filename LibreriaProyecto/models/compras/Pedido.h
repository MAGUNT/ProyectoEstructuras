/*
 * Pedido.h
 *
 *  Created on: Aug 1, 2015
 *      Author: daniel
 */

#ifndef LIBRERIAPROYECTO_MODELS_PEDIDO_H_
#define LIBRERIAPROYECTO_MODELS_PEDIDO_H_

#include <string>
#include "../../lists/ClinkedList.h"
#include "Articulo.h"


class Pedido {

private:
	Articulo* articulo;
	int cantidad;

public:
	Pedido(Articulo* _articulo, int _cantidad);
	virtual ~Pedido();
	const Articulo* getArticulo() const;
	void setArticulo(Articulo* articulo);
	int getCantidad() const;
	void setCantidad(int cantidad);
	double precio();
};


#endif /* LIBRERIAPROYECTO_MODELS_PEDIDO_H_ */
