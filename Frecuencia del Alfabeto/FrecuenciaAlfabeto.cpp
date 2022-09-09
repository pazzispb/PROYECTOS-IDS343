// FrecuenciaAlfabeto.cpp
// Materia - Estructuras de Datos y Algoritmos I
/*

Asunto: Elaborar un programa en C++ que tome los caracteres de un archivo y especifique su frecuencia.

Autor:  Pazzis Paulino 1103790
        Huan Hao Wu 1104326
        Johan Contreras 1106473
        Luis Adames 1106170
        Paola Saldana 1104081
Fecha:  12 - Septiembre - 2022

*/
#include <iostream>
#include <locale.h> //setlocale
#include <cctype> //tolower
#include <windows.h>
#include <fstream>

using namespace std;

//Estructura para almacenar las frecuencias
struct Nodo{
	unsigned char letra;
	int frecuencia;
	Nodo* siguiente;
};

//Prototipo de funciones
bool VerificarCaracter(unsigned char caracter);
void AgregarFrecuencia(unsigned char caracter);
bool VerificarSeparadores(unsigned char caracter);
void LeerArchivo(string nombreArchivo);
char ConvertirCaracter(unsigned char caracter);
void ImprimirFrecuencia();
Nodo* BuscarLetra(unsigned char caracter);
double CalcularPorcentaje(int frecuencia);

//Variables globales
int nCaracteres = 0;
int nPalabras = 0;
Nodo* lista = NULL;

//Funcion principal
int main(){
	//Configuracion del idioma
	setlocale(LC_ALL, "spanish"); //Agregar el idioma español a C+
	SetConsoleCP(1252); //Codificar la consola para que pueda tomar acentos
    SetConsoleOutputCP(1252); //Codificar la consola para que despliegue acentos
	
	string ruta = "Ejemplo.txt";
	
	LeerArchivo(ruta);
	return 0;
}

//Definicion de funciones

void LeerArchivo(string nombreArchivo){	
	unsigned char caracter = ' '; //variable para cada caracter del archivo
	bool caracterValido = false; //bandera para saber si el caracter pertenece al alfabeto español
	bool palabraContada = true; //bandera para saber si ya una palabra fue agregada al conteo
	fstream archivo; //stream
	archivo.open(nombreArchivo, ios::in); //abrimos el stream de lectura
    if(!archivo){ //si el archivo no existe
        cout<<"Lo sentimos, el archivo no existe";
    }
    else{
        while(!archivo.eof()){ //mientras no sea el final del archivo
        	caracter = archivo.get(); //lee un caracter del flujo
            caracter = ConvertirCaracter(caracter); //covierte el caracter a formato estandar (sin acentos y minusculas)
			caracterValido = VerificarCaracter(caracter); //valida que el caracter pertenezca al alfabeto español
			if(palabraContada == false){ //si la palabra no ha sido contada
				if(VerificarSeparadores(caracter)){ //si el caracter es un separador
					nPalabras++; //suma al contador de palabras
					palabraContada = true;	//di que la palabra ya se conto
				}	
			}
			if(caracterValido){ //si el caracter pertenece al alfabeto espanol
				AgregarFrecuencia(caracter); //Suma a la frecuencia de la letra
				nCaracteres++; //suma a la cantidad de caracteres del total
				palabraContada = false; //di que la palabra no ha sido contada
			}
        }
        archivo.close(); //cierra el flujo
    }
	ImprimirFrecuencia();
}
/*
	Alfabeto
	a 97	i 105	q 113	y 121    
	b 98	j 106	r 114	z 122   
	c 99	k 107	s 115	á 225
	d 100	l 108	t 116	é 233
	e 101	m 109	u 117	í 277
	f 102	n 110	v 118	ó 243
	g 103	o 111	w 119	ú 250
	h 104	p 112	x 120	ñ 241
*/

