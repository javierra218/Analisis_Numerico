#ifndef CUADRATICA_H
#define CUADRATICA_H

#include <vector>
#include <iostream>
#include <cmath>
#include "gauss.h"

using std::cout;
using std::endl;

using std::vector;

namespace regresion
{

    struct modelo_cuadratico
    /**
     * @brief Modelo de regresion Cuadratico.
     *
     * polimonio de la forma y = a[2]*x^2 + a[1]*x + a[0]
     */
    {
        vector<double> x; /**< Vector de valores de x */
        vector<double> y; /**< Vector de valores de y */
        vector<double> a; /**< Vector de coeficientes */
        double st = 0.0f; /**< Sumatoria de la diferencia  */
        double sy = NAN;  /**< Desviacion estandar */
        double sr = 0.0f; /**< Discrepancia entre valor real y estimado */
        double syx = NAN; /**< Error estandar de la estimacion */
        double r2 = 0.0f; /**< Coeficiente de determinacion */

        modelo_cuadratico(vector<double> v_x, vector<double> v_y) : x(v_x), y(v_y)
        {
            calcular();
        }

        void calcular()
        {
            size_t m = 2; // grado del polinomio
            size_t n = x.size();
            // validar que se tengan datos sufiencientes
            // se necesitan al menos dos datos para calcular sy
            // se necesitan al menos m+1 datos para calcular syx
            if (n <= m + 1)
            {
                return;
            }

            // validar que se tengan la misma cantidad de datos
            if (n != y.size())
            {
                return;
            }

            double s_x = 0.0f, s_x2 = 0.0f, s_x3 = 0.0f, s_x4 = 0.0f, s_y = 0.0f, s_xy = 0.0f, s_x2y = 0.0f;

            for (size_t i = 0; i < n; i++)
            {
                s_x += x[i];
                s_x2 += pow(x[i], 2);
                s_x3 += pow(x[i], 3);
                s_x4 += pow(x[i], 4);
                s_y += y[i];
                s_xy += x[i] * y[i];
                s_x2y += pow(x[i], 2) * y[i];
            }

            double y_prom = s_y / (double)n;

            vector<vector<double>> mat = {{(double)n, s_x, s_x2, s_y},
                                          {s_x, s_x2, s_x3, s_xy},
                                          {s_x2, s_x3, s_x4, s_x2y}}; // matriz de coeficientes

            a = gauss(mat); // calcular coeficientes

            // calcular parametros de calidad
            for (size_t i = 0; i < n; i++)
            {
                // Calcular st
                st += pow(y[i] - y_prom, 2);

                // Calcular sr
                sr += pow(y[i] - estimar(x[i]), 2);
            }

            // calcular desviacion estandar
            sy = sqrt(st / (double)(n - (m + 1)));

            // calcular error estandar de aproximacion
            syx = sqrt(sr / (double)(n - 2));

            // calcular coeficiente de determinacion
            r2 = (st - sr) / st;
        }

        void imprimir()
        {
            cout << "y= "
                 << a[2]
                 << " * x^2"
                 << (a[1] < 0 ? " - " : " + ")
                 << fabs(a[1])
                 << " * x"
                 << (a[0] < 0 ? " - " : " + ")
                 << fabs(a[0])

                 << endl;
            cout << "Desviacion Estándar: " << sy << endl;
            cout << "Error Estándar de aproximacion: " << syx << endl;
            cout << "Coeficiente de determinacion: " << r2 << endl;
        }

        double estimar(double p_x)
        {
            if (a.size() != 3)
            {
                return NAN;
            }
            return (a[2] * pow(p_x, 2)) + (a[1] * p_x) + a[0];
        }
    };

    class cuadratica
    {

    public:
        cuadratica(vector<double> v_x, vector<double> v_y) : modelo(v_x, v_y)
        {
        }
        modelo_cuadratico obtener_modelo()
        {
            return modelo;
        }

        double estimar(double p_x)
        {

            return modelo.estimar(p_x);
        }

    private:
        modelo_cuadratico modelo;
    };
}

#endif
