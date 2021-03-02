#include <iostream>
#include <fstream>
using namespace std;

const int MAX_VALOR = 200;

int main() {


	ofstream ficheroSalida;
	string nombreFichero;
	std::cout << "Introduce el nombre del fichero : ";
	std::cin >> nombreFichero;
	ficheroSalida.open(nombreFichero);
	int V, A;
	std::cout << "Introduce el numero de vector : ";
	std::cin >> V;
	std::cout << "Introduce el numero de aristas : ";
	std::cin >> A;

	ficheroSalida << V << " " << A << std::endl;

	int origen, destino, valor;

	for (int i = 0; i < A; i++) {
		ficheroSalida<< 1 + rand() % (V)<<" ";
		ficheroSalida << 1 + rand() % (V) << " ";
		ficheroSalida << 1 + rand() % (MAX_VALOR)<<std::endl;
	}

	ficheroSalida.close();
	return 0;
}