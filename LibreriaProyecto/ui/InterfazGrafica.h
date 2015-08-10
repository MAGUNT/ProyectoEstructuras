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

typedef std::vector<std::string> string_vect;

class InterfazGrafica {
	Local local;
	string_vect opcionesDependiente;
	string_vect opcionesCliente;
	string_vect opcionesAdmin;
	int capturarOpcion();
	void ejecutarOpcionCliente(int opcion, string_vect menuDefault);
	void mostrarMenu(string_vect menu);
	void verArticulos();
	void mostrarCategorias();
	void comprar();

	//	Seleccion de articulos
	int seleccionarCategoria();
	LineaGeneral* seleccionarLineaGeneral(int categoria);
	LineaEspecifica* seleccionarLineaEspecifica(LineaGeneral* lineaGeneral);
	Articulo* seleccionarArticulo(LineaEspecifica* lineaEspecifica);

public:
	InterfazGrafica(Local &local);
	virtual ~InterfazGrafica();

	void iniciarSesion();
	void inicializar();
};

#endif /* LIBRERIAPROYECTO_UI_INTERFAZGRAFICA_H_ */