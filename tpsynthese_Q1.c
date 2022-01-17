#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{	
	char console [50] ="enseash % ";
	char message_accueil[100] = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez \'exit\'.\n" ;
	write(STDOUT_FILENO, message_accueil,strlen(message_accueil));
	if (argc>2){
		write(STDOUT_FILENO,"trop peu d'argument \n ",strlen("trop peu d'argument"));
		sprintf(console,"usage de %s non valable",argv[0]);

	}
	while(1)
	{
		char console [10] ="enseash %";
		write(STDOUT_FILENO, console, strlen(console));}

}