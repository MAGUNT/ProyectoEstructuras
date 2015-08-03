/*
 * Inventario.cpp
 *
 *  Created on: Aug 2, 2015
 *      Author: daniel
 */

#include "Inventario.h"

Inventario::Inventario() {
	this->articulos = new ClinkedList<Articulo*>();
}

/*
 * Metodos Privados, accesibles solo para el admin
 */
Inventario::~Inventario() {
	delete this->articulos;
}
void Inventario::eliminarArticulo(int codigo) {}
void Inventario::modificarArticulo(int codigo, Articulo articuloNuevo){}

/*
 * Metodos publicos
 */
void Inventario::agregarArticulo(int codigo, int precio,
		std::string nombre, std::string marca) {

	Articulo* nuevoArticulo = new Articulo();
	/*Checkear si el codigo no es repetido
	 * y todos los demas datos sean validos.
	 */
	nuevoArticulo->setCodigo(codigo);
	nuevoArticulo->setPrecio(precio);
	nuevoArticulo->setNombre(nombre);
	nuevoArticulo->setMarca(marca);
	this->articulos->addAscendent(nuevoArticulo);
}

Articulo* Inventario::getArticulo(int codigo){
	return 0;
}
