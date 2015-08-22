#pragma once
#include "LineaGeneral.h"
#include "../../lists/ClinkedList.h"
class Categoria;

std::ostream& operator <<(std::ostream& os, const Categoria& linea);
std::ostream& operator <<(std::ostream& os, const Categoria* linea);
std::istream& operator >>(std::istream& is, Categoria& linea);
std::istream& operator >>(std::istream& is, Categoria*& linea);
bool operator<(const Categoria& x, const Categoria& y);

class Categoria
{
	ClinkedList<LineaGeneral*> lineasGenerales;
	int codigo;
	int pasillo;
	std::string nombre;
	
	const static char delimiter = 31;

public:
	Categoria(int codigo,int pasillo ,std::string nombre);
	Categoria();
	const ClinkedList<LineaGeneral*>& getLineaGenerals() const;
	int getCodigo() const;
	void setCodigo(int codigo);
	int getPasillo() const;
	void setPasillo(int codigo);
	const std::string& getNombre() const;
	void setNombre(const std::string& nombre);

	void agregarLineaGeneral(LineaGeneral*);
	LineaGeneral* buscarPorCodigo(int) const;
	LineaGeneral* buscarPorNombre(const std::string&) const;
	bool removerLineaGeneral(int);

	friend std::ostream& operator <<(std::ostream& os, const Categoria& linea);
	friend std::ostream& operator <<(std::ostream& os, const Categoria* linea);
	friend std::istream& operator >>(std::istream& is, Categoria& linea);
	friend std::istream& operator >>(std::istream& is, Categoria*& linea);
	friend bool operator<(const Categoria& x, const Categoria& y);
};

