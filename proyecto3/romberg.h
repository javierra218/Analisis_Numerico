#ifndef ROMBERG_H
#define ROMBERG_H

#include <iostream>
#include <string>
#include <vector>
#include "trapecio.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

using integracion::trapecio;

namespace integracion
{

	/**
	 * @brief Resultado de integracion de Romberg
	 */
	struct resultado_romberg
	{
		double valor = NAN; /*!< Valor de la integral*/
		double error = NAN; /*!< Valor del error de l aintegral.*/
	};

	/**
	 * @brief Integracion mediante el metodo de Romberg
	 */
	class romberg
	{
	public:
		/**
		 * @brief Crea una nueva instancia de romberg
		 * @param p_str_fn Texto de la funcion a integrar
		 */
		romberg(string p_str_fn) : str_fn(p_str_fn)
		{
		}

		/**
		 * @brief Calcula la integrarl en el intervalo dado
		 * @param a Limite inferior
		 * @param b Limite superior
		 * @param k Numero de aproximaciones
		 * @return Valor de la integral aproximada y error de aproximacion.
		 */
		resultado_romberg calcular(double a, double b, int k)
		{
			int i, j;
			int n = 1;
			resultado_romberg res;
			if (k <= 1)
			{
				return res;
			}
			vector<vector<double>> m(k);

			for (i = 0; i < k; i++)
			{
				m[i].resize(k - i);

				// Calcular el valor de la primera columna
				trapecio t(str_fn);
				m[i][0] = t.calcular(a, b, n);
				cout << n << " segmentos = " << m[i][0] << endl;
				n *= 2;
			}

			// Calcular las aproximaciones
			double pot = 4.0f;
			for (j = 1; j < k; j++)
			{
				for (i = 0; i < k - j; i++)
				{
					m[i][j] = ((pot / (pot - 1.0f)) * m[i + 1][j - 1]) - ((1 / (pot - 1.0f)) * m[i][j - 1]);
				}
				pot *= 4.0f;
			}
			res.valor = m[0][k - 1];
			res.error = fabs((m[0][k - 1] - m[0][k - 2]) / (m[0][k - 1])) * 100.0f;
			return res;
		}

	private:
		string str_fn; /*!< Texto de la funcion*/
	};
};

#endif
