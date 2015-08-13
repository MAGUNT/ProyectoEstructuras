/*
 * Local.h
 *
 *  Created on: Aug 2, 2015
 *      Author: daniel
 */

#ifndef LIBRERIAPROYECTO_MODELS_COMPRAS_LOCAL_H_
#define LIBRERIAPROYECTO_MODELS_COMPRAS_LOCAL_H_

#include <vector>
#include <string>
#include "../../lists/ClinkedList.h"
#include "LineaGeneral.h"
#include "LineaEspecifica.h"
#include "Articulo.h"

typedef std::vector<std::string> string_vect;

class Local {
private:
	std::vector<std::string> categorias;
	ClinkedList<LineaGeneral*>* lineasGenerales;

	ClinkedList<LineaEspecifica*>* crearLineasEspecificas(string_vect nombres);
	ClinkedList<Articulo*>* crearArticulos(string_vect nombres);
	void armarLineas();

public:
	Local();
	virtual ~Local();

	const std::vector<std::string> getCategorias();
	LineaGeneral* getLineaGeneral(int codigo, int categoria);
	LineaEspecifica* getLineaEspecifica(LineaGeneral* lineaGeneral, int codigo);
	Articulo* getArticulo(LineaEspecifica* lineaEspecifica, int codigo);
	ClinkedList<LineaGeneral*>* getLineasGenerales(int categoria);
	ClinkedList<LineaEspecifica*>* getLineasEspecificas(LineaGeneral* lineaGeneral);
	ClinkedList<Articulo*>* getArticulos(LineaEspecifica* lineaEspecifica);
	void imprimirEstructura();
};

#endif /* LIBRERIAPROYECTO_MODELS_COMPRAS_LOCAL_H_ */
