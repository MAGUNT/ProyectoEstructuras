/*
 * Articulo.h
 *
 *  Created on: Aug 1, 2015
 *      Author: daniel
 */
#pragma once
#ifndef LIBRERIAPROYECTO_MODELS_ARTICULO_H_
#define LIBRERIAPROYECTO_MODELS_ARTICULO_H_

#include <string>
#include <iostream>
/*
	Si da tiempo agrego las sobrecargas T&& rvaluereference
*/
/// seria bueno tener la difenicio de los friends en el cpp
class Articulo {
private:
	int codigo;
	long double precio;
	std::string nombre;
	std::string marca;

	const static char delimiter = 31;

public:
	Articulo();
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
	void imprimir();

	// Esto es para uso del sistema de archivos
	friend std::ostream& operator <<(std::ostream& os,  const Articulo& articulo) {
		
		return os << articulo.codigo 
			<< delimiter << articulo.nombre
			<< delimiter << articulo.marca
			<< delimiter << articulo.precio;
	}

	friend std::ostream& operator <<(std::ostream& os, const Articulo* articulo) {
		return os << *articulo;
	}

	//pendiente atrapar excepciones 
	friend std::istream& operator >>(std::istream& is, Articulo& articulo) {

		std::string token;
		getline(is, token, delimiter);
		//articulo.codigo = std::stoi(token);

		getline(is, articulo.nombre, delimiter);
		getline(is, articulo.marca, delimiter);
		
		getline(is, token, delimiter);
		//articulo.precio = std::stold(token);
		
		if (!is) articulo = Articulo();

		return is;
	}

	friend std::istream& operator >>(std::istream& is, Articulo*& articulo) {

		articulo = new Articulo();
		return is >> *articulo;
	}

	friend bool operator<(const Articulo& x, const Articulo& y) {
		return x.getNombre() < y.getNombre();
	}

};

#endif /* LIBRERIAPROYECTO_MODELS_ARTICULO_H_ */
