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

        double interpolar(double x_int, unsigned int grado)
        {
            if (grado >= x.size() || grado < 0)
            {
                return NAN;
            }
            if (grado == 0)
            {
                return interpolar(x_int);
            }

            /**\todo implementar la interpolacion de un valor con un grado*/

            // 1. Si el grado del polinomio es impar
            // la cantidad de puntos a tomar es par ( un solo sub-intervalo)
            //      cantidad = grado + 1
            //      1.1 Calcular los limites del sub-intervalo
            //      i=posicion del siguiente dato a x_int
            //      inicio = i - (cantidad/2)
            //      fin = inicio + grado
            //      TODO validar si inicio y fin son posiciones validas!!!
            //      1.2 Crear un arreglo x_sub =x[inicio,fin]
            //      1.3 Crear un arreglo y_sub =y[inicio,fin]
            //      1.4 y_int = interpolar x_int con  x_sub y y_sub
            // 2. Si el grado del polinomio es par
            // En el peor caso tendremos dos sub_intervalos
            // 2.1 Primer sub-intervalo:
            //      inicio = i - ((grado/2)+1)
            //      fin = inicio + grado
            //      Si el intervalo es valido
            //       y_int_sup = interpolar x_int con x[inicio,fin] y y[inicio,fin]
            //      Sino:
            //       y_int_sup = NAN
            // 2.2 Segundo sub-intervalo:
            //      inicio = i - ((grado/2))
            //      fin = inicio + grado + 1
            //      Si el intervalo es valido
            //       y_int_inf = interpolar x_int con x[inicio,fin] y y[inicio,fin]
            //      Sino:
            //       y_int_inf = NAN
            // 2.3  Si y_int_sup = NAN
            //          retornar y_int_inf
            //      fin si
            // 2.4  Si y_int_inf = NAN
            //          retornar y_int_sup
            //      fin si
            // 2.5  Calcular el error del sub_intervalo 1
            //      tomar el dato adicionar por debajo del sub_intervalo 1
            //      (suponiendo que se tiene un dato adicional)
            //      calcular F[] con los datos del sub_intervalo 
            //      Tomar el ultimo coeficiente F
            //      error_sup = R * (x_int - x0) * (x_int - x1) * ... * (x_int - xn)
            // 2.6  Calcular el error del sub_intervalo 2
            //      tomar el dato adicionar por encima del sub_intervalo 2
            //      (suponiendo que se tiene un dato adicional)
            //      calcular F[] con los datos del sub_intervalo
            //      Tomar el ultimo coeficiente F: R
            //      error_inf = R * (x_int - x0) (x_int - x1) ... (x_int - xn)
            // 2.7  Retornar y_int_sup o y_int_inf, el que tenga menor error
            //      si fabs(error_sup) < fabs(error_inf)
            //          retornar y_int_sup
            //      sino
            //          retornar y_int_inf
            //      fin si

            

            

            return NAN;


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
