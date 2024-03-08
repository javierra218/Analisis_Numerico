#ifndef REGLA_FALSA_H
#define REGLA_FALSA_H

using std::cout;
using std::endl;
using std::string;

using raices::aproximacion;
using raices::solucion;
using raices::es_raiz;

namespace raices
{

    class regla_falsa
    {
    public:
        /**
         * @brief Construct a new biseccion object
         *
         * @param str_func
         */
        regla_falsa(string str_func) : f(str_func)
        {
        }
        /**
         * @brief
         *
         * @param xi
         * @param xs
         * @param tol
         * @param n
         * @return solucion
         */
        solucion encontrar(double xi, double xs, double tol, int n)
        {

            // solucion a retornar
            solucion sol;

            // verificar los extremos e intervalo
            if (es_raiz(f, xi))
            {
                sol.raiz = xi;
                return sol;
            }
            if (es_raiz(f, xs))
            {
                sol.raiz = xs;
                return sol;
            }

            //verificar que se cumpla TVI
            if (f(xi) * f(xs) > 0)
            {
                cout << "No se cumple el teorema del valor intermedio" << endl;
                return sol;
            }

            // paso 1
            int i = 1;
            // paso 2 calcular la primera aproximacion y evaluar el subintervalo
            double xrAnt =  xs-((f(xs)*(xi-xs))/(f(xi)-f(xs)));
            if (f(xi) * f(xrAnt) > 0.0f)
            {
                xi= xrAnt;
            }
            else
            {
                xs = xrAnt;
            }
            // paso 3
            while (i <= n)
            {
                // paso 4
                double xrNueva =xs-((f(xs)*(xi-xs))/(f(xi)-f(xs)));

                aproximacion ap(xrAnt, xrNueva);

                sol.agregar(ap);


                // paso 5
                if (fabs(f(xrNueva)) < DBL_EPSILON || ap.erp < tol)
                {
                    // Solucion encontrada, guardar la raiz y retornar la solucion
                    sol.raiz = xrNueva;
                    return sol;
                }
                // paso 6
                i++;
                // paso 7
                if (f(xi) * f(xrNueva) > 0.0f)
                {
                    xi = xrNueva;
                }
                else
                {
                    xs = xrNueva;
                }

                xrAnt = xrNueva;
            }
            return sol;
        }

    private:
        expression f; // evaludor de la funcion
    };
};

#endif
