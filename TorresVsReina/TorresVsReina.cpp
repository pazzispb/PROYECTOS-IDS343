// TorresVsReina.cpp
// Materia - Estructuras de Datos y Algoritmos I
/*

Asunto: Realizar un programa que indique las posiciones en las que se puede mover una reina sin que la eliminen dos torres.

Autor:  Pazzis Paulino 1103790
        Huan Hao Wu 1104326
        Johan Contreras 1106473
        Luis Adames 1106170
        Paola Saldana 1104081
        
Fecha: 11 - Octubre - 2022

*/
#include <iostream>
#include <windows.h> //HANDLE, COORD, SetConsoleCursorPosition, GetStdHandle

using namespace std;

//Estructura de datos

struct Pieza {
	char nombre;
	string coordenada;
};
//Prototipado de funciones
void DibujarTablero(); //Dibuja el tablero del ajedrez con las piezas
void LimpiarPantalla(); 
void GotoXY(short x, short y);
void BannerEntrada();
void InicializarPiezas(); //Asignarle las posiciones a las piezas
bool ValidarEntrada(string posicion); 
string CapturarEntrada(string mensaje);
bool ValidarRepeticion(string entrada); //Valida que las piezas no se solapen
void ColocarPieza(Pieza* pieza); //Coloca una pieza en el tablero
int ObtenerCoordenadaX(char coordenada); //Obtiene la coordenada horizontal en pantalla
int ObtenerCoordenadaY(char coordenada); //Obtiene la coordenada vertical en pantalla
void MarcarMovimientoHorizontal(); //Marca el movimiento horizontal de la reina
void MarcarMovimientoDiagonal(); //Marca el movimiento diagonal de la reina
void MarcarMovimientoVertical(); //Marca el movimiento vertical de la reina
void Prueba(); //Datos de ejemplo

//Piezas a utilizar en el juego
Pieza* torre1 = NULL;
Pieza* torre2 = NULL;
Pieza* reina = NULL;

int main(){
	BannerEntrada();
	//InicializarPiezas();
	Prueba();
	DibujarTablero();
	return 0;
}

void InicializarPiezas(){
	string coordenada; //captura la coordenada
	
	coordenada = CapturarEntrada("Ingrese la posicion de la torre 1: ");
	torre1 = new Pieza();
	torre1->nombre = 'T';
	torre1->coordenada = coordenada;
	
	cout<<endl;
	coordenada = CapturarEntrada("Ingrese la posicion de la torre 2: ");	
	torre2 = new Pieza();
	torre2->nombre = 'T';
	torre2->coordenada = coordenada;
	
	cout<<endl;
	coordenada = CapturarEntrada("Ingrese la posicion de la reina: ");		
	reina = new Pieza();
	reina->nombre = 'R';
	reina->coordenada = coordenada;
	
}

bool ValidarEntrada(string entrada) {
    if (entrada.length() > 2) { //si tiene una longitud de mas de dos caracteres
        return false; //retorna falso
    }
    else {
		bool validoX = false, validoY = false; //variable para validar las coordenadas
    	
        if (entrada[0] > 64 && entrada[0] < 73) //si el primer caracter esta entre la A (65) y H (72)
			validoX = true; //coordenada en X valida
        
        if(entrada[1] > 48 && entrada[1] < 57){ //si el segundo numero esta entre el 1 (48) y el 8 (57)
        	validoY = true; //coordenada en Y valida
		}
		return validoX && validoY; //si ambos caracteres son validos, retorna verdadero. Si hay alguno invalido, retorna falso
    }
}

string CapturarEntrada(string mensaje) {
    string entrada; //variable para capturar la entrada del usuario
    bool correcta = false; //variable para validar dicha entrada
    bool repetida = true; //variable para saber si la coordenada ya esta repetida
    do
    {
        cout << mensaje;
        cin >> entrada;
        
        entrada[0] = toupper(entrada[0]); //convierte el primer caracter a mayuscula
        
        correcta = ValidarEntrada(entrada); //verifica si la entrada es correcta
		repetida = ValidarRepeticion(entrada); //verifica si la posicion ingresada ya esta asignada a una pieza
		
        if (correcta == false) //si la entrada no es correcta
        {
            cout << "Entrada no valida. La primera coordenada debe ser una letra entre A-H y, luego, un numero del 1-8" << endl << endl;
            system("pause");
            continue;
        }
        
        if(repetida == true){ //si la posicion esta repetida
        	cout<< "Esta posicion esta ocupada" << endl << endl;
        	system("pause");
        	continue;
		}

    } while (correcta == false || repetida == true); //mientras la posicion se repita y la entrada sea incorrecta
    
	return entrada;
}

