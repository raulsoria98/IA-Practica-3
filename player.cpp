#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include "player.h"
#include "environment.h"

#define PROF 8

using namespace std;

const double masinf=9999999999.0, menosinf=-9999999999.0;


// Constructor
Player::Player(int jug){
    jugador_=jug;
}

// Actualiza el estado del juego para el jugador
void Player::Perceive(const Environment & env){
    actual_=env;
}

double Puntuacion(int jugador, const Environment &estado){
    double suma=0;

    for (int i=0; i<7; i++)
      for (int j=0; j<7; j++){
         if (estado.See_Casilla(i,j)==jugador){
            if (j<3)
               suma += j;
            else
               suma += (6-j);
         }
      }

    return suma;
}


// Funcion de valoracion para testear Poda Alfabeta
double ValoracionTest(const Environment &estado, int jugador){
    int ganador = estado.RevisarTablero();

    if (ganador==jugador)
       return 99999999.0; // Gana el jugador que pide la valoracion
    else if (ganador!=0)
            return -99999999.0; // Pierde el jugador que pide la valoracion
    else if (estado.Get_Casillas_Libres()==0)
            return 0;  // Hay un empate global y se ha rellenado completamente el tablero
    else
          return Puntuacion(jugador,estado);
}

// ------------------- Los tres metodos anteriores no se pueden modificar


