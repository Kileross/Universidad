#include <iostream>
#include <windows.h> //Para el sleep

using namespace std;

void IniciarTablero(int** , int , int );
void DibujaTablero(int** , int , int );
void Movimiento(int** , int , int );
bool ComprobarSol(int** , int , int );

int main(){
	int f,c;
	int **tablero;
	
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
		Movimiento(tablero,f,c);
	}while(!ComprobarSol(tablero,f,c));
	DibujaTablero(tablero, f, c); //Aqui vuelve a dibujar el tablero ya que muestra asi la posicion ganadora
	
	cout << endl << "FELICIDADES GANASTE!!!" << endl;
	
	// Liberar memoria
    for (int i = 0; i < f; i++) {
        delete[] tablero[i];
    }
    delete[] tablero;
	
	return 0;
}




void DibujaTablero(int **tablero, int numfils, int numcols) {
    int i, j;
    system("cls");
    cout << "PUZZLE DESLIZANTE" << endl << endl;
    
    for (i = 0; i < numfils; i++) {
        for (j = 0; j < numcols; j++) {
            cout << " --";
        }
        cout << endl;
        
        for (j = 0; j < numcols; j++) {
            cout << "|";
            cout.width(2);
            if (tablero[i][j] != 0)
                cout << tablero[i][j];
            else
                cout << " ";
        }
        cout << "|" << endl;
    }
    
    for (j = 0; j < numcols; j++) {
        cout << " --";
    }
    
    cout << endl << endl;
    return;
}

void IniciarTablero(int **tablero, int numfils, int numcols){
	int cont = 0; //Contador en 0 ya que queremos que el primer elemento sea 0
	
	for(int i = 0; i < numfils; i++){
		for(int j = 0; j < numcols; j++){
			tablero[i][j] = cont;
			cont++;
		}
	}
	return;
}

void Movimiento(int **tablero, int numfils, int numcols){
	int mov,cM,fM,c0,f0;
	
	cout << "Movimiento a realizar: ";
	cin >> mov;
	
	//Bucle para ver donde se encuentra el numero con el cual hacer el movimiento y el 0
	for(int i = 0; i < numfils; i++){ 
		for(int j = 0; j < numcols; j++){
			if(tablero[i][j] == mov){
				cM = j;
				fM = i;
			}
			else if(tablero[i][j] == 0){
				c0 = j;
				f0 = i;
			}
		}
	}
	
	/***
	If que comprueba si el "cero" se encuentra en la misma fila 
	o columna en un posicion +1 o -1 (tanto en el caso para misma 
	misma fila como para columna) que el numero que se desea mover
	***/ 
	if ((cM == c0 && (fM + 1 == f0 || fM - 1 == f0)) || (fM == f0 && (cM + 1 == c0 || cM - 1 == c0))){
		tablero[f0][c0] = mov;
		tablero[fM][cM] = 0;
	}
	else if(mov == 0){
		cout << endl << "|| Juego abortado. Fin del juego ||" << endl;
		Sleep(500); //Pequeño sleep mas que nada para que se pueda llegar a leer el cout	
		exit(0); //Finaliza el juego directamente 
	}
	else{
		cout << endl << "|| Movimiento no permitido ||" << endl;
		Sleep(1000); //Pequeño sleep mas que nada para que se pueda llegar a leer el cout
	}
	return;
}

bool ComprobarSol(int** tablero, int numfils, int numcols) {
    int cont = 1;
    bool resultado = true;  // Asumimos que todo es correcto al principio

    for (int i = 0; i < numfils; i++) {
        for (int j = 0; j < numcols; j++) {
            if (i == numfils - 1 && j == numcols - 1) {
                // La última casilla debe ser 0
                if (tablero[i][j] != 0) {
                    resultado = false;
                }
            } 
            else if (tablero[i][j] != cont) {
                // Si cualquier otra casilla no es igual a "cont" cambiamos resultado a false
                resultado = false;
            }
            cont++;
        }
    }
    return resultado;  // Devolvemos el estado final de la verificación
}
