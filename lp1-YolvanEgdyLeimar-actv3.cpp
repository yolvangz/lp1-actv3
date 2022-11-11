/*
   Diseñe un programa que permita realizar la suma, resta y multiplicacion de matrices siguiendo las siguientes premisas:

   a. Utilizar el método FOR()
   b. El programa no debe cerrar hasta que el usuario lo indique
   c. Mostrar los resultados en forma de tablas
   d. Implementar un menu de selecciones para cada operación

   comando para compilar: g++ <archivo> -o <ejecutable>.exe
   comando para correr: ./<ejecutable>.exe
*/
#include <iostream>
#include "util.h"

using namespace std;

string cabecero = ""; // cabecero guarda un string que se debe imprimir SIEMPRE
/**
 * Clase Matriz.
 * Almacena los elementos y métodos necesarios para crear y manipular matrices
 * @author yolvangz
 * @version 1.0
 * @see namespace "operaciones" para ver las operaciones de matrices
*/
class Matriz {
   private:
      /** @private puntero
       * @typedef puntero de un arreglo de punteros
       * la variable puntero almacena un arreglo de punteros, y cada puntero almacenara otro arreglo de punteros de tipo entero
       * asi es como crea un arreglo bidimensional de punteros, o de otra forma una matriz dinamica
      */
      int** puntero = new int*[0];
      /** @private _filas
       * almacena las cantidad de filas de la matriz
       * es de solo lectura
      */
      int _filas;
      /** @private _columnas
       * almacena las cantidad de columnas de la matriz
       * es de solo lectura
      */
      int _columnas;
   public:
      /** Matriz Constructor
       * @param rows recibe el numero de filas con la que se creara la matriz
       * @param cols recibe el numero de columnas con la que se creara la matriz
      */
      Matriz (int rows, int cols) {
         // Asigna los valores recibidos de filas y columnas al objeto matriz
         _filas = rows;
         _columnas = cols;
         // Crea un puntero de matrices identico al miembro puntero, con el numero de filas indicado
         int** matrizCreada = new int*[filas()];

         for (int i = 0; i < filas(); i++) {
            // Inicializa cada fila iterada como un arreglo de enteros dinamicos
            matrizCreada[i] = new int[columnas()];
            // Si debe ser llenada, procede a recibir cada valor y guardarlo en la matriz
         }
         // Limpia la matriz dinamica antigua para liberar memoria
         delete[] puntero;
         // Reasigna la direccion de memoria a la de la nueva matriz creada
         puntero = matrizCreada;
      }
      /** Matriz Destructor 
       * Limpia la matriz y arreglos dinamicos de la memoria antes de destruir el objeto
      */
      void limpiar() {
         for (int i = 0; i < _filas; i++) {
            delete[] puntero[i];
         }
         delete[] puntero;
      }
      void llenar () {
         string mensaje = "";
         for (int i = 0; i < filas(); i++) {
            for (int j = 0; j < columnas(); j++) {
               mensaje = cabecero + "Ingrese el numero " + to_string(i+1) + "-" + to_string(j+1) + ": ";
               setElemento(i, j, util::inputNumber<int>(mensaje));
               util::borrarPantalla();
            }
         }
      }
      /** impresa()
       * @typedef string
       * Acomoda la matriz en un string en forma de tabla
       * 
       * @return str, es la cadena a regresar
       * divisorHorizontal almacena la linea divisora entre filas
       * elem almacena el elemento llevado a string
       * elemLen guarda la longitud del elemento
       * spc determina la cantidad de espacios a introducir para alinear los elementos
       * elementosMasLargos almacena las longitudes de las columnas mas largas
      */
      string impresa () {
         string str = "", divisorHorizontal = "", elem = "";
         int elemLen, spc;
         int elementosMasLargos[columnas()];
         /**
          * Inicializa los valores en el arreglo
         */ 
         for (int j = 0; j < columnas(); j++) { elementosMasLargos[j] = 0; }

         /**
          * Para cada elemento en cada columna y fila, compara y almacena la longitud mas larga en esa columna
         */
         for (int i = 0; i < filas(); i++) {
            for (int j = 0; j < columnas(); j++) {
               elemLen = 0;
               elemLen = to_string(elemento(i,j)).length();
               if (elemLen > elementosMasLargos[j]) elementosMasLargos[j] = elemLen;
            }
         }
         /**
          * Para cada elemento de la columna, concatena los caracteres para armar la linea divisora
         */
         for (int j = 0; j < columnas(); j++) {
            divisorHorizontal += "+-" + util::multiplyStr("-", elementosMasLargos[j]) + "-";
         }
         divisorHorizontal += "+\n"; // Termina de concatenar la fila divisora
         /**
          * Para cada elemento en cada columna y fila,
          * 1. Inicializa las variables y recupera el valor del elemento y longitud del elemento,
          * 2. Calcula spc como la resta de la longitud del elemento y el elemento mas largo de la columna,
          * 3. Concatena los espacios multiplicados por spc mas el valor del elemento
          * 4. Concatena el caracter divisor ' | ' si aun no es el ultimo elemento
         */ 
         for (int i = 0; i < filas(); i++) {
            str += divisorHorizontal;
            str += "| ";
            for (int j = 0; j < columnas(); j++) {
               spc = elemLen = 0;
               elem = to_string(elemento(i,j));
               elemLen = elem.length();
               spc = elementosMasLargos[j] - elemLen;
               str += util::multiplyStr(" ", spc) + elem;
               if (j+1 < columnas())  str += " | "; 
            }
            str += " |\n"; 
         }
         str += divisorHorizontal; // Cierra la tabla

         return str;
      }
      /*==============
      Getters & Setters
      ================*/
      /** Matriz.elemento()
       * Devuelve el valor del elemento [fila][columna] de la matriz
       * @param fila
       * @param columna
      */
      int elemento (int fila, int columna) {
         return puntero[fila][columna];
      }
      /** Matriz.setElemento()
       * Modifica el valor del elemento [fila][columna] de la matriz
       * @param fila
       * @param columna
       * @param num
      */
      void setElemento (int fila, int columna, int num) {
         puntero[fila][columna] = num;
      }
      /**
       * Encapsula las variables privadas para solo devolver su valor y no poder modificarlo
      */
      int filas () {
         return _filas;
      }
      int columnas () {
         return _columnas;
      }
};

