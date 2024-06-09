/**
 * @file
 * @brief Clase del metodo Simpson
 * @author 

 */

#ifndef SIMPSON_H
#define SIMPSON_H

#include <iostream>
#include "simpson13.h";
#include "simpson38.h"

using integracion::simpson13;
using integracion::simpson38;
using std::cout;
using std::endl;

namespace integracion
{
	/**
	 * @brief Integracion mediante el metodo de Simpson
	 */
	class simpson
	{
	public:
		/**
		 * @brief Calcula las integrales de cada metodo Simpson 1/3 o 3/8
		 * @param x Valores de la variable independiente
		 * @param y Valores de la variable dependiente
		 * @return Valor aproximado de la integral.
		 */
		double simpson_method(vector<double> x, vector<double> y)
		{
			int n = x.size() - 1;
			int div;
			int rest;
			double result_simpson13 = 0.0f;
			double result_simpson38 = 0.0f;
			// Si el numero de elementos es par, aplicar 1/3
			if (n % 2 == 0)
			{
				cout << "Metodo simpson 1/3:" << endl;
				return simpson13::calcular(x, y);
			}
			else if ((n % 2) != 0 && (n % 3) == 0)
			{
				// Si el numero de elementos es impar y multiplo de 3, aplicar 3/8
				cout << "Metodo simpson 3/8:" << endl;
				return simpson38::calcular(x, y);
			}
			else
			{
				// Si no es ninguno de los anteriores, dividir los elementos
				//  y aplicar 1/3 y 3/8 correspondientemente.
				div = n / 2;
				rest = n - div;
				vector<double> x1(x.begin(), x.begin() + div + 1);
				vector<double> y1(x.begin(), x.begin() + div + 1);
				vector<double> x2(x.begin() + div, x.begin() + div + rest + 1);
				vector<double> y2(x.begin() + div, x.begin() + div + rest + 1);
				cout << "Tamanio de x1 y y1 -> x1: " << x1.size() << "  y1: " << y1.size() << endl;
				for (size_t i = 0; i <= div; i++)
				{
					cout << "Para x1 Y y1 -> Valor x[" << i << "] = " << x[i] << "   Valor y[" << i << "] = " << y[i] << endl;
					x1[i] = x[i];
					y1[i] = y[i];
				}
				cout << "Tamanio de x2 y y2 -> x2: " << x2.size() << "  y2: " << y2.size() << endl;
				for (size_t i = 0; i <= rest; i++)
				{
					cout << "Para x2 Y y2 -> Valor x[" << i + div << "] = " << x[i + div] << "   Valor y[" << i + div << "] = " << y[i + div] << endl;
					x2[i] = x[i + div];
					y2[i] = y[i + div];
				}

				if (div % 2 == 0)
				{
					result_simpson13 = simpson13::calcular(x1, y1);
					cout << "Metodo simpson 1/3: " << result_simpson13 << endl;
				}
				if (rest % 2 == 0)
				{
					result_simpson13 = simpson13::calcular(x2, y2);
					cout << "Metodo simpson 1/3: " << result_simpson13 << endl;
				}
				if ((div % 2) != 0 && (div % 3) == 0)
				{
					result_simpson38 = simpson38::calcular(x1, y1);
					cout << "Metodo simpson 3/8: " << result_simpson38 << endl;
				}
				if ((rest % 2) != 0 && (rest % 3) == 0)
				{
					result_simpson38 = simpson38::calcular(x2, y2);
					cout << "Metodo simpson 3/8: " << result_simpson38 << endl;
				}
				return (result_simpson13 + result_simpson38);
			}
		}
	};
};

#endif
