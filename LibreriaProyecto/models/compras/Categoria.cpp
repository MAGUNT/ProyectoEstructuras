#include "Categoria.h"
#include "../../repositorys/Repositorios.h"
#include <iostream>

Categoria::Categoria(int pcodigo, int ppasillo, std::string pnombre)
	:codigo(pcodigo), pasillo(ppasillo), nombre(pnombre), lineasGenerales(ClinkedList<LineaGeneral*>()){}

Categoria::Categoria() : Categoria(0, 0, "Anonimo"){}

const ClinkedList<LineaGeneral*>& Categoria::getLineaGenerals() const
{
	return lineasGenerales;
}
int Categoria::getCodigo() const
{
	return codigo;
}
void Categoria::setCodigo(int codigo)
{
	this->codigo = codigo;
}
int Categoria::getPasillo() const
{
	return pasillo;
}
void Categoria::setPasillo(int pasillo)
{
	this->pasillo = pasillo;
}
const std::string& Categoria::getNombre() const
{
	return nombre;
}
void Categoria::setNombre(const std::string& nombre)
{
	this->nombre = nombre;
}

void Categoria::agregarLineaGeneral(LineaGeneral* linea)
{
	lineasGenerales.addAscendent(linea);
}

LineaGeneral* Categoria::buscarPorCodigo(int codigo) const
{
	LineaGeneral* linea = nullptr;

	lineasGenerales.find([=](LineaGeneral* a)
	{
		return a->getCodigo() == codigo;
	}, linea);

	return linea;
}
LineaGeneral* Categoria::buscarPorNombre(const std::string& nombre) const
{
	LineaGeneral* linea = nullptr;

	lineasGenerales.find([&nombre](LineaGeneral* a)
	{
		return a->getNombre() == nombre;
	}, linea);

	return linea;
}
bool Categoria::removerLineaGeneral(int codigo)
{
	return lineasGenerales.remove([=](LineaGeneral* a)
	{
		return a->getCodigo() == codigo;
	});
}
void Categoria::imprimir() {
	std::cout << "Categoria " << codigo << ". " << nombre << " en el pasillo " << pasillo << std::endl;
	std::cout << "	Lineas Generales" << std::endl;
	this->lineasGenerales.foreach([](LineaGeneral* l) {
		std::cout << "	"	<< l->getCodigo() << ". " << l->getNombre() << std::endl;
	});
}

 std::ostream& operator <<(std::ostream& os, const Categoria& cat)
 {
	 const char d = Categoria::delimiter;
	 
	 os << cat.codigo << d 
		 << cat.pasillo << d 
		 << cat.nombre << d;
	 
	 cat.lineasGenerales.foreach([&os](LineaGeneral* a)
	 {
		 os << " " << a->getCodigo();
	 });

	 return os;
 }
 std::ostream& operator <<(std::ostream& os, const Categoria* linea)
 {
	 return os << *linea;
 }
 std::istream& operator >>(std::istream& is, Categoria& cat)
 {
	 const char d = Categoria::delimiter;
		 //-----------Atrapar excepcion
	std::string token;
	 getline(is, token, d);
	 cat.codigo = std::stoi(token);
	 getline(is, token, d);
	 cat.pasillo = std::stoi(token);
	 getline(is, cat.nombre, d);
	 //-----------Atrapar excepcion
	 int codigo = 0;
	 while (is >> codigo)
	 {
		 LineaGeneral *categoria = Repositorios::repoLineaGeneral.getElement(codigo);
		 cat.lineasGenerales.addAscendent(categoria);
	 }
	 return is;
 }
 std::istream& operator >>(std::istream& is, Categoria*& linea)
 {
	 linea = new Categoria();
	 return is >> *linea;
 }
 bool operator<(const Categoria& x, const Categoria& y)
 {
	 return x.nombre < y.nombre;
 }
