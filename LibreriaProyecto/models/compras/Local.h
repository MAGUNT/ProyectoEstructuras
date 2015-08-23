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
#include "Categoria.h"


typedef std::vector<std::string> string_vect;

class Local {
private:
	ClinkedList<Categoria*> categorias;

public:
	Local();
	virtual ~Local();

	Categoria& getCategoria(int codigo);
	LineaGeneral& getLineaGeneral(int codigo, int categoria);
	LineaEspecifica& getLineaEspecifica(LineaGeneral* lineaGeneral, int codigo);
	Articulo& getArticulo(int codigo);
	Articulo& getArticulo(LineaEspecifica* lineaEspecifica, int codigo);

	const ClinkedList<Categoria*>& getCategorias();
	const ClinkedList<LineaGeneral*>& getLineasGenerales(int categoria);
	const ClinkedList<LineaEspecifica*>& getLineasEspecificas(LineaGeneral* lineaGeneral);
	const ClinkedList<Articulo*>& getArticulos(LineaEspecifica* lineaEspecifica);
	void imprimirEstructura();
};

#endif /* LIBRERIAPROYECTO_MODELS_COMPRAS_LOCAL_H_ */
