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


class LineaGeneral;

std::istream& operator >>(std::istream& is, LineaGeneral& linea);
std::istream& operator >>(std::istream& is, LineaGeneral*& linea);
bool operator<(const LineaGeneral& x, const LineaGeneral& y);
std::ostream& operator <<(std::ostream& os, const LineaGeneral& linea);
std::ostream& operator <<(std::ostream& os, const LineaGeneral* linea);

class LineaGeneral {
private:
	int codigo;
	std::string nombre;
	ClinkedList<LineaEspecifica*> lineasEspecificas;
	
	const static char delimiter = 31;

public:
	LineaGeneral(int codigo, std::string nombre);
	LineaGeneral();
	const ClinkedList<LineaEspecifica*>& getLineasEspecificas();
	int getCodigo() const;
	void setCodigo(int codigo);
	const std::string& getNombre() const;
	void setNombre(const std::string& nombre);
	LineaEspecifica* getLineaEspecifica(int) const;
	LineaEspecifica* getLineaEspecifica(const std::string &) const;
	bool agregarLineaEspecifica(LineaEspecifica*);
	bool eliminar(int);
	void imprimir();

	friend std::istream& operator >>(std::istream& is, LineaGeneral& linea);
	friend std::istream& operator >>(std::istream& is, LineaGeneral*& linea);
	friend bool operator<(const LineaGeneral& x, const LineaGeneral& y);
	friend std::ostream& operator <<(std::ostream& os, const LineaGeneral& linea);
	friend std::ostream& operator <<(std::ostream& os, const LineaGeneral* linea);
};

#endif /* LIBRERIAPROYECTO_MODELS_COMPRAS_LINEAGENERAL_H_ */
