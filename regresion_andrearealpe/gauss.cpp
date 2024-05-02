#include "gauss.h"
void imprimir_tabla(vector<double>x,
					vector<double>y,
					string titulo,
					string label_x,
					string label_y) 
{
	//Imprimir titulo
	cout << "----------------------------------------" << endl;
	cout << titulo << endl;
	//Imprimir etiquetas
	cout << std::setw(20)
		<< label_x
		<< std::setw(20)
		<< label_y
		<< endl;
	cout << "----------------------------------------" << endl;
	//Imprimir datos
	for (size_t i = 0; i < x.size(); i++) {
		cout << std::setw(20)
			<< x[i]
			<< std::setw(20)
			<< y[i]
			<< endl;
	}
	cout << "----------------------------------------" << endl;
}
	
vector<double> gauss(vector<vector<double>>& m)
{
	int i, j, k;
	int n = m.size();
	vector<double> resultado(n);
	// pivoteo: Para cada fila i, buscar en la columna i el valor mayor
	// e intercambiar la fila i por la que contenga el valor mayor.
	for (i = 0; i < n - 1; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			if (m[i][j] > m[i][i])
			{
				std::swap(m[i], m[j]);
			}
		}
	}
	// Eliminacion gaussiana
	for (i = 0; i < n; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			double v = m[j][i] / m[i][i]; // Valor que anula el elemento en la columna
			// Hacer la operacion fila[j] = fila[j] - v * fila[i]
			for (k = 0; k <= n; k++)
			{
				m[j][k] -= v * m[i][k];
			}
		}
	}
	// Despejar las variables
	for (i = n - 1; i >= 0; i--)
	{
		resultado[i] = m[i][n];
		// reemplazar las variables ya halladas
		for (j = i + 1; j < n; j++)
		{
			if (i != j)
			{ // reeemplazar las variables, menos el coeficiente
				resultado[i] = resultado[i] - m[i][j] * resultado[j];
			}
		}
		resultado[i] = resultado[i] / m[i][i];
	}
	return resultado;
}

