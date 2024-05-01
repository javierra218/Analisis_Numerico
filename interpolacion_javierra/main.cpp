/**
 * @brief Interpolacion
 * @author Javier Rojas Agredo <javierra@unicauca.edu.co>
 */
#include <iostream>
#include "newton.h"
#include <iostream>
#include <vector>
#include "lagrange.h"
#include "spline3.h"
#include <iomanip>

using std::cout;
using std::endl;
using std::setw;
using std::vector;

using interpolacion::lagrange;
using interpolacion::newton;
using interpolacion::spline3;

/**
 * @brief Caso 1 Newton - diapositivas
 *
 */
void caso_1_newton();

/**
 * @brief Caso 1 Lagrange - (mismo datos de caso 1 Newton)
 *
 */
void caso_1_lagrange();

/**
 * @brief Caso 1 Lineal - logaritomo neperiano ln
 *
 */
void caso_1_lineal();

/**
 * @brief Caso sodio
 *
 */
void caso_sodio();

void caso_1_spline3();

void caso_error_interpolacion();

/**
 * @brief Caso 1 examen - Pate2-A
 *
 */
void caso_1_interpolacion_examen();
/**
 * @brief Caso 1 examen - Parte2-B
 *
 */
void caso_1_spline3_examen();

int main(int argc, char *argv[])
{

	// caso_1_newton();
	// caso_1_lagrange();
	// caso_1_lineal();
	// caso_sodio();
	// caso_1_spline3();
	// caso_error_interpolacion();
	caso_1_interpolacion_examen();
	caso_1_spline3_examen();
	return 0;
}

void caso_1_newton()
{
	cout << "Interpolacion usando diferencias divididas de newton" << endl;

	vector<double> x{100.0f, 200.0f, 300.0f, 400.0f, 500.0f};
	vector<double> y{-160.0f, -35.0f, -4.2f, 9.0f, 15.9f};

	// Crear una instancia de la clase newton
	newton n(x, y);

	cout << "Polinomio interpolante: " << n.polinomio() << endl;

	// Interpolar un valor de x
	double x_int = 120.0f;

	double y_int = n.interpolar(x_int);

	cout << "f()" << x_int << " = " << y_int << endl;
}

void caso_1_lagrange()
{
	cout << "Interpolacion usando polinomio de lagrange" << endl;

	vector<double> x{100.0f, 200.0f, 300.0f, 400.0f, 500.0f};
	vector<double> y{-160.0f, -35.0f, -4.2f, 9.0f, 15.9f};

	// Crear una instancia de la clase newton
	lagrange l(x, y);

	cout << "Polinomio interpolante: " << l.polinomio() << endl;

	// Interpolar un valor de x
	double x_int = 120.0f;

	double y_int = l.interpolar(x_int);

	cout << "f()" << x_int << " = " << y_int << endl;
}

void caso_1_lineal()
{
	cout << "Interpolacion logaritmo neperiano" << endl;
	vector<double> x{
		0.0f,
		4.0f,
		6.0f};
	vector<double> y{
		0.0f,
		1.3862944f,
		1.7917595f};

	newton n(x, y);

	cout << "Polinomio interpolante: " << n.polinomio() << endl;

	// Interpolar un valor de x
	double x_int = 2.0f;

	// crear instancia del metod de lagrange
	lagrange l(x, y);

	cout << "Polinomio interpolante: " << l.polinomio() << endl;

	double y_int_newton = n.interpolar(x_int);
	double y_int_lagrange = l.interpolar(x_int);

	cout << "Newton f(" << x_int << ") = " << y_int_newton << endl;
	cout << "Lagrange f(" << x_int << ") = " << y_int_lagrange << endl;
}

void caso_sodio()
{
	cout << "Interpolacion sodio" << endl;
	vector<double> x{
		20.0f, 94.0f, 205.0f, 371.0f};
	vector<double> y{
		971.0f, 929.0f, 902.0f, 860.0f};

	// Interpolar un valor de x
	double x_int = 70.0f;

	newton n(x, y);
	cout << "Polinomio interpolante (Newton): " << n.polinomio() << endl;

	// crear instancia del metod de lagrange
	lagrange l(x, y);
	cout << "Polinomio interpolante (Lagrange): " << l.polinomio() << endl;

	double y_int_newton = n.interpolar(x_int);
	double y_int_lagrange = l.interpolar(x_int);

	cout << "Newton f(" << x_int << ") = " << y_int_newton << endl;
	cout << "Lagrange f(" << x_int << ") = " << y_int_lagrange << endl;
}

void caso_1_spline3()
{
	cout << "Interpolacion mediante trazadores cubicos" << endl;

	vector<double> x{3.0f, 4.5f, 7.0f, 9.0f};
	vector<double> y{2.5f, 1.0f, 2.5f, 0.5f};

	// Crear una instancia de la clase newton
	spline3 s(x, y);

	// Interpolar un valor de x
	double x_int = 5.0f;

	double y_int = s.interpolar(x_int);

	cout << "f(" << x_int << ") = " << y_int << endl;
}

