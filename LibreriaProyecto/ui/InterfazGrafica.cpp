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
			"1. Ver articulos.",
			"2. Agregar articulo.",
			"3. Modificar articulo.",
			"4. Eliminar articulo."
	};
}

InterfazGrafica::~InterfazGrafica() {}

//	Metodos Generales.

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

void InterfazGrafica::mostrarCategorias() {
	local.getCategorias().foreach([](Categoria* c) {
		c->imprimir();
	});
}

void InterfazGrafica::mostrarLineasGenerales(const ClinkedList<LineaGeneral*>* lgs) {
	if(lgs != nullptr) {
		lgs->foreach([](LineaGeneral* lg) {
			lg->imprimir();
		});
	} else {
		std::cout << "{InterfazGrafica::mostrarLineasGenerales} lista vacia" << std::endl;
	}

}

void InterfazGrafica::mostrarLineasEspecificas(const ClinkedList<LineaEspecifica*>* les) {
	if(les != nullptr) {
		les->foreach([](LineaEspecifica* le) {
			le->imprimir();
		});
	} else {
		std::cout << "{InterfazGrafica::mostrarLineasEspecificas} lista vacia" << std::endl;
	}
}

void InterfazGrafica::mostrarArticulos(const ClinkedList<Articulo*>* as) {
	if(as != nullptr) {
		as->foreach([](Articulo* a) {
			a->imprimir();
		});
	} else {
		std::cout << "{InterfazGrafica::mostrarArticulos} lista vacia" << std::endl;
	}
}

//	Metodos Clientes

void InterfazGrafica::ejecutarOpcionCliente(int opcion) {

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
			modificarCarrito();
			break;
		case 5:
			std::cout << " " << std::endl;
			std::cout << "----->Pagando carrito" << std::endl;
			pagarCarrito();
			break;
		default:
			std::cout << " " << std::endl;
			std::cout << "----->Opcion invalida. Volviendo al menu inicial" << std::endl;
			break;
	}

	inicializar();
}

void InterfazGrafica::comprar() {
	Categoria* categoria = seleccionarCategoria();

	if(categoria != nullptr) {
		LineaGeneral* lineaG = seleccionarLineaGeneral(categoria->getCodigo());
		if(lineaG != nullptr) {
			std::cout << "Linea General seleccionada: " << lineaG->getNombre() << std::endl;
			LineaEspecifica* lineaE = seleccionarLineaEspecifica(lineaG);
			if(lineaE != nullptr) {
				std::cout << "Linea Especifica seleccionada: " << lineaE->getNombre() << std::endl;
				Articulo* articulo = seleccionarArticulo(lineaE);
				if(articulo != nullptr) {
					comprarArticulo(articulo);
				}else {
					std::cout << "****Linea Especifica invalida****" << std::endl;
				}
			}else {
				std::cout << "****Linea General invalida****" << std::endl;
			}
		}else {
			std::cout << "****Linea general invalida****" << std::endl;
		}
	} else {
		std::cout << "****Categoria invalida****" << std::endl;
	}
}

void InterfazGrafica::comprarArticulo(Articulo* articulo) {
	int opcion = 0;
	int cantidad = 0;

	std::cout << "" << std::endl;
	std::cout << "Articulo seleccionado: " << *articulo << std::endl;
	std::cout << "Comprar este articulo? 1. Si / 2. No" << std::endl;

	opcion = capturarOpcion();
	if(opcion == 1) {
		if(opcion == 1) {
			std::cout << "Introduzca la cantidad que desea de este producto" << std::endl;
			cantidad = capturarOpcion();
			if(cantidad < 1) {
				Carrito* carr = getCarrito();
				carr->agregarArticulo(articulo, cantidad);
				std::cout << cantidad << " " << articulo->getNombre() <<
						" agregado a " << carr->getNombre() << std::endl;

			}
		} else {
			std::cout << "Volviendo al menu inicial" << std::endl;
		}
	} else {
		std::cout << "Opcion invalida" << std::endl;
	}
}

