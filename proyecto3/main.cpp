/**
 * @file
 * @brief Clase principal
 * @author Javier Rojas - Andrea Realpe

 */
#include <cmath>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "simpson.h"
#include "romberg.h"
#include "util.h"

#define M_PI 3.14159265358979323846

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using util::crear_tabla;
using util::imprimir_tabla;
using integracion::resultado_romberg;
using integracion::simpson;
using integracion::romberg;

/**
 * @brief Muestra el menú principal y gestiona la selección de opciones.
 */
void menu();

/**
 * @brief Calcula la integral usando diferentes métodos de integración.
 */
void caso_integracion();

/**
 * @brief Calcula las derivadas usando diferencias centrales y derivación analítica.
 */
void caso_derivacion();

/**
 * @brief Calcula la integral usando el método de Simpson 1/3.
 * @param str_fn La función como cadena de texto.
 * @param a El límite inferior de integración.
 * @param b El límite superior de integración.
 * @param n El número de segmentos.
 */
void caso_simpson13(string str_fn, double a, double b, int n);

/**
 * @brief Calcula la integral usando el método de Simpson 3/8.
 * @param str_fn La función como cadena de texto.
 * @param a El límite inferior de integración.
 * @param b El límite superior de integración.
 * @param n El número de segmentos.
 */
void caso_simpson38(string str_fn, double a, double b, int n);

/**
 * @brief Calcula la integral usando el método de Romberg.
 * @param str_fn La función como cadena de texto.
 * @param a El límite inferior de integración.
 * @param b El límite superior de integración.
 * @param k El número de aproximaciones.
 */
void caso_romberg(string str_fn, double a, double b, int k);

/**
 * @brief Calcula la primera derivada usando diferencias centrales.
 * @param f La función a derivar.
 * @param x El nodo en el cual calcular la derivada.
 * @param h El paso de cálculo.
 * @return Valor de la primera derivada.
 */
double primera_derivada_central(double (*f)(double), double x, double h);

/**
 * @brief Calcula la segunda derivada usando diferencias centrales.
 * @param f La función a derivar.
 * @param x El nodo en el cual calcular la derivada.
 * @param h El paso de cálculo.
 * @return Valor de la segunda derivada.
 */
double segunda_derivada_central(double (*f)(double), double x, double h);

/**
 * @brief La función a derivar: f(x) = cos(x) * tan(x)
 * @param x Valor de x.
 * @return Valor de la función en x.
 */
double funcion(double x);

/**
 * @brief Calcula la derivada analítica de la función.
 * @param x Valor de x.
 * @return Valor de la derivada analítica en x.
 */
double derivada_analitica(double x);

int main() {
    menu();
    return 0;
}

void menu() {
    int opcion;
    do {
        cout << "Seleccione una opción:\n";
        cout << "1. Calcular la integral\n";
        cout << "2. Calcular la derivada\n";
        cout << "3. Salir\n";
        cout << "Opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                caso_integracion();
                break;
            case 2:
                caso_derivacion();
                break;
            case 3:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opción no válida. Intente de nuevo.\n";
        }
    } while (opcion != 3);
}

void caso_integracion() {
    double a = 0.0;
    double b = 1.0;
    int n_simpson_13 = 16;
    int n_simpson_38 = 15;
    int k_romberg = 5;
    string str_fn = "-0.73*pow(x,7) + 0.2*pow(x,6) + 0.18*pow(x,3)";

    // Método de Simpson (1/3) con 16 segmentos
    caso_simpson13(str_fn, a, b, n_simpson_13);
    cout << endl << "-----------------------------------------" << endl << endl;

    // Método de Simpson (3/8) con 15 segmentos
    caso_simpson38(str_fn, a, b, n_simpson_38);
    cout << endl << "-----------------------------------------" << endl << endl;

    // Método de Romberg con 5 aproximaciones
    caso_romberg(str_fn, a, b, k_romberg);
}

