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
	

	int status;
	pid_t fpid;
	char message_lu[100];
	ssize_t ret;
	char pourcent[]=" %";
	char buffer[100];

	if (argc>2)
	{
		write(STDOUT_FILENO,"trop peu d'argument \n enseash %",strlen("trop peu d'argument"));
		sprintf(console,"usage de %s non valable",argv[0]);

	}
	write(STDOUT_FILENO, console, strlen(console));
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
			else if(strcmp(message_lu,"fortune") == 0)
			{
				char message_fortune[100] = "Today is what happened to yesterday.\n";
				write(STDOUT_FILENO, message_fortune,strlen(message_fortune));
			}
			else 
			{
				fpid=fork(); //creation d'un fils 
				if(fpid==0) //code du fils
				{ 
					execlp(message_lu,buffer,(char*)NULL); //mort du fils
				}
				else
				{
					wait(&status);
				}
				if(WIFEXITED(status))
				{
					sprintf(console,"enseash [exit:%d]",WEXITSTATUS(status));
					strcat(console, pourcent);
				}
				else if(WIFSIGNALED(status))
				{
					sprintf(console,"enseash [sign:%d]",WTERMSIG(status));
					strcat(console, pourcent);
				}	
			
			}
		}
		write(STDOUT_FILENO, console, strlen(console));
	}
}
