/*
 * Carrito.cpp
 *
 *  Created on: Aug 10, 2015
 *      Author: daniel.hernandez
 */

#include <iostream>
#include "Carrito.h"

Carrito::Carrito() 
	: Carrito("")  {
}

Carrito::Carrito(std::string _nombre) 
	: nombre(_nombre), productos(ClinkedList<Pedido*>())  {
}

const std::string& Carrito::getNombre() const {
	return nombre;
}

void Carrito::setNombre(const std::string& nombre) {
	this->nombre = nombre;
}

long double Carrito::precio() const{
	double precio = 0;
	productos.foreach([&precio](Pedido* x)
	{ 
		precio += x->precio(); 
	});

	return precio;
}

void Carrito::agregarArticulo(Articulo* articulo, int cantidad) {

	Pedido* nuevoPedido = new Pedido(articulo, cantidad);
	productos.addLast(nuevoPedido);
}

Pedido* Carrito::buscarPorCodigo(int codigo) const
{
	Pedido* p = nullptr;
	productos.find([=](Pedido* x)
	{
		return x->getArticulo()->getCodigo() == codigo; 
	},p);
	return p;
}
Pedido* Carrito::buscarPorMarca(const std::string& marca) const
{
	Pedido* p = nullptr;
	productos.find([&](Pedido* x)
	{
		return x->getArticulo()->getMarca() == marca;
	}, p);
	return p;
}
Pedido* Carrito::buscarPorNombre(const std::string& nombre) const
{
	Pedido* p = nullptr;
	productos.find([&](Pedido* x)
	{
		return x->getArticulo()->getNombre() == nombre;
	}, p);
	return p;
}

