#pragma once
#include <string>
#include "models\usuarios\Usuario.h"
#include "models\compras\Carrito.h"
#include  "lists\MultiplyList.h"
#include "utils\ListFactories.h"
class GestorUsuarios
{
public:
	bool iniciarSession(int id, const std::string& password) const;
	Usuario* getUsuarioActual()const;
	void cerrarSession()const;
	bool crearUsuario(Usuario*) const ;
	void crearCarrito(Carrito*) const;

	void imprimirCarritoPorCriterio(ListFactories::CriteriosCarritos c)const;
	void imprimirUsuarios() const;
	void crearCompra(Carrito*) const;
	MultiplyList<Carrito*>*getCarritosDeCliente(int idCliente) const;
	MultiplyList<Carrito*>* getComprasDeCliente(int idCliente) const;
	bool eliminarCompra(int idCompra) const;
	bool eliminarCarrito(int idCompra) const;
	void guardarCambiosDeUsuarios() const;

	void permmitEnforcer(Rol) const;

};

