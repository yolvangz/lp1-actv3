#include <iostream>
using namespace std;
//int m1[2][2], m2[2][2], aux[2][2], i, j;
int a,b,c,d,i,j;
int main () {
	cout << "Por favor, ingrese el numero que multiplicara la matriz " << endl;
	cin >> c;
	cout << "Por favor, ingrese el numero de filas que poseera la matriz: " << endl;
	cin >> a;
	cout << "Por favor, ingrese el numero de columnas que poseera la matriz: " << endl;
	cin >> b;
	
	int m1[a][b], aux[a][b];
		
		for (i=0; i<=a-1; i++) {
		for (j=0; j<=b-1; j++){
		cout << "introduzca el valor del digito en la fila " << i+1 << " y columna " << j+1 << " de la matriz 1." << endl;
		cin >> m1[i][j];
		}
	}

	
	
	for (i=0; i<=a-1; i++) {
		for (j=0; j<=b-1; j++){
		aux[i][j]=m1[i][j]*c;
		}
	}
	
				for (i=0; i<=a-1; i++) {
		for (j=0; j<=b-1; j++){
		cout << "El valor del digito en la fila " << i+1 << " y columna " << j+1 << " de la matriz resultante es: " << aux[i][j] << endl;
		}
	}
	
}