/*
 * InterfazGrafica.cpp
 *
 *  Created on: Aug 8, 2015
 *      Author: Daniel
 */

#include "InterfazGrafica.h"
#include "../repositorys/Repositorios.h"
#include <iostream>
#include <sstream>

InterfazGrafica::InterfazGrafica()
	: gUsuarios(GestorUsuarios()), gArticulos(GestorLineasDeAriculos()) {

	this->opcionesCliente = {
			"1. Ver articulos.",
			"2. Comprar articulos",
			"3. Ver carritos.",
			"4. Pagar pedido."
	};

	this->opcionesDependiente = {
			"1. Ver pedidos.",
			"2. Entregar pedido."
	};

	this->opcionesAdmin = {
			"1. Ver articulos.",
			"2. Agregar articulo.",
			"3. Modificar articulo.",
			"4. Eliminar articulo.",
			"5. Agregar Categoria",
			"6. Modificar Categoria",
			"7. Eliminar Categoria"
			"8. Agregar Linea General",
			"9. Modificar Linea General",
			"10. Eliminar Linea General",
			"11. Agregar Linea Especifica",
			"12. Modificar Linea Especifica",
			"13. Eliminar Linea Especifica"
	};

}

InterfazGrafica::~InterfazGrafica() {}

//	Metodos Generales.

