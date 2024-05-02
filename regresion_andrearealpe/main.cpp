#include <iostream>
#include <iomanip>
#include <vector>

#include "regresion.h"
#include "gauss.h"

using std::cout;
using std::endl;
using std::vector;

using regresion::regresion_lineal;
using regresion::solucion_lineal;

using regresion::regresion_lineal_exponencial;
using regresion::solucion_lineal_exponencial;

using regresion::regresion_lineal_potencia;
using regresion::solucion_lineal_potencia;

using regresion::regresion_cuadratica;
using regresion::solucion_cuadratica;

/**
* @brief Caso linealizacion con función lineal
*/
void caso_lineal();

/**
* @brief Caso linealizacion con función potencia
*/
void caso_potencial();

/**
* @brief Caso linealizacion con función exponencial
*/
void caso_exponencial();

/**
* @brief Caso linealizacion con función cuadratica
*/
void caso_cuadratica();

int main(int argc, char* argv[])
{
	cout << "- - - - - P R I M E R A P A R T E : R E G R E S I O N - - - - -\n" << endl;
	vector<double> x = { 2.0f, 3.0f, 4.0f, 5.0f, 7.0f, 8.0f,9.0f, 10.0f };
	vector<double> y = { 14.5f, 18.7f, 22.3f, 28.1f, 42.7f, 50.8f, 61.2f, 76.6f };
	imprimir_tabla(x, y, "Datos Establecidos", "x", "y");
	
	cout << "---------> REGRESION FUNCION LINEAL:" << endl;
	caso_lineal();
	
	cout << "\n---------> REGRESION FUNCION POTENCIAL:" << endl;
	caso_potencial();
	
	cout << "\n---------> REGRESION FUNCION EXPONENCIAL:" << endl;
	caso_exponencial();
	
	cout << "\n---------> REGRESION FUNCION CUADRATICA:" << endl;
	caso_cuadratica();
	
	return 0;
}

void caso_lineal(){
	
	vector<double> x = { 2.0f, 3.0f, 4.0f, 5.0f, 7.0f, 8.0f,9.0f, 10.0f };
	vector<double> y = { 14.5f, 18.7f, 22.3f, 28.1f, 42.7f, 50.8f, 61.2f, 76.6f };
	
	regresion_lineal rl;
	//Calcular la regresion
	solucion_lineal sl = rl.calcular(x, y);
	sl.imprimir();
	cout << "\nValores Estimados Lineales:" << endl;
	for (size_t i = 0; i < x.size(); i++) {
		double estimado = sl.b1 * x[i] + sl.b0;
		cout << "Para x = " << x[i] << ", y estimado = " << estimado << endl;
	}
}
void caso_potencial(){
	vector<double> x = { 2.0f, 3.0f, 4.0f, 5.0f, 7.0f, 8.0f,9.0f, 10.0f };
	vector<double> y = { 14.5f, 18.7f, 22.3f, 28.1f, 42.7f, 50.8f, 61.2f, 76.6f };
	
	regresion_lineal_potencia rlp;	
	//Calcular la regresion
	solucion_lineal_potencia slp = rlp.calcular(x, y);
	//imprimir
	slp.imprimir();
	cout << "\nValores Estimados Potenciales:" << endl;
	for (size_t i = 0; i < x.size(); i++) {
		double estimado = slp.c * pow(x[i], slp.a);
		cout << "Para x = " << x[i] << ", y estimado = " << estimado << endl;
	}

}
void caso_exponencial(){	
	vector<double> x = { 2.0f, 3.0f, 4.0f, 5.0f, 7.0f, 8.0f,9.0f, 10.0f };
	vector<double> y = { 14.5f, 18.7f, 22.3f, 28.1f, 42.7f, 50.8f, 61.2f, 76.6f };
	
	regresion_lineal_exponencial rle;
	//Calcular la regresion
	solucion_lineal_exponencial sle = rle.calcular(x, y);
	//imprimir
	sle.imprimir();
	cout << "\nValores Estimados Exponenciales:" << endl;
	for (size_t i = 0; i < x.size(); i++) {
		double estimado = sle.c * exp(sle.a * x[i]);
		cout << "Para x = " << x[i] << ", y estimado = " << estimado << endl;
	}
}

void caso_cuadratica(){
	vector<double> x = { 2.0f, 3.0f, 4.0f, 5.0f, 7.0f, 8.0f,9.0f, 10.0f };
	vector<double> y = { 14.5f, 18.7f, 22.3f, 28.1f, 42.7f, 50.8f, 61.2f, 76.6f };
	
	regresion_cuadratica rc;
	//Calcular regresion cuadrática
	solucion_cuadratica sc = rc.calcular(x, y);
	sc.imprimir();
	cout << "\nValores Estimados Cuadraticos:" << endl;
	for (size_t i = 0; i < x.size(); i++) {
		double estimado = sc.a2 * x[i] * x[i] + sc.a1 * x[i] + sc.a0;
		cout << "Para x = " << x[i] << ", y estimado = " << estimado << endl;
	}
}

