//LIBRERIA PARA SALIDA Y ENTRADA DE DATOS
#include <iostream>
//LIBRERIAS PARA LA GENERACION DE NUMEROS ALEATORIOS
#include <cstdlib> //rand
#include <ctime>
//LIBRERIA PARA INTERACTUAR CON EL USUARIO
#include <conio.h>
//LIBRERIA PARA AGRGAR CARACTERES DE IMPRESION EN CONSOLA
#include <wchar.h>
#include<string.h>
//LIBRERIA PARA IMPRESION GRAFICA
#include <allegro.h>



//FUNCIONES PARA IMPLEMENTAR LA INTERFAZ GRAFICA
void init();
void deinit();

using namespace std;

int out = 0;            //Variable para indicar la opcion elegida en el menu del juego





//----------------------------------ESTRUCTURAS---------------------------------------------
struct jugadas
{
    int posicion;
    int jugada;
    jugadas *siguiente;
};

jugadas *cabG;
jugadas *cabD;

struct tablero
{
    int posicion;
    char nombre;
    int jugada;
    tablero *siguiente;
};

struct caballero
{
     int casilla;
     int estado=0; // que un caballero este en estado 0 significa que no ha ganado, si gana pasa a estar en estado 1
};







//----------------------------------CLASES---------------------------------------------

class TABLERO{
protected:
    tablero *cab;
public:
    TABLERO(){ cab=NULL;}
    int posicion_lista(int n); // Valida si ya existe y ubica la posici�n para insertar
    void insertar(tablero *, tablero *, int);
    tablero *casillaDelTablero(int x);
};

class JUGADAS: public TABLERO{
public:
    JUGADAS(): TABLERO(){
        cab=NULL;
    }
};

class CABALLERO{
private:
    int casilla;
    int estado;
public:
    CABALLERO(int j=0){
        estado=j;
    }
    void winner(){
        estado=1;
    }
    int get_estado(){
        return estado;
    }
    void set_casilla(int k){
        casilla=k;
    }
    int get_casilla(){
        return casilla;
    }

};






//----------------------------------PROTOTIPOS PARA LISTA DINAMICA---------------------------------------------

// Prototipos de las funciones usadas para la creaci�n del tablero en forma de lista.
//int posicion_lista(int n); // Valida si ya existe y ubica la posici�n para insertar
//void insertar(tablero *, tablero *, int); // Inserta en la posicion adecuada

int posicion_lista_G(int n);
int posicion_lista_D(int n);

void insertar_G(jugadas *, jugadas *, int );
void insertar_D(jugadas *, jugadas *, int );

//----------------------------------FUNCIONES---------------------------------------------

//NODOS

int TABLERO:: posicion_lista(int n){
 tablero *p, *q;
 int encontro=0;
 p=NULL;
 q=cab;
 // Con el siguiente while recorremos la lista de principio a fin
 // y al final *p apunta al �ltimo nodo de la lista
 while(q != NULL && !encontro){
  if(n > q->posicion){
   p=q;
   q=q->siguiente;
  }
  else{
   encontro=1;
  }
 }
 if(encontro){
  if(n == q->posicion){
   return -1; // retorna -1 cuando el elemento est� repetido
  }
  else{
   insertar(p,q,n);
  }
 }
 else{
  insertar (p,q,n);
 }
 return 0; // En caso de hacerse la inserci�n correctamente retorna 0
}

void TABLERO:: insertar(tablero *p, tablero *q, int n){
 tablero *nuevo;
 nuevo=new tablero;
 nuevo->posicion=n;
 nuevo->siguiente=q;
 if(p != NULL){ // Quiere decir que hay uno o m�s nodos ya insertados
  p->siguiente=nuevo; // Al �ltimo nodo de la lista se le encadena el nodo nuevo
 }
 else{
  cab=nuevo;
 }
}

tablero* TABLERO:: casillaDelTablero(int x )
{
    tablero *p=cab;
    while(p -> posicion < x )
    {
        p=p->siguiente;
    }
    return p;
}




//--------------------------------------------



//DADOS

//Funci�n dado: determina el n�mero del dado que saca cada jugador.
//Par�metros(Posici�n actual, turno, variable para guardar el n�mero del dado)
int dado(int cx,int turno,int Pcx){

    //Si es el turno 1 o 2
    if(turno<3){
        cx=rand()%64;                           //Asigna un numero aleatorio de 0 a 63 a la posici�n actual
        cx=cx+1;                                //Le suma 1 a la posici�n actual para que su rango sea de 1 a 64
        return cx;                              //retorna la posici�n actual
    }

    //Si el turno es mayor a 2
    if(turno>2){
        Pcx=rand()%8;                           //Asigna un numero aleatorio de 0 a 7 a la variable que guarda el numero del dado
        Pcx=Pcx+1;                              //Le suma 1 a la variable anterior para que su rango sea de 1 a 8
        return Pcx;                             //retorna el numero del dado
    }
}




//--------------------------------------------



//ALLEGRO

