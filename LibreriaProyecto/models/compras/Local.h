/*
 * Local.h
 *
 *  Created on: Aug 2, 2015
 *      Author: daniel
 */

#ifndef LIBRERIAPROYECTO_MODELS_COMPRAS_LOCAL_H_
#define LIBRERIAPROYECTO_MODELS_COMPRAS_LOCAL_H_

#include "../../lists/ClinkedList.h"
#include "LineaGeneral.h"

class Local {
private:
	ClinkedList<LineaGeneral*> lineasGenerales;

public:
	Local();
	virtual ~Local();
};

#endif /* LIBRERIAPROYECTO_MODELS_COMPRAS_LOCAL_H_ */
