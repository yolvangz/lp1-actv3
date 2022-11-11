#include <iostream>
using namespace std;
//int m1[2][2], m2[2][2], aux[2][2], i, j;
int a,b,c,d,i,j,k;
int main () {
	cout << "Por favor, ingrese el numero de filas y columnas que poseeran las matrices: " << endl;
	cin >> a;
	

	int m1[a][a], m2[a][a], aux[a][a];
		
	for (i=0; i<=a-1; i++) {
		for (j=0; j<=a-1; j++){
		cout << "introduzca el valor del digito en la fila " << i+1 << " y columna " << j+1 << " de la matriz 1." << endl;
		cin >> m1[i][j];
		}
	}
	
	for (i=0; i<=a-1; i++) {
		for (j=0; j<=a-1; j++){
		cout << "introduzca el valor del digito en la fila " << i+1 << " y columna " << j+1 << " de la matriz 2." << endl;
		cin >> m2[i][j];
		}
	}
	
	
	for (i=0; i<=a-1; i++) {
		for (j=0; j<=a-1; j++){
			aux[i][j]=0;
			for (k=0; k<=a-1; k++){
				aux[i][j]+=m1[i][k]*m2[k][j];
				
			}
		}
	}
	
	for (i=0; i<=a-1; i++) {
		for (j=0; j<=a-1; j++){
		cout << "El valor del digito en la fila " << i+1 << " y columna " << j+1 << " de la matriz resultante es: " << aux[i][j] << endl;
		}
	}
}