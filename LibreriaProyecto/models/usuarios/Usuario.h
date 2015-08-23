#pragma once

#include <string>

enum class Rol : char {
	CLIENTE = 'C',
	ADMIN = 'A',
	DEPENDIENTE = 'D',
};

class Usuario;


std::istream& operator >>(std::istream& is, Usuario& linea);
std::istream& operator >>(std::istream& is, Usuario*& linea);
bool operator<(const Usuario& x, const Usuario& y);
std::ostream& operator <<(std::ostream& os, const Usuario& linea);
std::ostream& operator <<(std::ostream& os, const Usuario* linea);

class Usuario
{

private:

	int id;
	std::string nombre;
	std::string telefono;
	std::string direccion;
	std::string password;
	Rol tipo;

	const static char delimiter = 31;
		
public:
	Usuario(int id, std::string nombre,std::string telefono,
	std::string direccion,std::string password, Rol tipo);
	Usuario();
	virtual ~Usuario();
	virtual void setNombre(const std::string&);
	virtual const std::string& getNombre();
	virtual void setTelefono(const std::string&);
	virtual const std::string& getTelefono();
	virtual void setDireccion(const std::string&);
	virtual const std::string& getDireccion();
	int getCodigo()const;

	friend std::istream& operator >>(std::istream& is, Usuario& linea);
	friend std::istream& operator >>(std::istream& is, Usuario*& linea);
	friend bool operator<(const Usuario& x, const Usuario& y);
	friend std::ostream& operator <<(std::ostream& os, const Usuario& linea);
	friend std::ostream& operator <<(std::ostream& os, const Usuario* linea);

	friend class Session;
	template <typename T>
	friend class KeyRepository;
};

