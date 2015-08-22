#include "Repositorios.h"
#include "FileRepo.h"

KeyRepository<Articulo> Repositorios::repoA = new FileRepo<Articulo*>("filesystem/inventario/articulos");
KeyRepository<LineaEspecifica> Repositorios::repoLE = new FileRepo<LineaEspecifica*>("filesystem/inventario/linea_especifica");