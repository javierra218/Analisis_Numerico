#ifndef NEWTON_RAPHSONG_H
#define NEWTON_RAPHSONG_H

#include <string>

#include "expression.h"
#include "raices.h"

using raices::aproximacion;
using raices::solucion;

using std::string;

namespace raices
{
    class newton_raphsong
    {
    public:
        newton_raphsong(string str_func, string str_dfunc, string str_d2func) : f(str_func), df(str_dfunc), d2f(str_d2func)
        {
        }
        solucion encontrar(double p0, double tol, int n)
        {
            solucion sol;

            // verificar los extremos e intervalo
            if (es_raiz(f, p0))
            {
                sol.raiz = p0;
                return sol;
            }
            




            // paso 1
            int i = 1;

            // paso 2
            while (i <= n)
            {
                // paso 3
                double p = p0 - ((f(p0) * df(p0)) /
                                 (pow(df(p0), 2) -
                                  (f(p0) * d2f(p0))));
                // crear instancia de aproximacion
                aproximacion ap(p0, p);
                sol.agregar(ap);
                // paso 4
                if (ap.erp < tol)
                {
                    sol.raiz = p;
                    return sol;
                }
                // paso 5
                i++;
                // paso 6
                p0 = p;
            }

            return sol;
        }

    private:
        expression f;   /*!Funcion a evaluar*/
        expression df;  /*!Derivada de la Funcion a evaluar*/
        expression d2f; /*!Segunda derivada de la Funcion a evaluar*/
    };
}

#endif
