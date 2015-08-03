/*
 * LineasGenerales.h
 *
 *  Created on: Aug 2, 2015
 *      Author: daniel
 */

#ifndef LIBRERIAPROYECTO_MODELS_COMPRAS_LINEAGENERAL_H_
#define LIBRERIAPROYECTO_MODELS_COMPRAS_LINEAGENERAL_H_

#include "../../lists/ClinkedList.h"
#include "LineaEspecifica.h"

class LineaGeneral {
private:
	ClinkedList<LineaEspecifica> lineasEspecificas;

public:
	LineaGeneral();
	virtual ~LineaGeneral();
};

#endif /* LIBRERIAPROYECTO_MODELS_COMPRAS_LINEAGENERAL_H_ */
