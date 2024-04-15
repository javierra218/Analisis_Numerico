#ifndef LAGRANGE_H
#define LAGRANGE_H

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
     * @brief Clase para interpolar usando el polinomio de lagrange
     *
     */
    class lagrange
    {
    public:
        /**
         * @brief Constructor de la clase
         *
         * @param v_x vector con los valores de x
         * @param v_y vector con los valores de y
         */
        lagrange(vector<double> v_x, vector<double> v_y) : x(v_x), y(v_y)
        {
        }

        /**
         * @brief Retorna el polinomio interpolante usando todos los puntos
         *
         * @return string
         */
        double interpolar(double x_int)
        {

            if (!x.size() || x.size() != y.size())
            {
                return NAN;
            }

            if (x_int < x[0] || x_int > x[x.size() - 1])
            {
                return NAN;
            }

            double sum = 0.0f;
            size_t n = x.size();
            for (size_t j = 0; j < n; j++)
            {
                double Lj = 1.0f;

                for (size_t k = 0; k < n; k++)
                {
                    if (k != j)
                    {
                        Lj *= (x_int - x[k]) / (x[j] - x[k]);
                    }
                }

                sum += y[j] * Lj;
            }

            return sum;
        }

        /**
         * @brief Retorna el polinomio interpolante usando todos los puntos
         *
         * @return string
         */
        string polinomio()
        {
            ostringstream s;

            size_t n = x.size();

            for (size_t j = 0; j < n; j++)
            {

                ostringstream s_num;
                ostringstream s_denom;

                double Lj = 1.0f;

                for (size_t k = 0; k < n; k++)
                {
                    if (k != j)
                    {
                        if (s_num.str().size())
                        {
                            s_num << " * ";
                        }

                        s_num << "(x - " << x[k] << ")";

                        if (s_denom.str().size())
                        {
                            s_denom << " * ";
                        }

                        s_denom << "(" << x[j] << " - " << x[k] << ")";
                    }
                }

                s << y[j] << " * (" << s_num.str() << ") / (" << s_denom.str() << ")";
                if (j < n - 1)
                {
                    s << " + ";
                }
            }

            return s.str();
        }

    private:
        vector<double> x;
        vector<double> y;
    };
}

#endif
