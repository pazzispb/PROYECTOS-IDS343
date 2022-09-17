// ArbolBinario.cpp
// Materia - Estructuras de Datos y Algoritmos I
/*

Asunto:

Autor:  Pazzis Paulino 1103790
		Huan Hao Wu 1104326
		Johan Contreras 1106473
		Luis Adames 1106170
		Paola Saldana 1104081
Fecha:  19 - Septiembre - 2022

*/

#include <iostream>
#include <string>

using namespace std;

//Estructura del Nodo
struct Nodo {
	int dato;
	Nodo* derecho;
	Nodo* izquierdo;
	Nodo* padre;
};

//Prototipo de funciones
void Menu();
Nodo* CrearNodo(int n, Nodo* padre);
void InsertarNodo(Nodo*& arbol, int n, Nodo* padre);
void MostrarArbol(Nodo* arbol, int contador);
void BuscarEliminar(Nodo* arbol, int n); //busca el nodo a eliminar
void EliminarNodo(Nodo* NodoEliminar);
Nodo* Minimo(Nodo* arbol);
void Reemplazar(Nodo* arbol, Nodo* nuevoNodo);
void DestruirNodo(Nodo* NodoDestruir);
bool BuscarValor(Nodo* arbol, int buscar);
void PreOrden(Nodo* arbol);
void InOrden(Nodo* arbol);
void PostOrden(Nodo* arbol);
int CapturarEntrada(string mensaje);
bool ValidarEntrada(string entrada);
void EmptyTree();
void BannerEntrada();
void BannerFin();

Nodo* arbol = NULL; //raiz del arbol


//Función principal
int main()
{
	BannerEntrada();
	Menu();
	BannerFin;
    return 0;
}

void Menu() {
	int decision, entrada;
	int contador = 0; //para mostrar arbol de manera ordenada

	do {
		system("cls"); //para limpiar la pantalla
		system("Color 07");
		cout << "  +----------------------------------------------+" << endl;
		cout << "  |                   M E N U                    |" << endl;
		cout << "  +----------------------------------------------+" << endl;
		cout << "  | [1] - Insertar nuevo Nodo                    |" << endl;
		cout << "  | [2] - Eliminar Nodo                          |" << endl;
		cout << "  | [3] - Mostrar arbol                          |" << endl;
		cout << "  | [4] - Buscar valor                           |" << endl;
		cout << "  | [5] - Recorrer Pre-Order                     |" << endl;
		cout << "  | [6] - Recorrer In-Order                      |" << endl;
		cout << "  | [7] - Recorrer Post-Order                    |" << endl;
		cout << "  | [8] - Salir del programa                     |" << endl;
		cout << "  +----------------------------------------------+" << endl;
		cout << endl;
		cout << "Elija una opcion " << endl;
		cin >> decision;
		switch (decision) {
			case 1: {  //Insertar
				system("cls");
				cout << "  +----------------------------------------------+" << endl;
				cout << "  |               I N S E R T A R                |" << endl;
				cout << "  +----------------------------------------------+" << endl;

				cout << "\n";
				entrada = CapturarEntrada("Digite el valor del nuevo Nodo:  ");
				InsertarNodo(arbol, entrada, NULL);
				cout << "\n";
				system("pause");
				break;
			}
			case 2: { //Eliminar 
				system("cls");
				cout << "  +----------------------------------------------+" << endl;
				cout << "  |                E L I M I N A R               |" << endl;
				cout << "  +----------------------------------------------+" << endl;
			
				cout << "\n";
				/*cout << "Digite el valor que desea eliminar" << endl;
				cin >> entrada;*/
				
				if (arbol == NULL){
					EmptyTree();
				}else {
					entrada = CapturarEntrada("Digite el valor que desea eliminar:  ");
					if(BuscarValor(arbol, entrada) == false) {
						cout<<"El valor a eliminar no se encuentra en el arbol binario" << endl;
						system("pause");	
						return;
					}
					BuscarEliminar(arbol, entrada);
				}
				cout << "\n";
				system("pause");
				break;
			}
			case 3: { //Mostrar arbol completo
				system("cls");
				cout << "  +----------------------------------------------------------+" << endl;
				cout << "  |               M O S T R A R    A R B O L                 |" << endl;
				cout << "  +----------------------------------------------------------+" << endl;
			
				cout << "\n";

				if (arbol == NULL){
					EmptyTree();
				} else {
					cout << "		Mostrando el arbol completo" << endl;
					MostrarArbol(arbol, contador);
				}
				cout << "\n";
				system("pause");
				break;
			}
			case 4: { //Buscar
				system("cls");
				cout << "  +----------------------------------------------+" << endl;
				cout << "  |                  B U S C A R                 |" << endl;
				cout << "  +----------------------------------------------+" << endl;
			
				cout << "\n";
				/*cout << "Digite el valor que desea buscar" << endl;
				cin >> entrada;*/

				if (arbol == NULL){
					EmptyTree();
				}else {
					entrada = CapturarEntrada("Digite el valor que desea buscar:  ");

					bool valorEncontrado = BuscarValor(arbol, entrada);

					if (valorEncontrado == true) {
						cout << "El elemento " << entrada << " ha sido encontrado exitosamente" << endl;
					}
					else {
						cout << "El elemento " << entrada << " NO ENCONTRADO" << endl;
					}
				}
			
				cout << "\n";
				system("pause");
				break;
			}
			case 5: { // Recorrer Pre-Orden
				system("cls");
				cout << "  +---------------------------------------------------------+" << endl;
				cout << "  |        R E C O R R I D O       P R E - O R D E N        |" << endl;
				cout << "  +---------------------------------------------------------+" << endl;

				if (arbol == NULL){
					EmptyTree();
				}else {
					PreOrden(arbol);
				}
				cout << "\n\n";
				system("pause");
				break;
			}
			case 6: { // Recorrer In-Orden
				system("cls");
				cout << "  +---------------------------------------------------------+" << endl;
				cout << "  |         R E C O R R I D O       I N - O R D E N         |" << endl;
				cout << "  +---------------------------------------------------------+" << endl;

				if (arbol == NULL){
					EmptyTree();
				}else {
					InOrden(arbol);
				}
			
				cout << "\n\n";
				system("pause");
				break;
			}
			case 7: { // Recorrer Post-Orden
				system("cls");
				cout << "  +---------------------------------------------------------+" << endl;
				cout << "  |        R E C O R R I D O      P O S T - O R D E N       |" << endl;
				cout << "  +---------------------------------------------------------+" << endl;
				if (arbol == NULL){
					EmptyTree();
				}
				else {
					PostOrden(arbol);	
				}
				cout << "\n\n";
				system("pause");
				break;
			}
		}

	} while (decision != 8);
};


