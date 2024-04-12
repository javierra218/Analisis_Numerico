#include<iostream>
#include"newton.h"
#include<iostream>
#include<vector>

using std::cout;
using std::endl;
using std::vector;


using interpolacion::newton;

/**
 * @brief Caso 1 Newton - diapositivas
 * 
 */
void caso_1_newton();

int main (int argc, char *argv[]) {
	
	caso_1_newton();
	return 0;
}


void caso_1_newton(){
	cout << "Interpolacion usando diferencias divididas de newton" << endl;

	vector<double> x{100.0f,200.0f,300.0f,400.0f,500.0f};
	vector<double> y{-160.0f,-35.0f,-4.2f,9.0f,15.9f};

	//Crear una instancia de la clase newton
	newton n (x,y);

	//Interpolar un valor de x
	double x_int = 400.0f;

	double y_int = n.interpolar(x_int);

	cout << "f()"<< x_int << " = " << y_int << endl;



}