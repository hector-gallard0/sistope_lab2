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

    char linea[256];    
    int contador_lineas = 0, i = 0;
    while (1) {
        //Si llega al final, envía FIN para que los workers finalicen.
        if (fgets(linea, sizeof(linea), archivo_entrada) == NULL) {         
            for(int i = 0; i < n; i++){
                close(fd[i][0]);             
                char buffer2[5];
                sprintf(buffer2, "FIN\n");
                write(fd[i][1], buffer2, strlen(buffer2));
            }    
            //Terminar el bucle si no se lee ninguna entrada.
            break;
        }        

        //Para la última linea se agrega \n.
        if(linea[strlen(linea) - 1] != '\n'){
            strcat(linea, "\n");
        }

        //Se escriben la linea leida del archivo por el pipe para enviarlas a cada worker.
        if(contador_lineas < c){
            close(fd[i][0]);           
            write(fd[i][1], linea, strlen(linea));                                                               
        }else{
            i++;
            contador_lineas = 0;
            //si se pasa el último worker, se vuelve al inicial
            if(i == n){
                i = 0;
            }
            close(fd[i][0]);           
            write(fd[i][1], linea, strlen(linea));                                                               
        }
        contador_lineas++;        
    }
    
    pid_t wpid;
    int status;
    // //Espera por los hijos
    while((wpid = wait(&status)) > 0);

   	//Codigo del padre
    printf("Todos los hijos han terminado\n");
    
	return 0;
}