//Funci�n print_dado: Imprime en pantalla la imagen del dado correspondiente al jugaador.
//Par�metros(Numero de dado del jugador 1 y 2, turno)
void print_dado(int Pc1,int Pc2,int turno){

    int Pcx;                //Variable para almacenar el numero de dado con el cual trabajar

    if ((turno%2)==1){      //Si es turno del jugador 1, se trabaja con el dado del jugador 1
        Pcx = Pc1;
    }
    else if ((turno%2)==0){ //Si es turno del jugador 1, se trabaja con el dado del jugador 1
        Pcx = Pc2;
    }

    //Creaci�n de BITMAP's para futuras impresion del dado en pantalla, es decir,
    //accede las 8 imagenes de dados diferentes que puede sacar el jugador
    BITMAP *dado1 = load_bitmap("dado1.bmp",NULL);
    BITMAP *dado2 = load_bitmap("dado2.bmp",NULL);
    BITMAP *dado3 = load_bitmap("dado3.bmp",NULL);
    BITMAP *dado4 = load_bitmap("dado4.bmp",NULL);
    BITMAP *dado5 = load_bitmap("dado5.bmp",NULL);
    BITMAP *dado6 = load_bitmap("dado6.bmp",NULL);
    BITMAP *dado7 = load_bitmap("dado7.bmp",NULL);
    BITMAP *dado8 = load_bitmap("dado8.bmp",NULL);

    //Imprime el BITMAP correspondiente al numero del dado que saco el jugador actual
    switch(Pcx){

        case 1: blit(dado1,screen,0,0,273,444,72,72);
        break;

        case 2: blit(dado2,screen,0,0,273,444,72,72);
        break;

        case 3: blit(dado3,screen,0,0,273,444,72,72);
        break;

        case 4: blit(dado4,screen,0,0,273,444,72,72);
        break;

        case 5: blit(dado5,screen,0,0,273,444,72,72);
        break;

        case 6: blit(dado6,screen,0,0,273,444,72,72);
        break;

        case 7: blit(dado7,screen,0,0,273,444,72,72);
        break;

        case 8: blit(dado8,screen,0,0,273,444,72,72);
        break;
    }

}


