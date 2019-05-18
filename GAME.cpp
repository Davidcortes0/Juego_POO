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
 int table(){
char tablero[64];
int count = 0;

for(int i=0;i<64;i++){
    tablero[i]=' ';
}
tablero[2]='*';
tablero[4]='+';
for(int e=0; e<8;e++){
    for(int k=0; k<17; k++){
        if(k==16){
            cout << '-'<<endl;
        }else{
            cout << '-';
        }
    }
    for(int j=0; j<8;j++){
        if(j==7){
            cout << '|' <<tablero[count]<<'|'<< endl;
        } else{
            cout << '|' <<tablero[count];
        }
        count++;
    }
}
return 0;
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
        cout<<"Oprima la flecha arriba"<<endl;
        Tecla = getch();
        if( Tecla == char(72) )
          break;
    }

    return 0; // ANSI C/C++
 }

//JUEGO
int main() {

int c1=0,c2=0,Pc1=0,Pc2=0,turno=0,x,i=1,j=1,n=0,Valida;
bool win=false,valida=true,flag=false;


cout<<"BIENVENDIO A BATALLA POR LA PRINCESA"<<endl;
cout<<endl<<"PARA AVANZAR EN EL JUEGO OPRIMA LA FLECHA ARRIBA"<<endl;
cout<<endl<<"A CONTINUACION LANCE EL DADO QUE DARA LA POSICION INCIAL DEL CABALLERO 1 EN EL TABLERO"<<endl;

pass();
turno=turno+1;
c1=dado(c1,turno,Pc1);
cout<<endl<<"LA POSICION DEL CABALLERO 1 ES "<<c1<<endl;

cout<<endl<<"AHORA LANCE EL DADO QUE DARA LA POSICION INCIAL DEL CABALLERO 2 EN EL TABLERO"<<endl;
pass();
turno=turno+1;
c2=dado(c2,turno,Pc2);
if(c1==c2){
    c2++;
}
cout<<endl<<"LA POSICION DEL CABALLERO 2 ES "<<c2<<endl;

cout<<endl<<"A PARTIR DE ESTE MOMENTO SE JUAGRA CON UN DADO DE OCHO CARAS QUE DICATARA LA SIGUENTE POSICION DEL JUGADOR SEGUN LOS MOVIMIENTOS DEL CABALLO EN EL AJEDREZ"<<endl;

do{//Juego
    turno=turno+1;



    switch(turno%2){

    case 1:
        cout<<endl<<"TURNO DEL CABALLERO 1"<<endl;
        srand(time(NULL));
        while(flag==false){
            pass();
            Pc1=dado(c1,turno,Pc1);
            x=posicion(c1,Pc1);
            if(x<65){
                Valida=validapos(c1,Pc1,x);
                if (Valida==1){
                    if(x!=c2){
                            c1=x;
                            flag=true;
                            cout<<"Se movio a "<<c1<<endl;
                            cout<<"Dado: "<<Pc1<<endl;
                        }
                    else{
                            if(Pc1<8){
                                cout<<"EL MOVIMIENTO NO ES POSIBLE"<<Pc1<<endl;
                                Pc1=Pc1+1;
                            }
                            if(Pc1==8){
                                Pc1=1;
                            }
                        }
                }
                else{
                    if(Pc1<8){
                        cout<<"EL MOVIMIENTO NO ES POSIBLE"<<Pc1<<endl;
                        Pc1=Pc1+1;
                    }
                    if(Pc1==8){
                        Pc1=1;
                    }
                }
            }
            else{
                if(Pc1<8){
                    cout<<"EL MOVIMIENTO NO ES POSIBLE"<<Pc1<<endl;
                    Pc1=Pc1+1;
                }
                if(Pc1==8){
                    Pc1=1;
                }
            }
        }
        flag=false;
        break;

    case 0:
        cout<<endl<<"TURNO DEL CABALLERO 2"<<endl;
        srand(time(NULL));
        while(flag==false){
            pass();
            Pc2=dado(c2,turno,Pc2);
            x=posicion(c2,Pc2);
            if(x<65){
                Valida=validapos(c2,Pc2,x);
                if (Valida==1){
                    if(x!=c1){
                        c2=x;
                        flag=true;
                        cout<<"Se movio a "<<c2<<endl;
                        cout<<"Dado: "<<Pc2<<endl;
                    }
                    else{
                        if(Pc2<8){
                        cout<<"EL MOVIMIENTO NO ES POSIBLE"<<Pc2<<endl;
                        Pc2=Pc2+1;
                        }
                        if(Pc2==8){
                            Pc2=1;
                        }
                    }
                }

                else{
                    if(Pc2<8){
                        cout<<"EL MOVIMIENTO NO ES POSIBLE"<<Pc2<<endl;
                        Pc2=Pc2+1;
                    }
                    if(Pc2==8){
                        Pc2=1;
                    }
                }
            }
            else{
                if(Pc2<8){
                    cout<<"EL MOVIMIENTO NO ES POSIBLE"<<Pc2<<endl;
                    Pc2=Pc2+1;
                }
                if(Pc2==8){
                    Pc2=1;
                }
            }
        }
        flag=false;
        break;
    }

//table();

}
while(win=true);

   return 0;
}

