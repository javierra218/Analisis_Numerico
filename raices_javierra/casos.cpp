#include <iostream>
#include "casos.h"

#include "biseccion.h"
#include "raices.h"
#include "regla_falsa.h"
#include "newton_raphson.h"
#include "casos.h"
#include "secante.h"
#include "newton_raphsong.h"
#include "muller.h"

using raices::aproximacion;
using raices::biseccion;
using raices::imprimir_solucion;
using raices::newton_raphsong;
using raices::newton_raphson;
using raices::regla_falsa;
using raices::secante;
using raices::solucion;
using raices::muller;

using std::cout;
using std::endl;

#define TOL 1e-5f

void caso_1()
{
    string str_func = "e^~(x)-ln(x)";

	double xInf = 1.6f; // extremo inferior
	double xSup = 3.0f; // extremo superior
	double tol = TOL;	// error relativo porcentual
	int n = 100;		// numero maximo de iteraciones

	cout << "Funcion: " << str_func << endl;
	cout << "Intervalo: [" << xInf << " ... " << xSup << "]" << endl;

	cout << "Solucion por biseccion" << endl;
	// crear una instancia del metodo
	biseccion b(str_func);
	// encotrar la raiz en el intervalo [xa, xb]
	solucion sol = b.encontrar(xInf, xSup, tol, n);
	imprimir_solucion(sol);

	// parametros para el metodo de la regla falsa
	//  xInf=0.5f;//extremo inferior
	//  xSup=2.0f;//extremo superior

	cout << "Solucion por regla_falsa" << endl;
	// crear una instancia del metodo
	regla_falsa rf(str_func);
	// encotrar la raiz en el intervalo [xa, xb]
	solucion solRf = rf.encontrar(xInf, xSup, tol, n);
	imprimir_solucion(solRf);


	cout << "Solucion por newton_raphson" << endl;
	double p0 = xInf;
	string str_dfun = "~e^~(x)-(1/x)";
	newton_raphson nr(str_func, str_dfun);
	solucion solNr = nr.encontrar(p0, tol, n);
	imprimir_solucion(solNr);

	///Metodo de la secante
	double x0 = xInf;
	double x1 = xSup;

	cout << "Solucion por el metodo de secante:" << endl;
	cout << "Intervalo"<<x0<<"..."<<x1<<endl;
    //Crear una instancia del metodo
    secante sec(str_func);
    //Encontrar la raiz en el intervalo dado
    solucion solSec= sec.encontrar(x0, x1, tol, n);
    //Imprimir la solucion
    imprimir_solucion(solSec);


	///Metodo de Muller
	 x0 = 0.5f;
	 x1 = 2.0f;
	double x2 = 4.0f;

	cout << "Solucion por el metodo de Muller:" << endl;
	cout << "Puntos de la parabola: "<<x0<<" , "<<x1<<" , "<<x2<<endl;
    //Crear una instancia del metodo
    muller mul(str_func);
    //Encontrar la raiz en el intervalo dado
    solucion solMuller= mul.encontrar(x0, x1,x2, tol, n);
    //Imprimir la solucion
    imprimir_solucion(solMuller);

}

void caso_2()
{
    string str_func = "x^3+4*x^2-10";

	double xInf = -0.5f; // extremo inferior
	double xSup = 0.5f; // extremo superior
	double tol = TOL;	// error relativo porcentual
	int n = 100;		// numero maximo de iteraciones

	cout << "Funcion: " << str_func << endl;
	cout << "Intervalo: [" << xInf << " ... " << xSup << "]" << endl;

	cout << "Solucion por biseccion" << endl;
	// crear una instancia del metodo
	biseccion b(str_func);
	// encotrar la raiz en el intervalo [xa, xb]
	solucion sol = b.encontrar(xInf, xSup, tol, n);
	imprimir_solucion(sol);

	// parametros para el metodo de la regla falsa
	//  xInf=0.5f;//extremo inferior
	//  xSup=2.0f;//extremo superior

	cout << "Solucion por regla_falsa" << endl;
	// crear una instancia del metodo
	regla_falsa rf(str_func);
	// encotrar la raiz en el intervalo [xa, xb]
	solucion solRf = rf.encontrar(xInf, xSup, tol, n);
	imprimir_solucion(solRf);


	cout << "Solucion por newton_raphson" << endl;
	double p0 = xInf;
	string str_dfun = "3*x^2+8*x";
	newton_raphson nr(str_func, str_dfun);
	solucion solNr = nr.encontrar(p0, tol, n);
	imprimir_solucion(solNr);

	///Metodo de la secante
	double x0 = xInf;
	double x1 = xSup;

	cout << "Solucion por el metodo de secante:" << endl;
	cout << "Intervalo"<<x0<<"..."<<x1<<endl;
    //Crear una instancia del metodo
    secante sec(str_func);
    //Encontrar la raiz en el intervalo dado
    solucion solSec= sec.encontrar(x0, x1, tol, n);
    //Imprimir la solucion
    imprimir_solucion(solSec);
	
}

