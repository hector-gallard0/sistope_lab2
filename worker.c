#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(){
	while (1) {
	    char line[256];
        if (fgets(line, sizeof(line), stdin) == NULL) {
            break; // Terminar el bucle si no se lee ninguna entrada
        }

        printf("%s", line);
        if (strcmp(line, "FIN\n") == 0) {
            break;
        }
	}
}