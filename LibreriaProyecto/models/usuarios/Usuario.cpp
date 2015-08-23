#include "Usuario.h"


Usuario::Usuario(int pid, std::string pnombre, std::string ptelefono,
	std::string pdireccion, std::string ppassword, Rol ptipo)
	: id(pid), nombre(pnombre), telefono(ptelefono), direccion(pdireccion), password(ppassword), tipo(ptipo){}

Usuario::Usuario(): Usuario(0, "anonimo", "12345678", "por ahi", "7563532", Rol::CLIENTE){}

Usuario::~Usuario(){}

void Usuario::setNombre(const std::string& pnombre)
{
	nombre = pnombre;
}
const std::string& Usuario::getNombre()
{
	return nombre;
}
void Usuario::setTelefono(const std::string& ptelefono)
{
	telefono = ptelefono;
}
const std::string& Usuario::getTelefono()
{
	return telefono;
}
void Usuario::setDireccion(const std::string& pdireccion)
{
	direccion = pdireccion;
}
const std::string& Usuario::getDireccion()
{
	return direccion;
}

std::istream& operator >>(std::istream& is, Usuario& usuario)
{
	const char d = Usuario::delimiter;

	std::string token;
	getline(is, token, d);
	usuario.id = std::stoi(token);
	getline(is, usuario.nombre, d);
	getline(is, usuario.telefono, d);
	getline(is, usuario.direccion, d);
	getline(is, usuario.password, d);
	getline(is, token, d);
	usuario.tipo = static_cast<Rol>(token.c_str()[0]);

	if (!is) usuario = Usuario();

	return is;
}
std::istream& operator >>(std::istream& is, Usuario*& usuario)
{
	usuario = new Usuario();
	return is >> *usuario;
}
bool operator<(const Usuario& x, const Usuario& y)
{
	return x.id < y.id;
}
std::ostream& operator <<(std::ostream& os, const Usuario& usuario)
{
	const char d = Usuario::delimiter;

	return os << usuario.id 
		<< d << usuario.nombre 
		<< d << usuario.telefono 
		<< d << usuario.direccion 
		<< d << usuario.password 
		<< d << static_cast<char>(usuario.tipo);
}
std::ostream& operator <<(std::ostream& os, const Usuario* linea)
{
	return os << *linea;
}