// LinkedList.cpp
// Materia - Estructuras de Datos y Algoritmos I
/*

Asunto: Elaborar un programa en C++ que simule una Lista enlazada.

Autor:  Pazzis Paulino 1103790
        Huan Hao Wu 1104326
        Johan Contreras 1106473
        Luis Adames 1106170
        Paola Saldana 1104081
Fecha: 28 - Agosto - 2022

*/
#include <iostream>
#include <windows.h>
#include <cctype> //isdigit
#include <string> //stoi    - disponible para c++11
#include <conio.h> //_getch

using namespace std;

//Estructura
struct Nodo{
    int dato;
	Nodo *next;
};

//Prototipo de metodos

void Insertar(Nodo *&list, int dato); //insertar un nodo en la lista de manera ascendente
void Buscar(Nodo *list, int dato); //Verificar si existe un dato dentro de la lista
void Eliminar(Nodo *&list, int dato); //elimina un dato dentro de la lista
void Desplegar(Nodo *&list); //despliega la lista sin eliminar sus nodos
int CapturarEntrada(string mensaje);
bool ValidarEntrada(string entrada);

//Metodos para el diseño
void DibujarCuadro(int x1,int y1,int x2,int y2);
void Gotoxy(int x,int y);

//Funcion Principal

int main(){

    char opcion; //variable para manejar las opciones del menu
	int dato; //dato de un nodo
	
	Nodo* list = NULL; //puntero que apunta al inicio de la lista
		
	do{
	    DibujarCuadro(0,0,78,24); //SE DIBUJA EL CUADRO PRINCIPAL
	    DibujarCuadro(1,1,77,3); //SE DIBUJA EL CUADRO DEL TITULO
	    Gotoxy(28,2); cout << "MENU: LISTAS ENLAZADAS";
	    Gotoxy (3,5);
		cout<<"1) Insertar nodo" << endl;
		Gotoxy (3,6);
		cout<<"2) Eliminar nodo" << endl;
		Gotoxy(3,7);
		cout<<"3) Buscar dato" << endl;
		Gotoxy(3,8);
		cout<<"4) Desplegar lista" << endl;
		Gotoxy(3,9);
		cout<<"5) Finalizar el programa" << endl;
		Gotoxy (3,12);
		cout<<"Elija una opcion: ";
		opcion = _getch(); //leer el caracter
		system("cls");
		switch (opcion) //Se toma el caracter de la primera posicion
		{
			case '1':{
				DibujarCuadro(1,1,77,3); //SE DIBUJA EL CUADRO DEL TITULO
				Gotoxy(28,2);
				cout << "INSERTAR NODO" << endl;
				Gotoxy(5,5);
	            dato = CapturarEntrada("Ingrese el dato: "); //capturo el dato
				Gotoxy(5,7);
				Insertar(list,dato); //se el nodo al final
                cout<<"El dato " <<dato<< " fue insertado con exito\n";
				break;
			}
			case '2':{
				DibujarCuadro(1,1,77,3); //SE DIBUJA EL CUADRO DEL TITULO
				Gotoxy(28,2);
				cout << "ELIMINAR NODO" << endl; 
				Gotoxy(5,5);
				if(list!=NULL){ //verifica que la lista no este vacia
	        		dato = CapturarEntrada("Ingrese el dato a eliminar: ");  
					Gotoxy(5,7);               
	                Eliminar(list,dato); // se elimina el dato 	
				}
				else{
					cout<<"Lista vacia";
				} 
				break;
			}
			case '3':{
				DibujarCuadro(1,1,77,3); //SE DIBUJA EL CUADRO DEL TITULO
				Gotoxy(28,2);
				cout << "BUSCAR ELEMENTO" << endl;  
				Gotoxy(5,5);             
				if(list!=NULL){ //verifica que la lista no este vacia
	        		dato = CapturarEntrada("Ingrese el dato a buscar: ");
	        		Gotoxy(5,7);   
	                Buscar(list,dato); //Busca el elemento en la lista;	
				}
				else{
					cout<<"Lista vacia";
				}
				break;
			}
			case '4':{
				DibujarCuadro(1,1,77,3); //SE DIBUJA EL CUADRO DEL TITULO
				Gotoxy(28,2);
				cout << "DESPLEGAR LISTA" << endl;
				Gotoxy(5,5);
				Desplegar(list); //Se despliega los datos de la lista
				break;
			}
			case '5':{
				Gotoxy(5,5);
				cout<<"Programa finalizado" << endl;
				break;
			}
			default:{
				Gotoxy(5,7);
				cout<<"Opcion no valida" << endl;
				break;
			}
		}
        Gotoxy(5,9);
		system("pause");
	}while(opcion != '5');
	return 0;
}

