#include "GestorUsuarios.h"
#include "repositorys\Repositorios.h"
#include <sstream>
#include "utils\ListFactories.h"
#include <stdexcept>
#include <exception>



bool GestorUsuarios::iniciarSession(int id, const std::string& password) const
{
	return Repositorios::session.iniciarSession(id, password);
}
Usuario* GestorUsuarios::getUsuarioActual() const
{
	return Repositorios::session.getSessionActual();
}
void GestorUsuarios::cerrarSession() const
{
	Repositorios::session.cerrarSession();
}
bool GestorUsuarios::crearUsuario(Usuario* usuario) const
{
	auto u = getUsuarioActual();
	if (u != nullptr && u->getRol() != Rol::ADMIN)
		throw std::exception("Solo el administrador puede crear usuarios");

	return Repositorios::repoUsuario.addElement(usuario);
}

void GestorUsuarios::crearCarrito(Carrito* carrito) const
{
	permmitEnforcer(Rol::CLIENTE);
	Repositorios::repoCarritos.addElement(carrito);
}
//cambiar por un enum
void GestorUsuarios::imprimirCarritoPorCriterio(ListFactories::CriteriosCarritos c) const
{
	std::ostringstream os;
	Repositorios::repoCarritos.getAll().foreach([&os](Carrito *c)
	{
		c->printPretty(std::cout)<<std::endl;

	}, static_cast<int>(c));

	
}
void GestorUsuarios::imprimirUsuarios() const
{
	auto list = Repositorios::repoUsuario.getElements();

	list->foreach([](Usuario* u){ u->prettyPrint(std::cout) << std::endl; });
}
void GestorUsuarios::crearCompra(Carrito*carrito) const
{
	Repositorios::repoCompras.addElement(carrito);
}

MultiplyList<Carrito*>* GestorUsuarios::getCarritosDeCliente(int idCliente) const
{
	return Repositorios::repoCarritos.getALL([=](Carrito* c){return c->getIdUsuario() == idCliente; });
}
MultiplyList<Carrito*>* GestorUsuarios::getComprasDeCliente(int idCliente) const
{
	return Repositorios::repoCompras.getALL([=](Carrito* c){return c->getIdUsuario() == idCliente; });
}
bool GestorUsuarios::eliminarCompra(int idCompra) const
{
	permmitEnforcer(Rol::DEPENDIENTE);
	return Repositorios::repoCompras.remove([=](Carrito* c)
	{
		return c->getCodigo() == idCompra; 
	});
}
bool GestorUsuarios::eliminarCarrito(int idCarrito) const
{
	return Repositorios::repoCompras.remove([=](Carrito* c)
	{
		return c->getCodigo() == idCarrito;
	});
}

void GestorUsuarios::guardarCambiosDeUsuarios() const
{
	Repositorios::repoUsuario.saveUpdates();
}
void GestorUsuarios::permmitEnforcer(Rol rol) const
{
	auto u = getUsuarioActual();
	if (u == nullptr || u->getRol() != rol)
		throw std::invalid_argument("El usuario no tiene permiso");
}