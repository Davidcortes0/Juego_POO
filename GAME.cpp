//LIBRERIA PARA SALIDA Y ENTRADA DE DATOS
#include <iostream>
//LIBRERIAS PARA LA GENERACION DE NUMEROS ALEATORIOS
#include <cstdlib>
#include <ctime>
//LIBRERIA PARA INTERACTUAR CON EL USUARIO
#include <conio.h>
//LIBRERIA PARA AGRGAR CARACTERES DE IMPRESION EN CONSOLA
#include <wchar.h>

using namespace std;

//DADOS
//Función dado: determina el número del dado que saca cada jugador.
//Parámetros(Posición actual, turno, variable para guardar el número del dado)
int dado(int cx,int turno,int Pcx){

//Si es el turno 1 o 2
if(turno<3){
cx=rand()%64;                           //Asigna un numero aleatorio de 0 a 63 a la posición actual
cx=cx+1;                                //Le suma 1 a la posición actual para que su rango sea de 1 a 64
return cx;                              //retorna la posición actual
}

//Si el turno es mayor a 2
if(turno>2){
Pcx=rand()%8;                           //Asigna un numero aleatorio de 0 a 7 a la variable que guarda el numero del dado
Pcx=Pcx+1;                              //Le suma 1 a la variable anterior para que su rango sea de 1 a 8
return Pcx;                             //retorna el numero del dado
}
}




//TABLERO
//Función table: Despliega el tablero en pantalla
//Parámetros(Vector tablero)
int table(char* tablero){

int i=1,j=1,k=0;

//i y j son variables de ayuda para los ciclos for
//k es el índice que recorre el vector

//Imprime el tablero
for(i=1;i<9;i++){
    for(j=1;j<9;j++){
        cout<<'['<<tablero[k]<<']';
        k++;
    }
    cout<<endl;
}
}




//POSICION
//Función posición: Determina la posible nueva posición
//Parámetros(Posición actual, Numero del dado)
int posicion(int cx,int Pcx){
int x=0;//Variable para guardar la posible nueva posición


//Aplica determinada suma a la posición actual y la almacena en la variable x.
//La suma correspondiente está dada por el número del dado segun el valor que tendria en el vector tablero
switch(Pcx){

case 1: x=cx-15;
break;
case 2: x=cx-6;
break;
case 3: x=cx+10;
break;
case 4: x=cx+17;
break;
case 5: x=cx+15;
break;
case 6: x=cx+6;
break;
case 7: x=cx-10;
break;
case 8: x=cx-17;
break;
}


//Si la posible nueva posición es menor que 65 y mayor a 0 la retorna
//Si incumple alguna de estas condiciones retorna 1000
if(x<65){
    if(0<x){
        return x;
    }
    else{
        return 1000;
    }
}
else{
    return 1000;
}
}


//Función validapos: Determina si la jugada que se va a hacer es valida
//Parámetros(Posición actual, Número del dado, Posible nueva posición)
int validapos(int cx,int Pcx,int x){

bool valida=false;
int z=cx;

//valida: nos dice si el movimiento es o no es valido
//z: Nos dice la fila en la que esta la posición actual


//El siguiente ciclo toma la posición actual y convierte a z en el múltiplo de 8 que hay en la fila en la que se encuentra.
while((z%8)!=0){
    z=z+1;
}

//Evalúa el número del dado que saco el jugador y valida si esta jugada se
//puede hacer si y solo si está dentro de los siguientes intervalos:
//1 y 8: (z-24 , z-26]
//2 y 7: (z-16 , z-8]
//3 y 6: (z , z+8]
//4 y 5: (z+8, z+16]
//Si se puede hacer asigna true a valida
switch(Pcx){

case 1: if((z-24)<x){
            if(x<=(z-16)){
                valida=true;
            }
        }
break;
case 2: if((z-16)<x){
            if(x<=(z-8)){
                valida=true;
            }
        }
break;
case 3: if(z<x){
            if(x<=(z+8)){
                valida=true;
            }
        }
break;
case 4: if((z+8)<x){
            if(x<=(z+16)){
                valida=true;
            }
        }
break;
case 8: if((z-24)<x){
            if(x<=(z-16)){
                valida=true;
            }
        }
break;
case 7: if((z-16)<x){
            if(x<=(z-8)){
                valida=true;
            }
        }
break;
case 6: if(z<x){
            if(x<=(z+8)){
                valida=true;
            }
        }
break;
case 5: if((z+8)<x){
            if(x<=(z+16)){
                valida=true;
            }
        }
break;
}




//Si la jugada es valida retorna 1 si no 0
if (valida==false){
    return 0;
}
else{
    return 1;
}

}



