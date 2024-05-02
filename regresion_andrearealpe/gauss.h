#ifndef GAUSS_H
#define GAUSS_H

#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::string;

/**
* @brief Imprimir una tabla de datos.
* @param x Valores de la variable independiente
* @param y Valores de la variable dependiente
* @param titulo Titulo de la tabla
* @param label_x Etiqueta de la variable independiente
* @param label_y Etiqueta de la variable dependiente
*/
void imprimir_tabla(vector<double>x,
					vector<double>y,
					string titulo,
					string label_x,
					string label_y);
/*
* @brief Calcula la solucion de un sistema de ecuaciones
* @param m Matriz del sistema de ecuaciones
* @return Arreglo con los coeficientes
*/
vector<double> gauss(vector<vector<double>> &m);

#endif
