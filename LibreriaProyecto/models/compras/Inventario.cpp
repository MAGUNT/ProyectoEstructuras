/*
 * Inventario.cpp
 *
 *  Created on: Aug 2, 2015
 *      Author: daniel
 */
/*
A todos estos metodos les falta la parte de persistencia
*/
/*
Esta clase debe leer todos los articulos al inicio de la aplicacion.
*/

#include "Inventario.h"


Inventario::Inventario(): articulos( ClinkedList<Articulo*>()){}

Inventario::~Inventario()
{
	articulos.foreach([](Articulo* a){delete a; });
}
/*
 * Metodos Privados, accesibles solo para el admin
 */
bool Inventario::eliminarArticulo(int codigo) 
{
	Articulo* a = nullptr;
	bool isRemove = articulos.remove(createSLambda(codigo), a);
	if(isRemove) delete a; 
	
	return isRemove;
}
bool Inventario::modificarArticulo(int codigo, Articulo* articuloNuevo)
{
	// tres recorridos
	return getArticulo(codigo) != nullptr
		&& agregarArticulo(articuloNuevo)
		&& eliminarArticulo(codigo);
}

/*
 * Metodos publicos
 */


bool Inventario::agregarArticulo(Articulo* articulo) 
{
	return articulos.addAscendent(articulo);
}

Articulo* Inventario::getArticulo(int codigo) const{
	
	Articulo* articulo = nullptr;
	articulos.find(createSLambda(codigo), articulo);

	return  articulo;
}

//hubiera sido mas eficiente que el lambda en la lista tubiera dos parametros 
//T para no tener que capturar ni crear un lambda cada vez. 
std::function<bool(Articulo*)> Inventario::createSLambda(int codigo) const
{
	return [codigo](Articulo* a){ return a->getCodigo() == codigo; };
}
