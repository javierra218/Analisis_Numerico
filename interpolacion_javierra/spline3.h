/**
 * @file spline3.h
 * @author javierra
 * @brief Interpolacion mediante trazadores cubicos
 *
 */
#ifndef SPLINE3_H
#define SPLINE3_H

#include <vector>
#include <cmath>

using namespace std;

/*
x       y
3.0     2.5
4.5     1.0
7.0     2.5
9.0     0.5

                xi-1    xi  xi+1
primer intervalo (3.0, 4.5) 7.0
(4.5 - 3.0)f2(3)=>0
+2(7.0 -3.0)f2(4.5)
+(7.0 - 4.5)f2(7.0)
=c1

segundo intervalo (4.5, 7.0) 9.0
(7.0 - 4.5)f2(4.5)
+2(9.0 - 4.5)f2(7.0)
+(9.0 - 7.0)f2(9.0) => 0
=c2

con f2(4.50) y f2(7.0)

*/

namespace interpolacion
{
    /**
     * @brief Interpolacion mediante trazadores cubicos
     *
     */
    class spline3
    {
    public:
        spline3(vector<double> v_x, vector<double> v_y) : x(v_x), y(v_y)
        {
            f2 = calcular();
        }

        double interpolar(double x_int)
        {
            return NAN;
        }

    private:
        vector<double> x;
        vector<double> y;
        vector<double> f2;

        vector<double> calcular()
        {
            vector<double> resultado(x.size());

            size_t n = x.size();

            // Se requieren por lo menos 2 puntos itermedios,
            // para crear un sistema de ecuaciones de minimo 2x2
            if (n < 4)
            {
                return resultado;
            }

            vector<vector<double>> m(n - 2);

            for (size_t i = 0; i < m.size(); i++)
            {
                m[i].resize(n - 1); // cada fila incluye el termino independiente

                // llenar los coeficientes de la matriz
                for (size_t j = 0; j < m[i].size() - 1; j++)
                {
                    double t1 = 0.0f;
                    // si i =! 0 calcular el primer termino
                    if (i != 0)
                    {
                        t1 = x[i] - x[i - 1];
                    }

                    // calcular el segundo termino
                    double t2 = 2.0f * (x[i + 1] - x[i - 1]);

                    double t3 = 0.0f;
                    // si la i =! m.size() -1 calcualr el tercer termino
                    if (i != m.size() - 1)
                    {
                        t3 = x[i + 1] - x[i];
                    }

                    // sumar los terminos
                    m[i][j] = t1 + t2 + t3;
                }
                // Colocar el termino independiente
                double c1 = 0.0f;
                double c2 = 0.0f;
                m[i][j]= c1+c2;
            }

            vector<double> sol = gauss(m);

            //f = [0, sol, 0]

            return resultado;
        }
    };
}

#endif
