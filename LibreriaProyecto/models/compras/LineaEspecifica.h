/*
 * LineaEspecifica.h
 *
 *  Created on: Aug 2, 2015
 *      Author: daniel
 */

#ifndef LIBRERIAPROYECTO_MODELS_COMPRAS_LINEAESPECIFICA_H_
#define LIBRERIAPROYECTO_MODELS_COMPRAS_LINEAESPECIFICA_H_

#include "../../lists/ClinkedList.h"
#include "Articulo.h"

class LineaEspecifica {
private:
	ClinkedList<Articulo*>* articulos;
	int codigo;
	std::string nombre;

public:
	LineaEspecifica(int codigo, std::string nombre);
	virtual ~LineaEspecifica();
	ClinkedList<Articulo*>* getArticulos();
	int getCodigo() const;
	void setCodigo(int codigo);
	const std::string& getNombre() const;
	void setNombre(const std::string& nombre);
};

#endif /* LIBRERIAPROYECTO_MODELS_COMPRAS_LINEAESPECIFICA_H_ */
