/*
 * Carrito.cpp
 *
 *  Created on: Aug 10, 2015
 *      Author: daniel.hernandez
 */

#include <iostream>
#include "Carrito.h"
#include "../../repositorys/Repositorios.h"

Carrito::Carrito() 
	: Carrito("")  {
}

Carrito::Carrito(std::string _nombre) : Carrito(0,0, _nombre)
	  {
}
Carrito::Carrito(int pcodigo, int pidUsuario, const std::string& _nombre) 
	: Carrito(pcodigo, pidUsuario, _nombre, ClinkedList<Pedido*>())
{

}
Carrito::Carrito(int pcodigo, int pidUsuario, const std::string& _nombre, const ClinkedList<Pedido*>& list)
	: codigo(pcodigo), idUsuario(pidUsuario), nombre(_nombre), productos(list)
{
	
}
Carrito::Carrito(Carrito* c)
	: Carrito(c->codigo, c->idUsuario, c->nombre, c->getProductos())
{
	
}
Carrito::~Carrito()
{
	productos.foreach([](Pedido* p){delete p; });
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



std::istream& operator >>(std::istream& is, Carrito& carrito)
{
	const char d = Carrito::delimiter;
	//-----------Atrapar excepcion
	std::string token;
	getline(is, token, d);
	carrito.codigo = std::stoi(token);
	getline(is, token, d);
	carrito.idUsuario = std::stoi(token);
	//-----------Atrapar excepcion
	getline(is, carrito.nombre, d);

	Pedido *pedido;
	while (is >> pedido)
		carrito.productos.addLast(pedido);
	
	return is;
}
std::istream& operator >>(std::istream& is, Carrito*& carrito)
{
	carrito = new Carrito();
	return is >> *carrito;
}
bool operator<(const Carrito& x, const Carrito& y)
{
	return x.nombre < y.nombre;
}
std::ostream& operator <<(std::ostream& os, const Carrito& carrito)
{
	const char d = Carrito::delimiter;

	 os << carrito.codigo <<d
		 << carrito.idUsuario << d
		<< carrito.nombre << d;

	 carrito.productos.foreach([&os](Pedido* p){ os << " " << *p; });

	 return os;
}
std::ostream& operator <<(std::ostream& os, const Carrito* linea)
{
	return os << *linea;
}

int Carrito::getIdUsuario() const
{
	return idUsuario;
}

int Carrito::getCantidad() const
{
	return productos.length();
}
int Carrito::getCodigo() const
{
	return codigo;
}

std::ostream& Carrito::printPretty(std::ostream& os) const
{
	char* space = "   ";
	auto usuario = Repositorios::repoUsuario.getElement(idUsuario);
	os << "Codigo: " << getCodigo()
		<< " Nombre: " << getNombre()
		<< " Cantidad: " << getCantidad()
		<< " Precio: " << precio() << std::endl
		<< "Usuario: " << idUsuario << " " << usuario->getNombre() << std::endl
		<< "Articulos = [" << std::endl;

	productos.foreach([&os, space](Pedido* p)
	{
		os << space; 
	    p->prettyPrint(os) << ","<< std::endl; 
	});
		
	return os << "]";
	
}
const ClinkedList<Pedido*>& Carrito::getProductos() const
{
	return productos;
}
void Carrito::setCodigo(int pcodigo)
{
	codigo = pcodigo;
}