#include "ListFactories.h"
#include "..\lists\MultiplyList.h"
#include "..\models\compras\Carrito.h"



MultiplyList<Carrito*>* ListFactories::fabricaMultiListaCarrito(){

	return new MultiplyList < Carrito* >(
	{
		[](Carrito* p1, Carrito* p2)
		{
			if (p2->getCodigo() < p1->getCodigo())return 1;
			if (p1->getCodigo() < p2->getCodigo())return -1;
			return 0;
		},
			[](Carrito* p1, Carrito *p2)
		{
			if (p2->getNombre() < p1->getNombre())return 1;
			if (p1->getNombre() < p2->getNombre())return -1;
			return 0;
		},
			[](Carrito* p1, Carrito *p2)
		{
			if (p2->getIdUsuario() < p1->getIdUsuario())return 1;
			if (p1->getIdUsuario() < p2->getIdUsuario())return -1;
			return 0;
		},

			[](Carrito* p1, Carrito *p2)
		{
			if (p2->getCantidad() < p1->getCantidad())return 1;
			if (p1->getCantidad() < p2->getCantidad())return -1;
			return 0;
		},
			[](Carrito* p1, Carrito *p2)
		{
			long double precio1 = p1->precio(), precio2 = p2->precio();
			if (precio2 < precio1)return 1;
			if (precio1 < precio2)return -1;
			return 0;
		}
	}, 0);
}