void caso_simpson13(string str_fn, double a, double b, int n) {
    cout << "Integración con Simpson 1/3" << endl;
    cout << "Método de Simpson 1/3 con " << n << " segmentos." << endl;
    double h = (b - a) / n;
    cout << "Paso de integración (h): " << h << endl;

    // Crear una instancia de simpson
    simpson s;
    vector<double> x, y;
    crear_tabla(x, y, a, b, n, str_fn);
    imprimir_tabla(x, y, "   X   ", "   Y   ");
    double valor = s.simpson_method(x, y);
    cout << "Valor de la integral entre " << a << " y " << b << " con " << n << " segmentos es: " << std::setprecision(8) << valor << endl;
}

void caso_simpson38(string str_fn, double a, double b, int n) {
    cout << "Integración con Simpson 3/8" << endl;
    cout << "Método de Simpson 3/8 con " << n << " segmentos." << endl;
    double h = (b - a) / n;
    cout << "Paso de integración (h): " << h << endl;

    // Crear una instancia de simpson
    simpson s;
    vector<double> x, y;
    crear_tabla(x, y, a, b, n, str_fn);
    imprimir_tabla(x, y, "   X   ", "   Y   ");
    double valor = s.simpson_method(x, y);
    cout << "Valor de la integral entre " << a << " y " << b << " con " << n << " segmentos es: " << std::setprecision(8) << valor << endl;
}

void caso_romberg(string str_fn, double a, double b, int k) {
    cout << "Integración con Romberg" << endl;
    cout << "Método de Romberg con " << k << " aproximaciones." << endl;

    // Crear una instancia de Romberg
    romberg r(str_fn);
    resultado_romberg res = r.calcular(a, b, k);
    cout << "Valor de la integral entre " << a << " y " << b << " con " << k << " aproximaciones es: " << std::setprecision(8) << res.valor << endl;
    cout << "Error de aproximación (Porcentual): " << std::setprecision(8) << res.error << endl;
}

void caso_derivacion() {
    double x = M_PI / 2;
    double h = 0.1;

    // Calcular la primera y segunda derivada usando diferencias centrales
    double primera_derivada = primera_derivada_central(funcion, x, h);
    double segunda_derivada = segunda_derivada_central(funcion, x, h);

    // Ajustar x a un punto cercano para evitar la singularidad
    x = 1.67080;
    double primera_derivada_ajustada = primera_derivada_central(funcion, x, h);
    double segunda_derivada_ajustada = segunda_derivada_central(funcion, x, h);
    double derivada_analitica_valor = derivada_analitica(x);

    // Calcular el error relativo porcentual
    double error_relativo_porcentual = std::abs((derivada_analitica_valor - primera_derivada_ajustada) / derivada_analitica_valor) * 100;

    // Imprimir los resultados
    cout << "Primera derivada en x = " << M_PI / 2 << " es: " << std::setprecision(8) << primera_derivada << endl;
    cout << "Segunda derivada en x = " << M_PI / 2 << " es: " << std::setprecision(8) << segunda_derivada << endl;

    cout << endl << "Cálculo ajustado para evitar la singularidad en x = π/2:" << endl;
    cout << "Primera derivada en x = " << x << " usando diferencias centrales es: " << std::setprecision(8) << primera_derivada_ajustada << endl;
    cout << "Segunda derivada en x = " << x << " usando diferencias centrales es: " << segunda_derivada_ajustada << endl;
    cout << "Derivada analítica en x = " << x << " es: " << derivada_analitica_valor << endl;
    cout << "Error relativo porcentual de la primera derivada es: " << error_relativo_porcentual << "%" << endl;

    // Tabla de cálculo de la derivada
    vector<double> x_values = {x + h, x - h};
    vector<double> y_values = {funcion(x + h), funcion(x - h)};

    cout << "\nTabla de cálculo de la derivada usando diferencias centrales:\n";
    imprimir_tabla(x_values, y_values, "x", "f(x)");
}

double funcion(double x) {
    return cos(x) * tan(x);
}

double primera_derivada_central(double (*f)(double), double x, double h) {
    return (f(x + h) - f(x - h)) / (2 * h);
}

double segunda_derivada_central(double (*f)(double), double x, double h) {
    return (f(x + h) - 2 * f(x) + f(x - h)) / (h * h);
}

double derivada_analitica(double x) {
    return cos(x) * (1 / cos(x) * 1 / cos(x)) - tan(x) * sin(x);
}
