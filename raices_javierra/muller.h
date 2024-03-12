#ifndef MULLER_H
#define MULLER_H

#include <cmath>
#include <string>
#include <iostream>
#include <iomanip>

#include "expression.h"
#include "raices.h"

using std::string;
using std::cout;
using std::endl;

using raices::aproximacion;
using raices::solucion;

namespace raices
{
    class muller
    {
    public:
        muller(string str_func) : f(str_func) {}
        solucion encontrar(double x0, double x1, double x2, double tol, int n)
        {
            solucion sol;

            // verificar los puntos de la parabola inicial
            
            if (es_raiz(f, x0))
            {
                sol.establecer(x0);
                return sol;
            }
            if (es_raiz(f, x1))
            {
                sol.establecer(x1);
                return sol;
            }
            if (es_raiz(f, x2))
            {
                sol.establecer(x2);
                return sol;
            }


            // paso1
            double h1 = x1 - x0;
            double h2 = x2 - x1;
            double d1 = ((f(x1) - f(x0)) / h1);
            double d2 = ((f(x2) - f(x1)) / h2);
            double a = (d2 - d1) / (h2 + h1);
            int i = 2;

            // paso2
            while (i <= n)
            {
                // paso3
                double b = d2 + (h2 * a);
                double c = f(x2);

                cout << a << "(x-)"<< std::setprecision(9)<< x2 << ")^2 + " << b << "(x-"<<std::setprecision(9)<< x2 << ") + " << c << endl;

                double D = sqrt(pow(b, 2) - (4.0f * a * c));
                // paso4
                double E = b - D;
                if (fabs(b - D) < fabs(b + D))
                {
                    E = b + D;
                }
                // paso5
                double h = (-2.0f * c) / E;
                double p = x2 + h;
                // paso6
                aproximacion ap(x2, p);
                sol.agregar(ap);
                // Establecer la raiz y retornar si se cumple la tolerancia
                if (ap.erp < tol)
                {
                    sol.establecer(p);
                    return sol;
                }
                // paso7
                x0 = x1;
                x1 = x2;
                x2 = p;

                h1 = x1 - x0;
                h2 = x2 - x1;
                d1 = ((f(x1) - f(x0)) / h1);
                d2 = ((f(x2) - f(x1)) / h2);
                a = (d2 - d1) / (h2 + h1);
                i++;
            }

            return sol;
        }

    private:
        expression f;
    };

}

#endif
