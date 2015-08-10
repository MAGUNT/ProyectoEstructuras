/*
 * Articulo.h
 *
 *  Created on: Aug 1, 2015
 *      Author: daniel
 */

#ifndef LIBRERIAPROYECTO_MODELS_ARTICULO_H_
#define LIBRERIAPROYECTO_MODELS_ARTICULO_H_

#include <string>
#include <iostream>

class Articulo {
private:
	int codigo;
	int precio;
	std::string nombre;
	std::string marca;

public:
	Articulo(int _codigo, std::string _nombre);
	virtual ~Articulo();

	int getCodigo() const;
	void setCodigo(int codigo);
	int getPrecio() const;
	void setPrecio(int codigo);
	std::string getNombre() const;
	void setNombre(std::string nombre);
	std::string getMarca() const;
	void setMarca(std::string marca);

	friend std::ostream& operator <<(std::ostream& os,  const Articulo& articulo) {
		os << "["
			<< articulo.codigo << ", "
			<< articulo.nombre << ", "
			<< articulo.marca << ", "
			<< articulo.precio << "]" << std::endl;

		return os;
	};


	friend bool operator<(const Articulo& x, const Articulo& y) {
		return x.getCodigo() < y.getCodigo();
	}

};

#endif /* LIBRERIAPROYECTO_MODELS_ARTICULO_H_ */
