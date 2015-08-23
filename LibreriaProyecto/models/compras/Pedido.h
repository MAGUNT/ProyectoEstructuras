/*
 * Pedido.h
 *
 *  Created on: Aug 1, 2015
 *      Author: daniel
 */

#ifndef LIBRERIAPROYECTO_MODELS_PEDIDO_H_
#define LIBRERIAPROYECTO_MODELS_PEDIDO_H_

#include <string>
#include "../../lists/ClinkedList.h"
#include "Articulo.h"

class Pedido;
std::istream& operator >>(std::istream& is, Pedido& linea);
bool operator<(const Pedido& x, const Pedido& y);
std::ostream& operator <<(std::ostream& os, const Pedido& linea);
std::istream& operator >>(std::istream& is, Pedido*& linea);
class Pedido {

private:
	Articulo* articulo;
	int cantidad;

public:
	Pedido(Articulo* _articulo, int _cantidad);
	Pedido();
	const Articulo* getArticulo() const;
	void setArticulo(Articulo* articulo);
	int getCantidad() const;
	void setCantidad(int cantidad);
	long double precio() const;

	friend std::istream& operator >>(std::istream& is, Pedido& linea);
	friend bool operator<(const Pedido& x, const Pedido& y);
	friend std::ostream& operator <<(std::ostream& os, const Pedido& linea);
	friend std::istream& operator >>(std::istream& is, Pedido*& linea);
};


#endif /* LIBRERIAPROYECTO_MODELS_PEDIDO_H_ */