//MOVIMIENTO NO VALIDO
//Funcion mov_inv: Cambia el numero del dado cuando la jugada no se puede hacer
//Parametros(Numero del dado)
int mov_inv(int Pcx){


//Si el número del dado que saco el jugador es menor a 9, le suma 1 al número
//del dado para luego repetir el ciclo de código con el nuevo número de dado
if(Pcx<9){
    cout<<"EL MOVIMIENTO NO ES POSIBLE: "<<Pcx<<endl;
    Pcx=Pcx+1;                      //
}



//Si el número del dado que saco el jugador es 8, toma el número del
//dado como 1, para luego repetir el ciclo de código con este nuevo numero
if(Pcx==9){
    Pcx=1;
}

return Pcx;     //Devuelve el nuevo numero del dado
}





//INTERACCION CON EL USUARIO
int pass(){

//Crea una variable "tecla" y le asigna el valor de una tecla del teclado en codigo ASCII
char Tecla;
Tecla = char(0);
cout<<endl;

//El siguiente ciclo se repite mientras que la variable tecla sea diferente de la flecha arriba en ASCII (72)
while( Tecla != char(72) ){
    Tecla = getch();            //La función getch recibe la tecla que uno toca en el teclado y la retorna en codigo ASCII
    if( Tecla == char(72) )
        break;

    }

    return 0;
 }



