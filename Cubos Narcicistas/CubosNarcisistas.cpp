// CubosNarcisistas.cpp
// Materia - Estructuras de Datos y Algoritmos I
/*

Asunto:  Desde el numero 100 al 999 solo existen cuatro cubos narcisistas, el programa debe de identificar cuales son.

Autor:  Pazzis Paulino 1103790
        Huan Hao Wu 1104326
        Johan Contreras 1106473
        Luis Adames 1106170
        Paola Saldana 1104081
Fecha: 15 - Agosto - 2022

*/

#include <iostream>
#include <cmath>  //pow
#include <string> //stoi - to_string
using namespace std;

bool verificarCuboNarcisista(string numero)
{
  return pow((numero[0] - '0'), 3) + pow((numero[1] - '0'), 3) + pow((numero[2] - '0'), 3) == stoi(numero); // formula para hallar cubos narcisistas
}

// Encontrer cubos
int main()
{

  cout << "Listado de numeros narcisistas en el rango de 100 a 999" << endl;
  for (int i = 100; i < 1000; i++) // comprueba que los numeros filtrados sean del 100 al 999
  {
    string numero = to_string(i);        // convertir a string para poder utilizar cada indice
    if (verificarCuboNarcisista(numero)) // utilizamos la funcion verificarCuboNarcisista, y si es verdadero, significa que el numero es un cubo narcisista
    {
      cout << "- " << numero << endl; // imprimir los cubos narcisistas
    }
  }
  return 0;
}
