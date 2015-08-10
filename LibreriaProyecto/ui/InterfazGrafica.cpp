/*
 * InterfazGrafica.cpp
 *
 *  Created on: Aug 8, 2015
 *      Author: Daniel
 */

#include "InterfazGrafica.h"
#include <iostream>
#include <sstream>

InterfazGrafica::InterfazGrafica(Local& local) {
	this->local = local;
	this->carrito = new Carrito();
	carrito->setNombre("Carrito para testear");

	this->opcionesCliente = {
			"1. Ver articulos.",
			"2. Comprar articulos",
			"3. Ver carritos.",
			"4. Modificar carrito.",
			"5. Pagar pedido."
	};

	this->opcionesDependiente = {
			"1. Ver pedidos.",
			"2. Entregar pedido."
	};

	this->opcionesAdmin = {
			"1. Agregar articulo.",
			"2. Modificar articulo.",
			"3. Eliminar articulo."
	};
}

InterfazGrafica::~InterfazGrafica() {}

//	Metodos Privados.

int InterfazGrafica::capturarOpcion(){
	std::string opcion;
	bool esNumero = false;
	int numero;

	while (!esNumero) {
	   std::cout << "Ingrese el numero de opcion: ";
	   std::getline(std::cin, opcion);

	   // Convierte de string a numero de forma segura.
	   std::stringstream myStream(opcion);
	   if (myStream >> numero) {
		   esNumero = true;
	   } else {
		   std::cout << "Numero invalido, trate de nuevo." << std::endl;
	   }
	 }

	return numero;
}

void InterfazGrafica::ejecutarOpcionCliente(int opcion, string_vect menuDefault) {

	switch (opcion) {
		case 1:
			std::cout << " " << std::endl;
			std::cout << "----->Mostrando articulos" << std::endl;
			verArticulos();
			break;
		case 2:
			std::cout << " " << std::endl;
			std::cout << "----->Comprando Articulos" << std::endl;
			comprar();
			break;
		case 3:
			std::cout << " " << std::endl;
			std::cout << "----->Mostrando carritos" << std::endl;
			mostrarCarritos();
			break;
		case 4:
			std::cout << " " << std::endl;
			std::cout << "----->Modificando carrito" << std::endl;
			break;
		case 5:
			std::cout << " " << std::endl;
			std::cout << "----->Pagando carrito" << std::endl;
			break;
		default:
			std::cout << " " << std::endl;
			std::cout << "----->Opcion invalida. Volviendo al menu inicial" << std::endl;
			break;
	}

	this->inicializar();
}

void InterfazGrafica::mostrarMenu(string_vect menu) {
	std::cout << " " << std::endl;
	std::cout << "*-----------------------------------------*" << std::endl;
	for (unsigned i = 0; i < menu.size(); i++) {
		std::cout << menu[i] << std::endl;
	}
	std::cout << "*-----------------------------------------*" << std::endl;
	std::cout << " " << std::endl;
}

void InterfazGrafica::verArticulos() {
	local.imprimirEstructura();
}

void InterfazGrafica::comprar() {
	int categoria = seleccionarCategoria();

	if(categoria != 0) {
		LineaGeneral* lineaG = seleccionarLineaGeneral(categoria);
		if(lineaG != 0) {
			std::cout << "Linea General seleccionada: " << lineaG->getNombre() << std::endl;
			LineaEspecifica* lineaE = seleccionarLineaEspecifica(lineaG);
			if(lineaE != 0) {
				std::cout << "Linea Especifica seleccionada: " << lineaE->getNombre() << std::endl;
				Articulo* articulo = seleccionarArticulo(lineaE);
				if(articulo != 0) {
					comprarArticulo(articulo);
				}else {
					std::cout << "****Linea Especifica no tiene Articulos disponibles****" << std::endl;
				}
			}else {
				std::cout << "****Linea General no tiene Lineas Especificas aun****" << std::endl;
			}
		}else {
			std::cout << "****Categoria no tiene Lineas Generales aun****" << std::endl;
		}
	} else {
		std::cout << "****Categoria no existe****" << std::endl;
	}
}

