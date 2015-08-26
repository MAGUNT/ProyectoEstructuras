#pragma once

#include "../models/compras/Articulo.h"
#include "../models/compras/LineaGeneral.h"
#include "../models/compras/Categoria.h"
#include "../models/compras/LineaEspecifica.h"

class GestorLineasDeAriculos
{
public:
	template <typename T>
	using RepoView = const ClinkedList<T, std::function<int(T, T)>>*;

	GestorLineasDeAriculos();

	//------------------>Eliminar
	void eliminarArticulo(int codigo) const;
	void eliminarLineaEspecifica(int codigo) const;
	void eliminarLineaGeneral(int codigo) const;
	void eliminarCategoria(int codigo) const;
	ClinkedList<Categoria*>* getCopiaCategorias() const;
	
	
	
	RepoView<Categoria*> getCategorias() const;
	
	Categoria* getCategoria(int categoria) const;

	ClinkedList<Articulo*>* getCopiaArticulos() const;
	RepoView<Articulo*> getArticulos() const;

	Articulo* getArticulo(int) const;
	void imprimirEstrucutura() const;

	std::string agregarArticulo(Articulo*, LineaEspecifica*) const;
	void actualizarArticulos() const;
	std::string agregarCategoria(Categoria* cat) const;

	std::string agregarLineaGeneral(LineaGeneral*, Categoria*) const;

	std::string agregarLineaEspecifica(LineaEspecifica*, LineaGeneral*) const;

	void actualizarCategorias();

	LineaGeneral* getLineaGeneral(int codigo);

	LineaEspecifica* getLineaEspecifica(int codigo);

	void actualizarLineasEspecificas();

	void actualizarLineasGenerales();
};

