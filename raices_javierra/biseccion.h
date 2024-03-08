/**
 * @file biseccion.h
 * @author Javier Rojas
 * @brief
 * @version 0.1
 * @date 2024-03-03
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef BISECCION_H
#define BISECCION_H

#include <string>
#include <cmath>
#include "expression.h"
#include "raices.h"

using std::cout;
using std::endl;
using std::string;

using raices::aproximacion;
using raices::solucion;
using raices::es_raiz;

    namespace raices
{

    class biseccion
    {
    public:
        /**
         * @brief Construct a new biseccion object
         *
         * @param str_func
         */
        biseccion(string str_func) : f(str_func)
        {
        }
        /**
         * @brief
         *
         * @param xa
         * @param xb
         * @param tol
         * @param n
         * @return solucion
         */
        solucion encontrar(double xa, double xb, double tol, int n)
        {

            // solucion a retornar
            solucion sol;

            // verificar los extremos e intervalo
            if (es_raiz(f, xa))
            {
                sol.raiz = xa;
                return sol;
            }
            if (es_raiz(f, xb))
            {
                sol.raiz = xb;
                return sol;
            }

            // verificar que se cumpla TVI
            if (f(xa) * f(xb) > 0)
            {
                cout << "No se cumple el teorema del valor intermedio" << endl;
                return sol;
            }

            // paso 1
            int i = 1;
            // paso 2 calcular el punto medio y evaluar el subintervalo
            double xAnt = (xa + xb) / 2.0f;
            if (f(xa) * f(xAnt) > 0.0f)
            {
                xa = xAnt;
            }
            else
            {
                xb = xAnt;
            }
            // paso 3
            while (i <= n)
            {
                // paso 4
                double xNueva = (xa + xb) / 2.0f;

                aproximacion ap(xAnt, xNueva);

                sol.agregar(ap);

                // paso 5
                if (es_raiz(f, xNueva) || ap.erp < tol)
                {
                    // Solucion encontrada, guardar la raiz y retornar la solucion
                    sol.raiz = xNueva;
                    return sol;
                }
                // paso 6
                i++;
                // paso 7
                if (f(xa) * f(xNueva) > 0.0f)
                {
                    xa = xNueva;
                }
                else
                {
                    xb = xNueva;
                }

                xAnt = xNueva;
            }
            return sol;
        }

    private:
        expression f; // evaludor de la funcion
    };
};

#endif
