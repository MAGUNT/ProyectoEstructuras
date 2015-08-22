/*
 * Carrito.h
 *
 *  Created on: Aug 10, 2015
 *      Author: daniel.hernandez
 */
#pragma once
#ifndef LIBRERIAPROYECTO_MODELS_COMPRAS_CARRITO_H_
#define LIBRERIAPROYECTO_MODELS_COMPRAS_CARRITO_H_

#include "../../lists/ClinkedList.h"
#include "Pedido.h"
#include <string>
#include <memory>

class Carrito {
	ClinkedList<Pedido*> productos;
	std::string nombre;

public:
	Carrito();
	Carrito(std::string _nombre);
	const std::string& getNombre() const;
	void setNombre(const std::string& nombre);
	const ClinkedList<Pedido*>& getProductos() const;
	long double precio()const;
	void agregarArticulo(Articulo* articulo, int cantidad);
	Pedido* buscarPorCodigo(int) const;
	Pedido* buscarPorMarca(const std::string&) const;
	Pedido* buscarPorNombre(const std::string&) const;

};

#endif /* LIBRERIAPROYECTO_MODELS_COMPRAS_CARRITO_H_ */
