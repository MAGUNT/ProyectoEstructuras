#include "Inventario.h"


Inventario::Inventario(): articulos( ClinkedList<Articulo*>()){}

Inventario::~Inventario()
{
	articulos.foreach([](Articulo* a){delete a; });
}

bool Inventario::eliminarArticulo(int codigo) 
{
	Articulo* a = nullptr;
	bool isRemove = articulos.remove(createSLambda(codigo), a);
	if(isRemove) delete a; 
	
	return isRemove;
}
bool Inventario::modificarArticulo(int codigo, Articulo* articuloNuevo)
{
	// O(3n) = O(n)
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
std::function<bool(Articulo*)> Inventario::createSLambda(int codigo) const
{
	return [codigo](Articulo* a){ return a->getCodigo() == codigo; };
}

