// TorresDeHanoi.cpp
// Materia - Estructuras de Datos y Algoritmos I
/*

Asunto: Realizar un programa en C++ que simule las torres de hanoi

Autor:  Pazzis Paulino 1103790
		Huan Hao Wu 1104326
		Johan Contreras 1106473
		Luis Adames 1106170
		Paola Saldana 1104081
		
Fecha:  03 - octubre - 2022

*/

/* Descripcion del algoritmo: 

Caso base: si en una torre solo se tiene un disco, entonces se realizara un unico movimiento de la torre origen
a la torre destino.

La siguiente formula para la cantidad de movimientos esta dada por: 2^n - 1, siendo n la cantidad de discos que elija
el usuario para jugar.

*/

#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

unsigned long long contador = 0; //Contador para la cantidad de pasos del algoritmo

//Prototipo de metodos
void MoverDisco(int disco, char torreA, char torreB, char torreC); //torreA -> origen, torreB -> auxiliar, torreC -> destino
void EntradaDisco(int& disco); //valida que el usuario introduzca 3 discos o mas
void ImprimirTitulo(); //imprime el titulo del programa
void ImprimirMovimiento(char torreOrigen, char torreDestino); //Impresion del movimiento
//Función principal
int main()
{
	char torreA = 'A', torreB = 'B', torreC = 'C'; //torres definidas
	int disco = 0;
	
	ImprimirTitulo();
	EntradaDisco(disco); //Pedirle al usuario que ingrese la cantidad de discos
	MoverDisco(disco, torreA, torreB, torreC); //se comienza el algoritmo
    
	return 0;
}

void ImprimirTitulo(){
	system("cls");
	cout << "+----------------------------------------------+" << endl;
	cout << "|       T O R R E S     D E     H A N O I      |" << endl;
	cout << "+----------------------------------------------+" << endl;
	cout << "\n";
}

void EntradaDisco(int& disco){
	do{
		cout<< "Con cuantos discos desea jugar? ";
		cin>> disco;
		if(disco < 3){ //si el numero ingresado es menor a 3
			cout << "Debe ingresar al menos 3 discos" << endl << endl;
		}	
	} while(disco < 3); //repetir mientras el numero de discos ingresados es menor a 3
	ImprimirTitulo();
}

void MoverDisco(int disco, char torreA, char torreB, char torreC){
	
	if(disco == 1){ //si se solo se esta jugando con un disco, se movera directamente de la torre A (origen) a la torre C (destino)
		contador++; //se suma el paso
		ImprimirMovimiento(torreA, torreC);
	}
	else{ // si tenemos mas de un disco
		MoverDisco(disco - 1, torreA, torreC, torreB); 
		// moveremos los primeros n-1 discos (todos menos el ultimo) de la torre A (origen) a la torre B (auxiliar)
		contador++; //se suma el paso
		ImprimirMovimiento(torreA, torreC); //moveremos el unico disco de la torre A (origen) a la torre C (destino) 
		MoverDisco(disco - 1, torreB, torreA, torreC); // Los discos contenidos en la torre B (auxiliar) se mueven a la torre C (destino)
	}
}
//torre A -> rojo 4    torre B -> azul 9      torre C -> 6 amarilla
void ImprimirMovimiento(char torreOrigen, char torreDestino){
	int colorOrigen = 0, colorDestino = 0; //colores para las torres
	switch(torreOrigen){ //cambia el color de la torre de origen
		case 'A': colorOrigen = 4; break;
		case 'B': colorOrigen = 9; break;
		case 'C': colorOrigen = 6; break;
	}
	switch(torreDestino){ //cambia el color de la torre destino
		case 'A': colorDestino = 4; break;
		case 'B': colorDestino = 9; break;
		case 'C': colorDestino = 6; break;
	}
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); //toma control de la consola
	SetConsoleTextAttribute(h, 7); //Blanco
	cout<< contador <<". Mover disco de la torre ";
	SetConsoleTextAttribute(h, colorOrigen); //cambiamos el color de salida de la torre de origen
	cout << torreOrigen;
	SetConsoleTextAttribute(h, 7); //Blanco
	cout << " hacia la torre ";
	SetConsoleTextAttribute(h, colorDestino); //cambiamos el color de salida de la torre de destino
	cout << torreDestino << endl << endl;
	SetConsoleTextAttribute(h, 7); //Blanco
}