void caso_error_interpolacion()
{
	cout << "Error de interpolacion." << endl;

	vector<double> x{2.0f, 2.2f, 2.4f, 2.6f, 2.8f};
	vector<double> y{0.5103757f, 0.5207843f, 0.5104147f, 0.48133006f, 0.4359160f};

	// Crear una instancia del metodo de lagrange
	lagrange l(x, y);

	// interpolar un valor de x
	double x_int = 2.3f;

	double y_int = l.interpolar(x_int, 1);

	cout << "f(" << x_int << ") = " << y_int << endl;
}

/**
 * @brief Realiza la interpolación utilizando polinomios de Newton de segundo y tercer grado para las contracciones de un resorte.
 * @details Se tienen los siguientes datos:
 * - Carga en KiloPascales: 5.0, 10.0, 15.0, 20.0, 25.0
 * - Contracción en milímetros: 49.0, 105.0, 172.0, 253.0, 352.0
 *
 */
void caso_1_interpolacion_examen()
{
	cout << "Interpolacion utilizando polinomios de Newton de segundo y tercer grado para las contracciones de un resorte.\n"
		 << endl;

	vector<double> x = {5.0, 10.0, 15.0, 20.0, 25.0};	   // Carga en KiloPascales
	vector<double> y = {49.0, 105.0, 172.0, 253.0, 352.0}; // Contracción en milímetros

	// Imprimir tabla de datos
	cout << "Tabla de datos (Cargas en KPa y Contracciones en mm):\n";
	cout << setw(10) << "Carga(KPa)" << setw(20) << "Contracción(mm)" << endl;
	for (size_t i = 0; i < x.size(); ++i)
	{
		cout << setw(10) << x[i] << setw(20) << y[i] << endl;
	}

	// Crear una instancia de la clase newton
	newton n(x, y);

	// Mostrar el polinomio interpolante completo
	cout << "\nPolinomio interpolante completo:\n"
		 << n.polinomio() << endl;

	// Valor de x para interpolar
	double x_inter = 13.32;

	// Rango de los nodos utilizados
	cout << "\nNodos utilizados para la interpolación: desde " << x.front() << " KPa hasta " << x.back() << " KPa.\n";

	// Calcular la interpolación y error para segundo grado
	double error_segundo_grado;
	double interpolacion_segundo_grado = n.interpolar_con_error(x_inter, 2, error_segundo_grado);

	// Tabla de nodos usados para interpolación de segundo grado
	cout << "Nodos usados para interpolación de segundo grado:" << endl;
	cout << setw(10) << "x" << setw(20) << "y" << endl;
	for (int i = 0; i < 3; ++i)
	{
		cout << setw(10) << x[i] << setw(20) << y[i] << endl;
	}
	cout << "Interpolación de segundo grado en x = " << x_inter << " da como resultado: " << interpolacion_segundo_grado << endl;
	cout << "Error estimado para segundo grado: " << error_segundo_grado << endl;

	// Calcular la interpolación y error para tercer grado
	double error_tercer_grado;
	double interpolacion_tercer_grado = n.interpolar_con_error(x_inter, 3, error_tercer_grado);

	// Tabla de nodos usados para interpolación de tercer grado
	cout << "\nNodos usados para interpolación de tercer grado:" << endl;
	cout << setw(10) << "x" << setw(20) << "y" << endl;
	for (int i = 0; i < 4; ++i)
	{
		cout << setw(10) << x[i] << setw(20) << y[i] << endl;
	}
	cout << "Interpolación de tercer grado en x = " << x_inter << " da como resultado: " << interpolacion_tercer_grado << endl;
	cout << "Error estimado para tercer grado: " << error_tercer_grado << endl;
}

/**
 * @brief Función que realiza la interpolación mediante trazadores cúbicos.
 *
 * Esta función realiza la interpolación mediante trazadores cúbicos entre los puntos x = 12 y x = 20.
 * Utiliza un vector de valores de x y un vector de valores de y para realizar la interpolación.
 * Los valores a interpolar son 12, 15 y 20.
 *
 * @param None
 * @return None
 */
void caso_1_spline3_examen()
{
	cout << "TRAZADOR CUBICO ENTRE x = 12 y x = 20:" << endl;

	vector<double> x = {5.0, 10.0, 15.0, 20.0, 25.0};	   // Carga en KiloPascales
	vector<double> y = {49.0, 105.0, 172.0, 253.0, 352.0}; // Contracción en milímetros

	spline3 s3(x, y);

	double x_int, x_int2, x_int3;
	// int grado;
	cout << "Interpolacion mediante Trazadores Cubicos" << endl;

	// Valores a interpolar
	x_int = 12;
	x_int2 = 15;
	x_int3 = 20;
	// Interpolar el valor ingresador por el usuario

	double y_int = s3.interpolar(x_int);
	cout << "\ny1(" << x_int << ") =" << setprecision(7) << y_int << endl;
	double y_int2 = s3.interpolar(x_int2);
	cout << "\ny2(" << x_int2 << ") =" << setprecision(7) << y_int2 << endl;
	double y_int3 = s3.interpolar(x_int3);
	cout << "\ny3(" << x_int3 << ") =" << setprecision(7) << y_int3 << endl;
}
