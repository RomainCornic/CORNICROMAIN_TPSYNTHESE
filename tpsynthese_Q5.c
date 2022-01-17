#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define BILLION 1000000000

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
	struct timespec start, stop;
    long accum;
	
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
			else if(strcmp(message_lu,"fortune") == 0)
			{
				char message_fortune[100] = "Today is what happened to yesterday.\n";
				write(STDOUT_FILENO, message_fortune,strlen(message_fortune));
			}
			else 
			{
				clock_gettime( CLOCK_MONOTONIC, &start);
				fpid=fork(); //creation d'un fils 
				if(fpid==0) //code du fils
				{ 
					execlp(message_lu,buffer,(char*)NULL); //mort du fils
				}
				else
				{
					wait(&status);
				}
				clock_gettime( CLOCK_MONOTONIC, &stop);
				accum=((stop.tv_nsec-start.tv_nsec)/1000000 +(stop.tv_sec-start.tv_sec)*1000) ;
				if(WIFEXITED(status)){
					sprintf(console,"enseash [exit:%d|%ldms]",WEXITSTATUS(status),accum);
					strcat(console, pourcent);
				}
				else if(WIFSIGNALED(status)){
					sprintf(console,"enseash [sign:%d|%ldms]",WTERMSIG(status),accum) ;
					strcat(console, pourcent);
				}
			}
		}

		write(STDOUT_FILENO, console, strlen(console));
	}
}
