/**
 * @file
 * @brief M�todo de Trapecio
 * @author 

 */

#ifndef TRAPECIO_H
#define TRAPECIO_H

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
	 * @brief Resultado de calcular el maximo, el error no polinomico del trapecio y el paso
	 */
	struct resultado_trapecio
	{
		double paso = NAN;			  /*!< Valor del paso del a funcion*/
		double max = NAN;			  /*!< Valor maximo de la funcion*/
		double max_with_fabs = NAN;	  /*!< Valor maximo de la funcion con valor absoluto*/
		double error = NAN;			  /*!< Valor del error de la integral*/
		double error_with_fabs = NAN; /*!< Valor del error de la integral con valor absoluto.*/
	};

	/**
	 * @brief Integracion mediante el Metodo del Trapecio
	 */
	class trapecio
	{
	public:
		/**
		 * @brief Crea una nueva instancia de Trapecio.
		 * @param p_str_fn Texto de la funcion a integrar
		 */
		trapecio(string p_str_fn) : str_fn(p_str_fn)
		{
		}

		/**
		 * @brief Calcula el error de una funcion no polinomica
		 * @param a Limite inferior
		 * @param b Limite superior
		 * @param str_fn2 Segunda derivada de la funcion
		 * @return Valores contenidos en la estructura "resultado_trapecio"
		 */
		resultado_trapecio calcular_error_no_polinomica(double a, double b, string str_fn2)
		{
			size_t i;
			int k = 0;
			// Instanciamos una variable de la estructura
			resultado_trapecio r;
			// Paso de la funcion
			r.paso = (b - a);

			// Valores de la variable independiente y dependiente
			vector<double> x;
			vector<double> y;

			// Creamos la tabla de valores
			crear_tabla(x, y, a, b, 32, str_fn2);

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
			r.error = ((-(pow(r.paso, 3))) / (12.0f)) * r.max;
			r.error_with_fabs = fabs(((-(pow(r.paso, 3))) / (12.0f)) * r.max);

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
			// Evaluamos si hay segmentos
			if (n == 0)
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
		double calcular(vector<double> &x, vector<double> &y)
		{
			size_t n = x.size() - 1;
			// Evaluamos si la cantidad de segmentos es igual o menor a cero
			if (n <= 0)
			{
				return NAN;
			}

			double sum = 0.0f;
			// Hallamos la sumatoria
			for (size_t i = 1; i < n; i++)
			{
				sum += fabs(y[i]);
			}
			// Se halla el denominador
			double coef = fabs(y[0]) + (2.0f * sum) + fabs(y[n]);

			double a = x[0];
			double b = x[n];
			// Retornamos el resultado
			return (b - a) * (coef / (2.0f * n));
		}

	private:
		string str_fn; /*!< Evaluador de la funcion */
	};
};

#endif
