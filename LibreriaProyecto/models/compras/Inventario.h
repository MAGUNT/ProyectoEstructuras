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
	ClinkedList<Articulo*>* articulos;

	void eliminarArticulo(int codigo);
	void modificarArticulo(int codigo, Articulo articuloNuevo);

public:
	Inventario();
	virtual ~Inventario();

	/* Para efectos de prueba, este metodo es publico
	 * pero deberia ser privado.
	 */
	void agregarArticulo(int codigo, int precio,
			std::string nombre, std::string marca);
	Articulo* getArticulo(int codigo);
};

#endif /* LIBRERIAPROYECTO_MODELS_INVENTARIO_H_ */
