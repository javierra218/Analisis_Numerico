#include<iostream>
#include<vector>
#include "regresion.h"

using std::cout;
using std::endl;
using std::vector;

using regresion::lineal_simple;
using regresion::modelo_lineal;

void caso_1();

int main (int argc, char *argv[]) {

	caso_1();
	
	return 0;
}

void caso_1(){
	vector<double> x = {1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f};
	vector<double> y = {0.5f,2.5f,2.0f,4.0f,3.5f,6.0f,5.5f};

	lineal_simple regresion(x,y);
	regresion.obtener_modelo().imprimir();

	// double y_estimado = regresion.estimar(2.5f);
	double p_x=2.5f;

	double y_est=regresion.estimar(p_x);

	cout<<"x= "<<p_x<<"y estimado: "<<y_est<<endl;


	


}

