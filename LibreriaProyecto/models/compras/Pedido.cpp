/*
 * Pedido.cpp
 *
 *  Created on: Aug 1, 2015
 *      Author: daniel
 */

#include "Pedido.h"
#include <iostream>
#include <typeinfo>
#include "../../repositorys/Repositorios.h"

Pedido::Pedido(Articulo* _articulo, int _cantidad): articulo(_articulo), cantidad(_cantidad) {}
Pedido::Pedido(): Pedido(nullptr, 0){}


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

std::istream& operator >>(std::istream& is, Pedido& linea)
{
	int codigo, cantidad;
	if (is >> codigo >> cantidad)
	{
		Articulo* articulo = Repositorios::repoArticulo.getElement(codigo);
		linea.cantidad = cantidad;
		linea.articulo = articulo;
	}
	return is;
}
std::istream& operator >>(std::istream& is, Pedido*& linea)
{
	Pedido p;
	if (is >> p)
	{
		linea = new Pedido();
		*linea = p;
	}
	return is;
}
bool operator<(const Pedido& x, const Pedido& y)
{
	return x.articulo < y.articulo;
}
std::ostream& operator <<(std::ostream& os, const Pedido& linea)
{
	
	return os << linea.articulo->getCodigo() << " " << linea.cantidad;
}

std::ostream&  Pedido::prettyPrint(std::ostream& os)
{
	return os << "Codigo: " << getArticulo()->getCodigo()
		<< " Nombre: " << getArticulo()->getNombre() 
		<< "Cantidad: " << getCantidad()
		<< " Precio total: " << precio();
}