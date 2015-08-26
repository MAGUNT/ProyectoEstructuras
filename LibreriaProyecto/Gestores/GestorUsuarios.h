#pragma once
#include <string>
#include "..\models\usuarios\Usuario.h"
#include "..\models\compras\Carrito.h"
#include "..\lists\MultiplyList.h"
#include "..\utils\ListFactories.h"
class GestorUsuarios
{

private:
	void permmitEnforcer(Rol) const;
public:
	GestorUsuarios();

	bool iniciarSession(int id, const std::string& password) const;
	Usuario* getUsuarioActual()const;
	void cerrarSession()const;
	bool crearUsuario(Usuario*) const;

	void imprimirCarritoPorCriterio(ListFactories::CriteriosCarritos c)const;
	void imprimirComprasPorCriterio(ListFactories::CriteriosCarritos c)const;
	void imprimirUsuarios() const;
	MultiplyList<Carrito*>*getCarritosDeCliente(int idCliente) const;
	MultiplyList<Carrito*>* getComprasDeCliente(int idCliente) const;
	std::string eliminarCompra(int idCompra) const;
	bool eliminarCarrito(int idCompra) const;
	void guardarCambiosDeUsuarios() const;

	

	std::string agregarCarrito(Carrito*& carrito) const;
	std::string agregarCompra(Carrito*& carrito) const;

	void actualizarCarritos() const;

	Carrito* getCarritoPorId(int codigo) const;
	Carrito* getCompraPorId(int codigo) const;
	const MultiplyList<Carrito*>* getCarritos() const;

};

