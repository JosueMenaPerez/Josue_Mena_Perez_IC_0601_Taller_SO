//Declaración de ficheros
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

#define TAM 100
#define Cliente2 struct sockaddr

int main(int argc, char *argv[]){

	int Cliente, puerto; //Variables para guardar el puerto y identificador del socket.
	long longitud; //Variable de tipo long.
	struct sockaddr_in Server; //Estructura tipo sockaddr. Almacena informaciòn del cliente.
	puerto = atoi(argv[1]); //Asignación del primer parametro.
	
	//Comprueba la creación del socket.
	Cliente = socket(AF_INET, SOCK_STREAM, 0);
	if (Cliente == -1) {
		printf("\n\t---------------------------------------------------\n");
		printf("\t\tNo se logro crear el socket\n");
		printf("\n\t---------------------------------------------------\n");
		exit(0);
	} else {
		printf("\n\t---------------------------------------------------\n");
		printf("\n\tSocket Creado\n");	
	}
	
	//Configuración de los datos del servidor.
	bzero(&Server, sizeof(Server)); //Función para rellenar con ceros.
	Server.sin_family = AF_INET; //Familia TCP/IP
	Server.sin_addr.s_addr = inet_addr("127.0.0.1"); //Asignación de dirección.
	Server.sin_port = htons(puerto); //Carga del puerto recibido como parametro.

	//Comprueba la conexión.
	if (connect(Cliente, (Cliente2*)&Server, sizeof(Server)) != 0) {
		printf("\n\tNo se pudo conectar al servidor.\n");
		printf("\n\t---------------------------------------------------\n");
		exit(0);
	} else {
		printf("\n\tSe ha logrado conectar al servidor\n");
	}
	//Lectura de datos.
	char *Valor1,*Valor2; //Variables para leer los numeros ingresados.
	printf("\n\t\tIngresar el primer valor: ");
	scanf("%s",&*Valor1);
	fflush(stdin); //Limpia la entrada del teclado.
	printf("\n\t\tIngresar el segundo valor: ");
	scanf("%s",&*Valor2);
	fflush(stdin); //Limpia la entrada del teclado.

	//Variables para almacenar los valores ingresados.
	char buffer[TAM], resultado[TAM], num1[strlen(Valor1)], num2[strlen(Valor2)];
	strcpy(num1, Valor1); //Copia el contenido de una variable a otra.
	strcpy(num2, Valor2); //Copia el contenido de una variable a otra.
	
	//COmpara cual dato es mas largo.
	if(strlen(num1) >= strlen(num2)){
		longitud = strlen(num1) + 1;
	} else {
		longitud = strlen(num2) + 1;
	}

	bzero(buffer,TAM); //Lleanar el buffer de ceros.
	strcpy(buffer,num1); //Copia el contenido de una variable a otra.
	write(Cliente,buffer,sizeof(buffer)); //Escribe en el fichero asociado.

	bzero(buffer,TAM); //Lleanar el buffer de ceros.
	strcpy(buffer,num2); //Copia el contenido de una variable a otra.
        write(Cliente,buffer, sizeof(buffer)); //Escribe en el fichero asociado.

	bzero(buffer,TAM); //Lleanar el buffer de ceros.
	read(Cliente,buffer,sizeof(buffer)); //Llamada al sistema read colocando los valores en buffer.
	strncpy(resultado,buffer,longitud); //Copia el contenido de una variable a otra.

	printf("\n\t\tResultado regresado por el servidor\n\n");
	printf("\n\t\t%s + %s\n", num1, num2);
	printf("\n\t\tResultado de la suma: %s\n",resultado);

	printf("\n\t---------------------------------------------------\n");
	close(Cliente);
return 0;
}
