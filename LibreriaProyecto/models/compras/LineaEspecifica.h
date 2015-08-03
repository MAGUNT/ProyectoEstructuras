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
	ClinkedList<Articulo*> articulos;
public:
	LineaEspecifica();
	virtual ~LineaEspecifica();
};

#endif /* LIBRERIAPROYECTO_MODELS_COMPRAS_LINEAESPECIFICA_H_ */
