#include <iostream>
#include "practica2.h"

using namespace std;

int main(){
	int f,c;
	int **tablero;
	bool comprobacion;
	
	cout << "|| Introduzca el tamaño de del tablero [f][c] siendo f las filas y c las columnas ||\n" << endl << "Filas: " ;
	cin >> f;
	cout << "Columnas: ";
	cin >> c;
	
	tablero = new int *[f]; //Inicializar la matriz
	for (int i=0;i<f;i++)
		tablero[i] = new int[c];
	
	/***
	En esta parte de la funcion se comienza inicializando el tablero para
	que escriba los numeros en sus posiciones correspondientes matriz, una vez eso
	usamos la estructura do-while ya que queremos una primera iteracion siempre 
	independientemente de la condicion (por como lo he estructurado).
	Primero dibujara el tablero por cada iteracion y luego hara la funcion que 
	verifica y realiza si puede realizar el movimiento que el jugador indica, luego 
	se evalua llamando a la funcion ComprobarSol si la "solucion" es correcta
	***/
	
	IniciarTablero(tablero, f, c);
	do{
		DibujaTablero(tablero, f, c);
		comprobacion = Movimiento(tablero,f,c);
	}while(!ComprobarSol(tablero,f,c) && comprobacion);
	DibujaTablero(tablero, f, c); //Aqui vuelve a dibujar el tablero ya que muestra asi la posicion ganadora
	
	if(!comprobacion)
		cout << endl << "|| Juego abortado. Fin del juego ||" << endl;		
	else
		cout << endl << "FELICIDADES GANASTE!!!" << endl;
	
	
	// Liberar memoria
    for (int i = 0; i < f; i++) {
        delete[] tablero[i];
    }
    delete[] tablero;
	
	return 0;
}
