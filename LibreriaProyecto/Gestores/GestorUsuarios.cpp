#include "GestorUsuarios.h"
#include "..\repositorys\Repositorios.h"
#include <exception>

GestorUsuarios::GestorUsuarios() {}

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
void GestorUsuarios::imprimirComprasPorCriterio(ListFactories::CriteriosCarritos c)const
{
	Repositorios::repoCompras.getAll()->foreach([](Carrito *c)
	{
		c->printPretty(std::cout) << std::endl;

	}, static_cast<int>(c));

}
//cambiar por un enum
void GestorUsuarios::imprimirCarritoPorCriterio(ListFactories::CriteriosCarritos c) const
{

	Repositorios::repoCarritos.getAll()->foreach([](Carrito *c)
	{
		c->printPretty(std::cout)<<std::endl;

	}, static_cast<int>(c));

	
}
void GestorUsuarios::imprimirUsuarios() const
{
	auto list = Repositorios::repoUsuario.getElements();

	list->foreach([](Usuario* u){ u->prettyPrint(std::cout) << std::endl; });

	delete list;
}


MultiplyList<Carrito*>* GestorUsuarios::getCarritosDeCliente(int idCliente) const
{
	return Repositorios::repoCarritos.getALL([=](Carrito* c){return c->getIdUsuario() == idCliente; });
}
MultiplyList<Carrito*>* GestorUsuarios::getComprasDeCliente(int idCliente) const
{
	return Repositorios::repoCompras.getALL([=](Carrito* c){return c->getIdUsuario() == idCliente; });
}
std::string GestorUsuarios::eliminarCompra(int idCompra) const
{
	permmitEnforcer(Rol::DEPENDIENTE);
	bool seElimino= Repositorios::repoCompras.remove([=](Carrito* c)
	{
		return c->getCodigo() == idCompra; 
	});

	if (seElimino) return "Se elimino con exito";

	return "El codigo no existe";
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

std::string GestorUsuarios::agregarCarrito(Carrito*& carrito) const
{
	if (Repositorios::repoCarritos.addElement(carrito))
		return "Se agrego con exito";

	delete carrito;
	carrito = nullptr;

	return "Ya existe un carrito con ese codigo";
}
std::string GestorUsuarios::agregarCompra(Carrito*& carrito) const
{
	
	auto last = Repositorios::repoCompras.getAll();
	int codigo = last->empty() ? 0 : last->getMax(0)->getCodigo();
	carrito->setCodigo(codigo + 1);

	if (Repositorios::repoCompras.addElement(carrito))
		return "Se agrego con exito";

	delete carrito;
	carrito = nullptr;

	return "Ya existe una compra con ese codigo";
}

void GestorUsuarios::actualizarCarritos() const
{
	Repositorios::repoCarritos.saveALL();
}

Carrito*  GestorUsuarios::getCarritoPorId(int codigo) const
{
	return Repositorios::repoCarritos.get([=](Carrito* c)
	{
		return c->getCodigo() == codigo;
	});
}

Carrito* GestorUsuarios::getCompraPorId(int codigo) const
{
	return Repositorios::repoCarritos.get([=](Carrito* c)
	{
		return c->getCodigo() == codigo;
	});

}
const MultiplyList<Carrito*>* GestorUsuarios::getCarritos() const
{
	return Repositorios::repoCarritos.getAll();
}
