#include <iostream>
#include <windows.h> //Para el sleep

using namespace std;

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

bool Movimiento(int **tablero, int numfils, int numcols){
	int mov,cM,fM,c0,f0;
	int res = true;
	
	
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
	else if(mov == 0)
		res = false;
	
	else{
		cout << endl << "|| Movimiento no permitido ||" << endl;
		Sleep(1000); //Pequeño sleep mas que nada para que se pueda llegar a leer el cout
	}
	return res;
}

bool ComprobarSol(int** tablero, int numfils, int numcols) {
    int cont = 1;
    bool resultado = true;  // Asumimos que todo es correcto al principio

    for (int i = 0; i < numfils; i++) {
        for (int j = 0; j < numcols; j++) {
            if (i == numfils - 1 && j == numcols - 1) {
                // La última casilla debe ser 0
				if(tablero[i][j] != 0)
					resultado = false;
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
