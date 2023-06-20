#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/wait.h>
#include "fbroker.h"


int main(int argc, char *argv[]){
	FILE *archivo_entrada = NULL, *archivo_salida = NULL;
	int n, c, b = 0;
	abrirArchivos(&archivo_entrada, &archivo_salida, argc, argv, &n, &c, &b);

    int fd[n][2];    
    for (int i = 0; i < n; i++) {
        pipe(fd[i]);
    }	
    
	// char *linea = NULL;
    // size_t tamanio = 0;
 	char *args[] = {NULL};
    for (int i = 0; i < n; i++) {
        pid_t pid = fork();
        
        if (pid == 0) {            
            close(fd[i][1]);
            dup2(fd[i][0], STDIN_FILENO);
            execv("./worker", args);            
        }
    }

    //padre
    for(int i = 0; i < n; i++){
        close(fd[i][0]);    

        char buffer1[100];
        sprintf(buffer1, "Mensaje del padre\n"); 
        write(fd[i][1], buffer1, strlen(buffer1));       
        
        // sleep(1);

        char buffer2[100];
        sprintf(buffer2, "FIN\n"); 
        write(fd[i][1], buffer2, strlen(buffer2));   
        
        close(fd[i][1]);
    }
    
    pid_t wpid;
    int status;
    // //Espera por los hijos
    while((wpid = wait(&status)) > 0);

   	//Codigo del padre
    printf("Todos los hijos han terminado\n");
    
	return 0;
}