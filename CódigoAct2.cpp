#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <queue>
#include <stack>

using namespace std;

bool esGrafoCompleto(const vector<vector < int> > &matriz_adyacencia)
{
	// Si la matriz está vacía, no es un grafo completo
	if (matriz_adyacencia.empty())
	{
		return false;
	}

	// Si la matriz no es cuadrada, no es un grafo completo
	if (matriz_adyacencia.size() != matriz_adyacencia[0].size())
	{
		return false;
	}

	// Comprobamos que cada elemento de la matriz es igual a 1, excepto la diagonal
	for (size_t i = 0; i < matriz_adyacencia.size(); ++i)
	{
		for (size_t j = 0; j < matriz_adyacencia[i].size(); ++j)
		{
			// Si el elemento de la diagonal no es cero, no es un grafo completo
			if (i == j && matriz_adyacencia[i][j] != 0)
			{
				return false;
			}

			// Si el elemento fuera de la diagonal no es uno, no es un grafo completo
			if (i != j && matriz_adyacencia[i][j] != 1)
			{
				return false;
			}
		}
	}

	// Si todos los elementos de la matriz son 1 excepto la diagonal, es un grafo completo
	return true;
}

bool esGrafoKRegular(const vector<vector < int> > &matriz_adyacencia, int k)
{
	// Si la matriz está vacía, no es un grafo k-regular
	if (matriz_adyacencia.empty())
	{
		return false;
	}

	// Si la matriz no es cuadrada, no es un grafo k-regular
	if (matriz_adyacencia.size() != matriz_adyacencia[0].size())
	{
		return false;
	}

	// Comprobamos que cada fila de la matriz tiene exactamente k elementos iguales a 1
	for (size_t i = 0; i < matriz_adyacencia.size(); ++i)
	{
		int sum = 0;
		for (size_t j = 0; j < matriz_adyacencia[i].size(); ++j)
		{
			if (matriz_adyacencia[i][j] == 1)
			{
				sum++;
			}
		}

		if (sum != k)
		{
			return false;
		}
	}

	// Si todas las filas tienen k elementos iguales a 1, es un grafo k-regular
	return true;
}

bool esGrafoBipartito(const vector<vector < int> > &matriz_adyacencia)
{
	// Si la matriz está vacía, no es un grafo bipartito
	if (matriz_adyacencia.empty())
	{
		return false;
	}

	// Si la matriz no es cuadrada, no es un grafo bipartito
	if (matriz_adyacencia.size() != matriz_adyacencia[0].size())
	{
		return false;
	}

	// Creamos un vector para guardar el color de cada vértice
	vector<int> colores(matriz_adyacencia.size(), 0);

	// Coloreamos el primer vértice con el color 1
	colores[0] = 1;

	// Creamos una cola para realizar el recorrido BFS
	queue<int> cola;
	cola.push(0);

	// Realizamos el recorrido BFS para colorear todos los vértices
	while (!cola.empty())
	{
		int actual = cola.front();
		cola.pop();

		// Comprobamos los vértices adyacentes al vértice actual
		for (size_t i = 0; i < matriz_adyacencia[actual].size(); ++i)
		{
			// Si el vértice actual y el vértice adyacente están conectados, comprobamos si tienen el mismo color
			if (matriz_adyacencia[actual][i] == 1)
			{
			 	// Si el vértice adyacente no tiene color, lo coloreamos con el color opuesto al del vértice actual
				if (colores[i] == 0)
				{
					colores[i] = -colores[actual];
					cola.push(i);
				}

				// Si el vértice adyacente tiene el mismo color que el vértice actual, el grafo no es bipartito
				else if (colores[i] == colores[actual])
				{
					return false;
				}
			}
		}
	}

	// Si todos los vértices están coloreados sin conflicto, el grafo es bipartito
	return true;
}

bool esMultigrafo(const vector<vector < int> > &matriz_adyacencia)
{
	for (size_t i = 0; i < matriz_adyacencia.size(); ++i)
	{
		for (size_t j = 0; j < matriz_adyacencia[i].size(); ++j)
		{
			if (matriz_adyacencia[i][j] > 1)
			{
				return true;
			}
		}
	}

	return false;
}

bool esGrafoSimple(vector<vector < int> > matriz_adyacencia)
{
	int n = matriz_adyacencia.size();
	int aristas_repetidas = 0;

	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (matriz_adyacencia[i][j] > 1)
			{
				aristas_repetidas += (matriz_adyacencia[i][j] - 1);
			}
		}
	}

	return (aristas_repetidas == 0);
}

