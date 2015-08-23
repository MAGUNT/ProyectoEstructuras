#pragma once
#include "..\models\usuarios\Usuario.h"

class Session
{

private:
	Usuario* usuario;

public:


	Session();
	~Session();

	bool iniciarSession(int, std::string);
	void cerrarSession();
	Usuario* getSessionActual()const;

};