void InterfazGrafica::comprarArticulo(Articulo* articulo) {
	int opcion = 0;
	int cantidad = 0;

	std::cout << "" << std::endl;
	std::cout << "Articulo seleccionado: " << *articulo << std::endl;
	std::cout << "Comprar este articulo? 1. Si / 2. No" << std::endl;

	opcion = capturarOpcion();
	if(opcion == 1 || opcion == 0) {
		if(opcion == 1) {
			std::cout << "Introduzca la cantidad que desea de este producto" << std::endl;
			cantidad = capturarOpcion();
			if(cantidad < 0) {
				carrito->agregarArticulo(articulo, cantidad);
				std::cout << cantidad << " " << articulo->getNombre() <<
						" agregado a " << carrito->getNombre() << std::endl;
			}
		}
	} else {
		std::cout << "Opcion invalida" << std::endl;
	}
}

/*
 * 	Este metodo debe interactuar con el usuario directamente
 */
void InterfazGrafica::mostrarCarritos() {
	for(unsigned i = 0; i < carrito->getProductos()->length(); i++) {
		std::cout << (*carrito->getProductos())[i]->getCantidad() <<
			" " <<  (*carrito->getProductos())[0]->getArticulo()->getNombre() <<
			std::endl;
	}
	std::cout << "--------------------------------------" << std::endl;
	std::cout << "Total: " << carrito->precio() << std::endl;
}

//	Metodos Publicos

void InterfazGrafica::inicializar() {
	int opcion;

	this->mostrarMenu(this->opcionesCliente);
	opcion = this->capturarOpcion();
	this->ejecutarOpcionCliente(opcion, this->opcionesCliente);
}

void InterfazGrafica::mostrarCategorias() {
	string_vect categorias = this->local.getCategorias();
	for (unsigned i = 0; i < categorias.size(); i++) {
		std::cout << categorias[i] << std::endl;
	}
}

int InterfazGrafica::seleccionarCategoria() {
	int categoria = 0;

	mostrarCategorias();
	categoria = capturarOpcion();

	if(categoria > 0 && categoria < local.getCategorias().size()) {
		return categoria;
	} else {
		return 0;
	}

}

LineaGeneral* InterfazGrafica::seleccionarLineaGeneral(int categoria) {
	int opcion = 0;

	std::cout << "Lineas Generales en esta categoria: " << std::endl;
	for (unsigned i = 0; i < local.getLineasGenerales(categoria)->length(); i++) {
		std::cout << i+1 << ". " << (*local.getLineasGenerales(categoria))[i]->getNombre() << std::endl;
	}
	opcion = capturarOpcion();

	return local.getLineaGeneral(opcion);
}

LineaEspecifica* InterfazGrafica::seleccionarLineaEspecifica(LineaGeneral* lineaGeneral) {
	int opcion = 0;

	std::cout << "Lineas Especificas en esta Linea General: " << std::endl;
	for(unsigned i = 0; i < lineaGeneral->getLineasEspecificas()->length(); i++) {
		std::cout << i+1 << ". " << (*lineaGeneral->getLineasEspecificas())[i]->getNombre() << std::endl;
	}
	opcion = capturarOpcion();

	return local.getLineaEspecifica(lineaGeneral, opcion);
}

Articulo* InterfazGrafica::seleccionarArticulo(LineaEspecifica* lineaEspecifica) {
	int opcion = 0;

	std::cout << "Articulos en esta Linea Especifica: " << std::endl;
	for(unsigned i = 0; i < lineaEspecifica->getArticulos()->length(); i++) {
		std::cout << i+1 << ". " << *(*lineaEspecifica->getArticulos())[i] << std::endl;
	}
	opcion = capturarOpcion();

	return local.getArticulo(lineaEspecifica, opcion);
}




