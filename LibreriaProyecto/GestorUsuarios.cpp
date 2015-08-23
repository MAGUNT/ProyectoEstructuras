#include "GestorUsuarios.h"
#include "repositorys\Repositorios.h"
#include <sstream>

GestorUsuarios::GestorUsuarios()
{
}


GestorUsuarios::~GestorUsuarios()
{
}

bool GestorUsuarios::iniciarSession(int id, const std::string& password)
{
	return Repositorios::session.iniciarSession(id, password);
}
Usuario* GestorUsuarios::getUsuarioActual()
{
	return Repositorios::session.getSessionActual();
}
void GestorUsuarios::cerrarSession()
{
	Repositorios::session.cerrarSession();
}
bool GestorUsuarios::crearUsuario(Usuario* usuario) const
{
	Repositorios::repoUsuario.addElement(usuario);
}

bool GestorUsuarios::crearCarrito(Carrito* carrito) const
{
	Repositorios::repoCarritos.addElement(carrito);
}
//cambiar por un enum
std::string GestorUsuarios::consultarCarritos( int criterio) const
{
	std::ostringstream os;
	Repositorios::repoCarritos.getAll().foreach([&os](Carrito *c)
	{
		os << "Nombre de usuario:" << Repositorios::repoUsuario.getElement(c->getIdUsuario())->getNombre()
			<< "Id de usuario: " << c->getIdUsuario << "Carrito: " << c->getNombre()<<std::endl;

	}, criterio);
}
std::string GestorUsuarios::consultarUsuarios() const
{
	return "";
}
bool GestorUsuarios::crearCompra(Carrito*carrito) const
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
void GestorUsuarios::eliminarCompra(int idCompra) const
{

}