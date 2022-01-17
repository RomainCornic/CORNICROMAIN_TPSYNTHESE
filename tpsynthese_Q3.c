#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	char console [50] ="enseash % ";
	char message_accueil[100] = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez \'exit\'.\n" ;
	write(STDOUT_FILENO, message_accueil,strlen(message_accueil));
	write(STDOUT_FILENO, console, strlen(console));
	

	char message_lu[100];
	ssize_t ret;

	if (argc>2)
	{
		write(STDOUT_FILENO,"trop peu d'argument \n enseash %",strlen("trop peu d'argument"));
		sprintf(console,"usage de %s non valable",argv[0]);

	}
	while(1)
	{
		ret = read(STDIN_FILENO, message_lu, 50);	
		message_lu[ret-1]=0;
		if (ret >= 0)
		{	
			if(strcmp(message_lu,"exit") == 0 || (ret == 0)) //ret=0 --> ctrl+d
			{
				char sortie [20] = "Au revoir !\n";
				write(STDOUT_FILENO, sortie, strlen(sortie));
				exit(EXIT_SUCCESS);
			}
		}
	write(STDOUT_FILENO, console, strlen(console));
	}
}