//Funci�n print_table: Imprime en pantalla toda la parte grafica del juego.
//Par�metros(Posicion jugador 1 y 2, turno, apuntador a jugador 1 y 2, Numero de jugadas de jugador 1 y 2, Apuntador al tablero, Apuntador a las jugadas del jugador 1 y 2)
int print_table(int c1, int c2,int turno, CABALLERO *p_Gawain, CABALLERO *p_Dietrich,int jugadaG,int jugadaD, TABLERO *p_tablero, JUGADAS *p_jugadasG, JUGADAS *p_jugadasD){


    //Creacion de BITMAP's para la impresion de jugadores en pantalla,
    //es decir, accede las imagenes del jugador 1 y 2
    BITMAP *bmpG = load_bitmap("Gawain.bmp",NULL);
    BITMAP *bmpD = load_bitmap("Dietrich.bmp",NULL);

    //Limpia la pantalla
    rectfill(screen,0,429,200,530,pallete_color[16]);


    //IMPRESION DE AYUDAS EN PANTALLA PARA ENTENDIMIENTO DE DATOS
    textout(screen,font,"TURNO ",20,455,pallete_color[15]);
    textprintf(screen,font,80,455,palette_color[15],"%d",turno);
    textout(screen,font,"JUEGA ",20,430,pallete_color[15]);

    if ((turno%2)==0){          //Si es turno del jugador 1, imprime su nombre
    textout(screen,font," GAWAIN",60,430,pallete_color[6]);
    textout(screen,font,"JUGADAS REALIZADAS:",20,490,pallete_color[6]);
    }

    if ((turno%2)==1){          //Si es turno del jugador 2, imprime su nombre
    textout(screen,font," DIETRICH",60,430,pallete_color[3]);
    textout(screen,font,"JUGADAS REALIZADAS:",20,490,pallete_color[3]);
    }

    //------------------------------------------------------------------------------//
    //CREACION DEL TABLERO

    //Se crea un gran cuadrado y luego cuadros peque�os de otro color dejando entre
    //si espacios de 50 pixeles y si salir del cuadrado grande

    rectfill(screen,10,10,410,410,pallete_color[20]);

    rectfill(screen,10,10,60,60,pallete_color[12]);
    rectfill(screen,10,110,60,160,pallete_color[12]);
    rectfill(screen,10,210,60,260,pallete_color[12]);
    rectfill(screen,10,310,60,360,pallete_color[12]);

    rectfill(screen,60,60,110,110,pallete_color[12]);
    rectfill(screen,60,160,110,210,pallete_color[12]);
    rectfill(screen,60,260,110,310,pallete_color[12]);
    rectfill(screen,60,360,110,410,pallete_color[12]);

    rectfill(screen,110,10,160,60,pallete_color[12]);
    rectfill(screen,110,110,160,160,pallete_color[12]);
    rectfill(screen,110,210,160,260,pallete_color[12]);
    rectfill(screen,110,310,160,360,pallete_color[12]);

    rectfill(screen,160,60,210,110,pallete_color[12]);
    rectfill(screen,160,160,210,210,pallete_color[12]);
    rectfill(screen,160,260,210,310,pallete_color[12]);
    rectfill(screen,160,360,210,410,pallete_color[12]);

    rectfill(screen,210,10,260,60,pallete_color[12]);
    rectfill(screen,210,110,260,160,pallete_color[12]);
    rectfill(screen,210,210,260,260,pallete_color[12]);
    rectfill(screen,210,310,260,360,pallete_color[12]);

    rectfill(screen,260,60,310,110,pallete_color[12]);
    rectfill(screen,260,160,310,210,pallete_color[12]);
    rectfill(screen,260,260,310,310,pallete_color[12]);
    rectfill(screen,260,360,310,410,pallete_color[12]);

    rectfill(screen,310,10,360,60,pallete_color[12]);
    rectfill(screen,310,110,360,160,pallete_color[12]);
    rectfill(screen,310,210,360,260,pallete_color[12]);
    rectfill(screen,310,310,360,360,pallete_color[12]);

    rectfill(screen,360,60,410,110,pallete_color[12]);
    rectfill(screen,360,160,410,210,pallete_color[12]);
    rectfill(screen,360,260,410,310,pallete_color[12]);
    rectfill(screen,360,360,410,410,pallete_color[12]);
    //------------------------------------------------------------------------------//

    //ANALISIS DE DATOS PARA DETERMINAR POSICION DE JUGADORES EN PANTALLA

    //JUGADOR 1

    //Mediante la posicion actual del jugador se halla la cordenada en x que esta posicion representa en pantalla
    int x = (c1%8);
    if (x==0) x = 8;
    int z = c1;
    while((z%8)!=0){
        z=z+1;
    }

    //Mediante la posicion actual del jugador se halla la cordenada en y que esta posicion representa en pantalla
    int y = (z/8);
    int Gx = (50*x)-40;
    int Gy = (50*y)+10;



    //JUGADOR 2

    //Mediante la posicion actual del jugador se halla la cordenada en x que esta posicion representa en pantalla
    int t = (c2%8);
    if (t==0) t = 8;
    z = c2;
    while((z%8)!=0){
        z=z+1;
    }

    //Mediante la posicion actual del jugador se halla la cordenada en y que esta posicion representa en pantalla
    int r = (z/8);
    int Dx = (50*t)-40;
    int Dy = (50*r)+10;



    int i,PG,PD,aux;



    //Si es turno del jugador 1:
    if((turno%2)==1){
            blit(bmpD,screen,0,0,Dx,Dy-50,50,50);   //Imprime la imagen del jugador 2 segun las coordenadas obtenidas
            blit(bmpG,screen,0,0,Gx,Gy-50,50,50);   //Imprime la imagen del jugador 1 segun las coordenadas obtenidas

            for(i=0;i<jugadaG;i++){
                PD = ((p_jugadasD)->casillaDelTablero(i))->jugada;  //Halla el numero del dado del jugador actual

                aux = (20 + (i*15));    //Determina la posicion en el eje x para impresion del numerod el dado

                if (aux<211){               //Si esta dentro del limite para impresion y el numero del dado es un numero del 1 al 8:
                                            //Imprime el numero del dado en la posicion hallada
                    if ( PD>0 && PD<9){
                        textprintf(screen,font,(20 + (i*15)),500,palette_color[15],"%d, ",((p_jugadasD)->casillaDelTablero(i))->jugada);
                    }
                }
                else if (aux>211){          //Si esta fuera del limite para impresion y el numero del dado es un numero del 1 al 8:
                                            //Imprime el numero del dado en una nueva posicion que este dentro del limite teniendo en cuenta
                                            //la posicion hallada
                    if ( PD>0 && PD<9){
                        textprintf(screen,font,(20 + (i*15))-190,510,palette_color[15],"%d, ",((p_jugadasD)->casillaDelTablero(i))->jugada);
                    }
                }
            }
    }
    //Si es turno del jugador 2:
    if((turno%2)==0){
            blit(bmpG,screen,0,0,Gx,Gy-50,50,50);   //Imprime la imagen del jugador 1 segun las coordenadas obtenidas
            blit(bmpD,screen,0,0,Dx,Dy-50,50,50);   //Imprime la imagen del jugador 2 segun las coordenadas obtenidas

            for(i=0;i<jugadaD;i++){
                PG= ((p_jugadasG)->casillaDelTablero(i))->jugada;  //Halla el numero del dado del jugador actual

                aux = (20 + (i*15));    //Determina la posicion en el eje x para impresion del numerod el dado

                if (aux<211){               //Si esta dentro del limite para impresion y el numero del dado es un numero del 1 al 8:
                                            //Imprime el numero del dado en la posicion hallada
                    if ( PG>0 && PG<9 ){
                        textprintf(screen,font,(20 + (i*15)),500,palette_color[15],"%d, ",((p_jugadasG)->casillaDelTablero(i))->jugada);
                    }
                }
                else if (aux>211){          //Si esta fuera del limite para impresion y el numero del dado es un numero del 1 al 8:
                                            //Imprime el numero del dado en una nueva posicion que este dentro del limite teniendo en cuenta
                                            //la posicion hallada
                    if ( PG>0 && PG<9 ){
                        textprintf(screen,font,(20 + (i*15))-190,510,palette_color[15],"%d, ",((p_jugadasG)->casillaDelTablero(i))->jugada);
                    }
                }
            }
    }


    int j,k,l,Ix,Iy;
    i=0;


    //IMPRESION DE CASILLAS TACHADAS EN EL TABLERO
    //Este ciclo recorre el tablero casilla pos casilla
    for(;i<64;i++){
        if(((p_tablero)->casillaDelTablero(i))-> nombre == 'X'){    //Si en la casilla hay una X

            //Determina las coordenadas del las 4 esquinas de la casilla
            j = i%8;
            k=i;
            while((k%8)!=0){
                k=k+1;
            }
            l = (k/8);
            Ix = (50*j)-40;
            Iy = (50*l)+10;

            //Segun la comlumna en que este la casilla, ajusta las coordenadas e imprime un cuadrado con una x

            if (j!=0){
            line(screen,Ix+50,Iy,Ix+100,Iy-50,pallete_color[15]);
            line(screen,Ix+100,Iy,Ix+50,Iy-50,pallete_color[15]);
            rect(screen,Ix+50,Iy,Ix+100,Iy-50,pallete_color[15]);
            }
            else if (j==0){
            line(screen,Ix+50,Iy+50,Ix+100,Iy,pallete_color[15]);
            line(screen,Ix+100,Iy+50,Ix+50,Iy,pallete_color[15]);
            rect(screen,Ix+50,Iy+50,Ix+100,Iy,pallete_color[15]);
            }
        }
    }



    //Si el jugador 1 gano la partida, Muestra uun mensaje indicando que se debe avanzar
    if ( ((p_Gawain)->get_estado())==1){
            rectfill(screen,210,420,400,550,pallete_color[16]);
            textout(screen,font,"Presione la flecha arriba",210,450,pallete_color[15]);

        }
        //Si el jugador  gano la partida, Muestra uun mensaje indicando que se debe avanzar
        else if( ((p_Dietrich)->get_estado())==1){
            rectfill(screen,210,420,400,550,pallete_color[16]);
            textout(screen,font,"Presione la flecha arriba",210,450,pallete_color[15]);

        }

    //IMPRESION NOMBRE DE JUGADORES


    //Mediante las coordenadas obtenidas para la impresion de la imagen del jugador,
    //se imprime el nombre de cada uno de estos sobre su imagen
    textout(screen,font,"Gawain",Gx+2,Gy-12,pallete_color[15]);
    textout(screen,font,"D",Dx+0,Dy-12,pallete_color[15]);
    textout(screen,font,"i",Dx+7,Dy-12,pallete_color[15]);
    textout(screen,font,"e",Dx+12,Dy-12,pallete_color[15]);
    textout(screen,font,"t",Dx+18,Dy-12,pallete_color[15]);
    textout(screen,font,"r",Dx+25,Dy-12,pallete_color[15]);
    textout(screen,font,"i",Dx+31,Dy-12,pallete_color[15]);
    textout(screen,font,"c",Dx+36,Dy-12,pallete_color[15]);
    textout(screen,font,"h",Dx+42,Dy-12,pallete_color[15]);


    return 0;
}


