/*
 * Inventario.h
 *
 *  Created on: Aug 2, 2015
 *      Author: daniel
 */

#ifndef LIBRERIAPROYECTO_MODELS_INVENTARIO_H_
#define LIBRERIAPROYECTO_MODELS_INVENTARIO_H_

#include "../../lists/ClinkedList.h"
#include "Articulo.h"

class Inventario {
private:
	ClinkedList<Articulo*> articulos;
	std::function<bool(Articulo*)> createSLambda(int) const;
public:
	Inventario();
	virtual ~Inventario();

	/* Para efectos de prueba, este metodo es publico
	 * pero deberia ser privado.
	 */
	
	bool eliminarArticulo(int codigo);
	bool modificarArticulo(int codigo, Articulo* articuloNuevo);
	bool agregarArticulo(int codigo, const std::string& nombre, const std::string& marca, long double precio);
	Articulo* getArticulo(int codigo) const;
};

#endif /* LIBRERIAPROYECTO_MODELS_INVENTARIO_H_ */
