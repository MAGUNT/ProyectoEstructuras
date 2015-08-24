#pragma once
class GestorLineasDeAriculos
{
public:
	
	GestorLineasDeAriculos();

	//------------------>Eliminar
	void eliminarArticulo(int codigo) const;
	void eliminarLineaEspecifica(int codigo) const;
	void eliminarLineaGeneral(int codigo) const;
	void eliminarCategoria(int codigo) const;

};

