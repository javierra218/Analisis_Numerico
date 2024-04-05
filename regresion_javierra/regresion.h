#ifndef REGRESION_H
#define REGRESION_H

#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>
#include "algorithm"

using std::cout;
using std::endl;
using std::vector;

namespace regresion
{

	struct modelo_lineal
	/**
	 * @brief Modelo de regresion Lineal.
	 *
	 * This structure holds the regression coefficients for a linear regression model.
	 * It consists of two variables: b0 (the intercept) and b1 (the coefficient of x).
	 */
	{
		vector<double> x; /**< The independent variable values. */
		vector<double> y; /**< The dependent variable values. */
		double b0 = NAN;  /**< Termino independiente */
		double b1 = NAN;  /**< Coeficiente de x */
		double st = 0.0f; /**< Sumatoria de la diferencia  */
		double sy = NAN;  /**< Desviacion estandar */
		double sr = 0.0f; /**< Discrepancia entre valor real y estimado */
		double syx = NAN; /**< Error estandar de la estimacion */
		double r2 = 0.0f; /**< Coeficiente de determinacion */

		modelo_lineal(vector<double> v_x, vector<double> v_y) : x(v_x), y(v_y)
		{
			calcular();
		}

		void imprimir()
		{
			cout << "y= "
				 << b1
				 << " * x"
				 << (b0 < 0 ? " - " : " + ")
				 << fabs(b0)
				 << endl;
			cout << "Desviacion Estándar: " << sy << endl;
			cout << "Error Estándar de aproximacion: " << syx << endl;
			cout << "Coeficiente de determinacion: " << r2 << endl;
		}

		double estimar(double p_x)
		{
			size_t n = x.size();
			if (n == 0 || p_x < x[0] || p_x > x[n - 1])
			{
				return NAN;
			}

			return (b1 * p_x) + b0;
		}

		void calcular()
		{
			size_t n = x.size();
			// validar que se tengan datos sufiencientes
			// se necesitan al menos dos datos para calcular sy
			// se necesitan al menos tres datos para calcular syx
			if (n < 2)
			{
				return;
			}

			// validar que se tengan la misma cantidad de datos
			if (n != y.size())
			{
				return;
			}

			double s_x = 0.0f, s_y = 0.0f, s_x2 = 0.0f, s_xy = 0.0f;

			for (size_t i = 0; i < n; i++)
			{
				s_x += x[i];
				s_y += y[i];
				s_xy += x[i] * y[i];
				s_x2 += x[i] * x[i];
			}

			double x_prom = s_x / (double)n;
			double y_prom = s_y / (double)n;

			b1 = (s_xy - (s_x * y_prom)) / (s_x2 - (s_x * x_prom));
			b0 = y_prom - (b1 * x_prom);

			// calcular parametros de calidad
			for (size_t i = 0; i < n; i++)
			{
				// Calcular st
				st += pow(y[i] - y_prom, 2);

				// Calcular sr
				sr += pow(y[i] - estimar(x[i]), 2);
			}

			// calcular desviacion estandar
			sy = sqrt(st / (double)(n - 1));

			// calcular error estandar de aproximacion
			syx = sqrt(sr / (double)(n - 2));

			// calcular coeficiente de determinacion
			r2 = (st - sr) / st;
		}
	};

	/**
	 * @brief Modelo linealizado mediante funcion exponencial.
	 *
	 */
	struct modelo_exponencial
	{
		modelo_lineal lineal; /**< Modelo de los datos linealizados. */
		double a;			  /**< Potencia de e. */
		double c;			  /**< Coeficiente de e ^(a*x). */

		void imprimir()
		{
			cout << "y= "
				 << c
				 << " * e^( "
				 << a
				 << " * x)"
				 << endl;
			cout << "Desviacion Estándar: " << lineal.sy << endl;
			cout << "Error Estándar de aproximacion: " << lineal.syx << endl;
			cout << "Coeficiente de determinacion r2: " << lineal.r2 << endl;
		}

		double estimar(double p_x)
		{

			return c * exp(a * p_x);
		}
	};

	/**
	 * @brief Represents a simple linear regression model.
	 */
	class lineal_simple
	{
	public:
		lineal_simple(vector<double> v_x, vector<double> v_y) : modelo(v_x, v_y)
		{
		}

