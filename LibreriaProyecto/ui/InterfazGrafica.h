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

typedef std::vector<std::string> string_vect;

class InterfazGrafica {
	Local local;
	string_vect opcionesDependiente;
	string_vect opcionesCliente;
	string_vect opcionesAdmin;
	//Solo para testear, pero no deberia estar aqui
	Carrito* carrito;
	//Usuario* usuario.

	// 	Metodos Miscelaneos
	int capturarOpcion();
	void mostrarMenu(string_vect menu);

	//	Metodos para Cliente
	void ejecutarOpcionCliente(int opcion);
	void verArticulos();
	void mostrarCategorias();
	void comprar();
	void comprarArticulo(Articulo* articulo);
	void mostrarCarritos();
	void pagarCarrito();
	Carrito* getCarrito();
	void modificarCarrito();
	int seleccionarCategoria();
	LineaGeneral* seleccionarLineaGeneral(int categoria);
	LineaEspecifica* seleccionarLineaEspecifica(LineaGeneral* lineaGeneral);
	Articulo* seleccionarArticulo(LineaEspecifica* lineaEspecifica);

	//	Metodos para Dependiente
	void ejecutarOpcionDependiente(int opcion);
	void entregarCarrito();

	//	Metodos para Admin
	void ejecutarOpcionAdmin(int opcion);


public:
	InterfazGrafica(Local &local);
	virtual ~InterfazGrafica();

	void iniciarSesion();
	void inicializar();
};

#endif /* LIBRERIAPROYECTO_UI_INTERFAZGRAFICA_H_ */