void menu(){

    //Creacion de BITMAP's para la impresion de menu y cursor en pantalla,
    //es decir, accede las imagenes del menu y el cursor. Ademas, crea un
    //buffer sobre el screen para trabajar sobre este
    BITMAP *buffer = create_system_bitmap(420,531);
    BITMAP *fondo1 = load_bitmap("FONDO1.bmp",NULL);
    BITMAP *fondo2 = load_bitmap("FONDO2.bmp",NULL);
    BITMAP *fondo3 = load_bitmap("FONDO3.bmp",NULL);
    BITMAP *cursor = load_bitmap("cursor.bmp",NULL);

    bool salida=false;  //Nos indica si se elegio alguna obcion el el menu (true si se hizo y false si no)

    //Mientras no se seleccione ninguna opcion
    while (salida==false){

        //Si el mause esta dentro de las cordenadas de la opcion comenzar, imprime la imagen que tiene esta opcion exaltada
        if (mouse_x > 30 && mouse_x < 380 && mouse_y >315 && mouse_y < 375){
            blit(fondo2,buffer,0,0,0,0,420,531);
            if(mouse_b & 1){    //Si se da click mientras que el mause esta en dichas coordenadas, acaba el ciclo
                salida = true;
            }
        }

        //Si el mause esta dentro de las cordenadas de la opcion salir, imprime la imagen que tiene esta opcion exaltada
        else if (mouse_x > 107 && mouse_x < 293 && mouse_y > 418 && mouse_y < 465){
            blit(fondo3,buffer,0,0,0,0,420,531);
            if(mouse_b & 1){    //Si se da click mientras que el mause esta en dichas coordenadas,
                                //acaba el ciclo e indica que se quiere salir del juego
                out = 1;
                salida = true;
            }
        }
        //Si no se hace nada imprime la imagen base del menu
        else{
            blit(fondo1,buffer,0,0,0,0,420,600);
        }

    //Funciones para el control de la impresion del mause en pantalla
    masked_blit(cursor,buffer,0,0,mouse_x,mouse_y,13,22);
    blit(buffer,screen,0,0,0,0,420,531);

    }

    //Destruye el buffer ya que en el juego se trabaja sobre el screen
    destroy_bitmap(buffer);

}



