#ifndef NEWTON_H
#define NEWTON_H

#include <iostream>
#include <vector>
#include <cmath>

using std::vector;

namespace interpolacion
{
    /**
     * @brief Clase para interpolar usando diferencias divididas de newton
     *
     */
    class newton
    {
    public:
        /**
         * @brief Constructor de la clase
         *
         * @param v_x vector con los valores de x
         * @param v_y vector con los valores de y
         */
        newton(vector<double> v_x, vector<double> v_y) : x(v_x), y(v_y)
        {
            b = calcular_coeficientes(x, y);
        }

        /**
         * @brief calcular los coeficientes del polinomio interpolante
         *
         * @param x
         * @param y
         * @return vector<double>
         */
        static vector<double> calcular_coeficientes(vector<double> x, vector<double> y)
        {
            vector<double> coeficientes;

            //Verificar que existan valores de x y y
            if(x.size()==0 || x.size()!=y.size())
            {
                return coeficientes;
            }
            size_t n = x.size();

            //Reservar espacio para filas
            vector<vector<double>> F(n);

            //inicializar las filas
            for (size_t i = 0; i < n; i++)
            {
                F[i].resize(n-i);
            }

            //Llenar la primera columna
            for (size_t i = 0; i < n; i++)
            {
                F[i][0] = y[i];
            }

            //llenar las demas columnas
            for (size_t j = 1; j < n; j++)
            {
                for (size_t i = 0; i < n - j; i++)
                {
                    F[i][j] = (F[i + 1][j - 1] - F[i][j - 1]) / (x[i + j] - x[i]);
                }
            }

            //Obtener la primera fila de la matriz
            coeficientes=F[0];
            
            return coeficientes;
        }

        /**
         * @brief Interpolar un valor de x
         *
         * @param x_int valor de x a interpolar
         * @return valor del polinomio interpolante en x_int
         */
        double interpolar(double x_int)
        {
            double y_int = NAN;
            // validar si existen coeficientes
            if (b.size() == 0)
            {
                return y_int;
            }
            // POST: Existe al menos un coeficiente
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

    private:
        vector<double> x; /*!<Variable independiente */
        vector<double> y; /*!<Variable dependiente */
        vector<double> b; /*!<Coeficientes del polinomio interpolante */
    };

}

#endif
