 /*
 Realizado por Jorge Arevalo Echevarria
 Parte comentada en main, es para realizar las comprobaciones de tiempo

 EJEMPLO DE INPUT
 9 14
 1 2 4
 1 8 9
 2 3 9
 2 8 11
 3 4 7
 3 9 2
 3 6 4
 4 5 10
 4 6 15
 5 6 11
 6 7 2
 7 8 1
 7 9 6
 8 9 7
 */

 /*
 EJEMPLO PROFESOR
 7 12
 1 2 1
 1 4 4
 2 3 2
 2 4 6
 2 5 4
 3 5 5
 3 6 6
 4 5 3
 4 7 4
 5 6 8
 5 7 8
 6 7 3

 EJEMPLO VERIFICACION DE MST
 9 11
 1 2 4
 1 8 9
 2 3 9
 2 8 11
 3 9 2
 7 8 1
 7 9 6
 8 9 7
 4 5 10
 4 6 15
 5 6 11
 */

#include <stdio.h>
#include <algorithm>
#include <cstring>
#include<iostream>
#include <fstream>
#include<ctime>
#include <time.h>
#include <algorithm>
#include <chrono>

using namespace std;


#define MAX 3000  //maximo numero de vértices

 ///UNION-FIND
 int padre[MAX]; //Este arreglo contiene el padre del i-esimo nodo

 //Método de inicialización
 void makeSet(int n) {
	 for (int i = 1; i <= n; ++i) padre[i] = i;
 }

 //Método para encontrar la raiz del vértice actual X
 int find(int x) {
	 return (x == padre[x]) ? x : padre[x] = find(padre[x]);
 }

 //Método para unir 2 componentes conexas
 void Union(int x, int y) {
	 padre[find(x)] = find(y);
 }

 //Método que me determina si 2 vértices estan o no en la misma componente conexa (para no generar ciclos )
 bool sameComponent(int x, int y) {
	 if (find(x) == find(y)) return true;
	 return false;
 }
 ///FIN UNION-FIND

 int V, A;      //numero de vertices y aristas
 //Estructura arista( edge )
 struct arista {
	 int origen;     //Vértice origen
	 int destino;    //Vértice destino
	 int valor;       //Peso entre el vértice origen y destino
	 arista() {}
	 //Comparador por peso, me servira al momento de ordenar lo realizara en orden ascendente
	 //Cambiar signo a > para obtener el arbol de expansion maxima
	 bool operator<(const arista& e) const {
		 return valor < e.valor;
	 }
 }listaAristas[MAX];      //Arreglo de aristas para el uso en kruskal
 arista MST[MAX];     //Arreglo de aristas del MST(arbol de generacion minimo) encontrado

 void Kruskal() {
	 int origen, destino, valor;//Valores de la arista
	 int total = 0;          //Valor total del MST
	 int numAristas = 0;     //Numero de Aristas del MST

	 makeSet(V);           //Inicializamos cada vertice
	 std::sort(listaAristas, listaAristas + A);    //Ordenamos las aristas por su comparador 

	 for (int i = 0; i < A; ++i) {     //Recorremos las aristas ya ordenadas por el valor
		 origen = listaAristas[i].origen;    //Vértice origen de la arista actual
		 destino = listaAristas[i].destino;  //Vértice destino de la arista actual
		 valor = listaAristas[i].valor;        //Valor de la arista actual

		 //Verificamos si estan o no en la misma componente conexa
		 if (!sameComponent(origen, destino)) {  //Evito ciclos
			 total += valor;              //Incremento el valor total del MST
			 MST[numAristas++] = listaAristas[i];  //Agrego al MST la arista actual
			 Union(origen, destino);  //Union de ambas componentes en una sola
		 }
		 //Si no esta en la componente conexa, comprobamos la siguiente arista
	 }

	 //Si el MST encontrado no posee todos los vértices mostramos mensaje de error
	 //Para saber si contiene o no todos los vértices basta con que el numero de aristas sea igual al numero de vertices - 1
	 if (V - 1 != numAristas) {
		 cout<<"No existe MST valido para el grafo ingresado, el grafo debe ser conexo."<<std::endl;
		// for (int i = 0; i < numAristas; ++i)
			// cout << "prueba para el tiempo" << endl;
		 return;
	 }
	 cout<<("-----El MST encontrado contiene las siguientes aristas-----")<<std::endl;
	 for (int i = 0; i < numAristas; ++i)
		 printf("( %d , %d ) : %d\n", MST[i].origen, MST[i].destino, MST[i].valor); //( vertice u(origen) , vertice v(destino) ) : valor

	 printf("El costo minimo de todas las aristas del MST es : %d\n", total);
 }

 int main() {

	 //scanf("%d %d", &V, &A);//scanf me producia error
	 
	 ifstream ficheroEntrada;
	 string nombreFichero;
	 cout << "Introduce el nombre del fichero a ejecutar: ";
	 std::cin >> nombreFichero;
	 ficheroEntrada.open(nombreFichero);

	 while (!ficheroEntrada.is_open()) {
		 cout << "Error, introduce el nombre del fichero a ejecutar: ";
		 std::cin >> nombreFichero;
		 ficheroEntrada.open(nombreFichero);
	 }

	 ficheroEntrada >> V >> A;

	 //Realizamos el ingreso del grafo, almacenando las aristas en un arreglo con los datos respectivos
	 for (int i = 0; i < A; ++i) {
		 ficheroEntrada >> listaAristas[i].origen >> listaAristas[i].destino >> listaAristas[i].valor;
		 //scanf("%d %d %d", &listaAristas[i].origen, &listaAristas[i].destino, &listaAristas[i].valor);
	 }
	 //pruebas para calcular el tiempo de ejecucion

	// auto start = chrono::high_resolution_clock::now();
	 //Aquí el proceso a medir
	 //for (int j = 0; j <= 1000; j++) {
		 Kruskal();
	 //}
	// auto stop = chrono::high_resolution_clock::now();
	 //cout << "duration= " <<
	//	 chrono::duration_cast<chrono::milliseconds>((stop - start)/1000).
		// count() << " ms" << endl;


	 return 0;
 }

