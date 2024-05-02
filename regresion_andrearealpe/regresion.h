#ifndef REGRESION_H
#define REGRESION_H

#include <cmath>
#include <iostream>
#include <iomanip>
#include <vector>
#include "gauss.h"
//#include "algorithm"

using std::cout;
using std::endl;
using std::vector;

namespace regresion
{
	/**
	* @brief Solucion de una regresion lineal
	*/
	
	/**
	* @brief Modelo de regresion Lineal.
	*/
	struct solucion_lineal{
		double b0 = NAN;  /**< Termino independiente */
		double b1 = NAN;  /**< Coeficiente de x */
		double st = 0.0f; /**< Sumatoria de la diferencia  */
		double sy = NAN;  /**< Desviacion estandar */
		double sr = 0.0f; /**< Discrepancia entre valor real y estimado */
		double syx = NAN; /**< Error estandar de la estimacion */
		double r2 = 0.0f; /**< Coeficiente de determinacion */
		
		/**
		* @brief Imprime la solucion
		*/
		void imprimir()
		{
			cout << "Recta de regresion: "
				<< "y = "
				<< b1
				<< " * x "
				<< ((b0 > 0) ? " + " : " - ")
				<< fabs(b0)
				<< endl;
			cout << "\nDesviacion Estandar (sy): " << sy << endl;
			cout << "Error Estandar de Aproximacion (syx): " << syx << endl;
			cout << "Coeficiente de Determinacion (r2): " << r2 << endl;
		}
	};
	
	/**
	* @brief Solucion de una regresion cuadratica
	*/
	struct solucion_cuadratica {
		double a0; /*!< Coeficiente independiente del polinimio */
		double a1; /*!< Coeficiente de x del polinomio */
		double a2; /*!< Coeficiente de x^2 del polinomio */
		double st = 0.0f; /*!< Sumatoria de la diferencia cuadratica de yi y el promedio */
		double sr = 0.0f; /*!< Sumatoria de la diferencia cuadratica de yi y la estimacion */
		double sy = 0.0f; /*!< Desviacion estandar */
		double syx = 0.0f; /*!< Error estandar de aproximacion */
		double r2 = 0.0f; /*!< Coeficiente de determinacion */
		/**
		* @brief Imprime la solucion
		*/
		void imprimir() {
			cout << "Regresion cuadratica" << endl;
			cout << "Ecuacion: "
				<< "y = "
				<< a0
				<< ((a1 > 0) ? " + " : " - ") << fabs(a1) << " * x "
				<< ((a1 > 0) ? " + " : " + ") << fabs(a2) << " * x^2 "
				<< endl;
			cout << "\nDesviacion Estandar (sy): " << sy << endl;
			cout << "Error Estandar de Aproximacion (syx): " << syx << endl;
			cout << "Coeficiente de determinacion (r2): " << r2 << endl;
		}
	};
	
	/**
	* @brief Solucion de regresion linealizada mendiante potencia
	*/
	struct solucion_lineal_potencia {
		double c = 0.0f; /*!< Coeficiente de potencia */
		double a = 0.0f; /*!<  */
		solucion_lineal lineal;
		double r2 = 0.0f; /*!< Coeficiente de determinacion */
		void imprimir()
		{
			cout << "Ecuacion: "
				<< "y = " << c << " * e ^"
				<< a << " * x "
				<<endl;
			cout << "\nDesviacion Estandar (sy): " << lineal.sy << endl;
			cout << "Error Estandar de Aproximacion (syx): " << lineal.syx << endl;
			cout << "Coeficiente de Determinacion (r2): " << lineal.r2 << endl;
		}
	};
	
	/**
	* @brief Solucion de regresion linealizada mendiante exponencial
	*/
	struct solucion_lineal_exponencial {
		double c = 0.0f;
		double a = 0.0f;
		solucion_lineal lineal;
		double r2 = 0.0f; /*!< Coeficiente de determinacion */
		void imprimir()
		{
			cout << "Ecuacion: "
				<< "y = " << c << " * e ^"
				<< a << "x "
				<<endl;
			cout << "\nDesviacion Estandar (sy): " << lineal.sy << endl;
			cout << "Error Estandar de Aproximacion (syx): " << lineal.syx << endl;
			cout << "Coeficiente de Determinacion (r2): " << lineal.r2 << endl;
		}
	};
	
	
	
	
	/**
	* @brief Represents a simple linear regression model acording to the function
	* @brief Halla la recta de regresion lineal para los datos datos
	* @param x Valores de la variable independiente (x)
	* @param y Valores de la variable dependiente (y)
	* @return Recta solucion de regresion lineal
	*/
	class regresion_lineal{
	public:
		solucion_lineal calcular(vector<double> x, vector<double> y) {
			solucion_lineal s;
			
			//Validar que los dos vectores tengan el mismo tamaño
			if (x.size() != y.size()) {
				return s;
			}
			
			double n = x.size();
			
			if (n == 0) {
				return s;
			}
			
			double sum_x, sum_y, x_prom, y_prom, sum_x2, sum_xy;
			sum_x = sum_y = sum_x2 = sum_xy = 0.0f;
			
			for (size_t i = 0; i < n; i++) {
				sum_x += x[i];
				sum_y += y[i];
				sum_x2 += pow(x[i], 2.0f);
				sum_xy += x[i] * y[i];
			}
			
			x_prom = sum_x / n;
			y_prom = sum_y / n;
			
			s.b1 = (sum_xy - (y_prom * sum_x)) / (sum_x2 - (x_prom * sum_x));
			s.b0 = y_prom - (s.b1 * x_prom);
			
			s.st = 0.0f;
			
			for (size_t i = 0; i < n; i++) {
				s.st += pow(y[i] - y_prom, 2.0f);
			}
			
			s.sy = sqrt(s.st / (double)(n - 1));
			
			s.sr = 0.0f;
			
			for (size_t i = 0; i < n; i++) {
				s.sr += pow(y[i] - (s.b1 * x[i] + s.b0), 2.0f);
			}
			s.syx = sqrt(s.sr / (double)(n - 2));
			
			s.r2 = (s.st - s.sr) / s.st;
			return s;
		}
	};
	
