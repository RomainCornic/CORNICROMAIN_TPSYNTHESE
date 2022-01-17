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
	char message_lu[100];
	ssize_t ret;
	while(1)
	{
		char console [10] ="enseash %";
		write(STDOUT_FILENO, console, strlen(console));
		ret = read(STDIN_FILENO, message_lu, 50);
		message_lu[ret-1]=0;
		if (ret > 0)
		{
			if(strcmp(message_lu,"fortune") == 0)
			{
				char message_fortune[100] = "Today is what happened to yesterday.\n";
				write(STDOUT_FILENO, message_fortune,strlen(message_fortune));
			}
			else if(strcmp(message_lu,"ls") == 0)
			{
				execlp("ls","ls",(char*)NULL);
			}
		}
		
		
	}

}