//Crear Nodo
Nodo* CrearNodo(int n, Nodo* padre) {
	Nodo* nuevo_Nodo = new Nodo(); //Reserva del espacio de memoria

	//voy asignandole valores a los componentes del Nodo
	nuevo_Nodo->dato = n;
	nuevo_Nodo->derecho = NULL;
	nuevo_Nodo->izquierdo = NULL;
	nuevo_Nodo->padre = padre;

	return nuevo_Nodo; //retorna la direccion en memoria del nodo
}

//Insertar Nodos
void InsertarNodo(Nodo*& arbol, int n, Nodo* padre) {
	if (arbol == NULL) { //Si el árbol esta vacio
		Nodo* nuevo_Nodo = CrearNodo(n, padre); //Se recibe la direccion en memoria del nodo creado por la funcion
		arbol = nuevo_Nodo; //nuevo nodo se vuelve la raíz del árbol
	}
	else { //Si tiene elementos
		int valorRaiz = arbol->dato; //Obtener el valor de la raíz
		
		//Validar si se coloca a la derecho o la izquierdo
		if (n <= valorRaiz) { //menor o igual a la raiz se va a colocar en el subarbol izquierdo
			InsertarNodo(arbol->izquierdo, n, arbol);
		}
		else { //mayor a la raíz -> derecho
			InsertarNodo(arbol->derecho, n, arbol);
		}
	}
}

//Función para mostrar el árbol

void MostrarArbol(Nodo* arbol, int contador) { //le pasamos la raiz
	if (arbol == NULL){ //Verificamos si el árbol esta vacio o no
		return;
	}
	else {
		MostrarArbol(arbol->derecho, contador + 1); //Mostramos toda la rama derecha de la raíz 
		for (int i = 0; i < contador; i++){ //Separa cada nodo
			cout << "   ";
		}
		cout << arbol->dato << endl; //esto muestra los nodos
		if(arbol->izquierdo) MostrarArbol(arbol->izquierdo, contador + 1); //Mostramos toda la rama izquierda de la raíz
	}
}

