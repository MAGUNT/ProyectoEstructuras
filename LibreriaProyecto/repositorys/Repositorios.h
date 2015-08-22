#pragma once
#include "KeyRepository.h"
#include "../models/compras/Articulo.h"
#include "../models/compras/LineaEspecifica.h"
#include "../models/compras/LineaGeneral.h"
#include "../models/compras/Categoria.h"

//Problema al incluir #include "../models/compras/LineaEspecifica.h"

class Repositorios
{
public:
	static KeyRepository<Articulo> repoArticulo;
	static KeyRepository<LineaEspecifica> repoLineaEspecifica;
	static KeyRepository<LineaGeneral> repoLineaGeneral;
	static KeyRepository<Categoria> repoCategoria;
};

