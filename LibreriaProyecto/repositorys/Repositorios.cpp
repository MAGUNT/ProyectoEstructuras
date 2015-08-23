#include "Repositorios.h"
#include "FileRepo.h"

KeyRepository<Articulo> Repositorios::repoArticulo = new FileRepo<Articulo*>("filesystem/inventario/articulos");
KeyRepository<LineaEspecifica> Repositorios::repoLineaEspecifica = new FileRepo<LineaEspecifica*>("filesystem/inventario/linea_especifica");
KeyRepository<LineaGeneral> Repositorios::repoLineaGeneral = new FileRepo<LineaGeneral*>("filesystem/inventario/linea_general");
KeyRepository<Categoria> Repositorios::repoCategoria = new FileRepo<Categoria*>("filesystem/inventario/linea_general");
KeyRepository<Usuario> Repositorios::repoUsuario = new FileRepo<Usuario*>("filesystem/usuarios/usuarios");