	/**
	* @brief regresion mediante funcion potencia.
	*/
	class regresion_lineal_potencia{
	public:
		solucion_lineal_potencia calcular(vector<double> x, vector<double> y) {
			solucion_lineal_potencia solucion;
			regresion_lineal rl;
			vector<double> X = x;
			vector<double> Y = y;
			
			//Retornat si los arreglos son de diferente tamaño
			if (x.size() != y.size()) {
				return solucion;
			}
			//POST: losa rreglos tienen el mismo tamaño
			for (size_t i = 0; i < Y.size(); i++) {
				X[i] = log10(x[i]);
				Y[i] = log10(y[i]);
			}
			
			//Calcular la regresión lineal sobre los datos tranformados
			solucion.lineal = rl.calcular(X, Y);
			//Obtener r2 de la regresión con los datos transformados
			solucion.r2 = solucion.lineal.r2;
			//Calcular c
			solucion.c = pow(10, solucion.lineal.b0);
			//Calcular a
			solucion.a = solucion.lineal.b1;
			
			//Return la solucion
			return solucion;
		}
	};
	
	/**
	* @brief regresion mediante funcion exponencial.
	*/
	class regresion_lineal_exponencial{
	public:
		
		solucion_lineal_exponencial calcular(vector<double> x, vector<double> y) {
			
			solucion_lineal_exponencial solucion;
			regresion_lineal rl;
			vector<double> X = x;
			vector<double> Y = y;
			
			//Retornar si los arreglos son de diferente tamaño
			if (x.size() != y.size()) {
				return solucion;
			}
			//POST: los arreglos tienen el mismo tamaño
			for (size_t i = 0; i < X.size(); i++) {
				X[i] = x[i];
				Y[i] = log(y[i]);
			}
			
			//Calcular la regresión lineal sobre los datos tranformados
			solucion.lineal = rl.calcular(X, Y);
			//Obtener r2 de la regresión con los datos transformados
			solucion.r2 = solucion.lineal.r2;
			//Calcular c
			solucion.c = pow(2.71828f, solucion.lineal.b0);
			//Calcular a
			solucion.a = solucion.lineal.b1;
			
			//Return la solucion
			return solucion;
		}
	};
	
	/**
	* @brief regresion mediante funcion cuadratica.
	*/
	class regresion_cuadratica {
	public:
		/*
		* @brief Calcula la regresión cuadrática de los datos proporcionados
		* @param x Variable independiente
		* @param y Variable independiente
		* @param
		*/
		solucion_cuadratica calcular(vector<double> x, vector<double> y) {
			solucion_cuadratica s;
			int n = x.size();
			double sumx = 0.0f;
			double sumx2 = 0.0f;
			double sumx3 = 0.0f;
			double sumx4 = 0.0f;
			double sumy = 0.0f;
			double sumxy = 0.0f;
			double sumx2y = 0.0f;
			
			double y_prom;
			
			if (x.size() == 0 || x.size() != y.size()) {
				return s;
			}
			
			if (n < 3) {
				return s;
			}
			
			//POST: Los arreglos tienen la misma cantidad de datos 
			
			//
			for (size_t i = 0; i < x.size(); i++) {
				sumx += x[i];
				sumx2 += pow(x[i], 2.0f);
				sumx3 += pow(x[i], 3.0f);
				sumx4 += pow(x[i], 4.0f);
				sumy += y[i];
				sumxy += x[i] * y[i];
				sumx2y += pow(x[i], 2.0f) * y[i];
			}
			
			//Calcular el promedio de y
			y_prom = sumy / (double)n;
			
			//Construir la matriz de regresion
			vector<vector<double>> m(3);
			m[0] = { (double)n, sumx, sumx2, sumy };
			m[1] = { sumx, sumx2, sumx3, sumxy };
			m[2] = { sumx2, sumx3, sumx4, sumx2y };
			
			//Eliminacion de Gauss
			vector<double> resultado = gauss(m);
			
			s.a0 = resultado[0];
			s.a1 = resultado[1];
			s.a2 = resultado[2];
			
			for (size_t i = 0; i < x.size(); i++) {
				s.st += pow(y[i] - y_prom, 2.0f);
				s.sr += pow(y[i] - (s.a0 + (s.a1 * x[i]) + (s.a2 * pow(x[i], 2.0f))), 2.0f);
			}
			
			s.syx = sqrt(s.sr / (double)(n - 3));
			s.sy = sqrt(s.st / (double)(n - 1));
			
			s.r2 = (s.st - s.sr) / s.st;
			
			return s;
		}
	};
}	
#endif
	
