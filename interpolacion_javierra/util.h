#ifndef UTIL_H
#define UTIL_H


#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using std::setprecision;
using std::setw;
using std::cout;
using std::endl;
using std::string;
using std::vector;


namespace util{
	/**
	* @brief Repite una cadena de caracteres actuando como delimitadores
	* @param s Cadena a repetir
	* @param n Cantidad de repeticiones
	* @return Concatenacion de s n veces
	*/
	string str_repeat(string s, int n){
		string ret = "";
		for(size_t i = 0; i < n; i++){
			ret += s;
		}
		return ret;
	}
		
		/**
		* @brief Imprime una tabla de datos
		* @param x Variable independiente
		* @param y Variable dependiente
		* @param x_label Etiqueta de la variable independiente
		* @param y_label Etiqueta de la variable dependiente
		*/
		void imprimir_tabla(vector<double> x, vector<double> y, string x_label = "", string y_label = ""){
			if(x_label.length() == 0){
				x_label = "X";
			}
			if(y_label.length() == 0){
				y_label = "Y";
			}
			//Obtiene el tamaño que ocupa el titulo de la columna x
			int tamX = x_label.length()+4;
			//Obtiene el tamaño que ocupa el titulo de la columna y
			int tamY = y_label.length()+4;
			//Obtiene la suma que ocupan ambos titulos de x e y
			int tamAll = tamX+tamY+4;
			cout << str_repeat("-", tamAll)
				<< endl
				<< setw(tamX)
				<< x_label
				<< setw(tamY)
				<< y_label
				<< endl
				<< str_repeat("-", tamAll)
				<< endl;
			for(size_t i = 0; i < x.size(); i++){
				cout << setw(tamX)
					<< x[i]<<"  "
					<< setw(tamY)
					<< y[i] 
					<< endl;
			}
			cout << str_repeat("-", tamAll) << endl;
		}
			
			/**
			* @brief Imprime una matriz de numeros reales.
			* @param m Matriz a imprimir
			*/
			void imprimir_matriz(vector<vector<double>> m){
				for(size_t i = 0; i < m.size(); i++){
					for(size_t j = 0; j < m[i].size(); j++){
						cout << ((j > 0)?"  ":"")<<m[i][j];
					}
					cout<<""<<endl;
				}
			}
				
				/**
				* @brief Eliminacion de Gauss para una matriz de reales.
				* @param m Matriz
				* @return Vector de coeficientes
				*/
				vector<double> gauss(vector<vector<double>> m) {
					int i, j, k;
					int n = m.size();
					vector<double> resultado(n);
					//pivoteo: Para cada fila i, buscar en la columna i el valor mayor
					//e intercambiar la fila i por la que contenga el valor mayor.
					for (i = 0; i < n - 1; i++) {
						for (j = i + 1; j < n; j++) {
							if (m[i][j] > m[i][i]) {
								std::swap(m[i], m[j]);
							}
						}
					}
					//Eliminacion gaussiana
					for (i = 0; i < n; i++) {
						for (j = i + 1; j < n; j++) {
							double v = m[j][i] / m[i][i]; //Valor que anula el elemento en la columna
							//Hacer la operacion fila[j] = fila[j] - v * fila[i]
							for(k=0; k <= n; k++) {
								m[j][k] -= v * m[i][k];
							}
						}
					}
					//Despejar las variables
					for (i= n - 1; i >= 0; i--) {
						resultado[i] = m[i][n];
						//reemplazar las variables ya halladas
						for (j = i + 1; j < n; j++) {
							if (i != j) { //reeemplazar las variables, menos el coeficiente
								resultado[i] = resultado[i] - m[i][j] * resultado[j];
							}
						}
						resultado[i] = resultado[i] / m[i][i];
					}
					return resultado;
				}
};

#endif
