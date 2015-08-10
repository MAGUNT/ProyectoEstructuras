/*
 * Carrito.h
 *
 *  Created on: Aug 10, 2015
 *      Author: daniel.hernandez
 */

#ifndef LIBRERIAPROYECTO_MODELS_COMPRAS_CARRITO_H_
#define LIBRERIAPROYECTO_MODELS_COMPRAS_CARRITO_H_

#include "../../lists/ClinkedList.h"
#include "Pedido.h"
#include <string>

class Carrito {
	ClinkedList<Pedido*>* productos;
	std::string nombre;
	bool estaPago;

public:
	Carrito();
	virtual ~Carrito();
	bool isEstaPago() const;
	void setEstaPago(bool estaPago);
	const std::string& getNombre() const;
	void setNombre(const std::string& nombre);
	ClinkedList<Pedido*>* getProductos() const;

	double precio();
	void agregarArticulo(Articulo* articulo, int cantidad);
	void pagarCarrito();
};

#endif /* LIBRERIAPROYECTO_MODELS_COMPRAS_CARRITO_H_ */
