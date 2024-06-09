#ifndef DERIVACION_H
#define DERIVACION_H

#include "Expression.h"

namespace derivacion
{
	/**
	 * @brief
	 */
	class derivada
	{
	public:
		/**
		 * @brief
		 */
		derivada(string p_str_fn) : f(p_str_fn)
		{
		}

		/**
		 * @brief Construye una tabla de datos espaciados uniformemente.
		 * @param x Referencia al vector donde se almacenaran los valores de X
		 * @param y Referencia al vector donde se almacenaran los valores de Y
		 * @param punto Punto inicial para evaluar
		 * @param paso Paso que tendra la funcion entre cada valor
		 * @param str_fn Texto de la funcion a evaluar
		 */
		void crear_tabla(vector<double> &x, vector<double> &y, double punto, double paso, string str_fn)
		{
			// Crear el evaluador
			Expression f(str_fn);

			// Reservar espacio para la cantidad requerida de segmentos
			x.resize(6);
			y.resize(6);

			double xi = punto;
			// Rellenar la tabla con los datos de X y Y
			for (int i = 0; i <= 5; i++)
			{
				x[i] = xi;
				y[i] = f(xi);
				xi += paso;
			}
		}

		/**
		 * @brief
		 */
		double diferenciacion(double xi, double paso, int diferencias, int direccion)
		{
			// La direccion se ve representada por:
			// 0  Hacia atr�s
			// 1   Central
			// 2   Hacia delante

			// Primeras diferencias, hacia delante
			if (diferencias == 1 && direccion == 2)
			{
				double yi = f(xi);
				double yiplus1 = f(xi + paso);
				return (yiplus1 - yi) / paso;
			} // Primeras diferencias, hacia atras
			else if (diferencias == 1 && direccion == 0)
			{
				double yi = f(xi);
				double yiminus1 = f(xi - paso);
				return (yi - yiminus1) / paso;
			} // Primeras diferencias, central
			else if (diferencias == 1 && direccion == 1)
			{
				double yiplus1 = f(xi + paso);
				double yiminus1 = f(xi - paso);
				return (yiplus1 - yiminus1) / (2.0f * paso);
			} // Segundas diferencias, hacia delante
			else if (diferencias == 2 && direccion == 2)
			{
				double yi = f(xi);
				double yiplus1 = f(xi + paso);
				double yiplus2 = f(xi + (2.0f * paso));
				return ((-yiplus2) + (4.0f * yiplus1) - (3.0f * yi)) / (2.0f * paso);
			} // Segundas diferencias, hacia atras
			else if (diferencias == 2 && direccion == 0)
			{
				double yi = f(xi);
				double yiminus1 = f(xi - paso);
				double yiminus2 = f(xi - (2.0f * paso));
				return ((3.0f * yi) - (4.0f * yiminus1) + yiminus2) / (2.0f * paso);
			} // Segundas diferencias, central
			else if (diferencias == 2 && direccion == 1)
			{
				double yiplus1 = f(xi + paso);
				double yiplus2 = f(xi + (2.0f * paso));
				double yiminus1 = f(xi - paso);
				double yiminus2 = f(xi - (2.0f * paso));
				return ((-yiplus2) + (8.0f * yiplus1) - (8.0f * yiminus1) + yiminus2) / (12.0f * paso);
			} // No encuentra ninguna de las opciones
			else
			{
				return NAN;
			}
		}

	private:
		Expression f; /*!< Texto de la funcion*/
	};
};

#endif