//JUEGO
int main() {
setlocale(LC_ALL, "");  //FUNCIÓN PARA ESCRIBIR CON TILDES LAS IMPRESIONES EN PANTALLA
srand(time(NULL));      //SEMILLA PARA GENERACIÍON DE NUMEROS ALEATORIOS

//1. DECLARACION DE VARIABLES  Y VECTORES:

int c1=0,c2=0,Pc1=0,Pc2=0,turno=0,x,i,Valida,contador,winner,jugadaG=0,jugadaD=0;
bool win=false,flag=false;
int jugadasG[32];
int jugadasD[32];
char tablero[64];

//Variables:
//c1: Número que da la posición actual del jugador 1 (GAWAIN).
//c2: Número que da la posición actual del jugador 2 (DIETRICH).
//Pc1: Número del 1 al 8 que el jugador 1 saca al tirar el dado (Juagada Gawain).
//Pc2: Número del 1 al 8 que el jugador 2 saca al tirar el dado (Juagada Dietrich).
//turno: Indica en que turno se esta actualmente.
//i: Variable de apoyo en los ciclos for.
//Valida: Indica si la jugada se puede hacer o no.
//contador: Determina la cantidad de veces seguidas que un jugador no puede realizar un movimiento.
//winner: Indica cual jugador gano.
//win: Indica si alguien gano.
//flag: Indica si el jugador termino o no termino su turno.
//jugadaG: Variable de apoyo para la impresion del vector jugadasG.
//jugadaD: Variable de apoyo para la impresion del vector jugadasD.


//Vectores:
//jugadasG: Almacena las jugadas del jugador 1 (Pc1) que se hacen y son válidas en el orden que se hacen.
//jugadasD: Almacena las jugadas del jugador 2 (Pc2) que se hacen y son válidas en el orden que se hacen.
//tablero: Almacena los datos del tablero que se verán en pantalla.




//2. CONSTRUCCION DEL TABLERO:

//Este ciclo toma el vector tablero y a cada espacio que tiene le asigna un carácter ' '.
for(i=0;i<64;i++){
    tablero[i]=' ';
}




//3.INTRODUCCION AL JUEGO

//Se explica el funcionamiento del juego
cout<<"BIENVENDIO A BATALLA POR LA PRINCESA"<<endl;
cout<<endl<<"PARA AVANZAR EN EL JUEGO OPRIMA LA FLECHA ARRIBA"<<endl;
cout<<"CUANDO UN MOVIMIENTO NO SEA POSIBLE SE LE AVISARÁ JUNTO CON EL NUMERO DEL DADO QUE SACÓ"<<endl<<endl<<endl;

//Primer turno del jugador 1
cout<<endl<<"A CONTINUACIÓN LANCE EL DADO QUE DARA LA POSICIÓN INCIAL DEL CABALLERO GAWAIN EN EL TABLERO"<<endl;
pass();                                 //Función que para el juego hasta que se oprima la flecha arriba
turno=turno+1;                         //Suma 1 a la variable turno
cout<<"Turno: "<<turno<<endl;                      //Imprime la variable turno (TURNO 1)
c1=dado(c1,turno,Pc1);                  //toma un numero de1 1 al 64 mediante la función dado() y la asigna al jugador 1
cout<<"LA POSICIÓN DE GAWAIN ES "<<c1; //Imprime la posición del jugador 1
cout<<endl<<endl<<endl;
tablero[c1-1]='G';                      //Toma la posición actual del jugador 1 y le asigna la letra G a esa posicion en el vector tablero
table(tablero);                         //Imprime el tablero actualizado

//Primer turno del jugador 2
cout<<endl<<"AHORA LANCE EL DADO QUE DARA LA POSICIÓN INCIAL DEL CABALLERO DIETRICH EN EL TABLERO"<<endl;
pass();                                 //Función que para el juego hasta que se oprima la flecha arriba
turno=turno+1;                          //Suma 1 a la variable turno
cout<<"Turno: "<<turno<<endl;                      //Imprime la variable turno (TURNO 2)
c2=dado(c2,turno,Pc2);                  //toma un numero de1 1 al 64 mediante la función dado() y la asigna al jugador 1

//Este siclo evalúa si el jugador 1 y el jugador 2 están en la misma posición y si es así pone al jugador 2 en la posición del jugador 1 más uno
if(c1==c2){
    c2++;
}
cout<<"LA POSICIÓN DE DIETRICH ES "<<c2<<endl<<endl<<endl<<endl<<endl;//Imprime la posición del jugador 1
tablero[c2-1]='D';                      //Toma la posición actual del jugador 2 y le asigna la letra G a esa posicion en el vector tablero
table(tablero);                         //Imprime el tablero actualizado


//SE EXPLICA COMO FUNCIONARA EL JUEGO A PARTIR DE AHORA
cout<<endl<<"A PARTIR DE ESTE MOMENTO SE JUGARÁ CON UN DADO DE OCHO CARAS QUE DICTARÁ LA SIGUENTE POSICIÓN DEL JUGADOR SEGUN LOS MOVIMIENTOS DEL CABALLO EN EL AJEDREZ"<<endl<<endl<<endl;
pass();                                 //Imprime el tablero actualizado


//4. JUEGO
while(win==false){                      // Este ciclo se repite hasta que uno de los dos jugadores gane y contiene lo que se hara durante el turno 3 hasta que un jugador se queda sin movimientos
    turno=turno+1;                      //Suma 1 a la variable turno
    cout<<endl;
    contador=0;                         //Asigna el valor cero al contador de movimientos no validos
    cout<<endl<<endl;
    cout<<endl<<"Turno: "<<turno<<endl; //Imprime el turno actual



    //Para saber a que jugador le toca se hace la operación turno modulo dos.
    //Luego si es 1 es porque turno es impar y por tanto le toca al jugador 1 y si es 0 es porque el número es par y le toca al jugador 2
    switch(turno%2){


    //TURNO DEL JUGADOR 1
    case 1://Si turno modulo dos es uno, ejecuta el siguiente código
        cout<<endl<<"TURNO DEL CABALLERO GAWAIN"<<endl;
        srand(time(NULL));
        Pc1=dado(c1,turno,Pc1);         //Adquiere un número del 1 al 8 (Se lanza el dado)
        jugadaG++;
        while(flag==false){             //Ciclo que se repite hasta que el jugador termine su turno, llámese ciclo de turno
            pass();                     //Función que para el juego hasta que se oprima la flecha arriba
            contador++;                 //Suma 1 al contador
            if(contador==8){            //Si el contador suma 8 errores ejecuta las siguientes tres líneas
                win=true;                   //Indica que alguien gano
                flag=true;                  //termina el turno
                winner=2;                   //Indica que el jugador 2 gano
            }
            x=posicion(c1,Pc1);         //Haya la posible nueva posición del jugador 1
            if(x<65){                   //Si la posible nueva posición es menor a 65 continua con el código
                Valida=validapos(c1,Pc1,x); //Valida la nueva posible posición a ver si se puede hacer
                if (Valida==1){                 //Si la posible nueva posición es válida continua con el código
                    if(x!=c2){                      //Si la nueva posible posición es diferente al de la posición actual del jugador 2, continua con el código
                        if(tablero[x-1]==' '){          //Si al evaluar la posible nueva posición en el vector tablero corresponde al carácter ' ', continua con el código
                            tablero[c1-1]='X';              //Toma la posición actual del jugador 1 en el vector tablero y le asigna el carácter 'X'. Que en el tablero indicara que no se pueden mover a ese sitio
                            c1=x;                           //Asigna el valor de la posible nueva posición a la posición actual
                            tablero[c1-1]='G';              //Toma la nueva posición actual del jugador 1 en el vector tablero y le asigna el carácter 'G'. Que en el tablero indica la posición de Gowin
                            flag=true;                      //termina el turno
                            jugadasG[jugadaG-1]=Pc1;           //Agrega al vector jugadas el número de dado que saco el jugador 1 para moverse a la nueva posición
                            //Se imprime lo que paso en el tablero de forma escrita
                            cout<<"Se movió a "<<c1<<endl;
                            cout<<"Dado: "<<Pc1<<endl;
                        }
                        else{                           //Si al evaluar la posible nueva posición en el vector tablero NO corresponde al caracter ' ', vuelve a tirar el dado
                            Pc1=mov_inv(Pc1);
                        }
                    }
                    else{                           //Si la nueva posible posición es IGUAL al de la posición actual del jugador 2, continua con el código
                        Pc1=mov_inv(Pc1);
                    }
                }
                else{                           //Si la nueva posición no es valida, vuelve a tirar el dado
                    Pc1=mov_inv(Pc1);
                }
            }
            else{                           //Si x es menor o igual a 64 vuelve a tirar el dado
                Pc1=mov_inv(Pc1);
            }
        }
        break;


    //TURNO DEL JUGADOR 2
    case 0://Si turno modulo dos es 0, ejecuta el siguiente código
        cout<<endl<<"TURNO DEL DIETRICH"<<endl;
        srand(time(NULL));              //Adquiere un número del 1 al 8 (Se lanza el dado)
        Pc2=dado(c2,turno,Pc2);         //Ciclo que se repite hasta que el jugador termine su turno, llámese ciclo de turno
        jugadaD++;
        while(flag==false){
            pass();                     //Función que para el juego hasta que se oprima la flecha arriba
            contador++;                 //Suma 1 al contador
            if(contador==8){            //Si el contador suma 8 errores ejecuta las siguientes tres líneas
                win=true;                   //Indica que alguien gano
                flag=true;                  //termina el turno
                winner=1;                   //Indica que el jugador 1 gano
            }
            x=posicion(c2,Pc2);         //Haya la posible nueva posición del jugador 1
            if(x<65){                   //Si la posible nueva posición es menor a 65 continua con el código
                Valida=validapos(c2,Pc2,x); //Valida la nueva posible posición a ver si se puede hacer
                if (Valida==1){                 //Si la posible nueva posición es válida continua con el código
                    if(x!=c1){                      //Si la nueva posible posición es diferente al de la posición actual del jugador 1, continua con el código
                        if(tablero[x-1]==' '){          //Si al evaluar la posible nueva posición en el vector tablero corresponde al carácter ' ', continua con el código
                            tablero[c2-1]='X';              //Toma la posición actual del jugador 2 en el vector tablero y le asigna el carácter 'X'. Que en el tablero indicara que no se pueden mover a ese sitio
                            c2=x;                           //Asigna el valor de la posible nueva posición a la posición actual
                            tablero[c2-1]='D';
                            flag=true;                      //termina el turno
                            jugadasD[jugadaD-1]=Pc2;           //Agrega al vector jugadas el número de dado que saco el jugador 2 para moverse a la nueva posición
                            //Se imprime lo que paso en el tablero de forma escrita
                            cout<<"Se movió a "<<c2<<endl;
                            cout<<"Dado: "<<Pc2<<endl;
                        }
                        else{                           //Si al evaluar la posible nueva posición en el vector tablero NO corresponde al caracter ' ', vuelve a tirar el dado
                            Pc2=mov_inv(Pc2);
                        }
                    }
                    else{                           //Si la nueva posible posición es IGUAL al de la posición actual del jugador 1, continua con el código
                        Pc2=mov_inv(Pc2);
                    }
                }

                else{                           //Si la nueva posición no es valida, vuelve a tirar el dado
                    Pc2=mov_inv(Pc2);
                }
            }
            else{                           //Si x es menor o igual a 64 vuelve a tirar el dado
                Pc2=mov_inv(Pc2);
            }
        }
        break;
    }
flag=false;                             //Asigna false a la variable flat para que el turno se pueda ejecutar correctamente el código del siguiente jugador
table(tablero);                         //Imprime el tablero

//Imprime el vector que contiene las jugadas de Gawain de forma lineal y separando cada número por comas
cout<<"Jugadas Gawain: ";
    for(i=0;i<=jugadaG;i++){
        if ((jugadasG[i]<9) && (0<jugadasG[i])) {   //Valida que el numero del dado almacenado en el vesctor jugadasG este entre 0 y 9
            cout<<jugadasG[i]<<", ";
        }
    }
    cout<<endl;

//Imprime el vector que contiene las jugadas de Dietrich forma lineal y separando cada número por comas
cout<<"Jugadas Dietrich: ";
    for(i=0;i<jugadaD;i++){
        if ((jugadasD[i]<9) && (0<jugadasD[i])) {   //Valida que el numero del dado almacenado en el vesctor jugadasD este entre 0 y 9
            cout<<jugadasD[i]<<", ";
        }
    }
    cout<<endl;


}

//5. GANADOR:
cout<<endl<<endl<<endl;
//Evalúa si gano el jugador 1 y si es así lo muestra en pantalla
if (winner==1){
    cout<<endl<<endl<<"DIETRICH HA PERDIDO"<<endl<<"GAWAIN HA GANADO EL AMOR DE LA PRINCESA"<<endl;
}
//Evalúa si gano el jugador 1 y si es así lo muestra en pantalla
if (winner==2){
    cout<<endl<<endl<<"GAWAIN HA PERDIDO"<<endl<<"DIETRICH HA GANADO EL AMOR DE LA PRINCESA"<<endl;
}
pass();//Función que para el juego hasta que se oprima la flecha arriba

   return 0;
}
