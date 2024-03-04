#include<iostream>
#include "biseccion.h"
#include <string>

using std::cout;
using std::endl;
using std::string;

using raices::biseccion;

int main (int argc, char *argv[]) {

	string str_func="e^~(X)-ln(X)";
	double xa= 1.0f; //extremo inferior
	double xb= 1.5f; //extremo superior
	double tol=1.0f; //error relativo porcentual
	int n=100;

	cout << "Funcion: " << str_func << endl;
	cout << "Intervalo: [" << xa << " ... " << xb << "]" << endl;

	//crear una instancia del metodo
	biseccion b(str_func);

	//encotrar la raiz en el intervalo [xa, xb]
	double xr=b.encontrar(xa, xb, tol, n);

	cout << "La raiz es: " << xr << endl;
	
	return 0;
}