		double estimar(double p_x)
		{

			return modelo.estimar(p_x);
		}
		modelo_lineal obtener_modelo()
		{
			return modelo;
		}

	private:
		modelo_lineal modelo; /**< Modelo de regresion Lineal. */
							  /**
							   * Calculates the linear model.
							   *
							   * @return The calculated linear model.
							   */
	};

	class potencia
	{
	public:
		potencia(vector<double> v_x, vector<double> v_y) : x(v_x), y(v_y)
		{
			calcular_modelo();
		}
		double estimar(double p_x)
		{
			size_t n = x.size();
			if (n == 0 || p_x < x[0] || p_x > x[n - 1])
			{
				return NAN;
			}
			return modelo.estimar(p_x);
		}
		modelo_potencia obtener_modelo()
		{
			return modelo;
		}

	private:
		vector<double> x;		/*!< variable independiente */
		vector<double> y;		/*!< variable dependiente */
		modelo_potencia modelo; /*!< Modelo de regresion potencia */
	};

	/**
	 * @brief regresion mediante funcion exponencial.
	 */
	class exponencial
	{
	public:
		exponencial(vector<double> v_x, vector<double> v_y) : x(v_x), y(v_y)
		{
			calcular_modelo();
		}
		double estimar(double p_x)
		{
			size_t n = x.size();
			if (n == 0 || p_x < x[0] || p_x > x[n - 1])
			{
				return NAN;
			}
			return modelo.estimar(p_x);
		}
		modelo_exponencial obtener_modelo()
		{
			return modelo;
		}

	private:
		vector<double> x;		   /*!< variable independiente */
		vector<double> y;		   /*!< variable dependiente */
		modelo_exponencial modelo; /*!< Modelo de regresion potencia */

		void calcular_modelo()
		{
			// 1. X = x (no se transforma)
			vector<double> X(x);

			// 2. transformat y = log(y)
			vector<double> Y(y);

			std::for_each(Y.begin(), Y.end(), [](double &val)
						  { val = log(val); });
			// 3. crear una instancia de la clase lineal_simple,pasandole los datos transformados
			lineal_simple reg_lineal(X, Y);
			// 4. obtener el modelo lineal y asignarlo a la variable miembro 'modelo.lineal'
			modelo.lineal = reg_lineal.obtener_modelo();
			// 5. con base en el modelo obtenido calcular c y a
			modelo.c = exp(modelo.lineal.b0);
			modelo.a = modelo.lineal.b1;
		}
	};

	/**
	 * @brief Modelo linealizado mediante funcion de la potencia.
	 *
	 */
	struct modelo_potencia
	{
		vector<double> x;	  /**< The independent variable values. */
		vector<double> y;	  /**< The dependent variable values. */
		modelo_lineal lineal; /**< Modelo de los datos linealizados. */
		double a;			  /**< Potencia de x. */
		double c;			  /**< Coeficiente de la potencia. */

		void imprimir()
		{
			cout << "y= "
				 << c
				 << " * x^"
				 << a
				 << endl;
			cout << "Desviacion Estándar: " << lineal.sy << endl;
			cout << "Error Estándar de aproximacion: " << lineal.syx << endl;
			cout << "Coeficiente de determinacion r2: " << lineal.r2 << endl;
		}

		void calcular()
		{
			// 1. transformat x = log(x)
			vector<double> X(x);

			std::for_each(X.begin(), X.end(), [](double &val)
						  { val = log10(val); });

			// 2. transformat y = log(y)
			vector<double> Y(y);

			std::for_each(Y.begin(), Y.end(), [](double &val)
						  { val = log10(val); });
			// 3. crear una instancia de la clase lineal_simple,pasandole los datos transformados
			lineal_simple reg_lineal(X, Y);
			// 4. obtener el modelo lineal y asignarlo a la variable miembro 'modelo.lineal'
			lineal = reg_lineal.obtener_modelo();
			// 5. con base en el modelo obtenido calcular c y a
			c = pow(10.0f, lineal.b0);
			a = lineal.b1;
		}

		double estimar(double p_x)
		{
			return c * pow(p_x, a);
		}
	};

};

#endif
