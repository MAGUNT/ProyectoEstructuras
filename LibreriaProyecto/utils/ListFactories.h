#pragma once

#include "ListFactories.h"
#include "..\lists\MultiplyList.h"
#include "..\models\compras\Carrito.h"

namespace ListFactories
{
	enum class CriteriosCarritos : int
	{
		ID = 0,
		NOMBRE = 1,
		IDUSUARIO = 2,
		CANTIDAD = 3,
		PRECIO = 4,
		FIFO =5
	};

	MultiplyList<Carrito*>* fabricaMultiListaCarrito();
};

