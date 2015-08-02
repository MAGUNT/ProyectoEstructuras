/*
 * Articulo.h
 *
 *  Created on: Aug 1, 2015
 *      Author: daniel
 */

#ifndef LIBRERIAPROYECTO_MODELS_ARTICULO_H_
#define LIBRERIAPROYECTO_MODELS_ARTICULO_H_

#include <string>
#include <iostream>

class Articulo {
private:
	int codigo;
	int precio;
	std::string nombre;
	std::string marca;

public:
	Articulo();
	virtual ~Articulo();

	friend std::ostream& operator <<(std::ostream& os, Articulo& articulo);

};

#endif /* LIBRERIAPROYECTO_MODELS_ARTICULO_H_ */
