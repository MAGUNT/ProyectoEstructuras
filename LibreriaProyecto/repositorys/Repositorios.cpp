#include "Repositorios.h"
#include "FileRepo.h"
#include "../utils/ListFactories.h"

KeyRepository<Articulo> Repositorios::repoArticulo = new FileRepo<Articulo*>("filesystem/inventario/articulos");
KeyRepository<LineaEspecifica> Repositorios::repoLineaEspecifica = new FileRepo<LineaEspecifica*>("filesystem/inventario/linea_especifica");
KeyRepository<LineaGeneral> Repositorios::repoLineaGeneral = new FileRepo<LineaGeneral*>("filesystem/inventario/linea_general");
KeyRepository<Categoria> Repositorios::repoCategoria = new FileRepo<Categoria*>("filesystem/inventario/categoria");
KeyRepository<Usuario> Repositorios::repoUsuario = new FileRepo<Usuario*>("filesystem/usuarios/usuarios");
MultiRepo<Carrito> Repositorios::repoCompras(ListFactories::fabricaMultiListaCarrito, new FileRepo<Carrito*, MultiplyList<Carrito*>>("filesystem/usuarios/compras"));
MultiRepo<Carrito> Repositorios::repoCarritos(ListFactories::fabricaMultiListaCarrito, new FileRepo<Carrito*, MultiplyList<Carrito*>>("filesystem/usuarios/carritos"));
Session Repositorios::session = Session();




