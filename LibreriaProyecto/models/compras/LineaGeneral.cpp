/*
 * LineaGeneral.cpp
 *
 *  Created on: Aug 2, 2015
 *      Author: daniel
 */

#include "LineaGeneral.h"

LineaGeneral::LineaGeneral(int _codigo, std::string _nombre)
	: codigo(_codigo), nombre(_nombre) , lineasEspecificas(ClinkedList<LineaEspecifica*>()){
}

int LineaGeneral::getCodigo() const {
	return codigo;
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

	if (exito) delete output; 

	return exito;
}