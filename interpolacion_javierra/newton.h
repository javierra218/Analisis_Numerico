#ifndef NEWTON_H
#define NEWTON_H_H

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>

using std::ostringstream;
using std::string;
using std::vector;

namespace interpolacion
{
    /**
     * @brief Clase para interpolar usando el polinomio de Newton
     *
     */
    class newton
    {
    public:
        newton(vector<double> v_x, vector<double> v_y) : x(v_x), y(v_y)
        {
            b = calcular_coeficientes(x, y);
        }

        double interpolar(double x_int)
        {
            double y_int = NAN;
            if (b.size() == 0)
            {
                return y_int;
            }

            y_int = b[0];
            for (size_t i = 1; i < b.size(); i++)
            {
                double prod = 1.0;
                for (size_t j = 0; j < i; j++)
                {
                    prod *= (x_int - x[j]);
                }
                y_int += b[i] * prod;
            }
            return y_int;
        }

        /**
         * @brief Interpola el valor de una función en un punto dado utilizando el polinomio de Newton.
         * @param x_int El valor en el que se desea interpolar la función.
         * @param grado El grado del polinomio a utilizar.
         * @return El valor interpolado de la función en el punto dado.
         */
        double interpolar_con_error(double x_int, unsigned grado, double &error)
        {
            // Asegurarse de que el grado es válido
            if (grado >= b.size() || grado < 1)
            {
                error = NAN;
                return NAN;
            }

            double resultado = b[0];
            double producto = 1.0;
            for (unsigned i = 1; i <= grado; ++i)
            {
                producto *= (x_int - x[i - 1]);
                resultado += b[i] * producto;
            }

            // Calcular el error utilizando el término siguiente de las diferencias divididas
            error = b[grado + 1] * producto * (x_int - x[grado]);

            return resultado;
        }

        /**
         * @brief Retorna el polinomio interpolante
         *
         * @return string
         */
        string polinomio()
        {
            if (b.size() == 0)
            {
                return "No hay coeficientes";
            }

            ostringstream s;
            s << b[0];
            for (size_t i = 1; i < b.size(); i++)
            {
                s << (b[i] >= 0 ? " + " : " - ") << fabs(b[i]);
                for (size_t j = 0; j < i; j++)
                {
                    s << "(x - " << x[j] << ")";
                }
            }
            return s.str();
        }

        /**
         * @brief Calcula los coeficientes del polinomio de Newton
         *
         * @param x Vector con los valores de x
         * @param y Vector con los valores de y
         * @return vector<double> Vector con los coeficientes del polinomio de Newton
         */
        static vector<double> calcular_coeficientes(vector<double> x, vector<double> y)
        {
            size_t n = x.size();
            vector<vector<double>> F(n, vector<double>(n));
            vector<double> coeficientes(n);

            for (size_t i = 0; i < n; i++)
            {
                F[i][0] = y[i];
            }

            for (size_t j = 1; j < n; j++)
            {
                for (size_t i = 0; i < n - j; i++)
                {
                    F[i][j] = (F[i + 1][j - 1] - F[i][j - 1]) / (x[i + j] - x[i]);
                }
            }

            for (size_t i = 0; i < n; i++)
            {
                coeficientes[i] = F[0][i];
            }
            return coeficientes;
        }

    private:
        vector<double> x; /*!<Variable independiente */
        vector<double> y; /*!<Variable dependiente */
        vector<double> b; /*!<Coeficientes del polinomio interpolante */
    };
}
#endif
