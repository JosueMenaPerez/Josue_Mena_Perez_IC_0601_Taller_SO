//Declaraciòn de ficheros
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define TAM 500

int main(int argc, char *argv[]){
	int Leer; //Variable para guardar la la funciòn read.
	char buffer[TAM] = {0}; //VAriable que guardará los valores a sumar y el resultado.

//Comprueba si declaro el puerto como parametro.
if(argc >1){
	struct sockaddr_in servidor; //Estructura tipo sockaddr. Almacena informaciòn del servidor.
	struct sockaddr_in cliente; //Estructura tipo sockaddr. Almacena informaciòn del cliente.
	int Server, Client; //Declaración de variables para guardar el identificador del socket.
	int longCliente; //Declaración de variable para almacenar la longitud de la estructura. 
	int puerto = atoi(argv[1]); //Declaraciòn de variable para guardar el parametro 1.
	int addrlen = sizeof(servidor);

	//Configurar el servidor.
	servidor.sin_family = AF_INET; //Familia TCP/IP
	servidor.sin_addr.s_addr = INADDR_ANY; //Permitir la conexion de cualquier cliente.
	servidor.sin_port = htons(puerto); //Carga del puerto recibido como parametro.
	bzero(&(servidor.sin_zero),8); //Función para rellenar con ceros.

	//Definiendo el socket.
	//Apertura del socket, pasando el parametro "AF_INET" y de tipo "SOCK_STREAM" y con 0 elige el protocolo.
	if((Server=socket(AF_INET,SOCK_STREAM,0))<0){
		printf("\n\t---------------------------------------------------\n");
		printf("\tError en la apertura del socket. \n");
		printf("\n\t---------------------------------------------------\n");
		exit(-1); //Salir del programa.
	}else{
		printf("\t------------------------------------------------\n");
		printf("\tSocket abierto correctamente \n");
	}

	//Con bind se avisa al sistema la creación del socket
	//Se le indica que el socket se va unir a la estructura del servidor
	if(bind(Server,(struct sockaddr*)&servidor,sizeof(struct sockaddr))==-1){
		printf("\n\t\tError al asignar el socket a un puerto \n");
		printf("\n\t---------------------------------------------------\n");
		exit(-1);
	}else{
		printf("\n\t\tSocket asignado a un puerto\n");
	}

	//Se establece el socket en modo escucha
	if(listen(Server,5)==-1){
		printf("\n\t\t\tError al establecer el servidor en modo escucha.\n");
		printf("\n\t---------------------------------------------------\n");
		exit(-1);

	}else{
		printf("\n\t\t\tServidor establecido en modo escucha\n");
	}

	//Bucle para acceptar conexiones mientras sea 1.
	while(1){
	longCliente = sizeof(struct sockaddr_in); //Guarda el tamaño de la estructura.
	//LLamada a accept pasando el socket address, la estructura sockaddr, si hay error devuelve 0.
	if ((Client = accept(Server,(struct sockaddr *)&cliente,&longCliente))==-1){
		printf("\n\t\t\t\tError al aceptar la conexión.\n");
		printf("\n\t---------------------------------------------------\n");
		exit(-1);
	}else{
		printf("\n\t\t\t---------------------------------------------------\n");
		printf("\n\t\t\tLa conexión ha sido aceptada.\n");
	}

	//Declaración de variables.
	int ValorX[TAM], ValorY[TAM], ValorR[TAM]; //Arrays tipo entero para almacenar los dos valores a sumar y el resultado.
	char array1[TAM]; //Almacena los valores enviados por el cliente.
	char array2[TAM]; //Almacena los valores enviados por el cliente.
	int longitud1, longitud2; //Declaración de variables para guardar longitud de arrays.
	int i=0, j=0; //Variables para estructuras de repetición. 
	int acarreo=0,temporal=0; //Variables para intercambio de valores durante la suma y acarreos de una suma.
	
	bzero(buffer, TAM); //Llena de ceros el arreglo.
	Leer = read(Client,buffer,TAM); //Llamada al sistema read colocando los valores en buffer.
    	printf("\n\t\t\t\tValor 1: %s",buffer ); //Imprime el valor a sumar 
	strcpy(array1, buffer); //Copia el contenido de una variable a otra.
	
	bzero(buffer, TAM); //Llena de ceros el arreglo.
	Leer = read(Client,buffer,TAM); //Llamada al sistema read colocando los valores en buffer.
    	printf("\n\t\t\t\tValor 2: %s",buffer ); //Imprime el valor a sumar 
	strcpy(array2, buffer); //Copia el contenido de una variable a otra.
   
	longitud1 = strlen(array1); //Se asigna a la variable la longitud del Array1.
	longitud2 = strlen(array2); //Se asigna a la variable la longitud del Array2.

	//Comiezo del calculo de la suma.
	//Bucle para llenar los arrays. 
	while (i <= longitud1){
		ValorX[i] = array1[i] - '0';
		i++;
	}
	i = 0;
	while(i <= longitud2){
		ValorY[i] = array2[i] - '0';
		i++;
	}
	
	//Compara cual de los dos arreglos es más grande.
        temporal = 0;
	if (longitud1 < longitud2) {
        	acarreo = 0;
        	j = longitud1 - 1;
        	for (i = longitud2 - 1; i >= 0; i--){
                	temporal = ValorY[i] + ValorX[j] + acarreo;
                	if (temporal >= 10){
                        	acarreo = temporal/10;
                        	temporal = temporal%10;
                	} else {
                        	acarreo = 0;
                	}
                	j--;
                	ValorR[i] = temporal;
        	}
        	if (acarreo != 0){
                	ValorR[0] = ValorR[0]+(acarreo*10);
        	}

	} else {
        	temporal = 0;
        	acarreo = 0;
        	j = longitud2 - 1;
        	for (i = longitud1 - 1; i >= 0; i--){
                	temporal = ValorX[i] + ValorY[j] + acarreo ;
                	if (temporal >= 10){
                        	acarreo = temporal/10;
                        	temporal = temporal%10;
                	} else {
                        	acarreo = 0;
                	}
                	j--;
                	ValorR[i] = temporal;
        	}
        	if (acarreo != 0){
                	ValorR[0] = ValorR[0]+(acarreo*10);
        	}

	}
	bzero(buffer, TAM); //Llena de ceros el buffer.
	if (longitud1 < longitud2) {
        	i = 0;
	        j = 0;
        	if ((ValorR[i]) >= 10){
	                temporal = ValorR[i];
	                buffer[0] = (temporal/10) + '0';
	                buffer[1] = (temporal%10) + '0';
	                longitud2++;
	                i = i + 2;
	                j++;
        	}
	        while(i != longitud2){
	                buffer[i] = ValorR[j] + '0';
        	        i++;
	                j++;
        	}
	} else {
	        i = 0;
        	j = 0;
	        if ((ValorR[i]) >= 10){
        	        temporal = ValorR[i];
                	buffer[0] = (temporal/10) + '0';
	                buffer[1] = (temporal%10) + '0';
        	        longitud1++;
                	i = i + 2;
	                j++;
        	}
	        while(i != longitud1){
        	        buffer[i] = ValorR[j] + '0';
	                i++;
        	        j++;
	        }	
	}

	send(Client, buffer, strlen(buffer), 0); //Envía al cliente el resultado.
    	printf("\n\n\t\t\tResultado= %s\n", buffer); //Imprime el resultado de la suma.
    	printf("\n\t\t\t\tCliente desconectado.\n");
	printf("\n\t\t\t---------------------------------------------------\n");
	
	close(Client); //Cierra el socket del cliente.
	}
	close(Server); //Cierra el socket del servidor.
	}
	else{
		printf("\nIngresar el puerto como parametro.\n");
		printf("\n---------------------------------------------------\n");
	}
	return 0;
}



