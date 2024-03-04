#include<iostream>
#include "biseccion.h"
#include <string>
#include "raices.h"
#include "regla_falsa.h"

using std::cout;
using std::endl;
using std::string;

using raices::biseccion;
using raices::regla_falsa;
using raices::solucion;
using raices::aproximacion;
using raices::imprimir_solucion;

int main () {

	string str_func = "e^~(x)-ln(x)";
	
	double xInf=1.0f;//extremo inferior
	double xSup=1.5f;//extremo superior
	double tol=1.0f;//error relativo porcentual
	int n = 100;//numero maximo de iteraciones

	cout << "Funcion: " << str_func << endl;
	cout << "Intervalo: [" << xInf << " ... " << xSup << "]" << endl;

	cout <<"Solucion por biseccion" << endl;
	//crear una instancia del metodo
	biseccion b(str_func);
	//encotrar la raiz en el intervalo [xa, xb]
	solucion sol=b.encontrar(xInf, xSup, tol, n);
	imprimir_solucion(sol);


	//parametros para el metodo de la regla falsa
	// xInf=0.5f;//extremo inferior
	// xSup=2.0f;//extremo superior


	cout <<"Solucion por regla_falsa" << endl;
	//crear una instancia del metodo
	regla_falsa rf(str_func);
	//encotrar la raiz en el intervalo [xa, xb]
	solucion solRf=rf.encontrar(xInf, xSup, tol, n);
	imprimir_solucion(solRf);
	
	return 0;
}

