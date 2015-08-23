#pragma once
#include <string>
#include "models\usuarios\Usuario.h"
#include "models\compras\Carrito.h"
#include  "lists\MultiplyList.h"
class GestorUsuarios
{
public:
	GestorUsuarios();
	~GestorUsuarios();

	bool iniciarSession(int id, const std::string& password);
	Usuario* getUsuarioActual();
	void cerrarSession();
	bool crearUsuario(Usuario*) const ;
	void crearCarrito(Carrito*) const;

	std::string consultarCarritos(int criterio) const;
	std::string consultarUsuarios() const;
	void crearCompra(Carrito*) const;
	void imprimirCarritosPorCriterio() const;
	void imprimirComprasPorCriterio() const;
	MultiplyList<Carrito*>*getCarritosDeCliente(int idCliente) const;
	MultiplyList<Carrito*>* getComprasDeCliente(int idCliente) const;
	void eliminarCompra(int idCompra) const;

};