int InterfazGrafica::capturarOpcion(){
	std::string opcion;
	bool esNumero = false;
	int numero;

	while (!esNumero) {
	   std::cout << "Ingrese un numero: ";
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

void InterfazGrafica::mostrarMenu(Usuario* usuario) {
	string_vect menu;

	std::cout << " " << std::endl;
	std::cout << "*-----------------------------------------*" << std::endl;
	if (usuario != nullptr) {
		switch (usuario->getRol()) {
		case Rol::ADMIN:
			menu = this->opcionesAdmin;
			break;
		case Rol::DEPENDIENTE:
			menu = this->opcionesDependiente;
			break;
		case Rol::CLIENTE:
			menu = this->opcionesCliente;
			break;
		default:
			break;
		}
	} else {
	}
	
	std::cout << "*-----------------------------------------*" << std::endl;
	std::cout << " " << std::endl;

	for (unsigned i = 0; i < menu.size(); i++) {
		std::cout << menu[i] << std::endl;
	}
}

void InterfazGrafica::verPedidos() {
	Repositorios::repoCompras.getAll().foreach([=](Carrito* c) {
		std::cout << c->getCodigo() << ". "  << c->getNombre() ;
		c->getProductos().foreach([=](Pedido* p){
			std::cout << p->getCantidad()
				<<" unidades de "
				<< p->getArticulo()->getNombre()
				<< std::endl;
		});
	});
}

void InterfazGrafica::verArticulos() {
	gArticulos.imprimirEstrucutura();
}

void InterfazGrafica::mostrarCategorias() {
	std::cout << "******************" << std::endl;
	auto categorias = gArticulos.getCategorias();
	
	
	categorias->foreach([](Categoria* c) {
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

void InterfazGrafica::mostrarLineasGenerales() {
	gArticulos.getCategorias()->foreach([](Categoria* c) {
		c->getLineaGenerals().foreach([](LineaGeneral* lg) {
			lg->imprimir();
		});
	});
}

void InterfazGrafica::mostrarLineasEspecificas() {
	gArticulos.getCategorias()->foreach([](Categoria* c) {
		c->getLineaGenerals().foreach([](LineaGeneral* lg) {
			lg->getLineasEspecificas().foreach([](LineaEspecifica* le) {
				le->imprimir();
			});
		});
	});
}

void InterfazGrafica::mostrarCarritos(int codigoCliente) {
		gUsuarios.getCarritos().foreach([codigoCliente](Carrito* c){
			if(c->getIdUsuario() == codigoCliente) {
				c->printPretty(std::cout)<<std::endl;
				c->getProductos().foreach([=](Pedido* p){
					
					std::cout << p->getCantidad() 
						<<" unidades de " 
						<< p->getArticulo()->getNombre() 
						<< std::endl;
				});
			}
		});
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
			mostrarCarritos(gUsuarios.getUsuarioActual()->getCodigo());
			break;
		case 4:
			std::cout << " " << std::endl;
			std::cout << "----->Pagando carrito" << std::endl;
			pagarCarrito();
			break;
		default:
			std::cout << " " << std::endl;
			std::cout << "----->Opcion invalida. Volviendo al menu inicial" << std::endl;
			break;
	}
}

//El usuario no compra articulos los agrega al carrito
void InterfazGrafica::comprar() {

	Categoria* categoria = seleccionarCategoria();
	if(categoria != nullptr) {
		LineaGeneral* lineaG = seleccionarLineaGeneral(categoria);
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
	std::cout << "Agregar a un carrito este articulo? 1. Si / 2. No" << std::endl;

	opcion = capturarOpcion();
	if(opcion == 1) 
	{
			std::cout << "Introduzca la cantidad que desea de este producto" << std::endl;
			cantidad = capturarOpcion();
			if(cantidad > 0) 
			{
				Carrito* carr = getCarrito();
				carr->agregarArticulo(articulo, cantidad);
				gUsuarios.actualizarCarritos();

				std::cout << cantidad << " " << articulo->getNombre() <<
						" agregado a " << carr->getNombre() << std::endl;
			}
	} 
	else 
	{
		std::cout << "Volviendo al menu inicial" << std::endl;
	}
}

Carrito* InterfazGrafica::getCarrito() {
	std::cout << "1. Crear un nuevo carrito, 2. Usar uno existente" << std::endl;
	int opcion = capturarOpcion();

	if(opcion == 1)
	{
		std::string nombre = "";
		std::cout << "Ingrese el codigo del carrito:" << std::endl;
		int codigo = capturarOpcion();
		std::cout << "Ingrese el nombre del carrito:" << std::endl;
		std::getline(std::cin, nombre);
		
		Carrito* nuevoCarrito = new Carrito(codigo, gUsuarios.getUsuarioActual()->getCodigo(), nombre);
		std::cout << gUsuarios.agregarCarrito(nuevoCarrito) << std::endl;

		return nuevoCarrito;
	} 
	else if(opcion == 2)
	{
		std::cout << "Mis carritos:" << std::endl;
		mostrarCarritos(gUsuarios.getUsuarioActual()->getCodigo());
	}

	return nullptr;
}

void InterfazGrafica::pagarCarrito() {

	std::cout << "Elija el carrito que desea pagar" << std::endl;
	mostrarCarritos(gUsuarios.getUsuarioActual()->getCodigo());
	int opcion = capturarOpcion();
	Carrito* carrito = gUsuarios.getCarritoPorId(opcion);
	
	std::cout << "Ingrese el codigo de la compra"<<std::endl;
	int codigo  = capturarOpcion();
	Carrito *compra = new Carrito(codigo, carrito->getIdUsuario(), carrito->getNombre());
	
	std::cout << "El carrito que ud va a pagar es: " << carrito->getNombre() << std::endl;
	std::cout << gUsuarios.agregarCompra(compra) << std::endl;
	

}
void InterfazGrafica::modificarCarrito() {
	std::cout << "Elija el carrito:" << std::endl;
	 //Mostrar los carritos y verificar que no este pago

	std::cout << "1. Cambiar el nombre del carrito" << std::endl;
	std::cout << "2. Eliminar un articulo" << std::endl;
	std::cout << "3. Eliminar carrito" << std::endl;
}

/*
 * 	Este metodo tiene que modificarse
para que ejecute la accion
 * 	de cada tipo de usuario.
 */
void InterfazGrafica::inicializar() {
	int opcion = 0;
	int id = 0;
	std::string psswrd;
	this->gUsuarios.imprimirUsuarios();
	std::cout << "Ingrese su numero de ID" << std::endl;
	id = capturarOpcion();
	std::cout << "Ingrese su contraseña" << std::endl;
	std::getline(std::cin, psswrd);

	this->gUsuarios.iniciarSession(id, psswrd);
	if(this->gUsuarios.getUsuarioActual() != nullptr) 
	{
		std::cout << "Bienvenido " << this->gUsuarios.getUsuarioActual()->getNombre() << std::endl;
		do 
		{
			this->mostrarMenu(this->gUsuarios.getUsuarioActual());
			opcion = this->capturarOpcion();
			this->routeOpcion(opcion, this->gUsuarios.getUsuarioActual()->getRol());
		} 
		while(opcion != 0);
	} 
	else 
	{
		std::cout << "Usuario no existe" << std::endl;
	}
}

void InterfazGrafica::routeOpcion(int opcion, Rol rol) {
	switch (rol) {
		case Rol::CLIENTE:
			ejecutarOpcionCliente(opcion);
			break;
		case Rol::DEPENDIENTE:
			ejecutarOpcionDependiente(opcion);
			break;
		case Rol::ADMIN:
			ejecutarOpcionAdmin(opcion);
			break;
		default:
			std::cout << "fuck offfffffff" << std::endl;
			break;
	}
}


Categoria* InterfazGrafica::seleccionarCategoria() {
	int categoria = 0;

	mostrarCategorias();
	categoria = capturarOpcion();
	return gArticulos.getCategoria(categoria);
}

LineaGeneral* InterfazGrafica::seleccionarLineaGeneral(Categoria* categoria) {

	std::cout << "Lineas Generales en esta categoria: " << std::endl;
	mostrarLineasGenerales(&categoria->getLineaGenerals());
	return categoria->buscarPorCodigo(capturarOpcion());
}

LineaEspecifica* InterfazGrafica::seleccionarLineaEspecifica(LineaGeneral* lineaGeneral) {
	
	std::cout << "Lineas Especificas en esta Linea General: " << std::endl;
	mostrarLineasEspecificas(&lineaGeneral->getLineasEspecificas());
	return lineaGeneral->getLineaEspecifica(capturarOpcion());
}

Articulo* InterfazGrafica::seleccionarArticulo(LineaEspecifica* lineaEspecifica) {
	
	std::cout << "Articulos en esta Linea Especifica: " << std::endl;
	mostrarArticulos(&lineaEspecifica->getArticulos());
	return lineaEspecifica->buscarPorCodigo(capturarOpcion());
}

//	Metodos Dependiente

void InterfazGrafica::ejecutarOpcionDependiente(int opcion) {
	switch (opcion) {
		case 1:
			std::cout << " " << std::endl;
			std::cout << "----->Ver Pedidos pendientes" << std::endl;
			verPedidos();
			break;
		case 2:
			std::cout << " " << std::endl;
			std::cout << "----->Entregando Pedido" << std::endl;
			entregarCarrito();
			break;
		default:
			std::cout << " " << std::endl;
			std::cout << "----->Opcion invalida. Volviendo al menu inicial" << std::endl;
			break;
	}

}

void InterfazGrafica::entregarCarrito() {
	
	using ListFactories::CriteriosCarritos;
	
	std::cout << "Elija un criterio de ordenamiento" << std::endl;
	std::cout << "ID = 0, NOMBRE = 1, IDUSUARIO = 2, CANTIDAD = 3, PRECIO = 4, FIFO = 5" <<std::endl;
	int criterio = static_cast<unsigned>(capturarOpcion());
	if (criterio > 5) criterio = 0; 


	std::cout << "Elija la compra que desea entregar" << std::endl;
	gUsuarios.imprimirComprasPorCriterio(static_cast<CriteriosCarritos>(criterio));
	std::cout << gUsuarios.eliminarCompra(capturarOpcion()) << std::endl;

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
			agregarArticulo();
			break;
		case 3:
			std::cout << " " << std::endl;
			std::cout << "----->Modificando Articulo" << std::endl;
			modificarArticulo();
			break;
		case 4:
			std::cout << " " << std::endl;
			std::cout << "----->Eliminando Articulo" << std::endl;
			eliminarArticulo();
			break;
		case 5:
			std::cout << " " << std::endl;
			std::cout << "----->Agregando Categoria" << std::endl;
			agregarCategoria();
			break;
		case 6:
			std::cout << " " << std::endl;
			std::cout << "----->Modificando Categoria" << std::endl;
			modificarCategoria();
			break;
		case 7:
			std::cout << " " << std::endl;
			std::cout << "----->Eliminando Categoria" << std::endl;
			eliminarCategoria();
			break;
		case 8:
			std::cout << " " << std::endl;
			std::cout << "----->Agregando Linea General" << std::endl;
			agregarLineaGeneral();
			break;
		case 9:
			std::cout << " " << std::endl;
			std::cout << "----->Modificando Linea General" << std::endl;
			modificarLineaGeneral();
			break;
		case 10:
			std::cout << " " << std::endl;
			std::cout << "----->Eliminando Linea General" << std::endl;
			eliminarLineaGeneral();
			break;
		case 11:
			std::cout << " " << std::endl;
			std::cout << "----->Agregando Linea Especifica" << std::endl;
			agregarLineaEspecifica();
			break;
		case 12:
			std::cout << " " << std::endl;
			std::cout << "----->Modificando Linea Especifica" << std::endl;
			modificarLineaEspecifica();
			break;
		case 13:
			std::cout << " " << std::endl;
			std::cout << "----->Eliminando Linea Especifica" << std::endl;
			elimnarLineaEspecifica();
			break;
		default:
			std::cout << " " << std::endl;
			std::cout << "----->Opcion invalida. Volviendo al menu inicial" << std::endl;
			break;
	}
}

void InterfazGrafica::verTodosArticulos() {
	std::cout << "Todos los articulos disponibles: " << std::endl;
	
	auto articulos = gArticulos.getCopiaArticulos();
		
	articulos->foreach([](Articulo* a)
	{
		a->imprimir();
	});
	delete articulos;
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
	categoria = seleccionarCategoria();
	std::cout << "Seleccione la linea general donde va a agregar el articulo" << std::endl;
	lineaG = seleccionarLineaGeneral(categoria);
	std::cout << "Seleccione la linea especifica donde va a agregar el articulo" << std::endl;
	lineaE = seleccionarLineaEspecifica(lineaG);

	std::cout << "Ingrese el codigo del nuevo articulo" << std::endl;
	codigo = capturarOpcion();
	std::cout << "Ingrese el nombre del nuevo articulo" << std::endl;
	std::cin >> nombre;
	std::cout << "Ingrese la marca del nuevo articulo" << std::endl;
	std::cin >> marca;
	std::cout << "Ingrese el precio " << std::endl;
	precio = (double) capturarOpcion();

	std::cout << "Agregando articulo" << std::endl;

	auto art = new Articulo(codigo, nombre, marca, precio);
	
	gArticulos.agregarArticulo(art, lineaE);
	
}

void InterfazGrafica::modificarArticulo() {
	int opcion = 0;
	Articulo* articulo = nullptr;
	std::cout << "Elija el articulo que desea modificar" << std::endl;
	verTodosArticulos();
	opcion = capturarOpcion();
	articulo = gArticulos.getArticulo(opcion);
	articulo->imprimir();

	std::cout << "1. Cambiar Nombre" << std::endl;
	std::cout << "2. Cambiar Marca" << std::endl;
	std::cout << "3. Cambiar Precio" << std::endl;
	opcion = capturarOpcion();

	switch (opcion) {
		case 1: {
				std::string nombre;
				std::cout << "Digite el nuevo nombre del articulo" << std::endl;
				std::getline(std::cin, nombre);
				articulo->setNombre(nombre);
			}
			break;
		case 2: {
				std::string marca;
				std::cout << "Digite la nueva marca del articulo" << std::endl;
				std::getline(std::cin, marca);
				articulo->setMarca(marca);
			}
			break;
		case 3: {
				std::cout << "Digite el nuevo precio del articulo" << std::endl;
				double precio = static_cast<double> (capturarOpcion());
				articulo->setPrecio(precio);
			}
			break;
		default:
			std::cout << "Opcion invalida" << std::endl;
			break;
	}

	gArticulos.actualizarArticulos();
	std::cout << "Resultado:" << std::endl;
	articulo->imprimir();
}

void InterfazGrafica::eliminarArticulo() 
{
	auto articulos = gArticulos.getCopiaArticulos();
	mostrarArticulos(articulos);
	std::cout << "Ingrese el numero de codigo" << std::endl;

	gArticulos.eliminarArticulo(capturarOpcion());

	delete articulos;
}

void InterfazGrafica::agregarCategoria() {
	int codigo = 0;
	int pasillo = 0;
	std::string nombre;

	std::cout << "Ingrese el numero de codigo" << std::endl;
	codigo = capturarOpcion();
	std::cout << "Ingrese el numero de pasillo" << std::endl;
	pasillo = capturarOpcion();
	std::cout << "Ingrese el nombre categoria" << std::endl;
	std::getline(std::cin, nombre);

	std::cout << "Agregando Categoria:" << std::endl;
	std::cout<< gArticulos.agregarCategoria(new Categoria(codigo, pasillo, nombre));
	std::cout << std::endl;
}

void InterfazGrafica::modificarCategoria() {
	int opcion = 0;
	Categoria* categoria = 0;
	std::cout << "Elija la categoria que desea modificar" << std::endl;
	mostrarCategorias();
	categoria = gArticulos.getCategoria(capturarOpcion());

	if (categoria == nullptr)
	{
		std::cout << "la categoria no existe" << std::endl;
		return;
	}

	categoria->imprimir();

	std::cout << "1. Cambiar codigo" << std::endl;
	std::cout << "2. Cambiar nombre" << std::endl;
	std::cout << "3. Cambiar numero de pasillo" << std::endl;
	opcion = capturarOpcion();

	switch (opcion) {
		case 1: {
				std::cout << "Digite el nuevo codigo de la categoria" << std::endl;
				int codigo = capturarOpcion();
				categoria->setCodigo(codigo);
			}
			break;
		case 2: {
				std::string nombre;
				std::cout << "Digite el nuevo nombre de la categoria" << std::endl;
				std::getline(std::cin, nombre);
				categoria->setNombre(nombre);
			}
			break;
		case 3: {
				std::cout << "Digite el nuevo numero de pasillo del categoria" << std::endl;
				int pasillo = capturarOpcion();
				categoria->setPasillo(pasillo);
			}
			break;
		default:
			std::cout << "Opcion invalida" << std::endl;
			break;
	}

	gArticulos.actualizarCategorias();
	std::cout << "Resultado:" << std::endl;
	categoria->imprimir();
}

void InterfazGrafica::eliminarCategoria() {
	std::cout << "Ingrese el codigo de la categoria que desea eliminar" << std::endl;
	mostrarCategorias();
	int codigo = capturarOpcion();

	gArticulos.eliminarCategoria(codigo);
}

void InterfazGrafica::agregarLineaGeneral() {
	int codigo = 0;
	std::string nombre;
	Categoria* cat = nullptr;

	std::cout << "Ingrese el codigo de la nueva linea general" << std::endl;
	codigo = capturarOpcion();
	std::cout << "Ingrese el nombre" << std::endl;
	std::getline(std::cin, nombre);
	std::cout << "Escoja la categoria a la que quiere agregarle esta nueva linea" << std::endl;
	mostrarCategorias();
	cat = gArticulos.getCategoria(capturarOpcion());

	if (cat == nullptr)
	{
		std::cout << "La categoria no existe" << std::endl;
		return;
	}
	std::cout << "Agregando Linea General" << std::endl;
	std::cout << gArticulos.agregarLineaGeneral(new LineaGeneral(codigo, nombre), cat);
	
	std::cout << std::endl;
}

void InterfazGrafica::modificarLineaGeneral() {
	
	LineaGeneral* lg = 0;
	std::cout << "Elija la linea general que desea modificar" << std::endl;
	mostrarLineasGenerales();

	lg = gArticulos.getLineaGeneral(capturarOpcion());
	
	if (lg == nullptr)
	{
		std::cout << "La linea general no existe" << std::endl;
		return;
	}
	
	lg->imprimir();



			
	std::string nombre;
	std::cout << "Digite el nuevo nombre de la linea general" << std::endl;
	std::getline(std::cin, nombre);
	lg->setNombre(nombre);
			

	gArticulos.actualizarLineasGenerales();
	std::cout << "Resultado:" << std::endl;
	lg->imprimir();
}

void InterfazGrafica::eliminarLineaGeneral() {
	std::cout << "Ingrese el codigo de la linea general que desea eliminar" << std::endl;
	mostrarLineasGenerales();
	int codigo = capturarOpcion();

	gArticulos.eliminarLineaGeneral(codigo);
}

void InterfazGrafica::agregarLineaEspecifica() {
	int codigo = 0;
	int codigo2 = 0;
	std::string nombre;
	Categoria* cat = 0;
	LineaGeneral* lg = 0;
	LineaEspecifica* le = 0;

	std::cout << "Ingrese el codigo de la nueva linea general" << std::endl;
	std::getline(std::cin, nombre);
	std::cout << "Escoja la categoria a la que quiere agregarle esta nueva linea" << std::endl;
	mostrarCategorias();
	cat = Repositorios::repoCategoria.getElement(capturarOpcion());
	mostrarLineasGenerales(&cat->getLineaGenerals());
	std::cout << "Escoja la linea general a la que quiere agregarle esta nueva linea" << std::endl;
	lg = Repositorios::repoLineaGeneral.getElement(capturarOpcion());

	std::cout << "Agregando Linea General" << std::endl;
	le = new LineaEspecifica(codigo, nombre);
	std::cout << gArticulos.agregarLineaEspecifica(le, lg) << std::endl;
}

void InterfazGrafica::modificarLineaEspecifica() {
	int opcion = 0;
	LineaEspecifica* le = 0;
	std::cout << "Elija la linea especifica que desea modificar" << std::endl;
	mostrarLineasEspecificas();
	opcion = capturarOpcion();
	le = gArticulos.getLineaEspecifica(opcion);
	
	if (le == nullptr)
	{
		std::cout << "No existe una linea especifica con este codigo" << std::endl;
		return;
	}
	le->imprimir();

	std::cout << "1. Cambiar codigo" << std::endl;
	std::cout << "2. Cambiar nombre" << std::endl;
	opcion = capturarOpcion();

	switch (opcion) {
		case 1: {
				std::cout << "Digite el nuevo codigo de la linea especifica" << std::endl;
				int codigo = capturarOpcion();
				le->setCodigo(codigo);
			}
			break;
		case 2: {
				std::string nombre;
				std::cout << "Digite el nuevo nombre de la linea especifica" << std::endl;
				std::getline(std::cin, nombre);
				le->setNombre(nombre);
			}
			break;
		default:
			std::cout << "Opcion invalida" << std::endl;
			break;
	}

	gArticulos.actualizarLineasEspecificas();
	std::cout << "Resultado:" << std::endl;
	le->imprimir();
}

void InterfazGrafica::elimnarLineaEspecifica() {
	std::cout << "Ingrese el codigo de la linea especifica que desea eliminar" << std::endl;
	mostrarLineasEspecificas();
	int codigo = capturarOpcion();

	gArticulos.eliminarLineaEspecifica(codigo);
}
