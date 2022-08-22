// Mastermind.cpp
// Materia - Estructuras de Datos y Algoritmos I
/*

Asunto:  Crear un juego de Mastermind, en el que se adivine una clave de 4 caracteres con digitos del 1 al 6.

Autor:  Pazzis Paulino 1103790
        Huan Hao Wu 1104326
        Johan Contreras 1106473
        Luis Adames 1106170
        Paola Saldana 1104081
Fecha: 15 - Agosto - 2022

*/
#include <iostream>
#include <cctype> //tolower
#include <cstring> //length
#include <cstdlib> //srand - rand
#include <ctime> //time
#include <windows.h> //HANDLE, COORD, SetConsoleCursorPosition, GetStdHandle
#include <conio.h>


using namespace std;

//variables globales
string intentos[10]; //arreglo donde se almacenan los intentos del jugador
string nombreJugador; //nombre del jugador
int cantidadIntentos; //cantidad de intentos que tiene disponible el jugador
int intentosJugados; //cantidad de intentos que ya jugo el usuario
int calificacion; //calificacion del jugador
int longitud = 4; //cantidad de caracteres


//prototipo de funciones - TOP DOWN
void ComenzarNuevaPartida();
void SetValoresIniciales();
string GenerarClave();
string CaptutarIntento(int intento);
string GenerarPistas(string intento, string clave);
void ImprimirTabla(int intento, string clave);
void ImprimirMensajeFinalizacion(bool ganador, string clave);
void LimpiarPantalla();
bool VerificarRepeticion(char digito, string generarClave);
void Gotoxy(short x, short y);

//funcion principal
int main()
{
	char continuar = 's';
	do{
		ComenzarNuevaPartida();
		cout<<"Desea jugar otra partida? (S/N): ";
		continuar = _getch();
		cout<<continuar;
	}while(tolower(continuar) == 's');
	cout<< "\nGracias por jugar!";
	return 0;
}

//Definicion de funciones

void ComenzarNuevaPartida(){
	SetValoresIniciales(); //inicializa las variables globales
	
	string intento = "";
	string clave = GenerarClave(); //clave aleatoria que el jugador debe de adivinar
	bool ganador = false;
	
	cout<<"Ingrese su nombre: ";
	cin>>nombreJugador;
	
	while(intentosJugados < cantidadIntentos){
		ImprimirTabla(intentosJugados, clave);
	
		intento = CaptutarIntento(intentosJugados); //se captura del intento
		intentos[intentosJugados] = intento; //se guarda el intento en el arreglo
	
		ImprimirTabla(intentosJugados, clave); //se imprimen las tablas de intentos y pistas
	
		intentosJugados++; //se aumenta el contador de intentos
	
		if(clave == intento){ //si el jugador logra adivinar la clave
			ganador = true;
			break;
		}
		else{
			calificacion--;
		}
	}
	ImprimirMensajeFinalizacion(ganador, clave);//se imprime el mensaje de finalizacion
}

void SetValoresIniciales(){
	LimpiarPantalla(); // se limpia la pantalla
	
	nombreJugador = ""; //nombre del jugador
	cantidadIntentos = sizeof(intentos)/sizeof(string); //tamano del arreglo intentos, su cantidad es igual al numero de intentos que tiene el jugador
	intentosJugados = 0; //cantidad de intentos jugados
	calificacion = cantidadIntentos; //calificacion con la que inicia el jugador
	
	for(int i = 0; i < cantidadIntentos; i++) intentos[i] = ""; //limpia el arreglo
}

bool VerificarRepeticion(char digito, string generarClave) {
    for(int i = 0; i < longitud; i++) 
		if(digito == generarClave[i]) return true; //si hay coincidencias retorna true
    
	return false; //sino, di que no hay repeticiones   
}

string GenerarClave(){
	string generarClave = ""; //variable con la clave a retornar
	int digito; // variable donde se almacenara cada digito de la contrasena
	int minValue = 1; //digito minimo permitido
	int maxValue = 6; //digito maximo permitido
	
	srand(time(NULL)); //punto de partida para empezar a generar numeros aleatorios
    
	for(int i = 0; i < longitud; i++){
        do
        {
            digito = rand() % (maxValue - minValue + 1) + minValue; //genera un digito entre el rango definido
        } while (VerificarRepeticion(digito + '0', generarClave));//repite la generacion del digito aleatorio hasta que no haya coincidencias
        generarClave += to_string(digito); //se agrega el digito a la clave	
    }
	
	return generarClave;
}

string CaptutarIntento(int intento)
{
    string str = "";    // crear nuestro string
    string x;
	int horix = 17; // horix = posicion horizontal en la consola
	int verty = 4  + intento; // vertY = posicion vertical en la consola
    
	for (int i = 0; i < 4; i++) // loop que se repite 4 veces, ya que necesitamos 4 numeros.
    {
        for (;;) // loop infinito, para comprobar la validacion de numeros del 1 al 6, y confirmar que sean digitos. Se utiliza esto ya que si el usuario coloca un dato erroneo, no avanzara al siguiente digito, sino que se va a reprtir.
        {
        	Gotoxy(horix ,verty); 
    
	        x = _getch();
    		Gotoxy(0,18);
			cout<<"                            "; //Borra el mensaje
	        if (isdigit(x[0]) && stoi(x) < 7 && stoi(x) > 0 && VerificarRepeticion(x[0], str) == false) // este if comprueba que el el dato ingresado sea un numero, ademas de que lo filtra del 1 al 6 y verifica que no se repita.
            {
            	Gotoxy(horix ,verty);                                         
				cout<<x;
                str.append(x); // en caso de que todo este correcto, se asigana el valor al array, y se continua con el siguiente.
                x = "";
                horix += 6; //se corre en el eje horizontal 6 espacios para colocar el primer caracter del arreglo en la columna A
                break;            // rompeos el bucle infinito de ese valor.
			}
			else{
				Gotoxy(0,18);
				cout<<"Entrada no valida";
			}
        }
    }
    return str; // retornamos el string ya escrito por el usuario.
}

