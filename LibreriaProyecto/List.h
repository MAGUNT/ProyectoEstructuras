#pragma once
#include <functional>

template 
<
	class T
> 
class List
{
public:

	//Esto se podria ver como el tipo de una funcion anonima en C++ (callback)
	//Formato: [//capturas](//parametros)->//tipo de retorno{ //cuerpo}
	//El tipo de retorno es opcional para la mayoria de los 
	//casos por lo tanto se puede escribir: [//capturas](//parametros){ //cuerpo}
	// Capturas: para capturar una variable que este en el scope en el cual creo el callback
	//Ejemplo:
	//int numero = 10;
	//[numero](int x){ x==numero;} o [=](int x){ x==numero;} 
	//(El igual le dice que capture todo lo que vea por valor).
	//Equivalente de javascript function(){} (algo asi era :/)
	typedef const std::function<bool(const T&)>& Predicate;

	virtual ~List(){}

	//Agrega el dato al principio de la lista
	virtual void addFist(const T&)=0;
	virtual void addFist(T&&)=0;
	
	//Agrega el dato al final de la lista
	virtual void addLast(const T&)=0;
	virtual void addLast(T&&) = 0;
	
	//Agrega el dato en el index especificado
	virtual void add(unsigned, const T&) = 0;
	virtual void add(unsigned, T&&) = 0;
	
	//agrega el dato antes del primer dato que cumpla el predicado. 
	//Ejemplo:
	// Para T= int, esto agrega el numero 33 antes del primer 3 que encuentre.
	//list.addBefore(33, [](int x){ return x == 3; });
	virtual bool addBefore(const T&, Predicate) = 0;
	virtual bool addBefore(T&&, Predicate) = 0;

	//agrega el dato antes del primer dato que cumpla el predicado. 
	//Ejemplo:
	// Para T= int, esto agrega el numero 33 despues del primer 3 que encuentre.
	//list.After(33, [](int x){ return x == 3; });
	virtual bool addAfter(const T&, Predicate) = 0;
	virtual bool addAfter(T&&, Predicate) = 0;

	//Agrega acendentemente segun la sobrecarga de el operador <
	virtual bool addAscendent(const T&) = 0;
	//Agrega decendentemente segun la sobrecarga de el operador <
	virtual bool addDescendent(const T&) = 0;

	//Remueve el primer elemento que cumpla con el predicado
	//Ejemplo:
	// Para T= int, esto remueve el primer 3 que encuentre
	//list.addBefore([](int x){ return x == 3; });
	virtual bool remove(Predicate predicate)=0;
	
	//Remueve el elemento en el index especificado
	virtual void remove(unsigned)=0;
	//Vacia la lista
	virtual void clear() = 0;
	//Si la lista esta vacia
	virtual bool isEmpty() const = 0;
	
	//Find busca el el primer elemento que cumpla el predicado
	//Ejemplo:
	//Para T= int
	//int resultado=0;
	//if(lista.find([](int x){x==20;}, resultado))
	//{
	//    //se le asigno a resultado el primer 20 que encontro
	//    //esto se debe a que se pasa el resultado por referencia no por valor
	//}else
	//{ 
	//   // no se modifico resultado, sique siendo 0
	//}
	virtual bool find(Predicate, T&) const =0;
	//El operador [] sigue el mismo estandar que un arreglo
	// por lo tanto se puede buscar por index o asignar a un index en especifico
	//Precuacion: la operacion de buscar por index es O(n) 
	//no ultilizar este operador para recorrer una lista ya que seria O(n^2)
	virtual T& operator[] (std::size_t index) = 0;
	virtual const T& operator[] (std::size_t index) const = 0;
	
	//Tamaño de la lista
	virtual unsigned length() const = 0;
	
	//Agrega el dato al index especificado y retorna el valor anterior
	virtual T set(unsigned, const T&)=0;
	virtual T set(unsigned, T&&) = 0;
	
	
	//falta cbegin, begin , cend, end
	template<typename E>friend std::ostream &operator<<(std::ostream &os, const List<E> &list)
	{
	}
	
};