void caso_3()
{
	string str_func = "(e^(~x)) + x^2 - 2";
	

	double xInf = 1.2f; // extremo inferior
	double xSup = 2.0f; // extremo superior
	double tol = TOL;	// error relativo porcentual
	int n = 100;		// numero maximo de iteraciones

	cout << "Funcion: " << str_func << endl;
	cout << "Intervalo: [" << xInf << " ... " << xSup << "]" << endl;

	cout << "Solucion por biseccion" << endl;
	// crear una instancia del metodo
	biseccion b(str_func);
	// encotrar la raiz en el intervalo [xa, xb]
	solucion sol = b.encontrar(xInf, xSup, tol, n);
	imprimir_solucion(sol);

	// parametros para el metodo de la regla falsa
	//  xInf=0.5f;//extremo inferior
	//  xSup=2.0f;//extremo superior

	cout << "Solucion por regla_falsa" << endl;
	// crear una instancia del metodo
	regla_falsa rf(str_func);
	// encotrar la raiz en el intervalo [xa, xb]
	solucion solRf = rf.encontrar(xInf, xSup, tol, n);
	imprimir_solucion(solRf);


	cout << "Solucion por newton_raphson" << endl;
	double p0 = xInf;
	string str_dfunc = "(~e^(~x)) + 2*x";
	newton_raphson nr(str_func, str_dfunc);
	solucion solNr = nr.encontrar(p0, tol, n);
	imprimir_solucion(solNr);


	///Metodo de la secante
	double x0 = xInf;
	double x1 = xSup;

	cout << "Solucion por el metodo de secante:" << endl;
	cout << "Intervalo"<<x0<<"..."<<x1<<endl;
    //Crear una instancia del metodo
    secante sec(str_func);
    //Encontrar la raiz en el intervalo dado
    solucion solSec= sec.encontrar(x0, x1, tol, n);
    //Imprimir la solucion
    imprimir_solucion(solSec);
}

void caso_4() {
    string str_func = "e^~(x^2) - x";
    double x0 = -0.5f; //Extremo inferior
    double x1 = 0.5f; //Extremo superior
    double tol = TOL; //Error relativo porcentual
    int n = 100;
    
    /** Probar el evaluador de expresiones
    expression f(str_func);
    cout << "xInf = " << xInf << " f(" << xInf << ") = " << f(xInf) << endl;
    cout << "xSup = " << xSup << " f(" << xSup << ") = " << f(xSup) << endl;
    */
    
    cout << "Funcion: " << str_func << endl;
    cout << "Intervalo: " << x0 << " ... " << x1 << endl;
    
    cout << "Solucion por el metodo de secante:" << endl;
    //Crear una instancia del metodo
    secante sec(str_func);
    //Encontrar la raiz en el intervalo dado
    solucion sol = sec.encontrar(x0, x1, tol, n);
    //Imprimir la solucion
    imprimir_solucion(sol);
}

void caso_5() {
    string str_func = "2*(e^(~x)) - sen(x)";
    double x0 = 1.2f; //Extremo inferior
    double x1 = 2.0f; //Extremo superior
    double tol = TOL; //Error relativo porcentual
    int n = 100;
    
    /** Probar el evaluador de expresiones
    expression f(str_func);
    cout << "xInf = " << xInf << " f(" << xInf << ") = " << f(xInf) << endl;
    cout << "xSup = " << xSup << " f(" << xSup << ") = " << f(xSup) << endl;
    */
    
    cout << "Funcion: " << str_func << endl;
    cout << "Intervalo: " << x0 << " ... " << x1 << endl;
    
    cout << "Solucion por el metodo de secante:" << endl;
    //Crear una instancia del metodo
    secante sec(str_func);
    //Encontrar la raiz en el intervalo dado
    solucion sol = sec.encontrar(x0, x1, tol, n);
    //Imprimir la solucion
    imprimir_solucion(sol);
}

void caso_6()
{
	string str_func = "x^3 -(5*(x^2)) + (7*x) - 3";

	cout << "Solucion por newton_raphson generalizado" << endl;
	double p0 = 2.33f;
	double tol = TOL;
	int n = 100;
	string str_dfunc = "3*(x^2) - 10*x + 7";
	string str_d2func = "6*x - 10";
	newton_raphsong nrg(str_func, str_dfunc, str_d2func);

	solucion solNrg = nrg.encontrar(p0, tol, n);
	imprimir_solucion(solNrg);
}

void caso_Redlich_Kwong()
{	
	string str_func = "( (115.514/(x-0.0019)) - (12.6126/(x*(x+0.0019)*(223^0.5))) - 65000 )";
	
	double xInf = 0.00270f; // extremo inferior
	double xSup = 0.00280f; // extremo superior
	double tol = TOL;	// error relativo porcentual
	int n = 100;		// numero maximo de iteraciones
	
	cout << "Funcion: " << str_func << endl;
	cout << "Intervalo: [" << xInf << " ... " << xSup << "]" << endl;
	
	cout << "Solucion por biseccion" << endl;
	// crear una instancia del metodo
	biseccion b(str_func);
	// encotrar la raiz en el intervalo [xa, xb]
	solucion sol = b.encontrar(xInf, xSup, tol, n);
	imprimir_solucion(sol);


	cout << "Solucion por regla_falsa" << endl;
	// crear una instancia del metodo
	regla_falsa rf(str_func);
	// encotrar la raiz en el intervalo [xa, xb]
	solucion solRf = rf.encontrar(xInf, xSup, tol, n);
	imprimir_solucion(solRf);

	
	cout << "Solucion por el metodo de secante:" << endl;
	cout << "Intervalo "<<xInf<<"..."<<xSup<<endl;
    //Crear una instancia del metodo
    secante sec(str_func);
    //Encontrar la raiz en el intervalo dado
    solucion solSec= sec.encontrar(xInf, xSup, tol, n);
    //Imprimir la solucion
    imprimir_solucion(solSec);


	///Metodo de Muller
	double x0 = 0.00270f;
	double x1 = 0.00275f;
	double x2 = 0.00280f;

	cout << "Solucion por el metodo de Muller:" << endl;
	cout << "Puntos de la parabola: "<<x0<<" , "<<x1<<" , "<<x2<<endl;
    //Crear una instancia del metodo
    muller mul(str_func);
    //Encontrar la raiz en el intervalo dado
    solucion solMuller= mul.encontrar(x0, x1,x2, tol, n);
    //Imprimir la solucion
    imprimir_solucion(solMuller);
}