bool ValidarRepeticion(string entrada){
	
	if(!torre1 && !torre2 && !reina){
	//si todas las piezas no han sido asignadas
		return false; //no hay repeticion	
	}
	
	if(torre1 && !torre2 && !reina && entrada == torre1->coordenada){
	//si solo la torre2 y la reina no han sido colocadas, 
	//y la entrada es igual a la coordenada de la torre 1
		return true; //hay repeticion	
	}
	
	if(torre1 && torre2)
	{
		if(!reina && (entrada == torre1->coordenada || entrada == torre2->coordenada) ){
		//si solo la reina no ha sido colocada, 
		//y la entrada es igual a la coordenada de la torre 1 o de la torre 2
			return true; //hay repeticion	
		} 
	}
	
	return false; //no hay repeticion	
}

void DibujarTablero() { 
	BannerEntrada();
	cout << "|-----|-----|-----|-----|-----|-----|-----|-----|-----|\n";
    cout << "|     |  A  |  B  |  C  |  D  |  E  |  F  |  G  |  H  |\n";
    cout << "|-----|-----|-----|-----|-----|-----|-----|-----|-----|\n";
    cout << "|  1  |     |     |     |     |     |     |     |     |\n";
    cout << "|-----|-----|-----|-----|-----|-----|-----|-----|-----|\n";
    cout << "|  2  |     |     |     |     |     |     |     |     |\n";
    cout << "|-----|-----|-----|-----|-----|-----|-----|-----|-----|\n";
    cout << "|  3  |     |     |     |     |     |     |     |     |\n";
    cout << "|-----|-----|-----|-----|-----|-----|-----|-----|-----|\n";
    cout << "|  4  |     |     |     |     |     |     |     |     |\n";
    cout << "|-----|-----|-----|-----|-----|-----|-----|-----|-----|\n";
    cout << "|  5  |     |     |     |     |     |     |     |     |\n";
    cout << "|-----|-----|-----|-----|-----|-----|-----|-----|-----|\n";
    cout << "|  6  |     |     |     |     |     |     |     |     |\n";
    cout << "|-----|-----|-----|-----|-----|-----|-----|-----|-----|\n";
    cout << "|  7  |     |     |     |     |     |     |     |     |\n";
    cout << "|-----|-----|-----|-----|-----|-----|-----|-----|-----|\n";
    cout << "|  8  |     |     |     |     |     |     |     |     |\n";
    cout << "|-----|-----|-----|-----|-----|-----|-----|-----|-----|\n";
    //colocamos a la reina
	ColocarPieza(reina);
	
    //Marcamos los movimientos de la reina
    MarcarMovimientoVertical();
	MarcarMovimientoHorizontal();
	MarcarMovimientoDiagonal();
	
	//Colocamos a las torres
	ColocarPieza(torre1);
    ColocarPieza(torre2);
    
    //POSICION FINAL
    GotoXY(0,25);
}

void LimpiarPantalla() {
	system("cls"); //borra toda la pantalla
}

void GotoXY(short x, short y) // se invoca la funcion GoToXY la cual admite dos valores enteros uno para X y otro para Y
{
    HANDLE hConsoleOutput;
    COORD Cursor_Pos = { x, y };

    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, Cursor_Pos);
}

void BannerEntrada() {
    LimpiarPantalla();
    cout << "|-----------------------------------------------------|\n";
    cout << "|           R E I N A    VS    T O R R E S            |\n";
    cout << "|-----------------------------------------------------|\n";
}

void ColocarPieza(Pieza* pieza) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); //toma control de la consola
    
	if(pieza){ //si la pieza no es nula
	    if (pieza->nombre == 'T') {
	        //usar gotoxy para posicionar bien
	        GotoXY( ObtenerCoordenadaX(pieza->coordenada[0]), ObtenerCoordenadaY(pieza->coordenada[1]));
	        SetConsoleTextAttribute(h, 9); //Azul
	        cout << 'T';
	        SetConsoleTextAttribute(h, 7); //Blanco
	    } 
		else if(pieza->nombre == 'R') {
			GotoXY( ObtenerCoordenadaX(pieza->coordenada[0]), ObtenerCoordenadaY(pieza->coordenada[1]));
	        SetConsoleTextAttribute(h, 14); //Amarillo
	        cout << 'R';
	        SetConsoleTextAttribute(h, 7); //Blanco
	    }	
	}
}

int ObtenerCoordenadaX(char coordenada){
	const int posicionX = 9; //posicion horizontal donde comienzan las casillas
	const int espacioColumna = 6; //espacios que hay entre columnas
	
	return posicionX + (int(coordenada) - 'A') * espacioColumna; 
}

int ObtenerCoordenadaY(char coordenada){
	const int posicionY = 6; //posicion vertical donde comienzan las casillas
	const int espacioFila = 2; //espacios que hay entre filas
	
	return posicionY + (int(coordenada) - '1') * espacioFila;
}

bool HayTorre(char coordenadaX, char coordenadaY){ //si en la posicion indicada comparte fila o columna con una torre
	
	return ((coordenadaX == torre1->coordenada[0]) || (coordenadaY == torre1->coordenada[1])) || 
	((coordenadaX == torre2->coordenada[0]) || (coordenadaY == torre2->coordenada[1]));
}