Carrito* InterfazGrafica::getCarrito() {
	int opcion = capturarOpcion();
	std::cout << "1. Crear un nuevo carrito, 2. Usar uno existente" << std::endl;

	if(opcion == 1) {
		std::string nombre = "";
		std::cout << "Ingrese el nombre del carrito:" << std::endl;
		std::getline(std::cin, nombre);
		Carrito* nuevoCarrito = new Carrito(nombre);
		//Usuario getCarritos()->addLast(nuevoCarrito);
		return nuevoCarrito;
	} else if(opcion == 2){
		std::cout << "Mis carritos:" << std::endl;
		//Imprimir carritos y elegir el fucking carrito
		// return carrito;
	}

	return 0;
}

void InterfazGrafica::pagarCarrito() {
	std::cout << "Elija el carrito que desea pagar" << std::endl;

	/*
	 *  Mostrar los carritos del cliente que no hayan sido comprados
	 *  int opcion = obtenerOpcion();
	 */

	std::cout << "El carrito que usd va a pagar es: " << carrito->getNombre() << std::endl;
//	carrito->setEstaPago(true);
	std::cout << "La transaccion ha sido realizada exitosamente" << std::endl;
}

void InterfazGrafica::modificarCarrito() {
	std::cout << "Elija el carrito:" << std::endl;
	 //Mostrar los carritos y verificar que no este pago

	std::cout << "1. Cambiar el nombre del carrito" << std::endl;
	std::cout << "2. Eliminar un articulo" << std::endl;
	std::cout << "3. Eliminar carrito" << std::endl;

	/*
	 *  DO SOME SHIT HERE
	 */
}

/*
 * 	Este metodo debe interactuar con el usuario directamente
 */
void InterfazGrafica::mostrarCarritos() {

	/*
	for(unsigned i = 0; i < carrito->getProductos()->length(); i++) {
		std::cout << (*carrito->getProductos())[i]->getCantidad() <<
			" " <<  (*carrito->getProductos())[0]->getArticulo()->getNombre() <<
			std::endl;
	}
	std::cout << "--------------------------------------" << std::endl;
	std::cout << "Total: " << carrito->precio() << std::endl;

	*/
}

/*
 * 	Este metodo tiene que modificarse para que ejecute la accion
 * 	de cada tipo de usuario.
 */
void InterfazGrafica::inicializar() {
	int opcion;

	this->mostrarMenu(this->opcionesCliente);
	opcion = this->capturarOpcion();
	this->ejecutarOpcionCliente(opcion);
}


Categoria* InterfazGrafica::seleccionarCategoria() {
	int categoria = 0;

	mostrarCategorias();
	categoria = capturarOpcion();

	if(categoria > 0 && categoria <= local.getCategorias().length()) {
		return &local.getCategoria(categoria);
	} else {
		return nullptr;
	}

}

LineaGeneral* InterfazGrafica::seleccionarLineaGeneral(int categoria) {
	int opcion = 0;

	std::cout << "Lineas Generales en esta categoria: " << std::endl;
	mostrarLineasGenerales(&local.getLineasGenerales(categoria));
	opcion = capturarOpcion();

	return &local.getLineaGeneral(opcion, categoria);
}

LineaEspecifica* InterfazGrafica::seleccionarLineaEspecifica(LineaGeneral* lineaGeneral) {
	int opcion = 0;

	std::cout << "Lineas Especificas en esta Linea General: " << std::endl;
	mostrarLineasEspecificas(&local.getLineasEspecificas(lineaGeneral));

	opcion = capturarOpcion();

	return &local.getLineaEspecifica(lineaGeneral, opcion);
}

Articulo* InterfazGrafica::seleccionarArticulo(LineaEspecifica* lineaEspecifica) {
	int opcion = 0;

	std::cout << "Articulos en esta Linea Especifica: " << std::endl;
	mostrarArticulos(&local.getArticulos(lineaEspecifica));
	opcion = capturarOpcion();

	return &local.getArticulo(lineaEspecifica, opcion);
}

