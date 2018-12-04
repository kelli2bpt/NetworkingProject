// Janelle Zorn

#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int palindrome (char string [])		//inputs a string and returns 1 if it is a palindrome. Else returns 0
{
	int length = strlen(string)-1;
	int i = 0, j = length, l = 0, ci, cj; //index i and j, character at i and j
	
	
	for (l=0; l <= length; l++ ) //loop through string
	{
		ci= string[i]; //pointer at beggining
		cj= string[j]; //pointer at end
		
		while (ispunct(ci) || isspace(ci))  //if punctuation or whitespace then skip over it
		{
			i++;
			length--; //Loop 1 less time. 
			ci= string[i]; //get character
		}
		while (ispunct(cj) || isspace(cj))  //if punctuation or whitespace then skip over it
		{
			j--;
			cj= string[j]; //get character
		}
		
		ci = tolower(ci); //turn both characters to lowercase
		cj = tolower(cj);
		
		printf("|%c|  |%c|\n",ci, cj);
		
		if (ci != cj)
			return(0); //if characters are not equal it is not a palindrome
		
		i++; //move indexs
		j--;

	}
	
	
	return(1); //it is a palindrome
}
























void interact(int);


int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno, clilen, pid;
    struct sockaddr_in serv_addr, cli_addr;
    
    if(argc < 2)
    {
		portno = 1200; //default port number
        //fprintf(stderr, "No port input.\n");
        //exit(1);
    }
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if(sockfd < 0)
    {
        fprintf(stderr, "Can't open socket.\n");
        exit(1);
    }
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
	if (argc > 1)
    portno = atoi(argv[1]); //if port number is supplied
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
    {
	fprintf(stderr, "Can't bind.\n");
        exit(1);
    }
    
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    
    while(1)
    {
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

        if(newsockfd < 0)
        {
            fprintf(stderr, "Couldn't accept.\n");
            exit(1);
        }
        
        pid = fork();
        if(pid != 0)
        {
            close(newsockfd);
        }
        else
        {
            close(sockfd);
            interact(newsockfd);
            exit(0);
        }
    }
    
return 0;
}

void interact(int socket)
{
    while(1)
    {
        int n;
        char buffer[256];
		char output[256];  //output string
		strcpy(output, "The string ");
        bzero(buffer, 256);
        n = read(socket, buffer, 255);
        if(n < 0)
        {
            fprintf(stderr, "Error reading from socket.\n");
            exit(1);
        }
        else
        {
			strcat(output,buffer);
			
			if (palindrome(buffer))
				//printf("The string \"%s\" is a palindrome\n",buffer);			
				strcat(output, " is a palindrome\n");
			else 
				//printf("The string \"%s\" is NOT a palindrome\n",buffer);
				strcat(output, " is NOT a palindrome\n");
			
			
			
			
			
			
			
            printf("Message: %s\n", buffer);
            n = write(socket, output ,255);  
        }
    }
}
