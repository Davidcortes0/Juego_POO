#include <iostream>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
#include <ctime>
#include <cmath>

using namespace std;

//DADOS
int dado(int cx,int turno,int Pcx){

if(turno<3){
cx=rand()%64;
cx=cx+1;
return cx;
}

if(turno>2){
Pcx=rand()%8;
Pcx=Pcx+1;
return Pcx;
}
 }

//TABLERO
int table(char* tablero){

int i=1,j=1,k=0;

for(i=1;i<9;i++){
    for(j=1;j<9;j++){
        cout<<'['<<tablero[k]<<']';
        k++;
    }
    cout<<endl;
}
}

//POSICION
int posicion(int cx,int Pcx){//Devuelve valor de la nueva posicion en el tablero

int x=0;


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

if(x<64){
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

int validapos(int cx,int Pcx,int x){//Devuelve cx con su nueva posicion o si no es valido false

bool valida;
int z=cx;
while((z%8)!=0){
    z=z+1;
}

valida=false;
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

if (valida==false){
    return 0;
}
else{
    return 1;
}

}

 //INTERACCION CON EL USUARIO
 int pass(){
    char Tecla=0;
    cout<<endl;
    Tecla = char(0);
    while( Tecla != char(72) ){
        Tecla = getch();
        if( Tecla == char(72) )
          break;

    }

    return 0; // ANSI C/C++
 }

//JUEGO
int main() {

int c1=0,c2=0,Pc1=0,Pc2=0,turno=0,x,i=1,j=1,n=0,Valida,contador,winner;
bool win=false,valida=true,flag=false;

int jugadas[64];

char tablero[64];
for(int i=0;i<64;i++){
    tablero[i]=' ';
}

cout<<"BIENVENDIO A BATALLA POR LA PRINCESA"<<endl;
cout<<endl<<"PARA AVANZAR EN EL JUEGO OPRIMA LA FLECHA ARRIBA"<<endl;
cout<<"CUANDO UN MOVIMIENTO NO SEA POSIBLE SE LE AVISARA JUNTO CON EL NUMERO DEL DADO QUE SACO"<<endl<<endl<<endl;
cout<<endl<<"A CONTINUACION LANCE EL DADO QUE DARA LA POSICION INCIAL DEL CABALLERO 1 EN EL TABLERO"<<endl;

pass();
turno=turno+1;
c1=dado(c1,turno,Pc1);
cout<<"LA POSICION DEL CABALLERO 1 ES "<<c1<<endl<<endl<<endl;
tablero[c1-1]='G';
table(tablero);

cout<<endl<<"AHORA LANCE EL DADO QUE DARA LA POSICION INCIAL DEL CABALLERO 2 EN EL TABLERO"<<endl;
pass();
turno=turno+1;
c2=dado(c2,turno,Pc2);
if(c1==c2){
    c2++;
}
cout<<"LA POSICION DEL CABALLERO 2 ES "<<c2<<endl<<endl<<endl<<endl<<endl;
tablero[c2-1]='D';
table(tablero);


cout<<endl<<"A PARTIR DE ESTE MOMENTO SE JUGARA CON UN DADO DE OCHO CARAS QUE DICTARA LA SIGUENTE POSICION DEL JUGADOR SEGUN LOS MOVIMIENTOS DEL CABALLO EN EL AJEDREZ"<<endl<<endl<<endl;
pass();



while(win==false){//Juego
    turno=turno+1;
    cout<<endl;
    contador=0;
    cout<<endl<<endl<<endl<<"Turno: "<<turno<<endl;
    switch(turno%2){

    case 1:
        cout<<endl<<"TURNO DEL CABALLERO GAWAIN"<<endl;
        srand(time(NULL));
        Pc1=dado(c1,turno,Pc1);
        while(flag==false){
            pass();
            contador++;
            if(contador==9){
                win=true;
                flag=true;
                winner=1;
            }
            x=posicion(c1,Pc1);
            if(x<65){
                Valida=validapos(c1,Pc1,x);
                if (Valida==1){
                    if(x!=c2){
                        if(tablero[x-1]==' '){
                            tablero[c1-1]='X';
                            c1=x;
                            tablero[c1-1]='G';
                            flag=true;
                            jugadas[turno-1]=Pc1;
                            cout<<"Se movio a "<<c1<<endl;
                            cout<<"Dado: "<<Pc1<<endl;
                        }
                        else{
                            if(Pc1<9){
                                cout<<"EL MOVIMIENTO NO ES POSIBLE: "<<Pc1<<endl;
                                Pc1=Pc1+1;
                            }
                            if(Pc1==9){
                                Pc1=1;
                            }
                        }
                    }
                    else{
                        if(Pc1<9){
                            cout<<"EL MOVIMIENTO NO ES POSIBLE: "<<Pc1<<endl;
                            Pc1=Pc1+1;
                        }
                        if(Pc1==9){
                            Pc1=1;
                        }
                    }
                }
                else{
                    if(Pc1<9){
                        cout<<"EL MOVIMIENTO NO ES POSIBLE: "<<Pc1<<endl;
                        Pc1=Pc1+1;
                    }
                    if(Pc1==9){
                        Pc1=1;
                    }
                }
            }
            else{
                if(Pc1<9){
                    cout<<"EL MOVIMIENTO NO ES POSIBLE: "<<Pc1<<endl;
                    Pc1=Pc1+1;
                }
                if(Pc1==9){
                    Pc1=1;
                }
            }
        }
        flag=false;
        break;

    case 0:
        cout<<endl<<"TURNO DEL DIETRICH"<<endl;
        srand(time(NULL));
        Pc2=dado(c2,turno,Pc2);
        while(flag==false){
            pass();
            contador++;
            if(contador==9){
                win=true;
                flag=true;
                winner=2;
            }
            x=posicion(c2,Pc2);
            if(x<65){
                Valida=validapos(c2,Pc2,x);
                if (Valida==1){
                    if(x!=c1){
                        if(tablero[x-1]==' '){
                            tablero[c2-1]='X';
                            c2=x;
                            tablero[c2-1]='D';
                            flag=true;
                            jugadas[turno-1]=Pc2;
                            cout<<"Se movio a "<<c2<<endl;
                            cout<<"Dado: "<<Pc2<<endl;
                        }
                        else{
                            if(Pc2<9){
                                cout<<"EL MOVIMIENTO NO ES POSIBLE: "<<Pc2<<endl;
                                Pc2=Pc2+1;
                            }
                            if(Pc2==9){
                                Pc2=1;
                            }
                        }
                    }
                    else{
                        if(Pc2<9){
                            cout<<"EL MOVIMIENTO NO ES POSIBLE: "<<Pc2<<endl;
                            Pc2=Pc2+1;
                        }
                        if(Pc2==9){
                            Pc2=1;
                        }
                    }
                }

                else{
                    if(Pc2<9){
                        cout<<"EL MOVIMIENTO NO ES POSIBLE: "<<Pc2<<endl;
                        Pc2=Pc2+1;
                    }
                    if(Pc2==9){
                        Pc2=1;
                    }
                }
            }
            else{
                if(Pc2<9){
                    cout<<"EL MOVIMIENTO NO ES POSIBLE: "<<Pc2<<endl;
                    Pc2=Pc2+1;
                }
                if(Pc2==9){
                    Pc2=1;
                }
            }
        }
        flag=false;
        break;
    }

table(tablero);
cout<<"Juagadas: ";
    for(i=2;i<turno;i++){
        if (jugadas[i]<9){
            cout<<jugadas[i]<<", ";
        }
    }
    cout<<endl;


}
cout<<endl<<endl<<endl;
if (winner==2){
    cout<<endl<<endl<<"DIETRICH HA PERDIDO"<<endl<<"GAWAIN HA GANADO EL AMOR DE LA PRINCESA"<<endl;
}
if (winner==1){
    cout<<endl<<endl<<"GAWAIN HA PERDIDO"<<endl<<"DIETRICH HA GANADO EL AMOR DE LA PRINCESA"<<endl;
}
pass();
   return 0;
}

