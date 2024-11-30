/*
*****************************************************************************
*				Créditos: Pablo Martín			    *
*****************************************************************************
*/

/* Incluimos las bibliotecas */
#include <stdio.h>

/* Declaramos las funciones */
int imprimirTablero(); // Imprime el tablero y cuenta cuantas fichas hay en juego
int testFicha(int filaAdd, int columnaAdd, int turno); // Devuelve 1 si hay una ficha tuya y 0 si no la hay
void deletFichaInput(int filaDell, int columnaDell, int turno); // Pregutna que ficha quiere eliminar
int testFichaDell(int filaDell, int columnaDell, int turno); // Devuelve 1 si la ficha está ocupada por el contrario y 0 si no
void addficha(int filaAdd, int columnaAdd, int turno); // Añade la ficha al tablero
void dellficha(int filaDell, int columnaDell); // Elimina la ficha del tablero
int combinaciones(int turno); // Devuelve 1 si hemos alguién ha hecho las 3 en raya

/* Declaramos el tablero global */
char tablero[3][3];

int main(){
	int contenidoTablero=0, ficha=0;
	int turno=-1, jugador=0; // par, impar
	int filaAdd=0, columnaAdd=0, scanFila=0, scanColumna=0;
	int filaDell=0, columnaDell=0;
	int condicion=0;
	char jugador1='x', jugador2='o';
	
	/* Preguntamos el movimiento */
	while(condicion != 1){
		turno++; // Cambiamos de turno
		
		do{
			/* Elige el jugador al que le toca mover */
			if((turno % 2) == 0){
				jugador = 1;
			} else{
				jugador = 2;
			}
			
			/* Input de la fila y columna*/
			printf("\n[+] Turno del jugador %i\n", jugador);
			
			contenidoTablero = imprimirTablero(); // Imprimimos el tablero
			
			printf("\n[?] Fila: ");
			scanFila = scanf("%i", &filaAdd);
			while(getchar() != '\n');
			
			printf("[?] Columna: ");
			scanColumna = scanf("%i", &columnaAdd);
			while(getchar() != '\n');
			
			if(((scanColumna + scanFila) != 2) || (columnaAdd >= 4) || (filaAdd >= 4) || (columnaAdd <= 0) || (filaAdd <= 0)){
				printf("\n[-] Error al ingresar los datos. Intentelo de nuevo.\n");
			} else{
				ficha = testFicha(filaAdd, columnaAdd, jugador);
				
				if(ficha == 1){
					printf("\n[-] Error, ya hay ficha ahi.\n");
				} else{
					if(contenidoTablero >= 6){
						deletFichaInput(filaDell, columnaDell, jugador);
					}
				}
			}

		} while(((scanColumna + scanFila) != 2) || (ficha == 1) || (columnaAdd > 4) || (filaAdd > 4) || (columnaAdd <= 0) || (filaAdd <= 0));
		
		addficha(filaAdd, columnaAdd, jugador); // Añadimos la ficha a la posición indicada
		
		condicion = combinaciones(jugador);
	}
	
	imprimirTablero();
	printf("\n[+] El juego ha terminado. Ha ganado el jugador %i!", jugador);
	
	return 0; // El código se ejecutó bien
}

int imprimirTablero(){
	int contenidoTablero=0;
	
	// Imprimir encabezado de las columnas
	printf("  ");
    for (int columna = 1; columna <= 3; columna++) {
        printf("%i ", columna);
    }
    printf("\n");
	
	for(int fila=1; fila <= 3; fila++){
		printf("%i ", fila);
			for(int columna=1; columna <= 3; columna++){
					char celda = tablero[fila][columna];
					
					if((celda == 'x') || (celda == 'o')){
						contenidoTablero++;
						printf("%c ", celda);
					} else{
						printf("  ", celda);
					}
			}		
		
		
		printf("\n");
		
	}
	
	return contenidoTablero;
}

int testFicha(int filaAdd, int columnaAdd, int turno){
	int salida=0;
	
	if((turno = 1) && (tablero[filaAdd][columnaAdd] == 'x')){
		salida = 1;
	}
			
	if((turno = 2) && (tablero[filaAdd][columnaAdd] == 'o')){
		salida = 1;
	}
	
	return salida;
}

void deletFichaInput(int filaDell, int columnaDell, int turno){
	int scanFila=0, scanColumna=0, ficha=0;
	
	do{
		/* Input de la ficha que quiere eliminar */
		printf("\n[?] Elige la ficha que quiere eliminar.");
		
		printf("\n[?] Fila: ");
		scanFila = scanf("%i", &filaDell);
		while(getchar() != '\n');
		
		printf("\n[?] Columna: ");
		scanColumna = scanf("%i", &columnaDell);
		while(getchar() != '\n');
		
		if((scanColumna + scanFila) != 2){
			printf("\n[-] Error al ingresar los datos. Intentelo de nuevo.");
		} else{
			ficha = testFichaDell(filaDell, columnaDell, turno);
			
			if(ficha == 1){
				printf("\n[-] Error, esa ficha no es tuya.");
			}
		}
		
	} while(((scanColumna + scanFila) != 2) || (ficha == 1));
	
	dellficha(filaDell, columnaDell);
}

int testFichaDell(int filaDell, int columnaDell, int turno){
	int salida=0;

	if((turno == 1) && (tablero[filaDell][columnaDell] == 'o')){
		salida = 1;
	}
			
	if((turno == 2) && (tablero[filaDell][columnaDell] == 'x')){
		salida = 1;
	}
	
	return salida;
}

void addficha(int filaAdd, int columnaAdd, int turno){
	if(turno == 1){
		tablero[filaAdd][columnaAdd] = 'x';
	} else{
		tablero[filaAdd][columnaAdd] = 'o';
	}
}

void dellficha(int filaDell, int columnaDell){
	tablero[filaDell][columnaDell] = ' ';
}

int combinaciones(int turno){
	int salida=0;
	char ficha='\0';
	
	if(turno == 1){
		ficha = 'x';
	} else{
		ficha = 'o';
	}
	
	/* Combinacions para ganar */
	int condicion1 = (tablero[1][1] == ficha) && (tablero[2][1] == ficha) && (tablero[3][1] == ficha);
	int condicion2 = (tablero[2][1] == ficha) && (tablero[2][2] == ficha) && (tablero[2][3] == ficha);
	int condicion3 = (tablero[3][1] == ficha) && (tablero[3][2] == ficha) && (tablero[3][3] == ficha);
	int condicion4 = (tablero[1][1] == ficha) && (tablero[2][2] == ficha) && (tablero[3][3] == ficha);
	int condicion5 = (tablero[1][3] == ficha) && (tablero[2][2] == ficha) && (tablero[3][1] == ficha);
	int condicion6 = (tablero[1][1] == ficha) && (tablero[1][2] == ficha) && (tablero[1][3] == ficha);
	int condicion7 = (tablero[2][1] == ficha) && (tablero[2][2] == ficha) && (tablero[2][3] == ficha);
	int condicion8 = (tablero[3][1] == ficha) && (tablero[3][2] == ficha) && (tablero[3][3] == ficha);
	
	if((condicion1 == 1) || (condicion2 == 1) || (condicion3 == 1) || (condicion4 == 1) || (condicion5 == 1) || (condicion6 == 1) || (condicion7 == 1) || (condicion8 == 1)){
		salida = 1;
	}
	
	return salida;
}
