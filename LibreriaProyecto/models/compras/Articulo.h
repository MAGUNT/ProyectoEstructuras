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
/*
	Si da tiempo agrego las sobrecargas T&& rvaluereference
*/

class Articulo {
private:
	int codigo;
	long double precio;
	std::string nombre;
	std::string marca;

public:
	Articulo(int _codigo, const std::string& _nombre); 
	Articulo(int _codigo, const std::string& _nombre, 
		const std::string& _marca, long double _precio);


	int getCodigo() const;
	void setCodigo(int codigo);
	long double getPrecio() const;
	void setPrecio(int codigo);
	const std::string& getNombre() const;
	void setNombre(const std::string& nombre);
	std::string getMarca() const;
	void setMarca(const std::string& marca);

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
