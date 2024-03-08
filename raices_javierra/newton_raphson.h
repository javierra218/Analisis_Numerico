#ifndef NEWTON_RAPHSON_H
#define NEWTON_RAPHSON_H

#include <string>

#include "raices.h"
#include "expression.h"

using std::string;

using raices::aproximacion;
using raices::solucion;

namespace raices
{
    class newton_raphson
    {
    public:
        newton_raphson(string str_func, string str_dfunc) : f(str_func), df(str_dfunc)
        {
        }
        solucion encontrar (double p0,double tol, int n){
            solucion sol;

            // verificar los extremos e intervalo
            if (es_raiz(f, p0))
            {
                sol.raiz = p0;
                return sol;
            }
            

            //paso 1
            int i=1;

            //paso 2
            while (i<=n)
            {
                //paso 3
                double p=p0-(f(p0)/df(p0));
                //crear instancia de aproximacion
                aproximacion ap(p0,p);
                sol.agregar(ap);
                //paso 4
                if (ap.erp<tol)
                {
                    sol.raiz=p;
                    return sol;
                }
                //paso 5
                i++;
                //paso 6
                p0=p;
                
                
            }
            
            return sol;
        }
    private:
        expression f;
        expression df;
    };
}

#endif
