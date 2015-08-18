/*
 * LineaEspecifica.cpp
 *
 *  Created on: Aug 2, 2015
 *      Author: daniel
 */

#include "LineaEspecifica.h"

LineaEspecifica::LineaEspecifica(int _codigo, std::string _nombre)
	: codigo(_codigo), nombre(_nombre), articulos(ClinkedList<Articulo*>()) {

}

int LineaEspecifica::getCodigo() const {
	return codigo;
}

void LineaEspecifica::setCodigo(int codigo) {
	this->codigo = codigo;
}

const std::string& LineaEspecifica::getNombre() const {
	return nombre;
}

void LineaEspecifica::setNombre(const std::string& nombre) {
	this->nombre = nombre;
}

const ClinkedList<Articulo*>& LineaEspecifica::getArticulos() {
	return articulos;
}

void LineaEspecifica::agregarArticulo(Articulo* articulo)
{
	articulos.addAscendent(articulo);
}
Articulo* LineaEspecifica::buscarPorCodigo(int codigo) const
{
	Articulo* articulo = nullptr;

	articulos.find([=](Articulo* a)
	{
		return a->getCodigo() == codigo; 
	}, articulo);

	return articulo;
}
Articulo* LineaEspecifica::buscarPorMarca(const std::string& marca) const
{
	Articulo* articulo = nullptr;

	articulos.find([&](Articulo* a)
	{
		return a->getMarca() == marca;
	}, articulo);

	return articulo;
}
Articulo* LineaEspecifica::buscarPorNombre(const std::string& nombre) const
{
	Articulo* articulo = nullptr;

	articulos.find([&](Articulo* a)
	{
		return a->getNombre() == nombre;
	}, articulo);

	return articulo;
}

bool LineaEspecifica::removerArticulo(int codigo)
{
	return articulos.remove([=](Articulo* a)
	{ 
		return a->getCodigo() == codigo; 
	});
}