#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Declaración de constantes.
#define TAM 50
#define TAM_PALABRAS 10000

//Declaración de estructuras para almacenar las palabras del archivo.
typedef struct DatoProximo{
  	char Cadena2[TAM];
  	struct DatoProximo *proximo;
}Datos;

typedef struct {
  char Cadena[TAM];
}Textos;

//Declaración de variables.
int i=0,j=0,k=0; //Variables para iteraciones.
Textos array_ordenado[TAM_PALABRAS]; //Arreglo para almacenar los valores ordenados.

int ArchivoExistente(char *nombreArchivo); //Función para comprobar la existencia del archivo.
int ArchivoConDatos(char *nombreArchivo); //FUnción para comprobar que el archivo tiene datos.
Datos *ListaDatos(Datos *DATOS); //Función de una lista enlazada.
Datos *Anadir(Datos *DATOS, char *Palabras); //Función para el ligado de la lista.
void Burbuja(Datos *DATOS); //Función para ordenar las palabras del archivo entrante y almacenarlas en
                            //un arreglo para mandarlas al archivo de salida.

int main(int argc, char *argv[]){
	FILE *ArcEntrada = NULL, *ArcSalida=NULL; // Creación de Files (estructuras).
	int ArcExiste = 0; //Comprobar si el archivo con el nombre del primer parámetro existe.
	char *archivo[TAM]; //Apuntador de tipo char con un tamaño de 50.
	Datos *PALABRAS = ListaDatos(PALABRAS); //Declaraciòn de apuntador a la lista enlazada.
	char temp[TAM]; //Arreglo para almacenar datos de los archivos de entrada y salida temporalmente. 
	*archivo = argv[1]; //Asignación a un apuntador del parámetro 1 (Nombre del archivo de entrada). 
	ArcExiste = ArchivoExistente(*archivo); //Asignación del valor retornado de la función ArchivoExistente. 

	//Estructura de decisión si existe o no el archivo e imprime un mensaje.
	printf("\n°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
	if(ArcExiste){
		printf("\tEl archivo [%s] existe.",*archivo);
	}else{
		printf("\tEl archivo [%s] no existe.",*archivo);
	}

	//Estructura de decisión si el archivo de entrada contiene datos.
	if(ArchivoConDatos(*archivo)){
		printf("\n\t\tEl archivo [%s] contiene datos.",*archivo);
		printf("\n\n\t\t>>>>>>>>>>>>>>>>>>>>  Leyendo Archivo  <<<<<<<<<<<<<<<<<<<<");
		ArcEntrada = fopen(argv[1],"r"); //Abrir el archivo de entrada (1er parámetro) para lectura.
		//Estructura de decisión si el archivo pudo abrirse.
		if(ArcEntrada == NULL){
			printf("\n\t\t\tEl archivo [%s] no se pudo abrir.", *archivo);
		}
		else{
			printf("\n\t\t\tArchivo [%s] abierto.", *archivo);
			while(!feof(ArcEntrada)){ //Permite saber si queda algún carácter por leer del archivo.
				fscanf(ArcEntrada, "%s", temp); //Funciona como un scanf.
				if(strcmp(temp,"")!=0){ //Estructura de decisión si el caráracter leído es diferente de vacío (espacio).
					PALABRAS = Anadir(PALABRAS,temp); //Asignación del valor retornado de la función Anadir.
				}
				memset(temp,0,50); //Copia el valor de 0 cincuenta veces en el arreglo temp.
			}
			rewind(ArcEntrada); //Coloca el indicador de posiciòn de fichero al comienzo del mismo.
			Burbuja(PALABRAS); //Invoca la función para ordenamiento con las palabras obtenidas.
			fclose(ArcEntrada); //Cierra el Archivo.
			printf("\n\t\t\t\tArchivo [%s] cerrado.", *archivo);
			printf("\n\t\t>>>>>>>>>>>>>>>>>>>  Lectura Terminada  <<<<<<<<<<<<<<<<<<<\n");
		}
	ArcSalida = fopen(argv[2],"w"); //Crea el archivo de salida (2do parámetro), si ya existe descarta el contenido actual. 
	printf("\n\t\t>>>>>>>>>>>>>>>>>>  Escritura iniciada  <<<<<<<<<<<<<<<<<<<");
	printf("\n\t\t\tArchivo [%s] abierto.",argv[2]);
	//Estructura de repetición para escribir las palabras ordenadas en el archivo de salida. 
  	for(i=0; i<=k; i++){
    		strcpy(temp,array_ordenado[i].Cadena); //Copia el valor del arreglo ordenado al arreglo temporal.
   		if(strcmp(temp,"") != 0){ //Estructura de decisión si el valor es diferente de vacío.
      			fprintf(ArcSalida,"%s\n",temp); //Escribe como texto en el archivo de salida.
    		}
  	}
	printf("\n\t\t\t\tArchivo [%s] cerrado.",argv[2]);
	printf("\n\t\t>>>>>>>>>>>>>>>>>>  Escritura terminada  <<<<<<<<<<<<<<<<<<");
  	fclose(ArcSalida); //Cierra el archivo de salida (2do parámetro).			
	}
	else{
		printf("\n\t\t\tEl archivo [%s]. Esta vacìo.",*archivo);
	}
	printf("\n\n°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
}

//Función para comprobar si esxite el archivo de entrada (1er parámetro) 
int ArchivoExistente(char *nombreArchivo){
	FILE *Archivo; //Creación de file (estructura).
	int existe = 0; //Variable para retornar si existe o no el archivo.
	Archivo = fopen(nombreArchivo, "r"); //Abre el archivo para lectura (r).
	if( Archivo != NULL ){ //Estructura de decisión si el archivo pudo abrirse.
		existe = 1; //Asigna 1 si el archivo existe.
		fclose(Archivo); //Cierra el archivo
	}	
	return existe; //Retorna el valor.
}

//Función para comprobar si el archivo contiene datos.
int ArchivoConDatos(char *nombreArchivo){
	int ExistenDatos = 0; //Variable para comprobar si el archivo contiene datos o no.
	FILE *Archivo; //Creación de FIle (estructura).
	int leer=0, cont=0; //
	Archivo = fopen(nombreArchivo,"r"); //Abrir archivo en solo lectura (r).
	//Estructura de decisión si se pudo abrir el archivo.
	if(Archivo == NULL){
		printf("\n\t\tEl archivo [%s] no pudo abrirse.",nombreArchivo);			
		ExistenDatos = 0; //Retorna cero si el archivo no logro abrirse.
	}
	else{
		fscanf(Archivo, "%d", &leer); //Leer si existen datos. Funciona como un scanf.
		while(!feof(Archivo)){ //Recorre el archivo mientras no sea el final del mismo.
			cont++; //Aumenta el conteo, salto del indicador de posición del archivo.
			fscanf(Archivo, "%d", &leer); //Leer si existen datos. Funciona como un scanf.
			//Si el conteo es mayor a cero entonces asigna uno a la variable para comprobar los datos.
			if(cont > 0){
				ExistenDatos = 1;
				break;
			}
		}
		fclose(Archivo); //Cierra el archivo
	}	
	return ExistenDatos; //Retorno de valor si existe o no.
}

//Función de la lista enlazada
Datos *ListaDatos(Datos *DATOS){
  	return DATOS=NULL; //Retorno de NULL.
};

//Funciòn para el ligado de la lista
Datos *Anadir(Datos *DATOS, char *Palabras){
  	Datos *aux1, *aux2; //Creación de apuntadores para almacenar datos sin riesgo de perdida.
  	aux1 = (Datos*)malloc(sizeof(Datos)); //Asignación de memoria en uso.
  	strcpy(aux1->Cadena2,Palabras); //Copia del dato al que el puntero apunta dentro de la estructura. 
  	aux1->proximo = NULL; //Apuntado a la variable proximo con valor null.
  	//Estructura de decisión si el apuntador es igual a NULL.
  	if(DATOS == NULL){
    		DATOS = aux1;
  	}else{
    		aux2 = DATOS;
		//Desplazamiento al último elemento de la lista enlazada.
    		while(aux2->proximo != NULL){
      			aux2 = aux2->proximo; //Asigna en aux2 el valor al que apunta en esa iteración.
    		}
    		aux2->proximo = aux1; //Asigna el valor de aux1 en el puntero al que apunta aux2.
  	}
	return DATOS; //Retorna el valor
};

//Función para ordenar el arreglo por método de burbuja.
void Burbuja(Datos *DATOS){
	char temporal[TAM]; //Variable para almacenar temporalmente los valos en los cambios de posición.
  	Textos array[TAM_PALABRAS]; //Arreglo para almacenar las palabras ordenadas.
	//Estructura de repetición para copiar la lista de palabras al arreglo donde se ordenarán.
  	while(DATOS->proximo != NULL){
    		strcpy(array[k].Cadena,DATOS->Cadena2); //Copia de los valores al arreglo a ordenar
    		DATOS = DATOS->proximo;
    		k++;
  	}
  	strcpy(array[k].Cadena,DATOS->Cadena2); //Copia del último elemeno de la lista.
  	//Estructura de repetición para ordenar el arreglo con método de burbuja de acuerdo a los valores en ASCII.
  	for(i=0; i<k; i++){
    		for(j=0; j<k; j++){
			//Estructura de decisión si el valor anterior es mayor o menor al siguiente. 
      			if(strcmp(array[j].Cadena,array[j+1].Cadena) > 0){
			//if(array[j].Cadena > array[j+1].Cadena){
				strcpy(temporal,array[j].Cadena);
				strcpy(array[j].Cadena,array[j+1].Cadena);
				strcpy(array[j+1].Cadena,temporal);
      			}
   		}
	}
	//Copia los valores ordenados al arreglo para escribirlos en el archivo de salida.
	for(i=0; i<=k; i++){
		strcpy(array_ordenado[i].Cadena,array[i].Cadena);
	}
};

