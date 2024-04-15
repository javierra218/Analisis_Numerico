#include <iostream>
#include "newton.h"
#include <iostream>
#include <vector>
#include "lagrange.h"

using std::cout;
using std::endl;
using std::vector;

using interpolacion::lagrange;
using interpolacion::newton;

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

int main(int argc, char *argv[])
{

	// caso_1_newton();
	// caso_1_lagrange();
	// caso_1_lineal();
	caso_sodio();
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