double evaluarCasilla(int fil, int col, const Environment &estado, int jugador)
{
   if(estado.See_Casilla(fil, col) == 0)
      return 0.0;
   
   /* // 4 en fila hacia derecha
   if(col < 4)
      if(estado.See_Casilla(fil, col) == estado.See_Casilla(fil, col + 1) == estado.See_Casilla(fil, col + 2) == estado.See_Casilla(fil, col + 3))
         if(estado.See_Casilla(fil, col) == jugador)
            return -5000.0;
         else
            return 5000.0;

   // 4 en fila hacia izquierda
   if(col > 2)
      if(estado.See_Casilla(fil, col) == estado.See_Casilla(fil, col - 1) == estado.See_Casilla(fil, col - 2) == estado.See_Casilla(fil, col - 3))
         if(estado.See_Casilla(fil, col) == jugador)
            return -5000.0;
         else
            return 5000.0;

   // 4 en fila hacia abajo
   if(fil < 4)
      if(estado.See_Casilla(fil, col) == estado.See_Casilla(fil + 1, col) == estado.See_Casilla(fil + 2, col) == estado.See_Casilla(fil + 3, col))
         if(estado.See_Casilla(fil, col) == jugador)
            return -5000.0;
         else
            return 5000.0;

   // 4 en fila hacia arriba
   if(fil > 2)
      if(estado.See_Casilla(fil, col) == estado.See_Casilla(fil - 1, col) == estado.See_Casilla(fil - 2, col) == estado.See_Casilla(fil - 3, col))
         if(estado.See_Casilla(fil, col) == jugador)
            return -5000.0;
         else
            return 5000.0;

   // 4 en diagonal derecha arriba
   if(fil > 2 && col < 4)
      if(estado.See_Casilla(fil, col) == estado.See_Casilla(fil - 1, col + 1) == estado.See_Casilla(fil - 2, col + 2) == estado.See_Casilla(fil - 3, col + 3))
         if(estado.See_Casilla(fil, col) == jugador)
            return -5000.0;
         else
            return 5000.0;
   
   // 4 en diagonal derecha abajo
   if(fil < 4 && col < 4)
      if(estado.See_Casilla(fil, col) == estado.See_Casilla(fil + 1, col + 1) == estado.See_Casilla(fil + 2, col + 2) == estado.See_Casilla(fil + 3, col + 3))
         if(estado.See_Casilla(fil, col) == jugador)
            return -5000.0;
         else
            return 5000.0;
   
   // 4 en diagonal izquierda arriba
   if(fil > 2 && col > 2)
      if(estado.See_Casilla(fil, col) == estado.See_Casilla(fil - 1, col - 1) == estado.See_Casilla(fil - 2, col - 2) == estado.See_Casilla(fil - 3, col - 3))
         if(estado.See_Casilla(fil, col) == jugador)
            return -5000.0;
         else
            return 5000.0;
   
   // 4 en diagonal izquierda abajo
   if(fil < 4 && col > 2)
      if(estado.See_Casilla(fil, col) == estado.See_Casilla(fil + 1, col - 1) == estado.See_Casilla(fil + 2, col - 2) == estado.See_Casilla(fil + 3, col - 3))
         if(estado.See_Casilla(fil, col) == jugador)
            return -5000.0;
         else
            return 5000.0; */
   
   // 3 en fila hacia derecha
   if(col < 5)
      if(estado.See_Casilla(fil, col) == estado.See_Casilla(fil, col + 1) == estado.See_Casilla(fil, col + 2))
         if(estado.See_Casilla(fil, col) == jugador)
            return -30.0;
         else
            return 30.0;

   // 3 en fila hacia izquierda
   if(col > 1)
      if(estado.See_Casilla(fil, col) == estado.See_Casilla(fil, col - 1) == estado.See_Casilla(fil, col - 2))
         if(estado.See_Casilla(fil, col) == jugador)
            return -30.0;
         else
            return 30.0;

   // 3 en fila hacia abajo
   if(fil < 5)
      if(estado.See_Casilla(fil, col) == estado.See_Casilla(fil + 1, col) == estado.See_Casilla(fil + 2, col))
         if(estado.See_Casilla(fil, col) == jugador)
            return -30.0;
         else
            return 30.0;

   // 3 en fila hacia arriba
   if(fil > 1)
      if(estado.See_Casilla(fil, col) == estado.See_Casilla(fil - 1, col) == estado.See_Casilla(fil - 2, col))
         if(estado.See_Casilla(fil, col) == jugador)
            return -30.0;
         else
            return 30.0;

   // 3 en diagonal derecha arriba
   if(fil > 1 && col < 5)
      if(estado.See_Casilla(fil, col) == estado.See_Casilla(fil - 1, col + 1) == estado.See_Casilla(fil - 2, col + 2))
         if(estado.See_Casilla(fil, col) == jugador)
            return -30.0;
         else
            return 30.0;
   
   // 3 en diagonal derecha abajo
   if(fil < 5 && col < 5)
      if(estado.See_Casilla(fil, col) == estado.See_Casilla(fil + 1, col + 1) == estado.See_Casilla(fil + 2, col + 2))
         if(estado.See_Casilla(fil, col) == jugador)
            return -30.0;
         else
            return 30.0;
   
   // 3 en diagonal izquierda arriba
   if(fil > 1 && col > 1)
      if(estado.See_Casilla(fil, col) == estado.See_Casilla(fil - 1, col - 1) == estado.See_Casilla(fil - 2, col - 2))
         if(estado.See_Casilla(fil, col) == jugador)
            return -30.0;
         else
            return 30.0;
   
   // 3 en diagonal izquierda abajo
   if(fil < 5 && col > 1)
      if(estado.See_Casilla(fil, col) == estado.See_Casilla(fil + 1, col - 1) == estado.See_Casilla(fil + 2, col - 2))
         if(estado.See_Casilla(fil, col) == jugador)
            return -30.0;
         else
            return 30.0;
   
   // 2 en fila hacia derecha
   if(col < 6)
      if(estado.See_Casilla(fil, col) == estado.See_Casilla(fil, col + 1))
         if(estado.See_Casilla(fil, col) == jugador)
            return -5.0;
         else
            return 5.0;

   // 2 en fila hacia izquierda
   if(col > 0)
      if(estado.See_Casilla(fil, col) == estado.See_Casilla(fil, col - 1))
         if(estado.See_Casilla(fil, col) == jugador)
            return -5.0;
         else
            return 5.0;

   // 2 en fila hacia abajo
   if(fil < 6)
      if(estado.See_Casilla(fil, col) == estado.See_Casilla(fil + 1, col))
         if(estado.See_Casilla(fil, col) == jugador)
            return -5.0;
         else
            return 5.0;

   // 2 en fila hacia arriba
   if(fil > 0)
      if(estado.See_Casilla(fil, col) == estado.See_Casilla(fil - 1, col))
         if(estado.See_Casilla(fil, col) == jugador)
            return -5.0;
         else
            return 5.0;

   // 2 en diagonal derecha arriba
   if(fil > 0 && col < 6)
      if(estado.See_Casilla(fil, col) == estado.See_Casilla(fil - 1, col + 1))
         if(estado.See_Casilla(fil, col) == jugador)
            return -5.0;
         else
            return 5.0;
   
   // 2 en diagonal derecha abajo
   if(fil < 6 && col < 6)
      if(estado.See_Casilla(fil, col) == estado.See_Casilla(fil + 1, col + 1))
         if(estado.See_Casilla(fil, col) == jugador)
            return -5.0;
         else
            return 5.0;
   
   // 2 en diagonal izquierda arriba
   if(fil > 0 && col > 0)
      if(estado.See_Casilla(fil, col) == estado.See_Casilla(fil - 1, col - 1))
         if(estado.See_Casilla(fil, col) == jugador)
            return -5.0;
         else
            return 5.0;
   
   // 2 en diagonal izquierda abajo
   if(fil < 6 && col > 0)
      if(estado.See_Casilla(fil, col) == estado.See_Casilla(fil + 1, col - 1))
         if(estado.See_Casilla(fil, col) == jugador)
            return -5.0;
         else
            return 5.0;
   
   return 0.0;
}

