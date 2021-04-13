#include<stdio.h>
#include<stdbool.h>
#include<string.h>

#define TAM 30

int NumPaises,LLENO,Vacia,i,j,cont,cliente;
bool ocup=false, lleno=false, ok=false, ID=false;
double Abono;
char NPais[TAM];
char pais[50];

struct ALTA{
	char nombre[TAM];
	char sexo;
	double sueldo;
	int id;
	bool ocupado;
}ALTA[TAM];

struct Pais{
	char pais[20];
	int clientes;
	struct ALTA alta[TAM];
}Pais[TAM];


void instrucciones(){
    printf("\n\n-------------------------------");
    printf("---- Menu ----\n");
    printf(" A) Mostrar menu.\n");
    printf(" B) Dar de alta Cliente.\n");
    printf(" C) Dar de baja Cliente.\n");
    printf(" D) Mostrar todos los clientes.\n");
    printf(" E) Mostrar cliente en especifico.\n");
    printf(" F) Mostrar solo clientes dados de alta.\n");
    printf(" G) Abonar saldo a cliente.\n");
    printf(" H) Retirar saldo de cliente.\n");
    printf(" I) Buscar indice vacio en toda la estructura.\n");
    printf(" J) Mostrar si esta toda llena la estructura.\n");
    printf(" K) Mostrar si esta toda vacia la estructura.\n");
    printf(" L) Mostrar nombre de paises.\n");
    printf(" M) Mostrar longitudes.\n");
    printf(" N) Actualizar datos de cliente especifico.\n");
    printf(" S) Salir.\n");
    printf("-------------------------------\n");
}

PaisClientes(){
	for(i=0;i<NumPaises;i++){
		printf("\n\tDel pais  %s, existen %i clientes.\n ",Pais[i].pais,Pais[i].clientes);
	}
	printf("\n");
}

DarAlta(){
	printf("\n\t\tIntroduce el nombre del cliente: ");
	gets(Pais[i].alta[j].nombre);
	printf("\n\t\tIntroduce el sexo F/M: ");
	scanf("%c",&Pais[i].alta[j].sexo);
	printf("\n\t\tIntroduce el sueldo: ");
	scanf("%d",&Pais[i].alta[j].sueldo);
	Pais[i].alta[j].id=j;
	Pais[i].alta[j].ocupado=true;
}

DarBaja(cliente){
	if (cliente==Pais[i].alta[j].id){
	printf("\n\t\t\tCliente %s con el id %i fue dado de baja.\n",Pais[i].alta[j].nombre,Pais[i].alta[j].id);
	int k;
	int x = sizeof(Pais[i].alta[j].nombre)/sizeof(*Pais[i].alta[j].nombre);
	for(k=0;k<x;k++){
		Pais[i].alta[j].nombre[k]='\0';
	}
	Pais[i].alta[j].sexo=' ';
	Pais[i].alta[j].sueldo=0;
	Pais[i].alta[j].ocupado=false;
	}
}

void MostrarTodo(){
	for(i=0;i<NumPaises;i++){
		printf("\n\tDel pais %s",Pais[i].pais);
		for(j= 0; j< Pais[i].clientes; j++){
			printf("\n\t\tEl cliente %i es: ",Pais[i].alta[j].id);
			printf("\n\t\t\tNombre: %s \tSexo: %c \t Saldo: %d \tOcupado: %s\n",Pais[i].alta[j].nombre, 
			Pais[i].alta[j].sexo, Pais[i].alta[j].sueldo, Pais[i].alta[j].ocupado?"true":"false");
		}
	}
}

PaisEncontrado(ok){
	if(ok==false){
		printf("\n\t\tPais no encontrado.\n");
	}
}

ClienteEncontrado(ID){
	if(ID==false){
		printf("\n\t\tCliente no encontrado.\n");
		ID=true;
	}
}

void instrucciones_actualizar(){
    printf("\n\t\t---- Menu Actualizar ----\n");
    printf("\t\t 0 Mostrar menu.\n");
    printf("\t\t 1 Actualizar Nombre.\n");
    printf("\t\t 2 Actualizar Sexo.\n");
    printf("\t\t 3 Regresar a menu principal.\n");
    printf("\t\t-------------------------------");
}

Actualizar_nombre(){
	printf("\n\t\t\tIntroduce el nombre del cliente: ");
	gets(Pais[i].alta[j].nombre);
	printf("\n\t\t\tNombre del cliente [%i] del pais %s cambiado a %s.\n",Pais[i].alta[j].id, Pais[i].pais, Pais[i].alta[j].nombre);
}

