
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

srand(time(NULL));

if(turno<3){
cx=(rand()%64)+1;
return cx;
}

if(turno>2){
Pcx=(rand()%8)+1;
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
int mismapos(int cx, int ck){//Devuelve bool

if (cx==ck){
    return true;
}
else{
    return false;
}
}

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

return x;
}

int validapos(int cx,int Pcx,int x){//Devuelve cx con su nueva posicion o si no es valido false

int statex=0,statey=0;
int resultx=cx%8;
double resulty=cx/8;



switch(Pcx){// Valida posicion en X

if(resultx==0){// Porque si resultx es un múltiplo de 8, resultx % 8 = 0 y result % 8 = 8
    resultx=8;
    }

case 1: resultx=resultx+1;
        if(1<=resultx<=8){
            statex=1;
        };break;

case 2: resultx=resultx+2;
        if(1<=resultx<=8){
            statex=1;
        };break;

case 3: resultx=resultx+2;
        if(1<=resultx<=8){
            statex=1;
        };break;

case 4: resultx=resultx+1;
        if(1<=resultx<=8){
            statex=1;
        };break;

case 5: resultx=resultx-1;
        if(1<=resultx<=8){
            statex=1;
        };break;

case 6: resultx=resultx-2;
        if(1<=resultx<=8){
            statex=1;
        };break;

case 7: resultx=resultx-2;
        if(1<=resultx<=8){
            statex=1;
        };break;

case 8: resultx=resultx-1;
        if(1<=resultx<=8){
            statex=1;
        };break;
}


switch(Pcx){// Valida posicion en Y

    case 1: if(0<(resulty)-2<=8){
                statey=1;
            }break;
    case 2: if(0<(resulty)-1<=8){
                statey=1;
            }break;
    case 3: if(0<(resulty)+1<=8){
                statey=1;
            }break;
    case 4: if(0<(resulty)+2<=8){
                statey=1;
            }break;
    case 5: if(0<(resulty)+2<=8){
                statey=1;
            }break;
    case 6: if(0<(resulty)+1<=8){
                statey=1;
            }break;
    case 7: if(0<(resulty)-1<=8){
                statey=1;
            }break;
    case 8: if(0<(resulty)-2<=8){
                statey=1;
            }break;
}

if(statex && statey){
    return 1;
    cout<<"yes"<<endl;
}
else{
    return 0;
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
        else{
            cout<<"Oprima la flecha arriba"<<endl;
        }
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
if(mismapos(c1,c2)==true){
    c2++;
}
cout<<endl<<"LA POSICION DEL CABALLERO 2 ES "<<c2<<endl;

cout<<endl<<"A PARTIR DE ESTE MOMENTO SE JUAGRA CON UN DADO DE OCHO CARAS QUE DICATARA LA SIGUENTE POSICION DEL JUGADOR SEGUN LOS MOVIMIENTOS DEL CABALLO EN EL AJEDREZ"<<endl;

do{//Juego
    turno=turno+1;



    switch(turno%2){

    case 1:
        cout<<endl<<"TURNO DEL CABALLERO 1"<<endl;

        while(flag==false){
            pass();
            Pc1=dado(c1,turno,Pc1);
            Valida=validapos(c1,Pc1,x);
            if (Valida==1){
                valida=mismapos(c1,c2);
                if (valida==false){
                    x=posicion(c1,Pc1);

                    c1=x;
                    flag=true;
                    cout<<"Se movio a "<<c1<<endl;
                    cout<<"MOVE: "<<Pc1<<endl;

                }
                else{
                    if(Pc1<8){
                        cout<<"EL MOVIMIENTO NO ES POSIBLE"<<endl;
                        Pc1=Pc1+1;
                    }
                    if(Pc1==8){
                        Pc1=1;
                    }
                }
            }

            else{
                 if(Pc1<8){
                    cout<<"EL MOVIMIENTO NO ES POSIBLE"<<endl;
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
        while(flag==false){
            pass();
            Pc2=dado(c2,turno,Pc2);
            Valida=validapos(c2,Pc2,x);
            if (Valida==1){
                valida=mismapos(c1,c2);
                if (valida==false){
                    x=posicion(c2,Pc2);
                    c2=x;
                    flag=true;
                    cout<<"Se movio a "<<c2<<endl;
                }
                else{
                    if(Pc2<8){
                        cout<<"EL MOVIMIENTO NO ES POSIBLE"<<endl;
                        Pc2=Pc2+1;
                    }
                    if(Pc2==8){
                        Pc2=1;
                    }
                }
            }

            else{
                if(Pc2<8){
                    cout<<"LEL MOVIMIENTO NO ES POSIBLE"<<endl;
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

table();

}
while(win=true);








    return 0;
}