//--------------------------------------------



//POSICION

//Funci�n posici�n: Determina la posible nueva posici�n
//Par�metros(Posici�n actual, Numero del dado)
int posicion(int cx,int Pcx){
    int x=0;//Variable para guardar la posible nueva posici�n


    //Aplica determinada suma a la posici�n actual y la almacena en la variable x.
    //La suma correspondiente est� dada por el n�mero del dado segun el valor que tendria en el vector tablero
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


    //Si la posible nueva posici�n es menor que 65 y mayor a 0 la retorna
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


//Funci�n validapos: Determina si la jugada que se va a hacer es valida
//Par�metros(Posici�n actual, N�mero del dado, Posible nueva posici�n)
int validapos(int cx,int Pcx,int x){

    bool valida=false;
    int z=cx;

    //valida: nos dice si el movimiento es o no es valido
    //z: Nos dice la fila en la que esta la posici�n actual


    //El siguiente ciclo toma la posici�n actual y convierte a z en el m�ltiplo de 8 que hay en la fila en la que se encuentra.
    while((z%8)!=0){
        z=z+1;
    }

    //Eval�a el n�mero del dado que saco el jugador y valida si esta jugada se
    //puede hacer si y solo si est� dentro de los siguientes intervalos:
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



//--------------------------------------------



//MOVIMIENTO NO VALIDO

//Funcion mov_inv: Cambia el numero del dado cuando la jugada no se puede hacer
//Parametros(Numero del dado)
int mov_inv(int Pcx){


    //Si el n�mero del dado que saco el jugador es menor a 9, le suma 1 al n�mero
    //del dado para luego repetir el ciclo de c�digo con el nuevo n�mero de dado
    if(Pcx<9){
        Pcx=Pcx+1;                      //
    }



    //Si el n�mero del dado que saco el jugador es 8, toma el n�mero del
    //dado como 1, para luego repetir el ciclo de c�digo con este nuevo numero
    if(Pcx==9){
        Pcx=1;
    }

    return Pcx;     //Devuelve el nuevo numero del dado
}



//--------------------------------------------



//INTERACCION CON EL USUARIO
//Funcion Pass: Uada para que el usuario avance en el juego
int pass(){

    //Crea una variable "tecla" y le asigna el valor de una tecla del teclado en codigo ASCII

    char tecla = readkey() >>8;
    cout<<endl;

    //El siguiente ciclo se repite mientras que la variable tecla sea diferente de la flecha arriba en ASCII (72)
    while((tecla!=KEY_UP) ){
        char tecla = readkey() >>8;
        if(tecla==KEY_UP){
            break;
        }
    }

    return 0;

 }




//--------------------------------------------



//----------------------------------JUEGO---------------------------------------------

int main() {

    init();     //Inicia la ejecucion de la interfaz grafica
    menu();     //Ejecuta el menu


    //Limpia la pantalla
    rectfill(screen,0,0,800,800,pallete_color[16]);


    //Si se eligio la opcion comenzar en el menu
    if (out==0){

        setlocale(LC_ALL, "");  //FUNCI�N PARA ESCRIBIR CON TILDES LAS IMPRESIONES EN PANTALLA
        srand(time(NULL));      //SEMILLA PARA GENERACI�ON DE NUMEROS ALEATORIOS

        //1. DECLARACION DE VARIABLES  Y VECTORES:

        int c1=0,c2=0,Pc1=0,Pc2=0,turno=0,x,i,Valida,contador,winner,jugadaG=0,jugadaD=0;
        bool win=false,flag=false;

        CABALLERO *p_Gawain;
        p_Gawain= new CABALLERO;
        if( p_Gawain == NULL )
        {
            exit(2);
        }


        CABALLERO *p_Dietrich;
        p_Dietrich = new CABALLERO;
        if( p_Dietrich == NULL )
        {
            exit(2);
        }


        JUGADAS *p_jugadasD;
        p_jugadasD= new JUGADAS;
        int j;
        for(j = 0; j < 32; j++ )
        {
	        (p_jugadasD)->posicion_lista(j);
        }


        JUGADAS *p_jugadasG;
        p_jugadasG= new JUGADAS;
        int r;
        for(r = 0; r < 32; r++ )
        {
	        (p_jugadasG)->posicion_lista(r);
        }


        TABLERO *p_tablero;
        p_tablero= new TABLERO;
        int m;
        for(m = 0; m < 64; m++ )
        {
	        (p_tablero)->posicion_lista(m);
        }




        //Variables:
        //c1: N�mero que da la posici�n actual del jugador 1 (GAWAIN).
        //c2: N�mero que da la posici�n actual del jugador 2 (DIETRICH).
        //Pc1: N�mero del 1 al 8 que el jugador 1 saca al tirar el dado (Juagada Gawain).
        //Pc2: N�mero del 1 al 8 que el jugador 2 saca al tirar el dado (Juagada Dietrich).
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
        //jugadasG: Almacena las jugadas del jugador 1 (Pc1) que se hacen y son v�lidas en el orden que se hacen.
        //jugadasD: Almacena las jugadas del jugador 2 (Pc2) que se hacen y son v�lidas en el orden que se hacen.
        //tablero: Almacena los datos del tablero que se ver�n en pantalla.




        //2. CONSTRUCCION DEL TABLERO:

        //Este ciclo toma el vector tablero y a cada espacio que tiene le asigna un car�cter ' '.
        for(i=0;i<64;i++){
            ((p_tablero)->casillaDelTablero(i)) -> nombre = ' ';
        }

        turno=turno+1;                         //Suma 1 a la variable turno
        c1=dado(c1,turno,Pc1);                  //toma un numero de1 1 al 64 mediante la funci�n dado() y la asigna al jugador 1
        ((p_tablero)->casillaDelTablero(c1-1)) -> nombre = 'G';
        (p_Gawain)->set_casilla(c1);



        //Primer turno del jugador 2
        turno=turno+1;                          //Suma 1 a la variable turno
        c2=dado(c2,turno,Pc2);                  //toma un numero de1 1 al 64 mediante la funci�n dado() y la asigna al jugador 1

        //Este siclo eval�a si el jugador 1 y el jugador 2 est�n en la misma posici�n y si es as� pone al jugador 2 en la posici�n del jugador 1 m�s uno
        if(c1==c2){
            c2++;
        }
        ((p_tablero)->casillaDelTablero(c2-1)) -> nombre = 'D';
        (p_Dietrich)->set_casilla(c2);

        //Imprime el tablero y un mensaje indicando como avanzar en el juego
        print_table(c1,c2,turno, p_Gawain,p_Dietrich,jugadaG,jugadaD, p_tablero, p_jugadasG, p_jugadasD);
        textout(screen,font,"Tire el dado o termine el",210,430,pallete_color[15]);
        textout(screen,font,"turno presionando la",210,440,pallete_color[15]);
        textout(screen,font,"flecha arriba",210,450,pallete_color[15]);
        textout(screen,font,"Presione la flecha arriba",210,480,pallete_color[15]);
        textout(screen,font,"para continuar",210,490,pallete_color[15]);
        pass();
        rectfill(screen,210,430,410,500,pallete_color[16]);
        textout(screen,font,"Tire el dado",210,430,pallete_color[15]);
        textout(screen,font,"DADO: ",210,450,pallete_color[15]);
        pass();

        //4. JUEGO
        while(win==false){                      // Este ciclo se repite hasta que uno de los dos jugadores gane y contiene lo que se hara durante el turno 3 hasta que un jugador se queda sin movimientos
            turno=turno+1;                      //Suma 1 a la variable turno
            contador=0;                         //Asigna el valor cero al contador de movimientos no validos


            //Para saber a que jugador le toca se hace la operaci�n turno modulo dos.
            //Luego si es 1 es porque turno es impar y por tanto le toca al jugador 1 y si es 0 es porque el n�mero es par y le toca al jugador 2
            switch(turno%2){


            //TURNO DEL JUGADOR 1
            case 1://Si turno modulo dos es uno, ejecuta el siguiente c�digo
                srand(time(NULL));
                Pc1=dado(c1,turno,Pc1);         //Adquiere un n�mero del 1 al 8 (Se lanza el dado)
                jugadaG++;
                while(flag==false){             //Ciclo que se repite hasta que el jugador termine su turno, ll�mese ciclo de turno
                    contador++;                     //Suma 1 al contador
                    if(contador>8){                 //Si el contador suma 8 errores ejecuta las siguientes tres l�neas
                        win=true;                       //Indica que alguien gano
                        flag=true;                      //termina el turno
                        (p_Dietrich)->winner();                //Indica que el jugador 2 gano
                    }
                    x=posicion(c1,Pc1);             //Haya la posible nueva posici�n del jugador 1
                    if(x<65){                       //Si la posible nueva posici�n es menor a 65 continua con el c�digo
                        Valida=validapos(c1,Pc1,x);     //Valida la nueva posible posici�n a ver si se puede hacer
                        if (Valida==1){                 //Si la posible nueva posici�n es v�lida continua con el c�digo
                            if(x!=c2){                      //Si la nueva posible posici�n es diferente al de la posici�n actual del jugador 2, continua con el c�digo
                                if(((p_tablero)->casillaDelTablero(x-1)) -> nombre == ' '){         //Si al evaluar la posible nueva posici�n en el vector tablero corresponde al car�cter ' ', continua con el c�digo
                                    ((p_tablero)->casillaDelTablero(c1-1))-> nombre = 'X';          //Toma la posici�n actual del jugador 1 en el vector tablero y le asigna el car�cter 'X'. Que en el tablero indicara que no se pueden mover a ese sitio
                                    c1=x;                                                           //Asigna el valor de la posible nueva posici�n a la posici�n actual
                                    ((p_tablero)->casillaDelTablero(c1-1)) -> nombre = 'G';
                                    (p_Gawain)->set_casilla(c1);                                    //Toma la nueva posici�n actual del jugador 1 en el vector tablero y le asigna el car�cter 'G'. Que en el tablero indica la posici�n de Gowin
                                    flag=true;                                                      //termina el turno
                                    ((p_jugadasG)->casillaDelTablero(jugadaG-1))->jugada =Pc1;      //Agrega al vector jugadas el n�mero de dado que saco el jugador 1 para moverse a la nueva posici�n
                                    textout(screen,font,"Termine el turno",210,430,pallete_color[15]);  //Imprime que acabe el turno
                                    textout(screen,font,"DADO: ",210,450,pallete_color[15]);
                                }
                                else{                           //Si al evaluar la posible nueva posici�n en el vector tablero NO corresponde al caracter ' ', vuelve a tirar el dado
                                    Pc1=mov_inv(Pc1);
                                }
                            }
                            else{                               //Si el jugador 1 cae en la posicion del jugador 2
                                ((p_tablero)->casillaDelTablero(c1-1)) -> nombre = 'X';              //Toma la posici�n actual del jugador 1 en el vector tablero y le asigna el car�cter 'X'. Que en el tablero indicara que no se pueden mover a ese sitio
                                c1=x;                                                                //Asigna el valor de laposible nueva posici�n a la posici�n actual
                                (p_Gawain)->set_casilla(c1);
                                ((p_tablero)->casillaDelTablero(c1-1)) -> nombre = 'G';              //Toma la nueva posici�n actual del jugador 1 en el vector tablero y le asigna el car�cter 'G'. Que en el tablero indica la posici�n de Gowin
                                flag=true;                                                           //termina el turno
                                ((p_jugadasG)->casillaDelTablero(jugadaG-1))->jugada = Pc1;          //Agrega al vector jugadas el n�mero de dado que saco el jugador 1 para moverse a la nueva posici�n
                                win=true;                                                            //Indica que alguien gano
                                (p_Gawain)->winner();                                                //Indica que el jugador 1 gano
                                textout(screen,font,"Termine el turno",210,430,pallete_color[15]);
                                textout(screen,font,"DADO: ",210,450,pallete_color[15]);
                            }
                        }
                        else{                           //Si la nueva posici�n no es valida, vuelve a tirar el dado
                            Pc1=mov_inv(Pc1);
                        }
                    }
                    else{                           //Si x es menor o igual a 64 vuelve a tirar el dado
                        Pc1=mov_inv(Pc1);
                    }
                }
                break;


            //TURNO DEL JUGADOR 2
            case 0://Si turno modulo dos es 0, ejecuta el siguiente c�digo
                srand(time(NULL));              //Adquiere un n�mero del 1 al 8 (Se lanza el dado)
                Pc2=dado(c2,turno,Pc2);         //Ciclo que se repite hasta que el jugador termine su turno, ll�mese ciclo de turno
                jugadaD++;
                while(flag==false){
                    contador++;                 //Suma 1 al contador
                    if(contador>8){            //Si el contador suma 8 errores ejecuta las siguientes tres l�neas
                        win=true;                   //Indica que alguien gano
                        flag=true;
                        (p_Gawain)->winner();
                        //(p_Gawain)->estado=1;                 //termina el turno
                        //winner=1;                   //Indica que el jugador 1 gano
                    }
                    x=posicion(c2,Pc2);         //Haya la posible nueva posici�n del jugador 1
                    if(x<65){                   //Si la posible nueva posici�n es menor a 65 continua con el c�digo
                        Valida=validapos(c2,Pc2,x); //Valida la nueva posible posici�n a ver si se puede hacer
                        if (Valida==1){                 //Si la posible nueva posici�n es v�lida continua con el c�digo
                            if(x!=c1){                      //Si la nueva posible posici�n es diferente al de la posici�n actual del jugador 1, continua con el c�digo
                                if(((p_tablero)->casillaDelTablero(x-1))-> nombre == ' '){          //Si al evaluar la posible nueva posici�n en el vector tablero corresponde al car�cter ' ', continua con el c�digo
                                    ((p_tablero)->casillaDelTablero(c2-1)) -> nombre = 'X';         //Toma la posici�n actual del jugador 2 en el vector tablero y le asigna el car�cter 'X'. Que en el tablero indicara que no se pueden mover a ese sitio
                                    c2=x;                                                           //Asigna el valor de la posible nueva posici�n a la posici�n actual
                                    (p_Dietrich)->set_casilla(c2);
                                    ((p_tablero)->casillaDelTablero(c2-1))-> nombre = 'D';
                                    flag=true;                      //termina el turno
                                    ((p_jugadasD)->casillaDelTablero(jugadaD-1))->jugada=Pc2;       //Agrega al vector jugadas el n�mero de dado que saco el jugador 2 para moverse a la nueva posici�n
                                    textout(screen,font,"Termine el turno",210,430,pallete_color[15]);
                                    textout(screen,font,"DADO: ",210,450,pallete_color[15]);
                                }
                                else{                           //Si al evaluar la posible nueva posici�n en el vector tablero NO corresponde al caracter ' ', vuelve a tirar el dado
                                    Pc2=mov_inv(Pc2);
                                }
                            }
                            else{                           //Si el jugador 2 cae en la posicion del jugador 1
                                ((p_tablero)->casillaDelTablero(c2-1))->nombre = 'X';       //Toma la posici�n actual del jugador 2 en el vector tablero y le asigna el car�cter 'X'. Que en el tablero indicara que no se pueden mover a ese sitio
                                c2=x;                                                       //Asigna el valor de la posible nueva posici�n a la posici�n actual
                                (p_Dietrich)->set_casilla(c2);
                                ((p_tablero)->casillaDelTablero(c2-1)) -> nombre = 'D';
                                flag=true;                                                   //termina el turno
                                ((p_jugadasD)->casillaDelTablero(jugadaD-1))->jugada = Pc2;  //Agrega al vector jugadas el n�mero de dado que saco el jugador 2 para moverse a la nueva posici�n
                                win=true;                                                    //Indica que alguien gano
                                (p_Dietrich)->winner();                                      //Indica que el jugador 2 gano
                                textout(screen,font,"Termine el turno",210,430,pallete_color[15]);
                                textout(screen,font,"DADO: ",210,450,pallete_color[15]);
                            }
                        }

                        else{                           //Si la nueva posici�n no es valida, vuelve a tirar el dado
                            Pc2=mov_inv(Pc2);
                        }
                    }
                    else{                           //Si x es menor o igual a 64 vuelve a tirar el dado
                        Pc2=mov_inv(Pc2);
                    }
                }
                break;
            }
            flag=false;                             //Asigna false a la variable flat para que el turno se pueda ejecutar correctamente el c�digo del siguiente jugador
            print_dado(Pc1,Pc2,turno);
            pass();

            //Imprime ell bloque de instrucciones del siguiente jugador luego de limpiar los datos del jugador actual
            rectfill(screen,210,410,410,530,pallete_color[16]);
            print_table(c1,c2,turno,p_Gawain,p_Dietrich,jugadaG,jugadaD, p_tablero, p_jugadasG, p_jugadasD);
            rectfill(screen,210,430,400,440,pallete_color[16]);
            textout(screen,font,"Tire el dado",210,430,pallete_color[15]);
            pass();
            }

        //Limpia los datos en pantalla
        print_table(c1,c2,turno,p_Gawain,p_Dietrich,jugadaG,jugadaD, p_tablero, p_jugadasG, p_jugadasG);
        rectfill(screen,210,410,410,500,pallete_color[16]);

        //Creacion de BITMAP's para la impresion de mensaje del ganador,
        //es decir, accede las imagenes de los mensajes de ganador
        BITMAP *winner1 = load_bitmap("winner1.bmp",NULL);
        BITMAP *winner2 = load_bitmap("winner2.bmp",NULL);

        //5. GANADOR:

        //Si gano el jugador 1, imprime un mensaje diciendo que gano
        if( ((p_Gawain)->get_estado())==1){
            rectfill(screen,423,0,800,550,pallete_color[16]);

            blit(winner1,screen,0,0,20,420,370,100);

        }
        //Si gano el jugador 2, imprime un mensaje diciendo que gano
        else if( ((p_Dietrich)->get_estado())==1){
            blit(winner2,screen,0,0,20,420,370,100);


        }

        pass(); //Funci�n que para el juego hasta que se oprima la flecha arriba

        deinit();   //Termina la ejecucion de la interfaz grafica
        return 0;
    }

    else{   //Si se eligio la opcion salir en el menu
        deinit();   //Termina la ejecucion de la interfaz grafica
        return 0;
    }

}
END_OF_MAIN();



//--------------------------------------------



//GRAFICOS

void init(){
    int depth, res;
    allegro_init();
    depth = desktop_color_depth();
    if (depth == 0) depth = 32;
    set_color_depth(depth);
    res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 420, 531 , 0, 0);
    if (res != 0) {
        allegro_message(allegro_error);
        exit(-1);
    }
    install_timer();
    install_mouse();
    install_keyboard();

}

void deinit(){
    clear_keybuf();
}
