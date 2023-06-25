#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "fworker.h"

int main(){
	LinkedList* resultados = createLinkedList();

	while (1) {
	    char linea[256];
	    int estado = 1;

        if (fgets(linea, sizeof(linea), stdin) == NULL) {
            break; // Terminar el bucle si no se lee ninguna entrada
        }

        if (strcmp(linea, "FIN\n") == 0) {  	        
            break;
        }
        
        char caracter;
        for (int i = 0; linea[i] != '\0'; i++) {
            caracter = linea[i];
            reconocedor(&estado, caracter);            
        }        

        

       	char resultado[256] = "";
       	strcat(resultado, linea);    
       	resultado[strlen(resultado) - 1] = '\0';
       	if(estado == 4){
       		strcat(resultado, " SI\n");       
       	}else{
       		strcat(resultado, " NO\n");
       	}

        append(resultados, resultado);        
	}	

	// printf("%d\n", getpid());
	// printf("----------------------------------------------------------\n");
	if(resultados->size > 0){	
		for(int i = 0; i < resultados->size; i++){			
			char buffer[256];
			sprintf(buffer, "%s", get(resultados, i)); 
			write(STDOUT_FILENO, buffer, sizeof(buffer));			
		}	
	}

	char buffer[256];
	sprintf(buffer, "Worker %d ha procesado %d lineas.\n", getpid(), resultados->size);
	// printf("%d\n", getpid());
	write(STDOUT_FILENO, buffer, sizeof(buffer));			

	freeLinkedList(resultados);
	return 0;
}