//	Metodos Dependiente

void InterfazGrafica::ejecutarOpcionDependiente(int opcion) {
	switch (opcion) {
		case 1:
			std::cout << " " << std::endl;
			std::cout << "----->Ver Pedidos pendientes" << std::endl;
			break;
		case 2:
			std::cout << " " << std::endl;
			std::cout << "----->Entregando Pedido" << std::endl;
			break;
		default:
			std::cout << " " << std::endl;
			std::cout << "----->Opcion invalida. Volviendo al menu inicial" << std::endl;
			break;
	}

}

void InterfazGrafica::entregarCarrito() {
	std::cout << "Elija el carrito que desea entregar" << std::endl;

	/*
	 *  Mostrar pedidos pendientes.
	 */
}


//	Metodos Admin

void InterfazGrafica::ejecutarOpcionAdmin(int opcion) {
	switch (opcion) {
		case 1:
			std::cout << " " << std::endl;
			std::cout << "----->Mostrando Articulos" << std::endl;
			verArticulos();
			break;
		case 2:
			std::cout << " " << std::endl;
			std::cout << "----->Agregando Articulo" << std::endl;
			comprar();
			break;
		case 3:
			std::cout << " " << std::endl;
			std::cout << "----->Modificando Articulo" << std::endl;
			mostrarCarritos();
			break;
		case 4:
			std::cout << " " << std::endl;
			std::cout << "----->Eliminando Articulo" << std::endl;
			modificarCarrito();
			break;
		default:
			std::cout << " " << std::endl;
			std::cout << "----->Opcion invalida. Volviendo al menu inicial" << std::endl;
			break;
	}
}

void InterfazGrafica::verTodosArticulos() {
	std::cout << "Todos los articulos disponibles: " << std::endl;
	local.getCategorias().foreach([](Categoria* c) {
		c->getLineaGenerals().foreach([](LineaGeneral* lg) {
			lg->getLineasEspecificas().foreach([](LineaEspecifica* le) {
				le->getArticulos().foreach([](Articulo* a) {
					a->imprimir();
				});
			});
		});
	});
}

void InterfazGrafica::agregarArticulo() {
	Categoria* categoria = 0;
	LineaGeneral* lineaG = 0;
	LineaEspecifica* lineaE = 0;
	int codigo = 0;
	long double precio = 0.0;
	std::string nombre;
	std::string marca;

	std::cout << "Seleccione la categoria donde va a agregar el articulo" << std::endl;
	mostrarCategorias();
	categoria = &local.getCategoria(capturarOpcion());

	std::cout << "Seleccione la linea general donde va a agregar el articulo" << std::endl;
	mostrarLineasGenerales(&local.getLineasGenerales(categoria->getCodigo()));
	lineaG = &local.getLineaGeneral(capturarOpcion(), categoria->getCodigo());

	std::cout << "Seleccione la linea especifica donde va a agregar el articulo" << std::endl;
	mostrarLineasEspecificas(&local.getLineasEspecificas(lineaG));
	lineaE = &local.getLineaEspecifica(lineaG, capturarOpcion());

	//	El Codigo no deberia generarse solo?
	std::cout << "Ingrese el codigo del nuevo articulo" << std::endl;
	codigo = capturarOpcion();
	std::cout << "Ingrese el nombre del nuevo articulo" << std::endl;
	std::cin >> nombre;
	std::cout << "Ingrese la marca del nuevo articulo" << std::endl;
	std::cin >> marca;
	std::cout << "Ingrese el precio " << std::endl;
	precio = (double) capturarOpcion();

	std::cout << "Agregando articulo" << std::endl;
	lineaE->agregarArticulo(new Articulo(codigo, nombre, marca, precio));
}

void InterfazGrafica::modificarArticulo() {
	int opcion = 0;
	Articulo* articulo = 0;
	std::cout << "Elija el articulo que desea modificar" << std::endl;
	verTodosArticulos();
	opcion = capturarOpcion();
	//articulo = local.getArticulo
}