//Buscar un elemento
bool BuscarValor(Nodo* arbol, int buscar) {
	if (arbol == NULL){ //Si el arbol esta vacio
		return false;
	}
	else if (arbol -> dato == buscar) { //cuando se encuentre el valor en el arbol
		return true;
	}
	else if (buscar < arbol->dato) { //Si el elemento a buscar es menor que el nodo, busca por la parte izquierda
		return BuscarValor(arbol->izquierdo, buscar); //recursividad
	}
	else { //Si el elemento a buscar es mayor que el nodo, busca por la parte derecha
		return BuscarValor(arbol->derecho, buscar); //recursividad
	}
}

//Pre-orden -> raíz, izquierdo y después derecho
void PreOrden(Nodo* arbol) {
	if (arbol == NULL){ //Arbol vacio
		return;
	}
	else{ //Tiene elementos
		cout << " " << arbol->dato << " -> "; //Imprimir valor raiz 
		PreOrden(arbol -> izquierdo); // Recorrer todo el sub-arbol izquierdo
		PreOrden(arbol -> derecho); // Recorrer todo el sub-arbol derecho
	}
}


//In-orden -> izquierdo, raíz y después derecho
void InOrden(Nodo* arbol) {
	if (arbol == NULL){ //Arbol vacio
		return; 
	}
	else { //tiene elementos 
		InOrden(arbol->izquierdo); // Recorrer todo el sub-arbol izquierdo
		cout << arbol->dato << " -> "; //Imprimir valor de la raiz
		InOrden(arbol->derecho); // Recorrer todo el sub-arbol derecho
	}
}


//Post-orden -> izquierdo, derecho y después raíz
void PostOrden(Nodo* arbol) {
	if (arbol == NULL){
		return;
	}
	else {
		PostOrden(arbol->izquierdo); // Recorrer todo el sub-arbol izquierdo
		PostOrden(arbol->derecho); // Recorrer todo el sub-arbol derecho
		cout <<  arbol->dato << " - "; //Imprimir valor 
	} 
}



//Buscar y eliminar un nodo del arbol
void BuscarEliminar(Nodo* arbol, int n) { //busca el nodo a eliminar
	if (arbol == NULL) { //Si el arbol está vacio
		return;
	}
	//Verificar/Buscar por la izquierdo 
	else if (n < arbol->dato) {
		BuscarEliminar(arbol->izquierdo, n);
	}
	//Verificar/Buscar por la derecho 
	else if (n > arbol->dato) {
		BuscarEliminar(arbol->derecho, n);
	}
	else { //Se encuentra el elemento n == arbol -> dato
		EliminarNodo(arbol);
		cout << "Elemento " << n << " ha sido eliminado exitosamente" << endl;
	}
}


//Eliminar el nodo encontrando
void EliminarNodo(Nodo* NodoEliminar) {
	//Verificar que tipo de Nodo es - raiz, rama u hoja
		//RAMA CON DOS HIJOS
	if (NodoEliminar->izquierdo && NodoEliminar->derecho) { //Verificar si es una rama con dos hijos
		Nodo* menor = Minimo(NodoEliminar->derecho); //Se busca el dato que va a reemplazar el Nodo que queremos borrar
		if(menor){ //si no es nulo
			NodoEliminar->dato = menor->dato;  //Se reemplaza el Nodo a elimina
		}
		else{
			menor = NodoEliminar->derecho;
		}
		EliminarNodo(menor); //Se borra el Nodo que sustituyo
	}
	//RAMA CON UN HIJO IZQ O DERECHO
	else if (NodoEliminar->izquierdo) { //Verificar si es una rama con un hijo
		Reemplazar(NodoEliminar, NodoEliminar->izquierdo);
		//Primer parametro para seleccionar el Nodo a eliminar
		//Segundo parametro para seleccionar el Nodo con el que lo vamos a reemplazar
		DestruirNodo(NodoEliminar);
	}
	else if (NodoEliminar->derecho) {
		Reemplazar(NodoEliminar, NodoEliminar->derecho);
		//Primer parametro para seleccionar el Nodo a eliminar
		//Segundo parametro para seleccionar el Nodo con el que lo vamos a reemplazar
		DestruirNodo(NodoEliminar);
	}
	//Es una HOJA, ningun hijo
	else {
		Reemplazar(NodoEliminar, NULL);
		//Primer parametro para seleccionar el Nodo a eliminar
		//Segundo parametro para reemplazarlo con NULL
		DestruirNodo(NodoEliminar);
	}
}

