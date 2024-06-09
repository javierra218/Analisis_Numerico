#ifndef SIMPSON38_H
#define SIMPSON38_H

#include <iostream>

#include <vector>
#include <string>
#include "util.h"

#include "Expression.h"

using std::string;
using std::vector;
using util::crear_tabla;

namespace integracion
{

	/**
	 * @brief Resultado de calcular el maximo, el error no polinomico de simpson 3/8 y el paso
	 */
	struct resultado_simpson38
	{
		double paso = NAN;			  /*!< Valor del paso del a funcion*/
		double max = NAN;			  /*!< Valor maximo de la funcion*/
		double max_with_fabs = NAN;	  /*!< Valor maximo de la funcion con valor absoluto*/
		double error = NAN;			  /*!< Valor del error de la integral*/
		double error_with_fabs = NAN; /*!< Valor del error de la integral con valor absoluto.*/
	};

	/**
	 * @brief Integracion mediante el Metodo de Simpson 3/8
	 */
	class simpson38
	{
	public:
		/**
		 * @brief Crea una nueva instancia de Simpson 3/8
		 * @param p_str_fn Texto de la funcion a integrar
		 */
		simpson38(string p_str_fn) : str_fn(p_str_fn)
		{
		}

		/**
		 * @brief Calcula el error de una funcion no polinomica
		 * @param a Limite inferior
		 * @param b Limite superior
		 * @param str_fn4 Cuarta derivada de la funcion
		 * @return Valores contenidos en la estructura "resultado_simpson38"
		 */
		resultado_simpson38 calcular_error_no_polinomica(double a, double b, string str_fn4)
		{
			size_t i;
			int k = 0;
			// Instanciamos una variable de la estructura
			resultado_simpson38 r;
			// Paso de la funcion
			r.paso = (b - a) / 3.0f;

			// Valores de la variable independiente y dependiente
			vector<double> x;
			vector<double> y;

			// Creamos la tabla de valores
			crear_tabla(x, y, a, b, 32, str_fn4);

			r.max_with_fabs = fabs(y[0]);
			r.max = y[0];
			// Hallar el valor maximo de la funcion
			for (i = 0; i < y.size(); i++)
			{
				if (fabs(y[i]) > r.max_with_fabs)
				{
					r.max = y[i];
					r.max_with_fabs = fabs(y[i]);
				}
			}
			r.error = ((-(pow(r.paso, 5) * 3.0f)) / (80.0f)) * r.max;
			r.error_with_fabs = fabs(((-(pow(r.paso, 5) * 3.0f)) / (80.0f)) * r.max);

			// Hallar cifras significativas
			double decimas = r.error_with_fabs;
			while (decimas < 1)
			{
				decimas = decimas * 10;
				k++;
			}
			cout << "La integral tiene " << k - 1 << " cifras decimales significativas" << endl;
			return r;
		}

		/**
		 * @brief Calcular el valor de la integral en el intervalo
		 * @param a Limite inferior del intervalo
		 * @param b Limite superior del intervalo
		 * @param n Cantidad de segmentos.
		 * @return Valor aproximado de la integral.
		 */
		double calcular(double a, double b, int n)
		{
			// Evaluamos si la cantidad de segmentos es igual o menor a cero,
			//  O la cantidad de segmentos es par o no es multiplo de 3
			if (n <= 0 || (n % 2) == 0 || (n % 3) != 0)
			{
				return NAN;
			}
			// Intercambiamos los limites si el limite inferior es mayor que el superior.
			if (a > b)
			{
				std::swap(a, b);
			}

			vector<double> x;
			vector<double> y;

			// Generar la tabla de datos
			crear_tabla(x, y, a, b, n, str_fn);

			// Calculamos el resultado
			return calcular(x, y);
		}

		/**
		 * @brief Calcula la integral de una tabla de datos
		 * @param x Valores de la variable independiente
		 * @param y Valores de la variable dependiente
		 * @return Valor aproximado de la integral.
		 */
		static double calcular(vector<double> &x, vector<double> &y)
		{
			size_t n = x.size() - 1;
			// Evaluamos si la cantidad de segmentos es igual o menor a cero,
			//  O la cantidad de segmentos es par o no es multiplo de 3
			if (n <= 0 || (n % 2) == 0 || (n % 3) != 0)
			{
				return NAN;
			}
			double h = (x[n] - x[0]) / (double)n;
			// TODO Calcular la integral mediante simpson 1/3
			double resultado = 0.0f;
			double sum_1 = 0.0f;
			double sum_2 = 0.0f;
			double sum_3 = 0.0f;
			for (size_t i = 1; i < n; i += 3)
			{
				sum_1 += fabs(y[i]);
			}
			for (size_t i = 2; i < n; i += 3)
			{
				sum_2 += fabs(y[i]);
			}
			for (size_t i = 3; i < n; i += 3)
			{
				sum_3 += fabs(y[i]);
			}
			// Se halla el resultado
			resultado = ((3.0f * h) / 8.0f) * (fabs(y[0]) + (3.0f * sum_1) + (3.0f * sum_2) + (2.0f * sum_3) + fabs(y[n]));
			return resultado;
		}

	private:
		string str_fn; /*!< Evaluador de la funcion */
	};
};

#endif