Actualizar_sexo(){
	printf("\n\t\t\tIntroduce el sexo F/M: ");
	scanf("%c",&Pais[i].alta[j].sexo);
	printf("\n\t\t\tSexo del cliente [%i] del pais %s cambiado a %c.\n",Pais[i].alta[j].id, Pais[i].pais, Pais[i].alta[j].sexo);
}

int main(){
	//int i,j,cont;
	//char pais[50];
	printf("\nIntroduce el numero de paises: ");
	scanf("%i",&NumPaises);
	
	for(i = 0; i < NumPaises; i++){
		fflush(stdin);
		printf("\n\tNombre del pais %i: ",i);
		gets(Pais[i].pais);

		printf("\n\t\tNumero total de clientes del pais %i:",i);
		scanf("%i",&Pais[i].clientes);
		
		LLENO = LLENO + Pais[i].clientes;
		NPais[i]=i;
    }
	
	PaisClientes();
	
	for(i=0;i<NumPaises;i++){
		for(j=0;j<Pais[i].clientes;j++){
			Pais[i].alta[j].id=j;
		}
	}
	
	instrucciones();
	char op;
	printf("\nElige una opcion: ");
	scanf("%s",&op);
	while(op != 'S'){
		ok=false;
		ID=false;
		switch(op){
			case 'A':instrucciones();
				break;
			case 'B':printf("\n --- Opcion alta ---\n");
				printf("\n\tIntroduce el nombre del pais: ");
				fflush(stdin);
				gets(pais);
				for(i=0;i<NumPaises;i++){
					if(strcmp(pais,Pais[i].pais)==0){
						for(j=0;j<Pais[i].clientes;j++){
							if(Pais[i].alta[j].ocupado!=true){
								DarAlta();
								ok=true;
								break;
							}
						}
					}
				}
				PaisEncontrado(ok);
				break;
				
			case 'C':
				printf("\n --- Opcion baja ---");
				fflush(stdin);
				printf("\n\tIntroduce el nombre del pais: ");
				gets(pais);
				for(i=0;i<NumPaises;i++){
					if(strcmp(pais,Pais[i].pais)==0){
						printf("\n\t\tIntroduce el id del cliente: ");
						scanf("%i",&cliente);
						ok=true;
						for(j=0;j<Pais[i].clientes;j++){
							DarBaja(cliente);
							//ID=true;
						}
						ClienteEncontrado(ID);
					}
				}PaisEncontrado(ok);
				break;
			case 'D':
				printf("\n --- Opcion mostrar todo ---");
				MostrarTodo();
				break;
			case 'E':
				printf("\n --- Opcion mostrar especifico ---\n");
				fflush(stdin);
				printf("\n\tIntroduce el nombre del pais: ");
				gets(pais);
				cliente=0;
				for(i=0;i<NumPaises;i++){
					if(strcmp(pais,Pais[i].pais)==0){
						printf("\n\t\tIntroduce el id del cliente: ");
						scanf("%i",&cliente);
						ok=true;
						for(j=0;j<Pais[i].clientes;j++){
							if (cliente==Pais[i].alta[j].id){
							printf("\n\t\t\tEl cliente %i es: ",Pais[i].alta[j].id);
			            	printf("\n\t\t\t\tNombre: %s \tSexo: %c \t Saldo: %d \tOcupado: %s\n",Pais[i].alta[j].nombre, 
							Pais[i].alta[j].sexo, Pais[i].alta[j].sueldo, Pais[i].alta[j].ocupado?"true":"false");
							ID=true;
							}
						}ClienteEncontrado(ID);
					}
				}PaisEncontrado(ok);
				break;
			case 'F':
				printf("\n --- Opcion mostrar solo ocupados ---");
				fflush(stdin);
				cliente=0;
				for(i=0;i<NumPaises;i++){
					for(j=0;j<Pais[i].clientes;j++){
						if (true==Pais[i].alta[j].ocupado){
							printf("\t\nDel pais %s",Pais[i].pais);
							printf("\n\tEl cliente %i es: ",Pais[i].alta[j].id);
			            	printf("\n\t\tNombre: %s \tSexo: %c \t Saldo: %d \tOcupado: %s\n",Pais[i].alta[j].nombre, 
							Pais[i].alta[j].sexo, Pais[i].alta[j].sueldo, Pais[i].alta[j].ocupado?"true":"false");
						}
					}
				}
				break;
			case 'G':
				printf("\n\n --- Opcion abonar---\n");
				fflush(stdin);
				printf("\n\tIntroduce el nombre del pais: ");
				gets(pais);
				cliente=0;
				Abono=0;
				for(i=0;i<NumPaises;i++){
					if(strcmp(pais,Pais[i].pais)==0){
						printf("\n\t\tIntroduce el id del cliente: ");
						scanf("%i",&cliente);
						ok=true;
						for(j=0;j<Pais[i].clientes;j++){
							if (cliente==Pais[i].alta[j].id){
							printf("\n\t\t\tIngresa la cantidad que quieres abonar: ");
							scanf("%d",&Abono);
							Pais[i].alta[j].sueldo = Pais[i].alta[j].sueldo + Abono;
							ID=true;
							}
						}ClienteEncontrado(ID);
					}
				}PaisEncontrado(ok);
				break;
			case 'H':
				printf("\n\n --- Opcion retirar---\n");
				fflush(stdin);
				printf("\n\tIntroduce el nombre del pais: ");
				gets(pais);
				cliente=0;
				Abono=0;
				for(i=0;i<NumPaises;i++){
					if(strcmp(pais,Pais[i].pais)==0){
						printf("\n\t\tIntroduce el id del cliente: ");
						scanf("%i",&cliente);
						ok=true;
						for(j=0;j<Pais[i].clientes;j++){
							if (cliente==Pais[i].alta[j].id){
							printf("\n\t\t\tIngresa la cantidad que quieres retirar: ");
							scanf("%d",&Abono);
							ID=true;
							if(Abono<=Pais[i].alta[j].sueldo){
								Pais[i].alta[j].sueldo = Pais[i].alta[j].sueldo - Abono;
							}else{
								printf("\n\t\tImposible, el saldo es insuficiente para retirar %d. \n",Abono);
							}
							}
						}ClienteEncontrado(ID);
					}
				}PaisEncontrado(ok);
				break;
			case 'I':
				printf("\n\n --- Opcion buscar id vacio en toda estructura ---\n");
				for(i=0;i<NumPaises;i++){
					for(j=0;j<Pais[i].clientes;j++){
						if(false==Pais[i].alta[j].ocupado){
							printf("\n\tEl pais  %s tiene el cliente [%i] vacio.",Pais[i].pais,Pais[i].alta[j].id);
						}
					}
				}
				printf("\n");
				break;
			case 'J':
				cont=0;
				lleno=false;
				printf("\n --- Opcion esta llena toda la estructura ---\n");
				for(i=0;i<NumPaises;i++){
					for(j=0;j<Pais[i].clientes;j++){
						if(Pais[i].alta[j].ocupado==true){
							cont++;
						}
					}
					if(LLENO==cont){
						lleno=true;
					}
				}
				if(lleno==true){
					printf("\n\tLa estructura esta llena.\n");
				}else{
					printf("\n\tLa estructura no esta toda llena.\n");
				}
				break;
			case 'K':
				printf("\n --- Opcion esta vacia toda la estructura ---\n");
				cont=0;
				lleno=false;
				for(i=0;i<NumPaises;i++){
					for(j=0;j<Pais[i].clientes;j++){
						if(Pais[i].alta[j].ocupado==false){
							cont++;
						}
					}
					if(LLENO==cont){
						lleno=true;
					}
				}
				if(lleno==true){
					printf("\n\tLa estructura esta vacia.\n");
				}else{
					printf("\n\tLa estructura no esta toda vacia.\n");
				}
				break;
			case 'L':
				for(i=0;i<NumPaises;i++){
					printf("\n\tPais [%i] %s.",NPais[i],Pais[i].pais);
				}
				printf("\n");
				break;
			case 'M':
				PaisClientes();
				break;
			case 'N':
				printf("\n --- Opcion actualizar ---");
				fflush(stdin);
				printf("\n\tIntroduce el nombre del pais: ");
				gets(pais);
				cliente=0;
				for(i=0;i<NumPaises;i++){
					if(strcmp(pais,Pais[i].pais)==0){
						printf("\n\tIntroduce el id del cliente: ");
						scanf("%i",&cliente);
						for(j=0;j<Pais[i].clientes;j++){
							int option;
							if(cliente==Pais[i].alta[j].id){
								instrucciones_actualizar();
								printf("\n\t\tSeleccionar opcion: ");
								fflush(stdin);
								scanf("%i",&option);
								while(option !=3){
									switch(option){
										case 0:
											instrucciones_actualizar();
											break;
										case 1:
											fflush(stdin);
											Actualizar_nombre();
											break;
										case 2:
											fflush(stdin);
											Actualizar_sexo();
											break;
										case 3:
											break;
									}
									printf("\n\t\tSeleccionar opcion: ");
									scanf("%i",&option);
								}
							}
						}
					}
				}
				break;
			case 'S':
				break;
		}
		printf("\nElige una opcion: ");
		scanf("%s",&op);
	}
	
	
	
	
	return 0;
}

