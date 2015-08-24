#include "GestorLineasDeAriculos.h"
#include "..\repositorys\Repositorios.h"

//etc etc etc

void GestorLineasDeAriculos::eliminarArticulo(int codigo) const
{
	auto le = Repositorios::repoLineaEspecifica.getElements();
	le->foreach([codigo](LineaEspecifica* e){e->removerArticulo(codigo); });
	Repositorios::repoArticulo.deleteElement(codigo);

	delete le;

}

void GestorLineasDeAriculos::eliminarLineaEspecifica(int codigo) const
{
	auto lg = Repositorios::repoLineaGeneral.getElements();
	lg->foreach([codigo](LineaGeneral* e){e->eliminar(codigo); });
	Repositorios::repoLineaEspecifica.deleteElement(codigo);

	delete lg;
}

void GestorLineasDeAriculos::eliminarLineaGeneral(int codigo) const
{
	auto c = Repositorios::repoCategoria.getElements();
	c->foreach([codigo](Categoria* e){e->removerLineaGeneral(codigo); });
	Repositorios::repoLineaGeneral.deleteElement(codigo);

	delete c;
}

//tener cuidado si tiene otra lista que tenga categorias
void GestorLineasDeAriculos::eliminarCategoria(int codigo) const
{
	Repositorios::repoCategoria.deleteElement(codigo);
}