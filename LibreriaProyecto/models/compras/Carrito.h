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
class Carrito;

std::istream& operator >>(std::istream& is, Carrito& linea);
std::istream& operator >>(std::istream& is, Carrito*& linea);
bool operator<(const Carrito& x, const Carrito& y);
std::ostream& operator <<(std::ostream& os, const Carrito& linea);
std::ostream& operator <<(std::ostream& os, const Carrito* linea);

class Carrito {

	int codigo;
	int idUsuario;
	ClinkedList<Pedido*> productos;
	std::string nombre;
	static const char delimiter = 31;

public:
	Carrito();
	Carrito(std::string _nombre);
	Carrito(int id, int idUsuario, const std::string& _nombre);
	Carrito(int id, int idUsuario, const std::string& _nombre, const ClinkedList<Pedido*>& list);
	Carrito(Carrito*);
	~Carrito();
	const std::string& getNombre() const;
	void setNombre(const std::string& nombre);
	const ClinkedList<Pedido*>& getProductos() const;
	long double precio()const;
	void agregarArticulo(Articulo* articulo, int cantidad);
	Pedido* buscarPorCodigo(int) const;
	Pedido* buscarPorMarca(const std::string&) const;
	Pedido* buscarPorNombre(const std::string&) const;
	void setCodigo(int);
	
	int getIdUsuario() const;
	int getCantidad() const;
	int getCodigo() const;
	std::ostream& printPretty(std::ostream&) const;
	friend std::istream& operator >>(std::istream& is, Carrito& linea);
	friend std::istream& operator >>(std::istream& is, Carrito*& linea);
	friend bool operator<(const Carrito& x, const Carrito& y);
	friend std::ostream& operator <<(std::ostream& os, const Carrito& linea);
	friend std::ostream& operator <<(std::ostream& os, const Carrito* linea);

};

#endif /* LIBRERIAPROYECTO_MODELS_COMPRAS_CARRITO_H_ */
