
#include "LineaEspecifica.h"
#include "../../repositorys/Repositorios.h"
#include <iostream>

LineaEspecifica::LineaEspecifica(int _codigo, std::string _nombre)
	: codigo(_codigo), nombre(_nombre), articulos(ClinkedList<Articulo*>()) {

}
LineaEspecifica::LineaEspecifica(): LineaEspecifica(0, "anonimo") {}


int LineaEspecifica::getCodigo() const {
	return codigo;
}

void LineaEspecifica::setCodigo(int codigo) {
	this->codigo = codigo;
}

const std::string& LineaEspecifica::getNombre() const {
	return nombre;
}

void LineaEspecifica::setNombre(const std::string& nombre) {
	this->nombre = nombre;
}

const ClinkedList<Articulo*>& LineaEspecifica::getArticulos() {
	return articulos;
}

void LineaEspecifica::agregarArticulo(Articulo* articulo)
{
	articulos.addAscendent(articulo);
}
Articulo* LineaEspecifica::buscarPorCodigo(int codigo) const
{
	Articulo* articulo = nullptr;

	articulos.find([=](Articulo* a)
	{
		return a->getCodigo() == codigo; 
	}, articulo);

	return articulo;
}
Articulo* LineaEspecifica::buscarPorMarca(const std::string& marca) const
{
	Articulo* articulo = nullptr;

	articulos.find([&](Articulo* a)
	{
		return a->getMarca() == marca;
	}, articulo);

	return articulo;
}
Articulo* LineaEspecifica::buscarPorNombre(const std::string& nombre) const
{
	Articulo* articulo = nullptr;

	articulos.find([&](Articulo* a)
	{
		return a->getNombre() == nombre;
	}, articulo);

	return articulo;
}

bool LineaEspecifica::removerArticulo(int codigo)
{
	return articulos.remove([=](Articulo* a)
	{ 
		return a->getCodigo() == codigo; 
	});
}
void LineaEspecifica::imprimir() {

	std::cout << "Linea Especifica " << codigo << ". " << nombre << std::endl;
	std::cout << "Articulos: " << std::endl;
	articulos.foreach([](Articulo* a) {
		a->imprimir();
	});
}

std::istream& operator >>(std::istream& is, LineaEspecifica& linea)
{
	//-----------Atrapar excepcion
	std::string token;
	getline(is, token, LineaEspecifica::delimiter);
	linea.codigo = std::stoi(token);
	getline(is, linea.nombre,LineaEspecifica::delimiter);
	//-----------Atrapar excepcion
	int codigo = 0;
	while (is >> codigo)
	{
		Articulo *articulo = Repositorios::repoArticulo.getElement(codigo);
		linea.articulos.addAscendent(articulo);
	}
	return is;

}

std::istream& operator >>(std::istream& is, LineaEspecifica*& linea)
{
	linea = new LineaEspecifica();
	return is >> *linea;
}

bool operator<(const LineaEspecifica& x, const LineaEspecifica& y)
{
	return x.nombre < y.nombre;
}
std::ostream& operator <<(std::ostream& os, const LineaEspecifica& linea)
{
	const char d = LineaEspecifica::delimiter;
	
	os << linea.codigo << d
		<< linea.nombre << d;
	linea.articulos.foreach([&os](Articulo* a)
	{ 
		os << " " << a->getCodigo(); 
	});

	return os;

}

std::ostream& operator <<(std::ostream& os, const LineaEspecifica* linea)
{
	return os << *linea;
}