// Funcion heuristica (ESTA ES LA QUE TENEIS QUE MODIFICAR)
double Valoracion(const Environment &estado, int jugador){
    int ganador = estado.RevisarTablero();

    if (ganador==jugador)
       return masinf; // Gana el jugador que pide la valoracion
    else if (ganador!=0)
            return menosinf; // Pierde el jugador que pide la valoracion
    else if (estado.Get_Casillas_Libres()==0)
            return 0;  // Hay un empate global y se ha rellenado completamente el tablero
    else
    {
      double suma = 0;
      for(int i = 0; i < 7; i++)
         for( int j = 0; j < 7; j++)
            suma += evaluarCasilla(i, j, estado, jugador);
      /* double suma = 0, eval;
      for(int i = 0; i < 7; i++)
         for( int j = 0; j < 7; j++)
         {
            eval = evaluarCasilla(i, j, estado, jugador);
            if(eval != masinf || eval != menosinf)
                suma += eval;
            else
                return eval;
         } */
      
      return suma;
    }
}




// Esta funcion no se puede usar en la version entregable
// Aparece aqui solo para ILUSTRAR el comportamiento del juego
// ESTO NO IMPLEMENTA NI MINIMAX, NI PODA ALFABETA
void JuegoAleatorio(bool aplicables[], int opciones[], int &j){
    j=0;
    for (int i=0; i<8; i++){
        if (aplicables[i]){
           opciones[j]=i;
           j++;
        }
    }
}

struct nodo
{
   Environment tablero;
   double valor = 0;
   nodo **hijos;
};

double Player::alfabeta(Environment entorno , int profundidad ,int &accion, double alpha , double beta ){

	//cout << " Accion -> " << accion << endl;
	Environment nuevo ; 
	double mejorValor;
	int auxiliar = -1;

	if(profundidad == 0 || entorno.JuegoTerminado())
		return Valoracion(entorno,jugador_);

	if(entorno.JugadorActivo() == jugador_ ){

		nuevo = entorno.GenerateNextMove(auxiliar);
		mejorValor = alpha;

		while(auxiliar<8){
			int otra = auxiliar;

			double valorHijo = alfabeta(nuevo , profundidad -1 ,otra, mejorValor , beta);
			
			//cout << "Mejor valor Max " << mejorValor << " y valor hijo " << valorHijo << " a prof. " << profundidad << endl; 

			if(valorHijo > mejorValor && auxiliar != -1 && profundidad == PROF){
       		 cout << "Mov . " << auxiliar << " con  " << valorHijo << " puntos \n";
				accion = auxiliar;

			}

			mejorValor = max( mejorValor , valorHijo);

			if (beta <= mejorValor) {
                break;
            }
			nuevo = entorno.GenerateNextMove(auxiliar);
			

		}

	}else{

		nuevo = entorno.GenerateNextMove(auxiliar);
		mejorValor = beta;

		while(auxiliar<8){
			int otra = auxiliar;

			double valorHijo = alfabeta(nuevo , profundidad -1 ,otra, alpha , mejorValor);
			
			//cout << "Mejor valor Min " << mejorValor << "y valor hijo " << valorHijo << " a prof. " << profundidad << endl;

			if(valorHijo < mejorValor && auxiliar != -1 && profundidad == PROF){
        		cout << "Mov . " << auxiliar << " con  " << valorHijo << " puntos \n";
				accion = auxiliar;
			}

			mejorValor = min( mejorValor , valorHijo);
            if (mejorValor <= alpha) {
                break;
            }
			nuevo = entorno.GenerateNextMove(auxiliar);

		}

	}

	return mejorValor;
}


