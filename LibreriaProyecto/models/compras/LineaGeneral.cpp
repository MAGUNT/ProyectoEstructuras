/*
 * LineaGeneral.cpp
 *
 *  Created on: Aug 2, 2015
 *      Author: daniel
 */

#include "LineaGeneral.h"
#include "../../repositorys/Repositorios.h"
#include <iostream>

LineaGeneral::LineaGeneral(int _codigo, std::string _nombre)
	: codigo(_codigo), nombre(_nombre) , lineasEspecificas(ClinkedList<LineaEspecifica*>()){
}
LineaGeneral::LineaGeneral(): LineaGeneral(0,"Anonimo"){}

int LineaGeneral::getCodigo() const {
	return codigo;
}

void LineaGeneral::setCodigo(int codigo) {
	this->codigo = codigo;
}

const std::string& LineaGeneral::getNombre() const {
	return nombre;
}

void LineaGeneral::setNombre(const std::string& nombre) {
	this->nombre = nombre;
}

const ClinkedList<LineaEspecifica*>& LineaGeneral::getLineasEspecificas() {
	return lineasEspecificas;
}

LineaEspecifica* LineaGeneral::getLineaEspecifica(int codigo) const
{
	LineaEspecifica* output = nullptr;
	lineasEspecificas.find([codigo](LineaEspecifica* l)
	{
		return l->getCodigo() == codigo; 
	},output );

	return output;
}

LineaEspecifica* LineaGeneral::getLineaEspecifica(const std::string & nombre) const
{
	LineaEspecifica* output = nullptr;
	lineasEspecificas.find([&nombre](LineaEspecifica* l)
	{
		return l->getNombre() == nombre;
	}, output);

	return output;
}

bool LineaGeneral::agregarLineaEspecifica(LineaEspecifica* linea)
{
	return lineasEspecificas.addAscendent(linea);
}

bool LineaGeneral::eliminar(int codigo)
{
	LineaEspecifica* output = nullptr;
	bool exito =lineasEspecificas.remove([codigo](LineaEspecifica* l)
	{
		return l->getCodigo() == codigo;
	}, output);
	return exito;
}

void LineaGeneral::imprimir() {
	std::cout << "LineaGeneral " << codigo << ". " << nombre << std::endl;
	std::cout << "	Lineas Especificas:" << std::endl;
	this->lineasEspecificas.foreach([](LineaEspecifica* l) {
		std::cout << "	" << l->getCodigo() << ". " << l->getNombre() << std::endl;
	});

}

std::istream& operator >>(std::istream& is, LineaGeneral& linea)
{
	const char d = LineaGeneral::delimiter;

	//-----------Atrapar excepcion
	std::string token;
	getline(is, token, d);
	linea.codigo = std::stoi(token);
	getline(is, linea.nombre, d);
	//-----------Atrapar excepcion
	
	int codigo = 0;
	while (is >> codigo)
	{
		LineaEspecifica *lineaE = Repositorios::repoLineaEspecifica.getElement(codigo);
		linea.lineasEspecificas.addAscendent(lineaE);
	}
	return is;
}
std::istream& operator >>(std::istream& is, LineaGeneral*& linea)
{
	linea = new LineaGeneral();
	return is >> *linea;

}
bool operator<(const LineaGeneral& x, const LineaGeneral& y)
{
	return x.nombre < y.nombre;
}
std::ostream& operator <<(std::ostream& os, const LineaGeneral& linea)
{
	const char d = LineaGeneral::delimiter;

	os << linea.codigo << d
		<< linea.nombre << d;

	linea.lineasEspecificas.foreach([&os](LineaEspecifica* l)
	{
		os << " " << l->getCodigo(); 
	});

	return os;
}
std::ostream& operator <<(std::ostream& os, const LineaGeneral* linea)
{
	return os << *linea;
}