bool VerificarCaracter(unsigned char caracter){
	if(isalpha(caracter) == false) return false; //si el caracter no es alfabetico returna falso
	
	bool caracterValido = false; //bandera para verificar si el caracter forma parte del alfabeto espanol
		
	if(caracter > 96 && caracter < 123) caracterValido = true; //si va de la a (97) - z (122)
	else if (int(caracter) == 241) caracterValido = true; //si es una ñ (241)
	
	return caracterValido;
}

char ConvertirCaracter(unsigned char caracter){
	caracter = tolower(caracter); //convierte a minisculas el caracter
	
	if (caracter == 225) return 'a'; //si es á, retorna a
	else if (caracter == 233) return 'e'; //si es é, retorna e
	else if (caracter == 277) return 'i'; //si es í, retorna i
	else if (caracter == 243) return 'o'; //si es ó, retorna o
	else if (caracter == 250) return 'u'; //si es ú, retorna u
	else return caracter; //de lo contrario retorna el mismo caracter
}

void AgregarFrecuencia(unsigned char caracter){
	Nodo* auxiliar = BuscarLetra(caracter); //retorna la direccion en memoria del nodo con la letra
	
	if(auxiliar == NULL){ //si no hay un nodo con esa letra
		
		Nodo *nuevoNodo = new Nodo(); //Crea un nuevo nodo en la memoria
    	nuevoNodo->letra = caracter; //se le asigna el la letra al nodo
		nuevoNodo->frecuencia = 1; //le asigna la frecuencia
		auxiliar = lista; //Nodo auxiliar con el elemento que esta en la cabeza de la Lista
		Nodo *anterior = NULL; //puntero que indica cual es el anterior de auxiliar

	    while (auxiliar != NULL && auxiliar->letra < caracter) // Se busca el lugar correspondiente del elemento
	    {
	        anterior = auxiliar;  //anterior se coloca en donde esta auxiliar
	        auxiliar = auxiliar->siguiente; //auxiliar se coloca en el nodo que le sigue
	    }
    	nuevoNodo->siguiente = auxiliar; //indicamos que el siguiente de nuevoNodo sera auxiliar
		if(anterior == NULL){ //en el caso que no exista un elemento anterior
			lista = nuevoNodo; //se le indica que nuevoNodo sera la cabecera de la list
		}
		else{ //de lo contrario
			anterior->siguiente = nuevoNodo; //indicamos que nuevoNodo tiene un elemento que le antecede
		}
	}
	else{
		auxiliar->frecuencia++; //se le suma 1 a su frecuencia
	}
}

Nodo* BuscarLetra(unsigned char caracter){ //retorna la direccion en memoria del nodo con la letra
	Nodo* auxiliar = lista;
	while(auxiliar != NULL && auxiliar->letra != caracter){ //mientras auxiliar no sea nulo ni tampoco se haya llegado al caracter deseado
		auxiliar = auxiliar->siguiente;
	}
	return auxiliar;
	//retornara NULL si no hay un nodo con esa posicion
}

void ImprimirFrecuencia(){
	Nodo* auxiliar = lista; 
	//DAR EL FORMATO
	double frecuencia = 0;
	cout<<"Cantidad de palabras: "<<nPalabras <<endl;
	cout<<"Cantidad de caracteres del alfabeto: "<<nCaracteres <<endl;
	while(auxiliar != NULL){
		cout<<auxiliar->letra;
		cout<<" ";
		cout<<auxiliar->frecuencia;
		cout<<" ";
		cout<<CalcularPorcentaje(auxiliar->frecuencia)<<"%"<< endl;
		frecuencia += CalcularPorcentaje(auxiliar->frecuencia);
		auxiliar = auxiliar->siguiente;
	}
}

bool VerificarSeparadores(unsigned char caracter){
	if(caracter == ' ' || caracter == ',' || caracter == '.' || 
		caracter == '-' || caracter == '/' || caracter == ':' || caracter == 10){
			return true;
	}
	else{
		return false;
	}
		
}
double CalcularPorcentaje(int frecuencia){ //calcula el porcentaje de frecuencia de cada letra
	return frecuencia*100.0/nCaracteres;
}

