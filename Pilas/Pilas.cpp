// Pilas.cpp
// Materia - Estructuras de Datos y Algoritmos I
/*

Asunto: Elaborar un programa en C++ que simule una Pila.

Autor:  Pazzis Paulino 1103790
        Huan Hao Wu 1104326
        Johan Contreras 1106473
        Luis Adames 1106170
        Paola Saldana 1104081
Fecha: 22 - Agosto - 2022

*/

#include <iostream>
#include <cctype> //isdigit
#include <string> //stoi    - disponible para c++11
#include <conio.h> //_getch

using namespace std;

//estructura
struct Nodo{
	int dato;
	Nodo *siguiente;
};

//Prototipo de metodos
void Push(Nodo *&pila, int dato);
bool Pop(Nodo *&pila, int& dato);
void DesplegarPila(Nodo*&);
int CapturarEntrada();
bool ValidarEntrada(string entrada);

//funcion principal
int main(){
	
	char opcion; //variable para manejar las opciones del menu
	int dato; //dato de un nodo
	
	Nodo* pila = NULL; //puntero de la pila
	
	do{
		system("cls");
	    cout<<"|-----------------------------|" << endl;
		cout<<"|            MENU             |" << endl;
		cout<<"|-----------------------------|" << endl;
		cout<<"|     1) Push                 |" << endl;
		cout<<"|     2) Pop                  |" << endl;
		cout<<"|     3) Desplegar pila       |" <<endl;
		cout<<"|     4) Salir del programa   |" <<endl;
		cout<<"|-----------------------------|" <<endl;
		cout<<"\nElija una opcion: ";
		opcion = _getch(); //leer el caracter
		system("cls");
		switch (opcion) //Se toma el caracter de la primera posicion
		{
			case '1':{
				dato = CapturarEntrada(); //capturo el dato
				Push(pila, dato); //se agrega a la pila
				break;
			}
			case '2':{
				bool llena = Pop(pila, dato); //elimino el nodo de la pila y verifico si se borro con exito
				if(llena == true) cout<<"El dato "<<dato<< " fue borrado." << endl;
				break;
			}
			case '3':{
				DesplegarPila(pila); //muestra la pila completa
				break;
			}
			case '4':{
				cout<<"Programa finalizado" << endl;
				break;
			}
			default:{
				cout<<"Opcion no valida" << endl;
				break;
			}
		}
		system("pause");
	}while(opcion != '4');
	return 0;
}

//Definición de métodos

void Push(Nodo*& pila, int dato){
	Nodo *nuevoNodo =  new Nodo(); //Crea un nuevo nodo en la memoria
	nuevoNodo->dato = dato; //se le asigna el dato al nodo
	nuevoNodo->siguiente = pila; //se especifica que el nodo que le sigue será al que apunte la pila
	pila = nuevoNodo; //el puntero pila apunta al nodo creado
	cout<<"Nodo agregado." << endl;
}

bool Pop(Nodo*& pila, int& dato){ //true - si se borro el nodo      false - si estaba vacia y no se pudo realizar la operacion
	Nodo *auxiliar = pila; //Nodo auxiliar con el elemento que esta en la cima de la pila
	if(auxiliar!=NULL) //Si la pila no esta vacia
	{ 
		pila = auxiliar->siguiente; //La nueva cima, va a ser el elemento que esta despues del tope
		dato = auxiliar->dato; //dato que estoy borrando
		delete auxiliar; //borro el nodo
		return true; //se hizo el pop
	}
	else{ //si esta vacia
		cout<<"Empty Stack" << endl;
		return false; //no se hizo el pop porque la pila estaba vacia
	}
}

void DesplegarPila(Nodo*& pila){
	int dato; //dato que voy a desplegar
	do{ //mientras la pila no este vacia
		bool llena = Pop(pila, dato); //elimino el nodo y verifico si se elimino con exito
		if(llena == true) cout << dato << endl; //imprimo el dato del nodo que se borro
	}while(pila != NULL); //mientras la pila no este nula
}

int CapturarEntrada()
{
	string entrada; //variable para almacenar la entrada
	bool correcta; //variable para verificar si la entrada es valida
	do{
	//se repetira hasta que el usuario ingrese una entrada valida 
		cout<<"Ingrese el numero para agregar a la pila: ";
		cin >> entrada; //Tome la entrada por pantalla
		correcta = ValidarEntrada(entrada); //Llama a la funcion para validar la entrada
		if(correcta == false) //si no es valida
		{
			cout << "Entrada no valida. Solo se permite un numero entero"<<endl;
			system("pause");
			system("cls");	
		}
	} while (correcta == false); //repetir mientras que la entrada no sea valida
	return stoi(entrada); //retorna la entrada convertida en entero
	return 0;
}

bool ValidarEntrada(string entrada){ //true - es valida       false - no es valida 
	int contadorSigno = 0; //variable para determinar cuantos '-' hay en la entrada
	for(int i = 0; i < entrada.length(); i++) //recorre todas las posiciones del string de entrada
	{
		if(entrada[i] == '-') //si el caracter de la posicion es '-'
		{
			if(entrada.length() > 1) //si la entrada tiene mas de un caracter
			{
				contadorSigno++; //agrega al contador
				if(contadorSigno > 1) return false; //si la entrada tiene mas de un signo '-'
				if(i != 0) return false; //si el signo '-' no esta en la primera posicion
			}
			else //si tiene un caracter o menos de un caracter
			{
				return false;
			}
		}
		if(isdigit(entrada[i])==false && entrada[i] != '-') return false; //si no es un digito ni es el signo de '-'
	}
	return true;
		
}