//Función para determinar el nodo más izquierdo posible
Nodo* Minimo(Nodo* arbol) {
	if (arbol == NULL) { //Arbol vacio
		return NULL;
	}
	if (arbol->izquierdo) { //Verifica si tiene más hijos izquierdos
		//Función recursiva
		return Minimo(arbol->izquierdo);
	}
	else { //cuando ya no tenga más hijos izquierdos
		return arbol;
	}
}

	
//Función para reemplazar dos Nodos (1ro - nodo seleccionado) (2ndo - nodo a reemplazar)
void Reemplazar(Nodo* arbol, Nodo* nuevoNodo) {
	//Verificar si el Nodo "arbol" tiene padre
	if (arbol->padre) {
		//Verificar que tipo de hijo es, si izq o derecho
		//Asignandole un nuevo hijo al Nodo padre
		if (arbol->padre->izquierdo && arbol->dato == arbol->padre->izquierdo->dato) { //Si es un hijo izquierdo
			arbol->padre->izquierdo = nuevoNodo;
		}
		else if (arbol->padre->derecho && arbol->dato == arbol->padre->derecho->dato) { //Si es un hijo derecho
			arbol->padre->derecho = nuevoNodo;
		}
	}
	else{ //si no tiene padre es la raiz
		extern Nodo* arbol; //variable global
		arbol = nuevoNodo; //se asignara la nueva raiz
	}
	//Asignandole un nuevo padre al nuevoNodo
	if (nuevoNodo) {
		nuevoNodo->padre = arbol->padre;
	}
}

//Función para borrar el nodo 
void DestruirNodo(Nodo* NodoDestruir) {
	//Eliminar la relación de los hijos del nodo
	NodoDestruir->izquierdo = NULL;
	NodoDestruir->derecho = NULL;
	delete NodoDestruir; //libera el espacio de la memoria
}

int CapturarEntrada(string mensaje)
{
	string entrada; //variable para almacenar la entrada
	bool correcta; //variable para verificar si la entrada es valida
	do {
		//se repetira hasta que el usuario ingrese una entrada valida 
		cout << mensaje;
		cin >> entrada; //Tome la entrada por pantalla
		correcta = ValidarEntrada(entrada); //Llama a la funcion para validar la entrada
		if (correcta == false) //si no es valida
		{
			cout << "Entrada no valida. Solo se permite un numero entero" <<endl;
			system("pause");
			cout << "\n";
			//for (int i = 0; i < 5; i++) cout << "                                        ";
		}
	} while (correcta == false); //repetir mientras que la entrada no sea valida
	return stoi(entrada); //retorna la entrada convertida en entero
	return 0;
}

bool ValidarEntrada(string entrada) { //true - es valida       false - no es valida 
	int contadorSigno = 0; //variable para determinar cuantos '-' hay en la entrada
	for (int i = 0; i < entrada.length(); i++) //recorre todas las posiciones del string de entrada
	{
		if (entrada[i] == '-') //si el caracter de la posicion es '-'
		{
			if (entrada.length() > 1) //si la entrada tiene mas de un caracter
			{
				contadorSigno++; //agrega al contador
				if (contadorSigno > 1) return false; //si la entrada tiene mas de un signo '-'
				if (i != 0) return false; //si el signo '-' no esta en la primera posicion
			}
			else //si tiene un caracter o menos de un caracter
			{
				return false;
			}
		}
		if (isdigit(entrada[i]) == false && entrada[i] != '-') return false; //si no es un digito ni es el signo de '-'
	}
	return true;
}

/*
	cout << "  +---------------------------------------------------------+" << endl;
	cout << "  |                        D I S E Ñ O                      |" << endl;
	cout << "  +---------------------------------------------------------+" << endl;
*/

void EmptyTree() {
	cout << "\n\n";
	cout << "  +---------------------------------------------------------+" << endl;
	cout << "  |                 E M P T Y      T R E E                  |" << endl;
	cout << "  +---------------------------------------------------------+" << endl;
}

void BannerEntrada() {
	system("cls");
	system("Color 04");
	cout << "  +----------------------------------------------+" << endl;
	cout << "  |           B I N A R Y     T R E E            |" << endl;
	cout << "  +----------------------------------------------+" << endl;
	system("pause");
}

void BannerFin() {
	system("cls");
	system("Color 04");
	cout << "  +----------------------------------------------+" << endl;
	cout << "  |                     F I N                    |" << endl;
	cout << "  +----------------------------------------------+" << endl;
	system("pause");
}
//Arbol de ejemplo 
/*
				8
		3				10
	1		6				14
		4		7		13
*/
