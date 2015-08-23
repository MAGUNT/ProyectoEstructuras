#pragma once

#include "../../lists/ClinkedList.h"
#include "Articulo.h"

class LineaEspecifica;

std::istream& operator >>(std::istream& is, LineaEspecifica& linea);
std::istream& operator >>(std::istream& is, LineaEspecifica*& linea);
bool operator<(const LineaEspecifica& x, const LineaEspecifica& y);
std::ostream& operator <<(std::ostream& os, const LineaEspecifica& linea);
std::ostream& operator <<(std::ostream& os, const LineaEspecifica* linea);

class LineaEspecifica {
private:
	ClinkedList<Articulo*> articulos;
	int codigo;
	std::string nombre;
	
	const static char delimiter = 31;

public:
	LineaEspecifica(int codigo, std::string nombre);
	LineaEspecifica();
	const ClinkedList<Articulo*>& getArticulos();
	int getCodigo() const;
	void setCodigo(int codigo);
	const std::string& getNombre() const;
	void setNombre(const std::string& nombre);
	
	void agregarArticulo(Articulo* articulo);
	Articulo* buscarPorCodigo(int) const;
	Articulo* buscarPorMarca(const std::string&) const;
	Articulo* buscarPorNombre(const std::string&) const;
	bool removerArticulo(int);
	void imprimir();

	friend std::ostream& operator <<(std::ostream& os, const LineaEspecifica& linea);
	friend std::ostream& operator <<(std::ostream& os, const LineaEspecifica* linea);
	friend std::istream& operator >>(std::istream& is, LineaEspecifica& linea);
	friend std::istream& operator >>(std::istream& is, LineaEspecifica*& linea);
	friend bool operator<(const LineaEspecifica& x, const LineaEspecifica& y);


};