// Invoca el siguiente movimiento del jugador
Environment::ActionType Player::Think(){
    const int PROFUNDIDAD_MINIMAX = 6;  // Umbral maximo de profundidad para el metodo MiniMax
    const int PROFUNDIDAD_ALFABETA = 8; // Umbral maximo de profundidad para la poda Alfa_Beta

    Environment::ActionType accion; // acci�n que se va a devolver
    bool aplicables[8]; // Vector bool usado para obtener las acciones que son aplicables en el estado actual. La interpretacion es
                        // aplicables[0]==true si PUT1 es aplicable
                        // aplicables[1]==true si PUT2 es aplicable
                        // aplicables[2]==true si PUT3 es aplicable
                        // aplicables[3]==true si PUT4 es aplicable
                        // aplicables[4]==true si PUT5 es aplicable
                        // aplicables[5]==true si PUT6 es aplicable
                        // aplicables[6]==true si PUT7 es aplicable
                        // aplicables[7]==true si BOOM es aplicable



    double valor; // Almacena el valor con el que se etiqueta el estado tras el proceso de busqueda.
    double alpha, beta; // Cotas de la poda AlfaBeta

    int n_act; //Acciones posibles en el estado actual


    n_act = actual_.possible_actions(aplicables); // Obtengo las acciones aplicables al estado actual en "aplicables"
    int opciones[10];

    // Muestra por la consola las acciones aplicable para el jugador activo
    //actual_.PintaTablero();
    cout << " Acciones aplicables ";
    (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
    for (int t=0; t<8; t++)
      if (aplicables[t])
         cout << " " << actual_.ActionStr( static_cast< Environment::ActionType > (t)  );
    cout << endl;


    //--------------------- COMENTAR Desde aqui
    /* cout << "\n\t";
    int n_opciones=0;
    JuegoAleatorio(aplicables, opciones, n_opciones);

    if (n_act==0){
      (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
      cout << " No puede realizar ninguna accion!!!\n";
      //accion = Environment::actIDLE;
    }
    else if (n_act==1){
           (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
            cout << " Solo se puede realizar la accion "
                 << actual_.ActionStr( static_cast< Environment::ActionType > (opciones[0])  ) << endl;
            accion = static_cast< Environment::ActionType > (opciones[0]);

         }
         else { // Hay que elegir entre varias posibles acciones
            int aleatorio = rand()%n_opciones;
            cout << " -> " << actual_.ActionStr( static_cast< Environment::ActionType > (opciones[aleatorio])  ) << endl;
            accion = static_cast< Environment::ActionType > (opciones[aleatorio]);
         } */

    //--------------------- COMENTAR Hasta aqui


    //--------------------- AQUI EMPIEZA LA PARTE A REALIZAR POR EL ALUMNO ------------------------------------------------


    // Opcion: Poda AlfaBeta
    // NOTA: La parametrizacion es solo orientativa
    // valor = Poda_AlfaBeta(actual_, jugador_, 0, PROFUNDIDAD_ALFABETA, accion, alpha, beta);
    //cout << "Valor MiniMax: " << valor << "  Accion: " << actual_.ActionStr(accion) << endl;

    int accionAuxiliar = -1;
    valor = alfabeta(actual_,PROF, accionAuxiliar, menosinf, masinf);
    //cout << "Valor MiniMax: " << valor << "  Accion: " << actual_.ActionStr(accion) << endl;

	cout << accionAuxiliar;

	switch (accionAuxiliar)
	{
      case 0: accion = Environment::PUT1; break;
      case 1: accion = Environment::PUT2; break;
      case 2: accion = Environment::PUT3; break;
      case 3: accion = Environment::PUT4; break;
      case 4: accion = Environment::PUT5; break;
      case 5: accion = Environment::PUT6; break;
      case 6: accion = Environment::PUT7; break;
      case 7: accion = Environment::BOOM; break;
	}

    return accion;
}

