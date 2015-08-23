#include "Repositorios.h"
#include "FileRepo.h"

KeyRepository<Articulo> Repositorios::repoArticulo = new FileRepo<Articulo*>("filesystem/inventario/articulos");
KeyRepository<LineaEspecifica> Repositorios::repoLineaEspecifica = new FileRepo<LineaEspecifica*>("filesystem/inventario/linea_especifica");
KeyRepository<LineaGeneral> Repositorios::repoLineaGeneral = new FileRepo<LineaGeneral*>("filesystem/inventario/linea_general");
KeyRepository<Categoria> Repositorios::repoCategoria = new FileRepo<Categoria*>("filesystem/inventario/linea_general");
KeyRepository<Usuario> Repositorios::repoUsuario = new FileRepo<Usuario*>("filesystem/usuarios/usuarios");
Session Repositorios::session = Session();

MultiRepo<Carrito> Repositorios::repoCompras([](){

	return new MultiplyList < Carrito* > {
		Repositorios::nameComparator,
		Repositorios::idUsuarioComparator,
		Repositorios::cantidadComparator,
		Repositorios::precioComparator
	};
}, 
new FileRepo<Carrito*, MultiplyList<Carrito*>>("filesystem/usuarios/compras"));
MultiRepo<Carrito> Repositorios::repoCarritos([](){

	return new MultiplyList < Carrito* >{ 
		Repositorios::nameComparator,
		Repositorios::idUsuarioComparator,
		Repositorios::cantidadComparator,
		Repositorios::precioComparator
	};
},
new FileRepo<Carrito*, MultiplyList<Carrito*>>("filesystem/usuarios/carritos"));

int Repositorios::nameComparator(Carrito* p1, Carrito *p2)
{
	if (p2->getNombre() < p1->getNombre())return 1;
	if (p1->getNombre() < p2->getNombre())return -1;
	return 0;
}
int Repositorios::idUsuarioComparator(Carrito* p1, Carrito *p2)
{
	if (p2->getIdUsuario() < p1->getIdUsuario())return 1;
	if (p1->getIdUsuario() <p2->getIdUsuario())return -1;
	return 0;
}

int Repositorios::cantidadComparator(Carrito* p1, Carrito *p2)
{
	if (p2->getCantidad() < p1->getCantidad())return 1;
	if (p1->getCantidad() <p2->getCantidad())return -1;
	return 0;
}
int Repositorios::precioComparator(Carrito* p1, Carrito *p2)
{
	long double precio1 = p1->precio(), precio2 = p2->precio();
	if (precio2 < precio1)return 1;
	if (precio1 < precio2)return -1;
	return 0;
}
