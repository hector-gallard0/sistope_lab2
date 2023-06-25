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
    int fd2[n][2];

    printf("\n");

    for (int i = 0; i < n; i++) {
        pipe(fd[i]);        
        pipe(fd2[i]);
    }
    
 	char *args[] = {NULL};
    for (int i = 0; i < n; i++) {
        pid_t pid = fork();
        
        if (pid == 0) {                 
            close(fd[i][1]);        
            close(fd2[i][0]);

            dup2(fd[i][0], STDIN_FILENO);            
            dup2(fd2[i][1], STDOUT_FILENO);            
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

    ////Espera por los hijos (finalizan con el write de FIN)
    while((wpid = wait(&status)) > 0);    

    int total = 0, regulares = 0, no_regulares = 0; 
    char *mensajes_finales[n];
    for(int i = 0; i < n; i++){
        char buffer[256];        
        close(fd2[i][1]);
        while(read(fd2[i][0], buffer, sizeof(buffer)) > 0){
            // printf("%s", buffer);
            if(buffer[0] == 'W'){                
                mensajes_finales[i] = strdup(buffer);  // Copia el mensaje en un nuevo espacio de memoria                                
            }else{
                char es_regular[3];            
                int longitud = strlen(buffer);

                es_regular[0] = buffer[longitud - 3];
                es_regular[1] = buffer[longitud - 2];
                es_regular[2] = '\0';                        

                if(strcmp(es_regular, "SI") == 0){
                    regulares++;
                }else if(strcmp(es_regular, "NO") == 0){
                    no_regulares++;
                }            
                if(b == 1){
                    printf("%s", buffer);
                }            
                fprintf(archivo_salida, "%s", buffer);
                total++;            
            }            
        }                
        close(fd2[i][0]);
    }

    printf("\n");
    fprintf(archivo_salida, "\n");
    for(int i = 0; i < n; i++){       
        if(b == 1){
            printf("%s", mensajes_finales[i]);                
        }
        fprintf(archivo_salida, "%s", mensajes_finales[i]); 
        
    }    

    if(b == 1){        
        printf("\nTotal de expresiones que Si son regulares:%d\n", regulares);
        printf("Total de expresiones que No son regulares:%d\n", no_regulares);
        printf("Total de lineas leidas:%d\n\n", total);    
    }        
    fprintf(archivo_salida, "\nTotal de expresiones que Si son regulares:%d\n", regulares);
    fprintf(archivo_salida, "Total de expresiones que No son regulares:%d\n", no_regulares);
    fprintf(archivo_salida, "Total de lineas leidas:%d", total);
    
	return 0;
}