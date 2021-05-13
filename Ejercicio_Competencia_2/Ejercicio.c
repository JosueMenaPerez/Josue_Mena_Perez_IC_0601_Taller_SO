#include<stdio.h>

int main(){
//Ejercicio 1.
printf("\nPrimer ejercicio.\n");
int x,*p;
int y,*puntero;

x=10;
p = &x;

printf("\nContenido del puntero [P]: %i",*p);

*p = *p+1;
printf("\nContenido del puntero [P]: %i",*p);

*p = *p+2;
printf("\nContenido del puntero [P]: %i",*p);

y=20;
puntero = &y;
printf("\nContenido del puntero [Puntero]: %i",*puntero);


//Ejercicio 2

printf("\n\n\nSegundo ejercicio.\n");
int arrayInt[5];

for(int i=0;i<=sizeof(arrayInt);i++){
	arrayInt[i]=i;
}

int *punteroInt = arrayInt;
int *punteroIntDos = &arrayInt[0];

printf("\nPrimer elemento del array [arrayInt]: %i",arrayInt[0]);
printf("\nPrimer elemento del puntero [punteroInt]: %i",*punteroInt);
printf("\nPrimer elemento del puntero [punteroIntDos]: %i",*punteroIntDos);
printf("\nQuinto elemento del array [arrayInt]: %i",arrayInt[4]);
printf("\nQuinto elemento del puntero [punteroInt]: %i",*punteroInt+4);
printf("\nQuinto elemento del puntero [punteroIntDos]: %i",*punteroIntDos+4);

for(int i=0;i<5;i++){
	printf("\npuntero [punteroInt][%i]: %i",i,*punteroInt++);
}

for(int i=0;i<5;i++){
	printf("\npuntero [punteroIntDos][%i]: %i",i,*punteroIntDos++);
}

printf("\n\n");

return 0;
}