void Gotoxy(int x,int y){  
	HANDLE hcon;  
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
	COORD dwPos;  
	dwPos.X = x;  
	dwPos.Y= y;  
	SetConsoleCursorPosition(hcon,dwPos);  
}
void DibujarCuadro(int x1,int y1,int x2,int y2){
	int i;
	system("mode con: cols=80 lines=25"); //SE DEFINE LAS DIMENSIONES DE LA VENTANA DEL PROGRAMA A 80 COLUMNAS Y 25 FILAS
	system("COLOR F1"); //SE DA UN COLOR DE FONDO (F=GRIS) Y COLOR (1 = AZUL) A LAS LETRAS
	    
    for (i=x1;i<x2;i++){
		Gotoxy(i,y1); cout << "\304"; //linea horizontal superior
		Gotoxy(i,y2); cout << "\304"; //linea horizontal inferior
    }

    for (i=y1;i<y2;i++){
		Gotoxy(x1,i); cout <<"\263"; //linea vertical izquierda
		Gotoxy(x2,i); cout <<"\263"; //linea vertical derecha
	}
	
	//esquinas del cuadro
    Gotoxy(x1,y1); cout<< "\332"; 
    Gotoxy(x1,y2); cout<< "\300";
    Gotoxy(x2,y1); cout<< "\277";
    Gotoxy(x2,y2); cout<< "\331";
}
void Insertar(Nodo *&list, int dato){

    Nodo *nuevoNodo = new Nodo(); //Crea un nuevo nodo en la memoria
    nuevoNodo->dato = dato; //se le asigna el dato al nodo

	Nodo *auxiliar = list; //Nodo auxiliar con el elemento que esta en la cabeza de la Lista

	Nodo *anterior = NULL; //puntero que indica cual es el anterior de auxiliar

    while (auxiliar != NULL && auxiliar->dato < dato) // Se busca el lugar correspondiente del elemento
    {
        anterior = auxiliar;  //anterior se coloca en donde esta auxiliar
        auxiliar = auxiliar->next; //auxiliar se coloca en el nodo que le sigue
    }
    nuevoNodo->next = auxiliar; //indicamos que el siguiente de nuevoNodo sera auxiliar
	if(anterior == NULL){ //en el caso que no exista un elemento anterior
		list = nuevoNodo; //se le indica que nuevoNodo sera la cabecera de la list
	}
	else{ //de lo contrario
		anterior->next = nuevoNodo; //indicamos que nuevoNodo tiene un elemento que le antecede
	} 
}

void Buscar(Nodo *list, int dato){
    
	bool encontrado = false; //variable para verificar si se encontro el dato
	   
    Nodo *auxiliar = new Nodo(); //nodo que utilizaremos para recorrer la lista
    auxiliar = list; //tendra asignada la cabecera de la lista

    while(auxiliar != NULL && auxiliar->dato <= dato){ // Verificamos si el valor se encuentra en la lista
        
        if(auxiliar->dato == dato){ // Si se encuentra el dato encontrado sera true.
            encontrado = true;             
        }
        auxiliar = auxiliar->next; // movemos a auxiliar hacia su siguiente.
    }
    if(encontrado == true) cout<<"El dato "<<dato<< " SI se encuentra en la lista\n"; 
    else cout<<"El dato "<<dato<<" NO se encuentra en la lista\n";
   
}
void Eliminar(Nodo *&list, int dato){

    Nodo *auxiliar = list; //auxiliar sera igual a la cabecera
    Nodo *anterior = NULL;

    while(auxiliar != NULL && auxiliar->dato != dato){ //verificamos si se encuentra el dato
        anterior = auxiliar;  //anterior se coloca en donde esta auxiliar
        auxiliar = auxiliar->next; // movemos a auxiliar hacia su siguiente.
    }
    if(anterior == NULL){ //si el elemento a eliminar se encuentra al inicio de la lista
        list = list->next; // la cabecera de la lista va a ser el siguiente del elemento a eliminar  
    }
    else{
        anterior->next = auxiliar->next; // Se le asigna como anterior al nodo que le sigue al elemento que se borro      
    }
    
    if(auxiliar == NULL){ // Si auxiliar llega a NULL entonces no se encuentra el elemento.
        cout<<"Elemento "<<dato<< " no encontrado en la lista.\n";
        return;
    }
    
    delete auxiliar; // se elimina auxiliar
    cout<< "El nodo con el dato "<<dato<< " fue eliminado con exito.\n";
}

void Desplegar(Nodo *&list){
    Nodo *auxiliar; //puntero para recorrer la lista
    auxiliar = list; //empieza en la cabecera de la lista

    if(list != NULL){ // Comprobamos si la lista esta vacia
        while(auxiliar != NULL){ // mientras no se llegue al final de la lista.
            cout<< auxiliar->dato;
            if(auxiliar->next != NULL) cout<< " --> ";
			else cout << "."; //si auxiliar ya no apunta a un siguiente/siguiente = NULL
            auxiliar = auxiliar->next; // auxiliar sera el elemento siguiente en cada ciclo.
        }
    }
    else{
        cout<< "La lista se encuentra vacia";
    }
}

int CapturarEntrada(string mensaje)			  
{
	string entrada; //variable para almacenar la entrada
	bool correcta; //variable para verificar si la entrada es valida
	do{
	//se repetira hasta que el usuario ingrese una entrada valida 
		Gotoxy(5,5);
		cout << mensaje;
		cin >> entrada; //Tome la entrada por pantalla
		correcta = ValidarEntrada(entrada); //Llama a la funcion para validar la entrada
		if(correcta == false) //si no es valida
		{
			Gotoxy(5,6);
			cout << "Entrada no valida. Solo se permite un numero entero";
			Gotoxy(5,7);
			system("pause");
			Gotoxy(5,5);
			for(int i = 0; i < 5; i++) cout << "                                        ";
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
