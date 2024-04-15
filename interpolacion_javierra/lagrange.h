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
         * @brief calcula el valor interpolado usando un polinomio de grado especial 
         * @return string
         */

        double interpolar(double x_int, int grado){
            if (grado >= x.size() || grado < 0){
                return NAN;
            }
            if (grado==0){
                return interpolar(x_int);
            }
            
            //1. si el grado de polinomio es impar
            // La cantidad de puntos a tomar es par (un solo subintervalo)
            // cantidad = grado + 1
            // 1.1 calcular los limintes del subintervalo
            // i = posicion  del siguiente dato a x_int
            // inicio = i - (cantidad/2)
            // fin = inicio+grado
            // TODO validar si inicio y fin son posiciones validas
            // 1.2  Crear un arreglo x_sub  = x[inicio, fin]
            // 1.3  Crear un arreglo y_sub  = y[inicio, fin]
            // 1.4  y=int= interpolar x_int con x_sub y y_sub
            // 2. si el grado de polinomio es par
            // en el peor caso tendremos dos subintervalos
            // 2.1 primer subintervalo
            // inicio = i -((grado/2)+1)
            // fin = inicio + grado
            // si el intervalo es valido
            // y_int_sup = interpolar x_int con x[inicio, fin] y y[inicio, fin]
            // sino: y_int_sup = NAN
            // 2.2 segundo subintervalo
            // inicio = i -((grado/2))
            // fin = inicio + grado + 1
            // si el intervalo es valido
            // y_int_inf = interpolar x_int con x[inicio, fin] y y[inicio, fin]
            // sino: y_int_inf = NAN
            // 2.3 si y_int_sup = NAN  return y_int_inf
            // 2.4 si y_int_inf = NAN  return y_int_sup
            // 2.5 calcular el error del subintervalo 1
            // tomar el dato adicional por debajo del subintervalo 1
            // Calcular F[] con los datos del subintervalo tomar el ultimo coeficiente F: R
            // error_sup = R * (x_int - x0)(x_int - x1)....
            // 2.6 calcular el error del subintervalo 2
            // tomar el dato adicional por encima del subintervalo 2
            // Calcular F[] con los datos del subintervalo tomar el primer coeficiente F: R
            // error_inf = R * (x_int - x0)(x_int - x1)....
            // 2.7 retornar y_int_sup o y_int_inf dependiendo el que tenga el menor error
            // si fabs(err_sup)<fabs(err_inf) return y_int_sup
            // sino return y_int_inf







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
