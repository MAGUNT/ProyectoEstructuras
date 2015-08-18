/*
 * LineaGeneral.h
 *
 *  Created on: Aug 2, 2015
 *      Author: daniel
 */

#ifndef LIBRERIAPROYECTO_MODELS_COMPRAS_LINEAGENERAL_H_
#define LIBRERIAPROYECTO_MODELS_COMPRAS_LINEAGENERAL_H_

#include <string>
#include <vector>
#include "../../lists/ClinkedList.h"
#include "LineaEspecifica.h"

typedef std::vector<std::string> string_vect;

class LineaGeneral {
private:
	int codigo;
	std::string nombre;
	ClinkedList<LineaEspecifica*> lineasEspecificas;

public:
	LineaGeneral(int codigo, std::string nombre);

	const ClinkedList<LineaEspecifica*>& getLineasEspecificas();
	int getCodigo() const;
	const std::string& getNombre() const;
	void setNombre(const std::string& nombre);
	LineaEspecifica* getLineaEspecifica(int) const;
	LineaEspecifica* getLineaEspecifica(const std::string &) const;
	bool agregarLineaEspecifica(LineaEspecifica*);
	bool eliminar(int);
};

#endif /* LIBRERIAPROYECTO_MODELS_COMPRAS_LINEAGENERAL_H_ */