string GenerarPistas(string intento, string clave){
	string pista = "NULO";
    
	for (int i = 0; i < 4; i++) {
        if (intento[i] == clave[0] || intento[i] == clave[1] || intento[i] == clave[2] || intento[i] == clave[3]) {
            //Se coloca F si existe un valor del intento igual a uno de los valores de la clave
            pista[i] = 'F';
        }
        else {
            //Sino existe entonces se coloca una X
            pista[i] = 'X';
        }
        for (int j = 0; j < 4; j++) {
            if (i == j) {
                if (intento[i] == clave[j]) {
                    pista[i] = 'C';
                }
            }
        }
    }
    return pista;
}

void Gotoxy(short x, short y) // se invoca la funcion GoToXY la cual admite dos valores enteros uno para X y otro para Y
{
	HANDLE hConsoleOutput;
	COORD Cursor_Pos = {x, y};

	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_Pos);
}

void ImprimirTabla(int intento, string clave){ // FUNCION DE IMPRIMIR TABLA: recibe la cantidad de intentos que tendra el juego para asi saber cuantos renglones se ameritan
	LimpiarPantalla();
	
	cout << "|-------------------------------------| |-------------------------------------|\n";
	cout << "| Calificacion|  A  |  B  |  C  |  D  | |   Intentos  |  A  |  B  |  C  |  D  |\n";
	cout << "|-------------------------------------| |-------------------------------------|\n";
	cout << "|             |     |     |     |     | |             |     |     |     |     |\n";
	cout << "|             |     |     |     |     | |             |     |     |     |     |\n";
	cout << "|             |     |     |     |     | |             |     |     |     |     |\n";
	cout << "|             |     |     |     |     | |             |     |     |     |     |\n";
	cout << "|             |     |     |     |     | |             |     |     |     |     |\n";
	cout << "|             |     |     |     |     | |             |     |     |     |     |\n";
	cout << "|             |     |     |     |     | |             |     |     |     |     |\n";
	cout << "|             |     |     |     |     | |             |     |     |     |     |\n";
	cout << "|             |     |     |     |     | |             |     |     |     |     |\n";
	cout << "|             |     |     |     |     | |             |     |     |     |     |\n";
	cout << "|             |     |     |     |     | |             |     |     |     |     |\n";
	cout << "|             |     |     |     |     | |             |     |     |     |     |\n";
	cout << "|             |     |     |     |     | |             |     |     |     |     |\n";
	cout << "--------------------------------------  ---------------------------------------\n";
	cout << "Bienvenido, " << nombreJugador << ", ingrese su clave en las casillas correspondientes.";
	
	string pistas; // string para las letras de las pistas
	int horix = 7; // horix = posicion horizontal, 7 coloca el cursor en el primer renglon de la tabla calificacion
	int verty = 4; // vertY = posicion vertircal, 4 coloca el cursor en el primer renglon de la tabla calificacion
	
	for(int i = 0; i < intento; i++){ 
		pistas = GenerarPistas(intentos[i], clave);
		Gotoxy(horix,verty);
	
		cout << 10 - i; // rellena primera colummna con los numeros de intentos del 10 al 1
		horix += 10; // se corre en el eje horizontal 10 espacios para colocar el primer caracter del arreglo en la columna A
	
		Gotoxy(horix ,verty); // se suman los 10 espacios a los 7 que tenia la variable horix inicialmente = 17
		cout << intentos[i][0]; // se imprime el primer caracter de la primera palabra del arreglo
		horix += 6; //se corre en el eje horizontal 6 espacios para colocar el primer caracter del arreglo en la columna A
	
		Gotoxy(horix ,verty); //se suman los 6 espacios a los 17 que tenia la variable horix inicialmente = 23
		cout << intentos[i][1];
		horix += 6;
	
		Gotoxy(horix,verty);
		cout << intentos[i][2];
		horix += 6;
	
		Gotoxy(horix,verty);
		cout << intentos[i][3];

		horix += 11; // posiciona el numero de intentos (primera columna de la tabla de intentos)
		Gotoxy(horix,verty);
		cout << i+1; // se rellena la columna de intentos con numeros del 1 al 9
		
	    horix += 11; //posiciona los caracteres de segunda columna de la tabla intentos
		Gotoxy(horix,verty);
		cout << pistas[0]; // en dicha columna se imprime el primer caracter del arreglo pistas
	
		horix += 6; // se corren 6 posiciones de las 11 que teniamos 6+11 = 17
		Gotoxy(horix,verty);
		cout << pistas[1]; // se imprime el segundo caractewr del arreglo pistas
	
		horix += 6;
		Gotoxy(horix,verty);
		cout << pistas[2];
	
		horix += 6;
		Gotoxy(horix,verty);
		cout << pistas[3];
		
		// coordenadas de inicio
		horix = 7; 
		verty +=1; // para hacer el salto de renglon
	}
	
}

void LimpiarPantalla(){
	system("cls"); //borra toda la pantalla
}

void ImprimirMensajeFinalizacion(bool ganador, string clave){
	LimpiarPantalla();
	ImprimirTabla(intentosJugados, clave);
	Gotoxy(0,18);
	
	if(ganador)
    {
        cout << "\nFelicidades, "<< nombreJugador << "! Usted adivino la clave. Gano con una calificacion de: " << calificacion << endl;
    }
    else
    {
        cout << "\nSe han agotado el numero de intentos, la clave es: " << clave << endl;
    }
}
