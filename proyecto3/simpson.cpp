/**
 * @file
 * @brief Clase del metodo Simpson
 * @author
 */

#include "simpson13.h";
#include "simpson38.h"

using integracion::simpson13;
using integracion::simpson38;

class simpson
{
public:
	double simpson_method(string p_str_fn, vector<double> x, vector<double> y, int n)
	{
		int div;
		int rest;
		double result_simpson13 = 0.0f;
		double result_simpson38 = 0.0f;
		if (n % 2 == 0)
		{
			simpson13 s13(p_str_fn);
			return s13.calcular(x, y);
		}
		else if ((n % 2) != 0 && (n % 3) == 0)
		{
			simpson38 s38(p_str_fn);
			return s38.calcular(x, y);
		}
		else
		{
			div = n / 2;
			rest = n - div;
			if (div % 2 == 0)
			{
				simpson13 s13(p_str_fn);
				result_simpson13 = s13.calcular(x, y);
			}
			if ((rest % 2) != 0 && (rest % 3) == 0)
			{
				simpson38 s38(p_str_fn);
				result_simpson38 = s38.calcular(x, y);
			}
			return (result_simpson13 + result_simpson38);
		}
	}
};

/*Creamos la clase simpson y verificamos si la cantidad de elementos es par se aplica 1 /3 y si es impar y multiplo de 3 se aplica 3/8

	Pero si ninguno se aplica, se debe se aplicar primero una divisi�n separandolos y verificar si aplicar en un apartado 1/3 o 3/8

	Verificar primero que el numero de elementos es impar

	18 --> 17 segmentos  --> 17/2 = 8 --> segmentos para aplicar 1/3, es decir, agarrar 9 datos de la tabla original.
	El resto va para 3/8

	Por �ltimo, sumar las dos integrales.*/
