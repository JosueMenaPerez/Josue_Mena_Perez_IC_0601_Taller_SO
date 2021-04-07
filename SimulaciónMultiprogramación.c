#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>

int main(){
    int a,i,j,sum,seg,ultprioridad,ultcont,ultentrada,k,l,x,y,tiempoT;
    
    //Cantidad de procesos a crear
    printf("Numero total de procesos: ");
    scanf("%i",&a);
    
    int prioridad[a], cont[a], entrada[a]; 
	int tiempo[a], ulttiempo;
	cont[0]=0;
	
	//Datos del proceso: asignacion del tiempo de ejecucion, prioridad y llegada al procesador 
    for(i=0; i<a; i++){
        printf("\n\nEstablecer tiempo en segundos de ejecucion del proceso %i: ",i+1);
        scanf("%i",&tiempo[i]);
        printf("\nPrioridad del proceso %i: ",i+1);
        scanf("%i",&prioridad[i]);
        if(i>0){
        	printf("\nSegundo de entrada del proceso %i: ",i+1);
        	scanf("%i",&entrada[i]);
    	}
    	else{
    		entrada[i]=0;
		}
        cont[i]=i+1;
    }
    
    printf("\n\n\t\t\tPROCESOS\n\n");
    printf("\nProceso \tTiempo rafaga \tPrioridad\tTiempo de llegada");
	for(i=0;i<a;i++){
		printf("\n%i  \t\t%iseg  \t\t%i  \t\t%iseg",cont[i],tiempo[i],prioridad[i],entrada[i]);
	}
    printf("\n\n");
    //Ordenamiento de los arreglos respecto a la llegada al procesador
    
    for(i=1;i<a;i++)
    {
    	for(j=i+1;j<a;j++){
    		x = entrada[i] - entrada[j];
        	if(x>0){
	            y = entrada[j];
	            entrada[j] = entrada[i];
	            entrada[i] = y;
	            
	            y=prioridad[j];
		        prioridad[j]=prioridad[i];
		        prioridad[i]=y;
		 
		        y=tiempo[j];
		        tiempo[j]=tiempo[i];
		        tiempo[i]=y;
		 
		        y=cont[j];
		        cont[j]=cont[i];
		        cont[i]=y;
        	}
		}
    }
    
    //Suma del tiempo total de los procesos
    sum=0;
    for(i=0;i<a;i++){
    	sum=tiempo[i];
    	tiempoT=tiempoT+sum;
    	
	}
	
	//Simulacion de la ejecucion de procesos
	for(i=0;i<a;i++){
	printf("\nComienzo de ejecucion del proceso %i \n",cont[i]);
	for (seg=0; seg<=tiempo[i]; seg++){
			Sleep(1000);
			
			//printf("\n %i " , seg); //Conteo de segundos
			
			//Decisiones para indicar la llegada de los procesos y si la prioridad es mayor
			if(i+1!=a){
			if(entrada[i+1]==seg && entrada[i+1]!=0){
				if(prioridad[i+1]<prioridad[i]){
					printf("\nProceso %i puesto en espera por la entrada del proceso %i con mayor prioridad.",cont[i],cont[i+1]);
					printf("\nComienzo de ejecucion del proceso %i \n",cont[i+1]);
					
					tiempo[i]=tiempo[i]-seg;
					entrada[i]=0;
				    
				    //Desplazamiento del arreglo si existe la llegada de un proceso con mayor prioridad
				    ultprioridad=prioridad[i];
					ultcont=cont[i];
					ultentrada=entrada[i];
					ulttiempo=tiempo[i];
					for(j=0;j<a;j++){
						cont[j]=cont[j+1];
						prioridad[j]=prioridad[j+1];
						tiempo[j]=tiempo[j+1];
						entrada[j]=entrada[j+1];
					}
					cont[a-1]=ultcont;
					prioridad[a-1]=ultprioridad;
					tiempo[a-1]=ulttiempo;
					entrada[a-1]=ultentrada;
					seg=0;
				}
				
			}
			}
			
			//Finalizar un proceso si se completa su tiempo de ejecución
			if(seg==tiempo[i]){
				printf("\nFinalizacion de la ejecucion del proceso %i \n",cont[i]);
			}
		}
	}
	
    return 0;
}