void MarcarMovimientoHorizontal(){
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); //toma control de la consola

	//coordenadas de la reina
	char coordenadaX = reina->coordenada[0]; 
	char coordenadaY = reina->coordenada[1];
	
	//marcar del lado izquierdo
	for(int i = int(coordenadaX) - 1 ; i >= 'A'; i--){
		GotoXY( ObtenerCoordenadaX(i), ObtenerCoordenadaY(coordenadaY) );
		if(HayTorre(i, coordenadaY)){ //si esta la torre1 o torre2 en la fila o columna
			SetConsoleTextAttribute(h, 4); //Rojo
			cout << 'X';
		}
		else{
			SetConsoleTextAttribute(h, 2); //Verde
			cout<<"V";
		}
	}
	
	//marcar del lado izquierdo
	for(int i = int(coordenadaX) + 1; i <= 'H'; i++){
		GotoXY( ObtenerCoordenadaX(i), ObtenerCoordenadaY(coordenadaY) );
		if(HayTorre(i, coordenadaY)){ //si esta la torre1 o torre2 en la fila o columna
			SetConsoleTextAttribute(h, 4); //Rojo
			cout << 'X';
		}
		else{
			SetConsoleTextAttribute(h, 2); //Verde
			cout<<"V";
		}
	}
	
	SetConsoleTextAttribute(h, 7); //Blanco

}
void MarcarMovimientoVertical(){
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); //toma control de la consola

	char coordenadaX = reina->coordenada[0];
	char coordenadaY = reina->coordenada[1];
	
	for(int i = int(coordenadaY) - 1 ; i >= '1'; i--){
		GotoXY( ObtenerCoordenadaX(coordenadaX), ObtenerCoordenadaY(i) );
		if(HayTorre(coordenadaX, i)){ //si esta la torre1 o torre2 en la fila o columna
			SetConsoleTextAttribute(h, 4); //Rojo
			cout << 'X';
		}
		else{
			SetConsoleTextAttribute(h, 2); //Verde
			cout<<"V";
		}
	}
	
	for(int i = int(coordenadaY) + 1; i <= '8'; i++){
		GotoXY( ObtenerCoordenadaX(coordenadaX), ObtenerCoordenadaY(i) );
		if(HayTorre(coordenadaX, i)){ //si esta la torre1 o torre2 en la fila o columna
			SetConsoleTextAttribute(h, 4); //Rojo
			cout << 'X';
		}
		else{
			SetConsoleTextAttribute(h, 2); //Verde
			cout<<"V";
		}
	}
}

void MarcarMovimientoDiagonal(){
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); //toma control de la consola

	char coordenadaX = reina->coordenada[0];
	char coordenadaY = reina->coordenada[1];
	
	for(int i = int(coordenadaY) - 1, j = int(coordenadaX) - 1; i >= '1' && j >= 'A'; i--, j--){
		GotoXY( ObtenerCoordenadaX(j), ObtenerCoordenadaY(i) );
		if(HayTorre(j, i)){ //si esta la torre1 o torre2 en la fila o columna
			SetConsoleTextAttribute(h, 4); //Rojo
			cout << 'X';
		}
		else{
			SetConsoleTextAttribute(h, 2); //Verde
			cout<<"V";
		}
	}
	
	for(int i = int(coordenadaY) - 1, j = int(coordenadaX) + 1; i >= '1' && j <= 'H'; i--, j++){
		GotoXY( ObtenerCoordenadaX(j), ObtenerCoordenadaY(i) );
		if(HayTorre(j, i)){ //si esta la torre1 o torre2 en la fila o columna
			SetConsoleTextAttribute(h, 4); //Rojo
			cout << 'X';
		}
		else{
			SetConsoleTextAttribute(h, 2); //Verde
			cout<<"V";
		}
	}
	for(int i = int(coordenadaY) + 1, j = int(coordenadaX) + 1; i <= '8' && j <= 'H'; i++, j++){
		GotoXY( ObtenerCoordenadaX(j), ObtenerCoordenadaY(i) );
		if(HayTorre(j, i)){ //si esta la torre1 o torre2 en la fila o columna
			SetConsoleTextAttribute(h, 4); //Rojo
			cout << 'X';
		}
		else{
			SetConsoleTextAttribute(h, 2); //Verde
			cout<<"V";
		}
	}
	
	for(int i = int(coordenadaY) + 1, j = int(coordenadaX) - 1; i <= '8' && j >= 'A'; i++, j--){
		GotoXY( ObtenerCoordenadaX(j), ObtenerCoordenadaY(i) );
		if(HayTorre(j, i)){ //si esta la torre1 o torre2 en la fila o columna
			SetConsoleTextAttribute(h, 4); //Rojo
			cout << 'X';
		}
		else{
			SetConsoleTextAttribute(h, 2); //Verde
			cout<<"V";
		}
	}
}

void Prueba(){
	torre1 = new Pieza();
	torre1->nombre = 'T';
	torre1->coordenada = "E4";
	
	torre2 = new Pieza();
	torre2->nombre = 'T';
	torre2->coordenada = "A7";
	
	reina = new Pieza();
	reina->nombre = 'R';
	reina->coordenada = "B2";
}
