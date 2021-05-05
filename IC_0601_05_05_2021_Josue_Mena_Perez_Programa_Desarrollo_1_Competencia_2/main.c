#include "scheduler.h"

//Funciones para crear los hilos (pthread)
void reproducir_musica(void);
void abrir_youtube(void);
void escribir_texto_word(void);
void descargar_archivo(void);
void subiendo_archivo(void);
void compilando_programa(void);
void ejecutando_programa(void);
void usando_terminal(void);

//Funciones para recibir y retornar un parametro de entrada de tipo void con el uso de punteros.
void *pthread_reproducir_musica(void *args);
void *pthread_abrir_youtube(void *args);
void *pthread_escribir_texto_word(void *args);
void *pthread_descargar_archivo(void *args);
void *pthread_subiendo_archivo(void *args);
void *pthread_compilando_programa(void *args);
void *pthread_ejecutando_programa(void *args);
void *pthread_usando_terminal(void *args);

int main(int argc, char const *argv[]){
	
	process *p1 = crear_Proceso(1, UN_SEGUNDO, "Proceso_1", reproducir_musica, ACTIVO); 		//<--
	process *p2 = crear_Proceso(1, DOS_SEGUNDOS, "Proceso_1", abrir_youtube, NO_ACTIVO);
	process *p3 = crear_Proceso(3, TRES_SEGUNDOS, "Proceso_2", escribir_texto_word, ACTIVO); 	//<--
	process *p4 = crear_Proceso(4, TRES_SEGUNDOS, "Proceso_3", descargar_archivo, ACTIVO);   	//<--
	process *p5 = crear_Proceso(3, TRES_SEGUNDOS, "Proceso_4", subiendo_archivo, ACTIVO);		
	process *p6 = crear_Proceso(4, TRES_SEGUNDOS, "Proceso_5", compilando_programa, NO_ACTIVO);
	process *p7 = crear_Proceso(0, TRES_SEGUNDOS, "Proceso_6", ejecutando_programa, ACTIVO);	//<--	
	process *p8 = crear_Proceso(2, CUATRO_SEGUNDOS, "Proceso_7", usando_terminal, ACTIVO);		//<--
	process *p9 = crear_Proceso(5, CUATRO_SEGUNDOS, "Proceso_8", usando_terminal, NO_ACTIVO);	//<--

	array_procesos *array = crear_ArrayProcesos();

	agregar_Proceso(array, *p1);
	agregar_Proceso(array, *p2);
	agregar_Proceso(array, *p3);
	agregar_Proceso(array, *p4);
	agregar_Proceso(array, *p5);
	agregar_Proceso(array, *p6);
	agregar_Proceso(array, *p7);
	agregar_Proceso(array, *p8);
	agregar_Proceso(array, *p9);

	ejecutar_Procesos(array);

	free(array);
	free(p1);
	free(p2);
	free(p3);
	free(p4);
	free(p5);
	free(p6);
	free(p7);
	free(p8);
	free(p9);

	pthread_exit(NULL); //Terminación del hilo
	return 0;
}


//Creación de los hilos
//pthread_create(Identificador, Especificaciòn de atributos, Función por ejecutar dentro del hilo, Argumento a pasar a la función)
void reproducir_musica(void){
	pthread_create(&Proceso1,NULL,pthread_reproducir_musica,NULL); //crear hilo con sus argumentos
	pthread_join(Proceso1,NULL); //Evita la muerte de los hilos al terminar el main.
}

void abrir_youtube(void){
	pthread_create(&Proceso2,NULL,pthread_abrir_youtube,NULL);
	pthread_join(Proceso2,NULL);
}

void escribir_texto_word(void){
	pthread_create(&Proceso3,NULL,pthread_escribir_texto_word,NULL);
	pthread_join(Proceso3,NULL);
}

void descargar_archivo(void){
	pthread_create(&Proceso4,NULL,pthread_descargar_archivo,NULL);
	pthread_join(Proceso4,NULL);
}

void subiendo_archivo(void){
	pthread_create(&Proceso5,NULL,pthread_subiendo_archivo,NULL);
	pthread_join(Proceso5,NULL);
}

void compilando_programa(void){
	pthread_create(&Proceso6,NULL,pthread_compilando_programa,NULL);
	pthread_join(Proceso6,NULL);
}

void ejecutando_programa(void){
	pthread_create(&Proceso7,NULL,pthread_ejecutando_programa,NULL);
	pthread_join(Proceso7,NULL);
}

void usando_terminal(void){
	pthread_create(&Proceso8,NULL,pthread_usando_terminal,NULL);
	pthread_join(Proceso8,NULL);
}


//Funciones para reecibir los argumentos de cada hilo, en este caso los parámetros son NULL. Imprimir la acción a realizar.
void *pthread_reproducir_musica(void *args){
	Accion = "Reproduciendo Música"; //Puntero con la acción que se realiza en el hilo.
	for(i = 0; i < strlen(Accion); i++){ //Estructura de repetición, si i es menor al tamaño de los carácteres del puntero.
		printf("%c",Accion[i]); //Imprime cada carácter de la variable definida en el apuntador.
	}
	printf("\n");
	return NULL; //Devolver el valor del puntero como NULL
}

void *pthread_abrir_youtube(void *args){
	Accion = "Usando Youtube";
	for(i = 0; i < strlen(Accion); i++){
		printf("%c",Accion[i]);
	}
	printf("\n");
	return NULL;
}

void *pthread_escribir_texto_word(void *args){
	Accion = "Escribiendo Texto en Word";
	for(i = 0; i < strlen(Accion); i++){
		printf("%c",Accion[i]);
	}
	printf("\n");
	return NULL;
}

void *pthread_descargar_archivo(void *args){
	Accion = "Descargando Archivo";
	for(i = 0 ; i < strlen(Accion); i++){
		printf("%c",Accion[i]);
	}
	printf("\n");
	return NULL;
}

void *pthread_subiendo_archivo(void *args){
	Accion = "Subiendo Archivo";
	for(i = 0; i < strlen(Accion); i++){
		printf("%c",Accion[i]);
	}
	printf("\n");
	return NULL;
}

void *pthread_compilando_programa(void *args){
	Accion = "Compilando programa";
	for(i = 0; i < strlen(Accion); i++){
		printf("%c",Accion[i]);
	}
	printf("\n");
	return NULL;
}

void *pthread_ejecutando_programa(void *args){
	Accion = "Ejecutando programa";
	for(i = 0; i < strlen(Accion); i++){
		printf("%c",Accion[i]);
	}
	printf("\n");
	return NULL;
}

void *pthread_usando_terminal(void *args){
	Accion = "Usando la terminal";
	for(i = 0; i < strlen(Accion); i++){
		printf("%c",Accion[i]);
	}
	printf("\n");
	return NULL;
}
