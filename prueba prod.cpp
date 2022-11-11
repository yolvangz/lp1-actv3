#include <iostream>
using namespace std;
//int m1[2][2], m2[2][2], aux[2][2], i, j;
int a,b,c,d,i,j,k;
int main () {
	cout << "Por favor, ingrese el numero de filas que poseera la matriz 1: " << endl;
	cin >> a;
	cout << "Por favor, ingrese el numero de columnas que poseera las matriz 1: " << endl;
	cin >> b;
		cout << "Por favor, ingrese el numero de filas que poseera la matriz 2: " << endl;
	cin >> c;
	cout << "Por favor, ingrese el numero de columnas que poseera las matriz 2: " << endl;
	cin >> d;
	
	if (b==c) {
	
	
	int m1[a][b], m2[c][d], aux[a][d];
		
		for (i=0; i<=a-1; i++) {
		for (j=0; j<=b-1; j++){
		cout << "introduzca el valor del digito en la fila " << i+1 << " y columna " << j+1 << " de la matriz 1." << endl;
		cin >> m1[i][j];
		}
	}
	
		for (i=0; i<=c-1; i++) {
		for (j=0; j<=d-1; j++){
		cout << "introduzca el valor del digito en la fila " << i+1 << " y columna " << j+1 << " de la matriz 2." << endl;
		cin >> m2[i][j];
		}
	}
	
	
	for (i=0; i<=a-1; i++) {
		for (j=0; j<=d-1; j++){
			aux[i][j]=0;
			for (k=0; k<=b-1; k++){
				aux[i][j]+=m1[i][k]*m2[k][j];
				
			}
		}
	}
	
				for (i=0; i<=a-1; i++) {
		for (j=0; j<=d-1; j++){
		cout << "El valor del digito en la fila " << i+1 << " y columna " << j+1 << " de la matriz resultante es: " << aux[i][j] << endl;
		}
	}
} else {
	cout << "Es imposible realizar esta operacion matematica, ya que en caso de" <<endl;
	cout << "calcular el producto de matrices de diferentes dimensiones, entonces" <<endl;
	cout << "el numero de columnas de la matriz 1 debe ser igual al numero de" <<endl;
	cout << "filas de la matriz 2."<<endl;
}
}