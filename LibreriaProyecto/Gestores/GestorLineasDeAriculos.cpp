#include "GestorLineasDeAriculos.h"
#include "..\repositorys\Repositorios.h"

//etc etc etc

GestorLineasDeAriculos::GestorLineasDeAriculos(){}

void GestorLineasDeAriculos::eliminarArticulo(int codigo) const
{
	auto le = Repositorios::repoLineaEspecifica.getElements();
	le->foreach([codigo](LineaEspecifica* e){e->removerArticulo(codigo); });
	Repositorios::repoLineaEspecifica.saveUpdates();
	Repositorios::repoArticulo.deleteElement(codigo);
	Repositorios::repoArticulo.saveUpdates();

	delete le;

}

void GestorLineasDeAriculos::eliminarLineaEspecifica(int codigo) const
{
	auto lg = Repositorios::repoLineaGeneral.getElements();
	lg->foreach([codigo](LineaGeneral* e){e->eliminar(codigo); });
	Repositorios::repoLineaGeneral.saveUpdates();
	Repositorios::repoLineaEspecifica.deleteElement(codigo);
	Repositorios::repoLineaEspecifica.saveUpdates();

	delete lg;
}

void GestorLineasDeAriculos::eliminarLineaGeneral(int codigo) const
{
	auto c = Repositorios::repoCategoria.getElements();
	c->foreach([codigo](Categoria* e){e->removerLineaGeneral(codigo); });
	Repositorios::repoCategoria.saveUpdates();
	Repositorios::repoLineaGeneral.deleteElement(codigo);
	Repositorios::repoLineaGeneral.saveUpdates();
	delete c;
}

//tener cuidado si tiene otra lista que tenga categorias
void GestorLineasDeAriculos::eliminarCategoria(int codigo) const
{
	Repositorios::repoCategoria.deleteElement(codigo);
	Repositorios::repoCategoria.saveUpdates();
}
