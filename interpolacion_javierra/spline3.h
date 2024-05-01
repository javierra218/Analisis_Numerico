#ifndef SPLINE3_H
#define SPLINE3_H

#include <iostream>
#include <vector>
#include <cmath>
#include "util.h"

using std::cout;
using std::endl;
using std::vector;
using util::gauss;
using util::imprimir_matriz;
using util::str_repeat;

/**
 * @namespace interpolacion
 */
namespace interpolacion
{
    /**
     * @brief Clase para interpolar usando splines cúbicos
     *
     */
    class spline3
    {
    public:
        spline3(vector<double> p_x, vector<double> p_y) : x(p_x), y(p_y)
        {
            // Calcular las segundas derivadas
            f2 = calcular_f2();
        }

        /**
         * @brief Interpola el valor de una función en un punto dado utilizando splines cúbicos.
         * @param x_int El valor en el que se desea interpolar la función.
         * @return El valor interpolado de la función en el punto dado.
         */
        double interpolar(double x_int)
        {
            size_t i, ant = 0, sig = 0;
            size_t n = x.size();
            size_t intervalos = n - 1;
            double fx1 = 0.0f, fx2 = 0.0f, fx3 = 0.0f, fx4 = 0.0f;
            // Vector para guardar los resultados a la hora de evaluar
            vector<double> fx(intervalos);
            // Determinar el intervalo i en donde se encuentra x_int
            // Evaluar el polinomio del trazador en x_int (imagen 18.36)
            for (i = 1; i < x.size(); i++)
            {
                fx1 = (f2[i - 1] * (pow(x[i] - x_int, 3))) / (6.0f * (x[i] - x[i - 1]));
                fx2 = (f2[i] * (pow(x_int - x[i - 1], 3))) / (6.0f * (x[i] - x[i - 1]));
                fx3 = ((y[i - 1] / (x[i] - x[i - 1])) - ((f2[i - 1] * (x[i] - x[i - 1])) / 6.0f)) * (x[i] - x_int);
                fx4 = ((y[i] / (x[i] - x[i - 1])) - ((f2[i] * (x[i] - x[i - 1])) / 6.0f)) * (x_int - x[i - 1]);
                fx[i - 1] = fx1 + fx2 + fx3 + fx4;
                cout << "Ecuacion [" << i << "]: "
                     << (f2[i - 1] / (6.0f * (x[i] - x[i - 1]))) << "(" << x[i] << " - x)^3 + "
                     << (f2[i] / (6.0f * (x[i] - x[i - 1]))) << "(x - " << x[i - 1] << ")^3 + "
                     << ((y[i - 1] / (x[i] - x[i - 1])) - ((f2[i - 1] * (x[i] - x[i - 1])) / 6.0f)) << "(" << x[i] << " - x) + "
                     << ((y[i] / (x[i] - x[i - 1])) - ((f2[i] * (x[i] - x[i - 1])) / 6.0f)) << "(x - " << x[i - 1] << ")"
                     << endl;
                cout << "\nIntervalo [" << x[i - 1] << ", " << x[i] << "]     Valor de f(" << x_int << ") = " << setprecision(8) << fx[i - 1] << endl;
            }
            // Definir en qu� intervalo se encuentra x_int y devolver el valor antes
            // obtenido guardado en el vector fx
            for (i = 1; i < intervalos; i++)
            {
                if ((x[i - 1] <= x_int) && (x[i] >= x_int))
                {
                    return fx[i - 1];
                }
                if ((x[i] <= x_int) && (x[i + 1] >= x_int))
                {
                    return fx[i];
                }
                if ((x[i + 1] <= x_int) && (x[i + 2] >= x_int))
                {
                    return fx[i + 1];
                }
            }
            return NAN;
        }

    private:
        vector<double> x;  /*!< Variable independiente*/
        vector<double> y;  /*!< Variable dependiente*/
        vector<double> f2; /*!< Segundas derivadas*/

        /** @brief Metodo para segundas derivadas */
        vector<double> calcular_f2()
        {
            vector<double> f2;
            size_t n = x.size();
            size_t intervalos = n - 1;
            size_t i;
            // 1. Construir la matriz de coeficientes m
            // m es una matriz de banda, en donde:
            // En los puntos interiores, se tienen tres coeficientes
            // En el primer punto se tienen dos valores
            // En el ultimo punto se tienen dos valores
            //  m . f2 = c
            vector<vector<double>> m(intervalos - 1);
            for (i = 0; i < intervalos - 1; i++)
            {
                m[i].resize(n);
            }

            for (i = 1; i < intervalos; i++)
            {
                size_t fila = i - 1;
                // Primer coeficiente
                if (i > 1)
                {
                    // Los puntos interiores tienen f''(xi-1)
                    m[fila][i - 1] = (x[i] - x[i - 1]);
                }
                // Segundo coeficiente
                m[fila][i] = (2.0f * (x[i + 1] - x[i - 1]));
                // Tercer coeficiente
                if (i < intervalos - 1)
                {
                    m[fila][i + 1] = (x[i + 1] - x[i]);
                }
                double ci1 = (6.0f / (x[i + 1] - x[i])) * (y[i + 1] - y[i]);
                double ci2 = (6.0f / (x[i] - x[i - 1])) * (y[i - 1] - y[i]);
                double ci = ci1 + ci2;
                m[fila][intervalos] = ci;
            }
            cout << "Coeficientes del sistema de ecuaciones" << endl;
            cout << str_repeat("_", 40) << endl;
            // Eliminar la primera columna que contiene ceros:
            for (i = 0; i < m.size(); i++)
            {
                m[i].erase(m[i].begin());
            }
            imprimir_matriz(m);
            cout << str_repeat("_", 40) << endl;
            // c = Terminos a la derecha del igual en (imagen 18.36)
            // 2. Calcular f2, f2 = gauss(m);  --> devuelve el vector de soluciones.
            f2 = gauss(m);
            // 2.1. Insertar 0 al inicio y al final de f2
            //  (f2 en los extremos vale 0)
            f2.insert(f2.begin(), 0);
            f2.insert(f2.end(), 0);
            // Mostrar todas las derivadas
            cout << "Derivadas obtenidas" << endl;
            cout << str_repeat("_", 40) << endl;
            for (size_t i = 0; i < f2.size(); i++)
            {
                std::cout << "f2[" << i << "] = " << f2[i] << std::endl;
            }
            cout << str_repeat("_", 40) << endl;
            // Calcular f2
            return f2;
        }
    };
};

#endif