class MyError : public std::exception {
   private:
      string mensaje;
   public:
      MyError(const char* err) : mensaje(err) {}
      string what () {
         return mensaje;
      }     
};

namespace operacion {
   //Se crea la funcion que fue citada en el switch del menu.
   Matriz* sumaDeMatrices (Matriz A, Matriz B);
   Matriz* restaDeMatrices (Matriz A, Matriz B);
   Matriz* multiplicacionDeMatrizYEscalar (Matriz A, int escalar);
   Matriz* multiplicacionDeMatrices (Matriz A, Matriz B);
}

int main () {
   int inputFilas = 0, inputColumnas = 0, numeroEscalar = 0;
   int op;
   string mensaje; // mensaje guarda el cabecero + algun enunciado a imprimir 
   //Bucle principal del programa

   cabecero += "===========================================\n";
   cabecero += "C A L C U L A D O R A  D E  M A T R I C E S\n";
   cabecero += "Coders:\n";
   cabecero += " - Yolvan Zambrano 28.715.823\n";
   cabecero += " - Egdy Arias 28.679.634\n";
   cabecero += " - Leimar Velazco 29.960.898 \n";
   cabecero += "===========================================\n\n";

   do {
      // Inicializa la matriz que guardara el resultado para almacenar
      Matriz* resultado;
      op = 0;
      while (true) {
         util::borrarPantalla();
         mensaje = "MENU DE OPCIONES\n";
         mensaje += "(1) Sumar dos matrices.\n";
         mensaje += "(2) Restar dos matrices.\n";
         mensaje += "(3) Multiplicar una matriz y un escalar.\n";
         mensaje += "(4) Multiplicar dos matrices de diferentes dimensiones.\n";
         mensaje += "(5) Salir del programa.\n";

         mensaje += "Que desea hacer? Ingrese un numero de opcion: ";
         op = util::inputNumber<int>(cabecero + mensaje, 5, 1);

         util::borrarPantalla();
         // Eligio salir del programa
         if (op == 5) {
            if (!util::inputBool("Esta seguro de querer salir? ", 'S', 'N')) continue;
            cout << "Adios.\n";
            system("pause");
            return 0;
         }
         // En cualquier caso hace uso de la matriz A
         inputFilas = util::inputNumber<int>(cabecero + "Ingrese el numero de filas de la matriz A: ", 10, 1);
         inputColumnas = util::inputNumber<int>("Ingrese el numero de columnas de la matriz A: ", 10, 1);
         Matriz A(inputFilas, inputColumnas);
         util::borrarPantalla();
         A.llenar();
         util::borrarPantalla();
         // Si elige 3, define el numero escalar y calcula su resultado
         if (op == 3) {
            numeroEscalar = util::inputNumber<int>(cabecero + "Ingrese el numero escalar: ");
            resultado = operacion::multiplicacionDeMatrizYEscalar(A, numeroEscalar);
            A.limpiar();
            break;
         }
         // Lo contrario, define la matriz B
         inputFilas = util::inputNumber<int>(cabecero + "Ingrese el numero de filas de la matriz B: ", 10, 1);
         inputColumnas = util::inputNumber<int>("Ingrese el numero de columnas de la matriz B: ", 10, 1);
         Matriz B(inputFilas, inputColumnas);
         util::borrarPantalla();
         B.llenar();
         util::borrarPantalla();
         try {
            switch (op) {
            case 1:
               resultado = operacion::sumaDeMatrices(A, B);
               break;
            case 2:
               resultado = operacion::restaDeMatrices(A, B);
               break;
            case 4:
               resultado = operacion::multiplicacionDeMatrices(A, B);
               break;
            }
         } catch (MyError err) {
            A.limpiar();
            B.limpiar();
            cout << cabecero << "ERROR. " << err.what() << "\nAbortar.\n";
            system("pause");
            op = 0;
            continue;
         }
         A.limpiar();
         B.limpiar();
         break;
      }
      cout << "La matriz resultante es: " << endl;
      cout << resultado->impresa() << endl;
      // Destruye la matriz dinamica para liberar espacio
      resultado->limpiar();
      delete resultado;
   } while (util::inputBool("Desea Continuar?", 'S', 'N'));
      
   cout << "Adios.\n";
   system("pause");
   return 0;
}
//Se crea un namespace especifico para clasificar y facilitar el llamado de las siguientes funciones
namespace operacion {
   /** sumaDeMatrices()
    * @param A de tipo matriz
    * @param B de tipo matriz
    * @return el puntero de una matriz con los resultados ya operados.
   */
   Matriz* sumaDeMatrices (Matriz A, Matriz B) {
      if (A.filas() != B.filas() || A.columnas() != B.columnas()) throw MyError("Las matrices NO pueden tener dimensiones diferentes");
      //Se crea la condicion de que ambas matrices deben tener las mismas dimensiones por ley matematica.
      
      Matriz* res = new Matriz (A.filas(), B.columnas()); //Se declara la matriz resultante

      for (int i = 0; i < res->filas(); i++) { //Marca la iteracion por cada fila de las matrices
         for (int j = 0; j < res->columnas(); j++) { //Marca la iteracion por cada columna de las matrices
            res->setElemento(i, j, A.elemento(i, j) + B.elemento(i, j)); /*Suma los elementos que
            se encuentren en la misma coordenada fila-columna en ambas matrices*/
         }
      }
      return res; //Se envian los datos obtenidos de la operacion.
   }
   Matriz* restaDeMatrices (Matriz A, Matriz B) {
      if (A.filas() != B.filas() || A.columnas() != B.columnas()) throw MyError("Las matrices NO pueden tener dimensiones diferentes");
      //Se crea la condicion de que ambas matrices deben tener las mismas dimensiones por ley matematica.

      Matriz* res = new Matriz (A.filas(), B.columnas()); //Se declara la matriz resultante

      for (int i = 0; i < res->filas(); i++) { //Marca la iteracion por cada fila de las matrices
         for (int j = 0; j < res->columnas(); j++) { //Marca la iteracion por cada columna de las matrices
            res->setElemento(i, j, A.elemento(i, j) - B.elemento(i, j));/*Resta los elementos que
            se encuentren en la misma coordenada fila-columna en ambas matrices*/
         }
      }
      return res; //Se envian los datos obtenidos de la operacion.
   }
   Matriz* multiplicacionDeMatrizYEscalar (Matriz A, int escalar) {
      Matriz* res = new Matriz (A.filas(), A.columnas()); //Se declara la matriz resultante

      for (int i = 0; i < res->filas(); i++) { //Marca la iteracion por cada fila de la matriz
         for (int j = 0; j < res->columnas(); j++) { //Marca la iteracion por cada columna de la matriz
            res->setElemento(i, j, A.elemento(i, j) * escalar); /*Multiplica los elementos que
            se encuentren en la matriz con el escalar ingresado*/
         }
      }
      return res; //Se envian los datos obtenidos de la operacion.
   }
   Matriz* multiplicacionDeMatrices (Matriz A, Matriz B) {
      int filasNuevaMatriz, columnasNuevaMatriz, lenComun, suma; //Se declaran dichas variables que son necesarias para
      //La nueva matriz y su calculo, asi como para almacenar los datos de las operaciones.
      if (A.columnas() != B.filas()) throw MyError("La matriz A debe tener el MISMO numero de COLUMNAS que FILAS la matriz B");
      //Se crea la condicion de que el numero filas de la matriz A debe ser igual al numero de columnas de la matriz b
      //Por ley matematica.

      /*Por ley matematica, las dimensiones de la matriz resultante son las siguientes:*/
      filasNuevaMatriz = A.filas(); //Las filas de la matriz A seran las filas de la matriz resultante
      columnasNuevaMatriz = B.columnas(); //Las columnas de la matriz B seran las columnas de la matriz resultante
      lenComun = A.columnas(); //Esta variable sera utilizada para marcar las iteraciones del tercer for que se usara
      Matriz* res = new Matriz (A.filas(), B.columnas()); //Se declara la matriz resultante

      for (int i = 0; i < filasNuevaMatriz; i++) { //Marca la iteracion por cada fila de la matriz resultante
         for (int j = 0; j < columnasNuevaMatriz; j++) { //Marca la iteracion por cada columna de la matriz resultante
            suma = 0; //Se inicializa la variable suma, para que tras el calculo de cada elemento de la matriz resultante,
            //Su valor vuelva a 0.
            for (int k = 0; k < lenComun; k++) { //Se crea un tercer ciclo que permitira la multiplicacion de los
            //elementos de una sola fila, con los elementos de una sola columna
               suma += A.elemento(i, k) * B.elemento(k, j); // Se multiplican los elementos en relacion fila-columna
               //y el resultado se ira sumando dentro de la variable suma 
            } 
            res->setElemento(i, j, suma); //La suma de estas multiplicaciones sera el valor del digito que tiene
            // las coordenadas de las filas y columnas que se multiplicaron
         } 
	   } 
      return res; //Se envian los datos obtenidos de la operacion.
   }
}