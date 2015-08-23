#include "Session.h"
#include "Repositorios.h"


Session::Session() :usuario(nullptr){}


Session::~Session(){}


bool Session::iniciarSession(int id, std::string password)
{
	usuario= Repositorios::repoUsuario.find([id, &password](Usuario* u)
	{
		return u->password == password && u->getCodigo() == id;
	});

	return usuario != nullptr;
}
void Session::cerrarSession()
{
	usuario = nullptr;
}
Usuario* Session::getSessionActual()const
{
	return usuario;
}
