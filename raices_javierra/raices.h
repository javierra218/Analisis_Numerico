#ifndef RAICES_H
#define RAICES_H

#include <cmath>
#include <vector>
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::vector;
using std::setw;
using std::setprecision;

namespace raices
{
    struct aproximacion
    {
        double anterior;
        double nuevo;
        double erp;

        aproximacion(double vAnterior, double vNuevo) : anterior(vAnterior), nuevo(vNuevo)
        {
            erp = fabs((nuevo - anterior) / nuevo) * 100.0f;
        };
    };

    struct solucion
    {
        double raiz = NAN;
        vector<aproximacion> aproximaciones;

        void agregar(aproximacion a)
        {
            aproximaciones.push_back(a);
        }
    };

    void imprimir_solucion(solucion &sol)
    {
        if (std::isnan(sol.raiz))
        {
            cout << "No se encontro la raiz" << endl;
        }
        else
        {
            cout << "La raiz es: " << setprecision(9)<< sol.raiz << endl;
        }

        size_t cantAproximaciones = sol.aproximaciones.size();

        if( cantAproximaciones== 0){
            return;
        }

        cout<< "Aproximaciones" << cantAproximaciones << endl;
        cout << setw(15)<< "Anterior" << setw(3) << "   " << setw(15) << "Nuevo" << setw(3)<<"   "<<setw(20)<< "Error rel.porcent" <<endl;

        for (size_t i = 0; i < cantAproximaciones; i++)
        {
            const aproximacion ap = sol.aproximaciones[i];
            cout << setw(15)<<setprecision(9) << ap.anterior <<setw(3)<< "   " <<setw(15)<< ap.nuevo <<setw(3)<<setprecision(9)<< "   " << setw(20)<<setprecision(3)<<ap.erp << endl;
        }
    }

};

#endif
