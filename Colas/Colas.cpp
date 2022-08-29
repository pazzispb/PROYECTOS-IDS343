// Colas.cpp
// Materia - Estructuras de Datos y Algoritmos I
/*

Asunto: Elaborar un programa en C++ que simule una Cola.

Autor:  Pazzis Paulino 1103790
        Huan Hao Wu 1104326
        Johan Contreras 1106473
        Luis Adames 1106170
        Paola Saldana 1104081
Fecha: 28 - Agosto - 2022

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
void Enqueue(Nodo*& tail, Nodo*& header, int dato); //Agregar un nodo al final de la cola
bool Dequeue(Nodo*& header, Nodo*& tail, int& dato); //Eliminar el primer nodo de la cola
void InsertarPrioridad(Nodo*& header, Nodo*& tail, int dato, int prioridad); //Insertar en una prioridad en especifico. 
															 //Se permiten del 0 al 15. 
														    //De 16 en adelante se coloca al final
void DesplegarCola(Nodo*& header, Nodo*& tail);
int CapturarEntrada(string mensaje);
bool ValidarEntrada(string entrada);

//funcion principal
int main(){
	
	char opcion; //variable para manejar las opciones del menu
	int dato, prioridad; //dato de un nodo
	
	Nodo* header = NULL; //puntero que apunta al inicio de la lista
	Nodo* tail = header; //puntero que apunta al final de la lista
	
	do{
		system("cls");
	    cout<<"|--------------------------------|" << endl;
		cout<<"|             MENU               |" << endl;
		cout<<"|--------------------------------|" << endl;
		cout<<"|     1) Enqueue                 |" << endl;
		cout<<"|     2) Dequeue                 |" << endl;
		cout<<"|     3) Desplegar cola          |" << endl;
		cout<<"|     4) Insertar con prioridad  |" << endl;
		cout<<"|     5) Finalizar el programa   |" << endl;
		cout<<"|--------------------------------|" << endl;
		cout<<"\nElija una opcion: ";
		opcion = _getch(); //leer el caracter
		system("cls");
		switch (opcion) //Se toma el caracter de la primera posicion
		{
			case '1':{
				cout << "ENQUEUE" << endl;
				cout << "-------------------------------"<< endl;
				dato = CapturarEntrada("Ingrese el dato para agregar a la cola: "); //capturo el dato
				Enqueue(tail, header, dato); //se el nodo al final
				break;
			}
			case '2':{
				cout << "DEQUEUE" << endl;
				cout << "-------------------------------"<< endl;
				bool exito = Dequeue(header, tail, dato); //elimino el nodo de la cola del principio y verifico si se borro con exito
				if(exito == true) cout<<"El dato "<<dato<< " fue borrado." << endl;
				break;
			}
			case '3':{
				cout << "DESPLEGAR COLA" << endl;
				cout << "-------------------------------"<< endl;
				DesplegarCola(header, tail); //muestra la cola completa
				break;
			}
			case '4':{
				cout << "INSERTAR CON PRIORIDAD" << endl;				
				cout << "-------------------------------"<< endl;
				dato = CapturarEntrada("Ingrese el dato para agregar a la cola: "); //capturo el dato
				prioridad = CapturarEntrada("Ingrese la prioridad con la que desea ingresar el dato: "); //captura la priorioridad
				InsertarPrioridad(header, tail, dato, prioridad); //se el nodo al final
				break;
			}
			case '5':{
				cout<<"Programa finalizado" << endl;
				break;
			}
			default:{
				cout<<"Opcion no valida" << endl;
				break;
			}
		}
		system("pause");
	}while(opcion != '5');
	return 0;
}

//Definición de métodos

void Enqueue(Nodo*& tail, Nodo*& header, int dato){
	Nodo *nuevoNodo =  new Nodo(); //Crea un nuevo nodo en la memoria
	nuevoNodo->dato = dato; //se le asigna el dato al nodo
	nuevoNodo->siguiente = NULL; //se especifica que el nodo que le sigue será al que apunte la cola
	if(header == NULL){ //si la cola esta vacia
		header = nuevoNodo;
		//el tail y el header apuntan al mismo nodo
	}
	else{ //cuando no esta vacia
		tail->siguiente = nuevoNodo; //Coloco la cola en el nuevo nodo
	}
	tail = nuevoNodo; //la cola sera el nuevo nodo
	cout<<"Nodo agregado." << endl;
}

bool Dequeue(Nodo*& header, Nodo*& tail, int& dato){ //true - si se borro el nodo      false - si estaba vacia y no se pudo realizar la operacion
	Nodo *auxiliar = header; //Nodo auxiliar con el elemento que esta en la cima de la cola
	if(header != NULL) //Si la cola no esta vacia
	{
		if(header == tail) tail = NULL; 
		header = auxiliar->siguiente; //La nueva cima, va a ser el elemento que esta despues del tope
		dato = auxiliar->dato; //dato que estoy borrando
		delete auxiliar; //borro el nodo
		return true; //se hizo el Dequeue
	}
	else{ //si esta vacia
		cout<<"Cola vacia" << endl;
		return false; //no se hizo el dequeue porque la cola estaba vacia
	}
}

void DesplegarCola(Nodo*& header, Nodo*& tail){
	int dato; //dato que voy a desplegar
	do{ //mientras la cola no este vacia
		bool exito = Dequeue(header, tail, dato); //elimino el nodo y verifico si se elimino con exito
		if(exito == true) cout << dato << endl; //imprimo el dato del nodo que se borro
	}while(header != NULL); //mientras la cola no este nula
}

void InsertarPrioridad(Nodo*& header, Nodo*& tail, int dato, int prioridad){

	Nodo *auxiliar = header; //Puntero para recorrer la cola
	Nodo *anterior = auxiliar; //puntero que indica cual es el anterior de auxiliar
	int contador = 0; //cuenta la cantidad de nodos que se han pasado dentro del bucle
	
	//creacion del nodo a insertar
	Nodo *nuevoNodo = new Nodo();
	nuevoNodo->dato = dato;
	if(header==NULL){
		cout<<"La cola esta vacia.\nSe insertara al principio"  << endl;
		Enqueue(tail, header, dato); //se hace un enqueue
		return;
	}
	
	if(prioridad > 16){
		cout<<"La prioridad insertada sobrepasa el limite de prioridades disponibles.\nSe insertara al final" << endl;
		Enqueue(tail, header, dato);
		return;
	}
	
	while(auxiliar != NULL && contador < prioridad){ //mientras no se llegue al final de la cola
		anterior = auxiliar; //anterior se coloca en donde esta auxiliar
		auxiliar = auxiliar->siguiente; //auxiliar se coloca en el nodo que le sigue
		contador++; //se le aumenta uno al contador
	}
	
	if(contador == prioridad) //si las prioridades son iguales
	{
		nuevoNodo->siguiente = auxiliar; //el siguiente del nuevo nodo sera el auxiliar
		if(prioridad == 0){ //si la prioridad es 0
			header = nuevoNodo; //el header sera el nuevo nodo
		}
		else // si la prioridad no es 0, hay anterior
		{
			anterior->siguiente = nuevoNodo;
		}
	}
	else{
		cout<<"La prioridad insertada sobrepasa la cantidad de elementos de la cola.\nSe insertara al final"  << endl;
		Enqueue(tail, header, dato); //se hace un enqueue
	}
}
int CapturarEntrada(string mensaje)			  
{
	string entrada; //variable para almacenar la entrada
	bool correcta; //variable para verificar si la entrada es valida
	do{
	//se repetira hasta que el usuario ingrese una entrada valida 
		cout << mensaje;
		cin >> entrada; //Tome la entrada por pantalla
		correcta = ValidarEntrada(entrada); //Llama a la funcion para validar la entrada
		if(correcta == false) //si no es valida
		{
			cout << "Entrada no valida. Solo se permite un numero entero"<<endl;
			system("pause");
		}
		cout << endl;
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