void bfs(vector<vector < int> > &matriz_adyacencia, int source)
{
	int n = matriz_adyacencia.size();
	vector<bool> visitado(n, false);
	queue<int> q;

	// Agregar el nodo de inicio a la cola y marcarlo como visitado
	q.push(source);
	visitado[source] = true;

	while (!q.empty())
	{
		// Tomar el nodo actual de la cola
		int nodo_actual = q.front();
		q.pop();

		// Imprimir el nodo actual o hacer cualquier otra operación deseada
		cout << nodo_actual << " ";

		// Agregar los vecinos no visitados a la cola
		for (int i = 0; i < n; ++i)
		{
			if (matriz_adyacencia[nodo_actual][i] != 0 && !visitado[i])
			{
				q.push(i);
				visitado[i] = true;
			}
		}
	}

	cout << endl;
}

void dfs(vector<vector < int> > &matriz_adyacencia, int source)
{
	int n = matriz_adyacencia.size();
	vector<bool> visitado(n, false);
	stack<int> pila;
	pila.push(source);
	visitado[source] = true;

	while (!pila.empty())
	{
		int actual = pila.top();
		pila.pop();
		cout << actual << " ";

		for (int i = 0; i < n; ++i)
		{
			if (matriz_adyacencia[actual][i] != 0 && !visitado[i])
			{
				pila.push(i);
				visitado[i] = true;
			}
		}
	}

	cout << endl;
}

int main()
{
	string filename = "matriz.txt";
	ifstream file(filename.c_str());

	if (!file.is_open())
	{
		cerr << "Error: no se pudo abrir el archivo." << endl;
		return 1;
	}

	vector<vector < int> > matriz_adyacencia;

	string line;
	while (getline(file, line))
	{
		vector<int> row;
		int val;
		size_t pos = 0;
		string token;
		while ((pos = line.find(',')) != string::npos)
		{
			token = line.substr(0, pos);
			val = atoi(token.c_str());
			row.push_back(val);
			line.erase(0, pos + 1);
		}

		val = atoi(line.c_str());
		row.push_back(val);
		matriz_adyacencia.push_back(row);
	}
	int opcion;
	cout << "Aqui esta el menu de opciones\n";
	cout << "-------------------------------------------------------\n";
	cout << "1.- Es grafo completo\n";
	cout << "2.- Es grafo k-regular\n";
	cout << "3.- Es grafo Bi-partito\n";
	cout << "4.- Es Multi-Grafon\n";
	cout << "5.- Es Grafo-simple\n";
	cout << "6.- Recorrido por anchura\n";
	cout << "7.- Recorrido por profundidad\n\n";
	cin >> opcion;
	bool verificador;
	switch (opcion){
		case 1:
			verificador=esGrafoCompleto(matriz_adyacencia);
			if(verificador==true){
				cout<<"Es un grafo completo";
			}else{
				cout<<"No es un grafo completo";
			}
			break;
		case 2:
			int k;
			cout<<"Ingresa el valor k del regular: \n";
			cin >> k;
			verificador=esGrafoKRegular(matriz_adyacencia,k);
			if(verificador==true){
				cout<<"Es un grafo-k-regular";
			}else{
				cout<<"No es un grafo-k-regular";
			}
			break;
		case 3:
			verificador=esGrafoBipartito(matriz_adyacencia);
			if(verificador==true){
				cout<<"Es un bi-partito";
			}else{
				cout<<"No es un bi-partito";
			}
			break;
		case 4:
			verificador=esMultigrafo(matriz_adyacencia);
			if(verificador==true){
				cout<<"Es un multi-grafo";
			}else{
				cout<<"No es un multi-grafo";
			}
			break;
		case 5:
			verificador=esGrafoSimple(matriz_adyacencia);
			if(verificador==true){
				cout<<"Es un grafo simple";
			}else{
				cout<<"No es un grafo simple";
			}
			break;
		case 6:
			bfs(matriz_adyacencia,0);
			break;
		case 7:
			dfs(matriz_adyacencia,0);
			break;
		}
	}
	
	/*
	    file.close();

	    for (size_t i = 0; i < matriz_adyacencia.size(); ++i) {
	        for (size_t j = 0; j < matriz_adyacencia[i].size(); ++j) {
	            cout << matriz_adyacencia[i][j] << " ";
	        }

	        cout << endl;
	    }

	*/


