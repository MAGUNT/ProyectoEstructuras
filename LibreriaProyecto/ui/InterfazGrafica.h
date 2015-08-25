/*
 * InterfazGrafica.h
 *
 *  Created on: Aug 8, 2015
 *      Author: Daniel
 */

#ifndef LIBRERIAPROYECTO_UI_INTERFAZGRAFICA_H_
#define LIBRERIAPROYECTO_UI_INTERFAZGRAFICA_H_

#include <vector>
#include <string>
#include "../models/compras/Local.h"
#include "../models/compras/Carrito.h"
#include "../models/usuarios/Usuario.h"
#include "../Gestores/GestorLineasDeAriculos.h"
#include "../Gestores/GestorUsuarios.h"

typedef std::vector<std::string> string_vect;

class InterfazGrafica {
	Local local;
	string_vect opcionesDependiente;
	string_vect opcionesCliente;
	string_vect opcionesAdmin;
	GestorLineasDeAriculos* gArticulos;
	GestorUsuarios* gUsuarios;

	// 	Metodos Miscelaneos
	int capturarOpcion();
	void mostrarMenu(Usuario* usuario);
	void verArticulos();
	void mostrarCategorias();
	void mostrarLineasGenerales(const ClinkedList<LineaGeneral*>* lgs);
	void mostrarLineasGenerales();
	void mostrarLineasEspecificas(const ClinkedList<LineaEspecifica*>* les);
	void mostrarLineasEspecificas();
	void mostrarArticulos(const ClinkedList<Articulo*>* as);
	void mostrarCarritos(int codigoUsuario);
	void routeOpcion(int opcion, Rol rol);

	//	Metodos para Cliente
	void ejecutarOpcionCliente(int opcion);
	void comprar();
	void comprarArticulo(Articulo* articulo);
	void mostrarCarritos();
	void pagarCarrito();
	Carrito* getCarrito();
	void modificarCarrito();
	Categoria* seleccionarCategoria();
	LineaGeneral* seleccionarLineaGeneral(int categoria);
	LineaEspecifica* seleccionarLineaEspecifica(LineaGeneral* lineaGeneral);
	Articulo* seleccionarArticulo(LineaEspecifica* lineaEspecifica);

	//	Metodos para Dependiente
	void ejecutarOpcionDependiente(int opcion);
	void entregarCarrito();

	//	Metodos para Admin
	void ejecutarOpcionAdmin(int opcion);
	void verTodosArticulos();
	void agregarArticulo();
	void modificarArticulo();
	void eliminarArticulo();
	void agregarCategoria();
	void modificarCategoria();
	void eliminarCategoria();
	void agregarLineaGeneral();
	void modificarLineaGeneral();
	void eliminarLineaGeneral();
	void agregarLineaEspecifica();
	void modificarLineaEspecifica();
	void elimnarLineaEspecifica();


public:
	InterfazGrafica(Local &local);
	virtual ~InterfazGrafica();

	void iniciarSesion();
	void inicializar();
};

#endif /* LIBRERIAPROYECTO_UI_INTERFAZGRAFICA_H_ */
