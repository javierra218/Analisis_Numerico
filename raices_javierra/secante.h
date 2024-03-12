#ifndef SECANTE_H
#define SECANTE_H

#include <cmath>
#include <iostream>
#include <string.h>
#include "expression.h"
#include "raices.h"

using std::string;
using std::cout;
using std::endl;

using raices::aproximacion;
using raices::solucion;

namespace raices {
    /**
    * @brief Metodo de la secante
    */
    class secante {
    public:
        /**
        * @brief Crea una nueva instancia de secante
        * @param str_func Texto de la funcion
        */
        secante(string str_func):f(str_func) {
        }
        
        /**
        * @brief Encuentra una raiz con los parametros dados
        * @param x0 Valor inicial del intervalo
        * @param x1 Valor siguiente del intervalo
        * @param tol Tolerancia (Error relativo porcentual)
        * @param n Maximo numero de iteraciones
        * @return Solucion del metodo
        */
        solucion encontrar(double x0, 
                           double x1, 
                           double tol, 
                           int n) {
            // Solucion a retornar
            solucion sol;

            // verificar los extremos e intervalo
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

            // Paso 1
            int i = 1;
            while(i <= n) {
                // Paso 2
                double x2 = x1 - ((f(x1)*(x0 - x1)) / (f(x0) - f(x1)));
                aproximacion ap(x1, x2);
                // Adicionar la nueva aproximacion al vector de la solucion
                sol.agregar(ap);
                //Paso 3
                if(ap.erp < tol) {
                    sol.establecer(x2);
                    return sol;
                }
                //Paso 4
                i++;
                // Paso 5
                x0 = x1;
                x1 = x2;
            }
            return sol;
        }
    private:
            expression f; /* Evaluador de la funcion */
    };
};

#endif
