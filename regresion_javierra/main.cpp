#include<iostream>
#include<vector>
#include "regresion.h"

using std::cout;
using std::endl;
using std::vector;

using regresion::lineal_simple;
using regresion::modelo_lineal;

using regresion::potencia;
using regresion::modelo_potencia;

using regresion::exponencial;
using regresion::modelo_exponencial;

void caso_1_lineal_simple();
void caso_1_potenia();
void caso_1_exponencial();

int main (int argc, char *argv[]) {

	// caso_1_lineal_simple();
	//caso_1_potenia();
	caso_1_exponencial();
	
	return 0;
}

void caso_1_lineal_simple(){
	vector<double> x = {1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f};
	vector<double> y = {0.5f,2.5f,2.0f,4.0f,3.5f,6.0f,5.5f};

	lineal_simple regresion(x,y);
	regresion.obtener_modelo().imprimir();

	// double y_estimado = regresion.estimar(2.5f);
	double p_x=2.5f;

	double y_est=regresion.estimar(p_x);

	cout<<"x= "<<p_x<<"y estimado: "<<y_est<<endl;
}

void caso_1_potenia(){
	vector<double> x = {10.0f,20.0f,30.0f,40.0f,50.0f,60.0f,70.0f,80.0f};
	vector<double> y = {1.06f,1.33f,1.52f,1.68f,1.81f,1.91f,2.01f,2.11f};

	potencia regresion(x,y);
	regresion.obtener_modelo().imprimir();

	// double y_estimado = regresion.estimar(2.5f);
	double p_x=45.0f;

	double y_est=regresion.estimar(p_x);

	cout<<"x= "<<p_x<<"y estimado: "<<y_est<<endl;
}

void caso_1_exponencial(){
	vector<double> x = {12.0f,41.0f,93.0f,147.0f,204.0f,264.0f,373.0f,509.0f,773.0f};
	vector<double> y = {930.0f,815.0f,632.0f,487.0f,370.0f,265.0f,147.0f,76.0f,17.0f};

	exponencial regresion(x,y);
	regresion.obtener_modelo().imprimir();

	// double y_estimado = regresion.estimar(2.5f);
	double p_x=93.0f;

	double y_est=regresion.estimar(p_x);

	cout<<"x= "<<p_x<<"y estimado: "<<y_est<<endl;
}

