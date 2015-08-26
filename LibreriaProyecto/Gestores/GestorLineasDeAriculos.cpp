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

ClinkedList<Categoria*>* GestorLineasDeAriculos::getCopiaCategorias() const
{
	return Repositorios::repoCategoria.getElements();
}

 GestorLineasDeAriculos::RepoView<Categoria*> GestorLineasDeAriculos::getCategorias() const
{
	return Repositorios::repoCategoria.getView();
}

void GestorLineasDeAriculos::imprimirEstrucutura() const
{
	getCategorias()->foreach([](Categoria* c) {
		std::cout << c->getCodigo() << ". " << c->getNombre() << " [" << std::endl;
		c->getLineaGenerals().foreach([](LineaGeneral* lg) {
			std::cout << "   " << lg->getCodigo() << ". " << lg->getNombre() << std::endl;
			lg->getLineasEspecificas().foreach([](LineaEspecifica* le) {
				std::cout << "      " << le->getCodigo() << ". " << le->getNombre() << std::endl;
				le->getArticulos().foreach([](Articulo* a) {
					std::cout << "          " << a->getCodigo() << ". " << a->getNombre() << std::endl;
				});
			});
		});
		std::cout << "]";
	});
}

Categoria* GestorLineasDeAriculos::getCategoria(int categoria) const
{
	return Repositorios::repoCategoria.getElement(categoria);
}
ClinkedList<Articulo*>* GestorLineasDeAriculos::getCopiaArticulos() const
{
	return Repositorios::repoArticulo.getElements();
}
 GestorLineasDeAriculos::RepoView<Articulo*> GestorLineasDeAriculos::getArticulos() const
{
	return Repositorios::repoArticulo.getView();
}

Articulo* GestorLineasDeAriculos::getArticulo(int codigo) const
{
	return Repositorios::repoArticulo.getElement(codigo);
}

std::string GestorLineasDeAriculos::agregarArticulo(Articulo* a, LineaEspecifica* le) const
{
	if (!Repositorios::repoArticulo.addElement(a))
	{
		delete a;
		a = nullptr;
		return "ya existe un codigo con este id";
	}
		
	
	le->agregarArticulo(a);
	Repositorios::repoLineaEspecifica.saveUpdates();
	return "El articulo se agrego con exito";

	
}
void GestorLineasDeAriculos::actualizarArticulos() const
{
	Repositorios::repoArticulo.saveUpdates();
}

std::string GestorLineasDeAriculos::agregarCategoria(Categoria* cat) const
{
	if (Repositorios::repoCategoria.addElement(cat))
		return "La categoria se agrego con exito";

	delete cat;
	return "ya existe una categoria con el codigo ingresado";
}


void GestorLineasDeAriculos::actualizarCategorias()
{
	Repositorios::repoCategoria.saveUpdates();

}

std::string GestorLineasDeAriculos::agregarLineaGeneral(LineaGeneral* linea, Categoria* a) const
{
	if (!Repositorios::repoLineaGeneral.addElement(linea))
	{
		delete linea;
		linea = nullptr;
		return "Ya existe una linea con este codigo";
	}

	a->agregarLineaGeneral(linea);
	Repositorios::repoLineaGeneral.saveUpdates();
	return "La linea general se agrego con exito";

}
LineaGeneral* GestorLineasDeAriculos::getLineaGeneral(int codigo)
{
	return Repositorios::repoLineaGeneral.getElement(codigo);
}

void GestorLineasDeAriculos::actualizarLineasGenerales()
{
	Repositorios::repoLineaGeneral.saveUpdates();
}

std::string GestorLineasDeAriculos::agregarLineaEspecifica(LineaEspecifica* le, LineaGeneral*lg) const
{
	if (!Repositorios::repoLineaEspecifica.addElement(le))
	{
		delete le;
		le = nullptr;
		return "Ya existe una linea especifica con este codigo";
	}

	lg->agregarLineaEspecifica(le);
	Repositorios::repoLineaGeneral.saveUpdates();
	return "La linea general se agrego con exito";
	
}

LineaEspecifica* GestorLineasDeAriculos::getLineaEspecifica(int codigo)
{

	return Repositorios::repoLineaEspecifica.getElement(codigo);
}
void GestorLineasDeAriculos::actualizarLineasEspecificas()
{
	Repositorios::repoLineaEspecifica.saveUpdates();
}